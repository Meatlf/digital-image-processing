%-- 2020/5/11 16:50 --%
f=checkerboard(8);
PSF=fspecial('motion',7,45);
gb=imfilter(f,PSF,'circular');
noise=imnoise(zeros(size(f)),'gaussian',0,0.001);
g=gb+noise;

subplot(2,2,1) 
imshow(pixeldup(f,8),[])
subplot(2,2,2) 
imshow(pixeldup(gb,8),[])
subplot(2,2,3) 
imshow(pixeldup(noise,8),[])
subplot(2,2,4) 
imshow(pixeldup(g,8),[])