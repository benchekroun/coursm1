img = imread('lena.jpg');
imdb = im2double(img);
imwrite(imdb,'lena.bmp');
%img2 = imread('FibroblastCellNucleus.jpg');
%imggray = rgb2gray(img2);
%imgdbgray = im2double(imggray);
%imgdi = histeq(imgdbgray,200);

%imshow(imgdi);

%BInarisation
%im2bw(img,seuil); seuil compris entre 0 et 1

%convolution produit de chaque pixels avec un masque
%Convolution en 2D, conv2
mat = [-1 0 1;-1 0 1;-1 0 1];
mat2 = [-1 -1 -1;0 0 0;1 1 1];
imgmasque = conv2(imdb,mat);
imgmasque2 = conv2(imdb,mat2);
imwrite(imgmasque,'lenamasque.bmp');
imwrite(imgmasque2,'lenamasque2.bmp');

%on tente la gaussienne
gauss_f = fspecial('gaussian',25);
gaussImg = filter2(gauss_f,imdb,'valid');

%on va faire un vecteur des valeurs, que l'on va trier par ordre croissant
%on prend la valeur médiane, on appelle ca faire un filtre median
medImg = medfilt2(imdb);
imgdiff = abs(imdb-medImg);
diffbw = im2bw(imgdiff,2/255);

imgbruit = imnoise(imdb,'salt & pepper');
bruitfilter = medfilt2(imgbruit);

g = sqrt(((imgmasque.*imgmasque2) + (imgmasque.*imgmasque2))./2);
%g = g/1,414;
figure;subplot(2,2,1);imshow(imdb);title('origine');
subplot(2,2,2);imshow(diffbw);title('diffBW');
subplot(2,2,3);imshow(imgbruit);title('buirt');
subplot(2,2,4);imshow(bruitfilter);title('bruit filter');

%filtre passe bas : filtre moyenneur, prendre un point et ses 8 voisins, 
%un masque avec des 1 partout, et on divise par la somme des coefficients
