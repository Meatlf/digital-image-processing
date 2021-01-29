f=checkerboard(8)
figure(1),imshow(pixeldup(f,8))

PSF=fspecial('gaussian',7,10)
figure(2),imshow(pixeldup(PSF,73),[])

SD=0.01
g=imnoise(imfilter(f,PSF),'gaussian',0,SD^2)
INITPSF=ones(size(PSF))

NUMIT=5
[fr,PSFe]=deconvblind(g,INITPSF,NUMIT,DAMPAR,WEIGHT)
figure(3),imshow(pixeldup(PSFe,73),[])

NUMIT=10
[fr,PSFe]=deconvblind(g,INITPSF,NUMIT,DAMPAR,WEIGHT)
figure(4),imshow(pixeldup(PSFe,73),[])

NUMIT=20
[fr,PSFe]=deconvblind(g,INITPSF,NUMIT,DAMPAR,WEIGHT)
figure(5),imshow(pixeldup(PSFe,73),[])