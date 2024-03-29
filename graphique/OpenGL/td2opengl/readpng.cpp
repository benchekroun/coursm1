/*
 *  readpng.cpp
 *  bras
 *
 *  Created by Emmanuel Melin on 24/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdlib.h>

#include "readpng.h"


struct gl_texture_t *ReadPNGFromFile (const char *filename) 
{
	
	FILE *fp;
	png_byte magic[8];
	
	/* Open image file */
	fp = fopen (filename, "rb");
	if (!fp) {
		fprintf (stderr, "error: couldn't open \"%s\"!\n", filename);
		return NULL;
	}
	
	/* Read magic number */
	fread (magic, 1, sizeof (magic), fp);
	
	/* Check for valid magic number */
	if (!png_check_sig (magic, sizeof (magic))) {
		fprintf (stderr, "error: \"%s\" is not a valid PNG image!\n",filename);
		fclose (fp);
		return NULL;
	}
	
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		fclose (fp);
		return NULL;
	}
	
	/* Create a png info struct */
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		fclose (fp);
		png_destroy_read_struct (&png_ptr, NULL, NULL);
		return NULL;
	}
	
	/* Create our OpenGL texture object */
	struct gl_texture_t *texinfo = (struct gl_texture_t *) malloc (sizeof (struct gl_texture_t));
	
	/* Initialize the setjmp for returning properly after a libpng
     error occured */
	if (setjmp (png_jmpbuf(png_ptr))) {
		fclose (fp);
		png_destroy_read_struct (&png_ptr, &info_ptr, NULL);
		
		if (texinfo) {
			if (texinfo->texels)
				free (texinfo->texels);      
			free (texinfo);
		}    
		return NULL;
	}
	
	/* Setup libpng for using standard C fread() function
     with our FILE pointer */
	png_init_io (png_ptr, fp);
	
	/* Tell libpng that we have already read the magic number */
	png_set_sig_bytes (png_ptr, sizeof (magic));
	
	/* Read png info */
	png_read_info (png_ptr, info_ptr);
	
	int bit_depth, color_type;
	
	/* Get some usefull information from header */
	bit_depth = png_get_bit_depth (png_ptr, info_ptr);
	color_type = png_get_color_type (png_ptr, info_ptr);
	
	/* Convert index color images to RGB images */
	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb (png_ptr);
	
	/* Convert 1-2-4 bits grayscale images to 8 bits
     grayscale. */
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_gray_1_2_4_to_8 (png_ptr);
	
	if (png_get_valid (png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha (png_ptr);
	if (bit_depth == 16)
		png_set_strip_16 (png_ptr);
	else if (bit_depth < 8)
		png_set_packing (png_ptr);
	
	/* Update info structure to apply transformations */
	png_read_update_info (png_ptr, info_ptr);
	
	/* Retrieve updated information */
	png_uint_32 w, h;
	
	png_get_IHDR (png_ptr, info_ptr, &w, &h, &bit_depth,&color_type, NULL, NULL, NULL);
	texinfo->width = w;
	texinfo->height = h;
	switch (color_type) {
		case PNG_COLOR_TYPE_GRAY:
			texinfo->format = GL_LUMINANCE;
			texinfo->internalFormat = 1;
			break;
			
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			texinfo->format = GL_LUMINANCE_ALPHA;
			texinfo->internalFormat = 2;
			break;
			
		case PNG_COLOR_TYPE_RGB:
			texinfo->format = GL_RGB;
			texinfo->internalFormat = 3;
			break;
			
		case PNG_COLOR_TYPE_RGB_ALPHA:
			texinfo->format = GL_RGBA;
			texinfo->internalFormat = 4;
			break;
			
		default:
			/* Badness */
			break;
	}
	/* We can now allocate memory for storing pixel data */
	texinfo->texels = (GLubyte *)malloc (sizeof (GLubyte)*texinfo->width*texinfo->height*texinfo->internalFormat);
	
	png_bytep *row_pointers;
	
	/* Setup a pointer array.  Each one points at the begening of a row. */
	row_pointers = (png_bytep *)malloc (sizeof (png_bytep) * texinfo->height);
	
	for (int i = 0; i < texinfo->height; ++i) 
		row_pointers[i] = (png_bytep)(texinfo->texels + ((texinfo->height - (i + 1)) * texinfo->width * texinfo->internalFormat));
	
	/* Read pixel data using row pointers */
	png_read_image(png_ptr, row_pointers);
	
	/* We don't need row pointers anymore */
	free (row_pointers);
	
	return(texinfo);
	
}