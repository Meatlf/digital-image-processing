f=checkerboard(8)
figure(1),imshow(pixeldup(f,8))
%7*7且标准偏差为10的高斯PSF
PSF=fspecial('gaussian',7,10)
SD=0.01
g=imnoise(imfilter(f,PSF),'gaussian',0,SD^2)
figure(2),imshow(pixeldup(g,8))
DAMPAR=10*SD
LIM=ceil(size(PSF,1)/2)
WEIGHT=zeros(size(g))
WEIGHT(LIM+1:end-LIM,LIM+1:end-LIM)=1
%迭代的次数
NUMIT=5
f5=deconvlucy(g,PSF,NUMIT,DAMPAR,WEIGHT)
figure(3),imshow(pixeldup(f5,8))
NUMIT=10
f5=deconvlucy(g,PSF,NUMIT,DAMPAR,WEIGHT)
figure(4),imshow(pixeldup(f5,8))
NUMIT=20
f5=deconvlucy(g,PSF,NUMIT,DAMPAR,WEIGHT)
figure(5),imshow(pixeldup(f5,8))
NUMIT=100
f5=deconvlucy(g,PSF,NUMIT,DAMPAR,WEIGHT)
figure(5),imshow(pixeldup(f5,8))