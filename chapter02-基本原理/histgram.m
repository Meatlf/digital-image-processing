clear,clc;
close all;
I=imread('ģ������.bmp')
J=imread('��������.bmp')
figure
imshow(I);title('��������')
figure
imshow(J);title('ģ������')
figure
subplot(2,2,1)
imhist(I);title('Histogramδ�ֶ�')
subplot(2,2,2)
imhist(I,64);title('Histogram��Ϊ64��С����')
subplot(2,2,3)
imhist(J);title('Histogramδ�ֶ�')
subplot(2,2,4)
imhist(J,64);title('Histogram��Ϊ64��С����')