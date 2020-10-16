close all;clc;
% clear all;
x=1:1:255;

fileID = fopen('3miltest_file.txt')
temp=fread(fileID)

y = temp(1:255)

size(x)
size(y)

plot(x,y,'r');
axis([0 255 0 255]);

title('test');
xlabel('xlabel');
ylabel('ylabel');
% grid;
% gtext('gtest');