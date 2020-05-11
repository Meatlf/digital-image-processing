%-- 2020/5/11 16:50 --%
f=checkerboard(8);
PSF=fspecial('motion',7,45);
gb=imfilter(f,PSF,'circular');
noise=imnoise(zeros(size(f)),'gaussian',0,0.001);
g=gb+noise;

subplot(3,3,1) 
imshow(pixeldup(f,8),[])

subplot(3,3,2) 
imshow(pixeldup(gb,8),[])

subplot(3,3,3) 
imshow(pixeldup(noise,8),[])

subplot(3,3,4) 
imshow(pixeldup(g,8),[])

subplot(3,3,5) 
fr=deconvwnr(g,PSF)
imshow(pixeldup(fr,8),[])

Sn=abs(fft2(noise)).^2
nA=sum(Sn(:))/prod(size(noise))
Sf=abs(fft2(f)).^2
fA=sum(Sf(:))/prod(size(f))
R=nA/fA

subplot(3,3,6) 
fr2=deconvwnr(g,PSF,R)
imshow(pixeldup(fr2,8),[])

subplot(3,3,7) 
NCORR = fftshift(real(ifft2(Sn)))
ICORR = fftshift(real(ifft2(Sf)))
fr3 = deconvwnr(g,PSF,NCORR,ICORR)
imshow(pixeldup(fr3,8),[])