% 移动平均的图像阈值处理
% 参考资料: [使用移动平均的图像阈值处理](https://blog.csdn.net/liyuqian199695/article/details/70076169)
clc;
clear all;
close all;

f = imread('./spot_shaded_text_image.tif');
figure;imshow(f);title('原图像');
T = graythresh(f);
g1 = im2bw(f, T); 
g2 = movingthresh(f, 20, 0.5);
figure, imshow(g2);title('变换后');