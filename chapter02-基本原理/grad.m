clear,clc;
close all;
src=imread('ģ������.bmp')
figure()
imshow(src,[])

bw=edge(src,'sobel')
figure()
imshow(bw,[])

I=double(src)
[x,y]=gradient(I)
figure()
imshow(x,[])
figure()
imshow(y,[])