img = imread('lena.jpg');
imdb = im2double(img);
imwrite(imdb,'lena.bmp');
img2 = imread('FibroblastCellNucleus.jpg');
imggray = rgb2gray(img2);
imgdbgray = im2double(imggray);
imgdi = histeq(imgdbgray,200);
figure : subplot(2,2,1) 
imshow(img2);
subplot(2,2,2) 
imshow(imgdi);

#BInarisation
#im2bw(img,seuil); seuil compris entre 0 et 1