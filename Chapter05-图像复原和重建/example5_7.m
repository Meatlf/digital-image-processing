f=checkerboard(8)
figure(1),imshow(pixeldup(f,8),[])
PSF=fspecial('motion',7,45)
%gb为运动模糊之后的图像
gb=imfilter(f,PSF,'circular')
figure(2),imshow(pixeldup(gb,8),[])
%noise为噪音图像
noise=imnoise(zeros(size(f)),'gaussian',0,0.001)
figure(3),imshow(pixeldup(noise,8),[])
%g为含有噪音的运动模糊之后的图像
g=gb+noise
figure(4),imshow(pixeldup(g,8),[])
%fr为约束的最小二乘方（正则）滤波
fr=deconvreg(g,PSF,4)
figure(5),imshow(pixeldup(fr,8),[])
fr2=deconvreg(g,PSF,0.04,[1e-7 1e7])
figure(6),imshow(pixeldup(fr2,8),[])