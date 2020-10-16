clear,clc;
close all;
I=imread('模糊条码.bmp')
J=imread('清晰条码.bmp')
figure
imshow(I);title('清晰条码')
figure
imshow(J);title('模糊条码')
figure
subplot(2,2,1)
imhist(I);title('Histogram未分段')
subplot(2,2,2)
imhist(I,64);title('Histogram分为64段小区间')
subplot(2,2,3)
imhist(J);title('Histogram未分段')
subplot(2,2,4)
imhist(J,64);title('Histogram分为64段小区间')