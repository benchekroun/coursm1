%{
	#include "progsynt.h"
%}
%option noyywrap
type		int|float
identifiant 	[a-zA-Z]+
pvirg		;
egal 		=
operateur  	\+|-|\*|\/
point 		\.
nombre		[0-9]+
parantheseOuv 	\(
parantheseFer 	\)
endOfLine	\n
%%
{type}		{return TYPE;}
{identifiant}	{return IDENTIFIANT;}
{pvirg}		{return PVIRG;}
{egal}		{return EGAL;}
{operateur}	{return OPERATEUR;}
{point}		{return POINT;}
{nombre}	{return NOMBRE;}
{parantheseOuv}	{return PARANTHESEOUV;}
{parantheseFer}	{return PARANTHESEFER;}
[[:blank:]]+
<<EOF>>		{return FIN;}
%%
