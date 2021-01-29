f=checkerboard(8)
figure(1),imshow(pixeldup(f,8),[])
PSF=fspecial('motion',7,45)
%gbΪ�˶�ģ��֮���ͼ��
gb=imfilter(f,PSF,'circular')
figure(2),imshow(pixeldup(gb,8),[])
%noiseΪ����ͼ��
noise=imnoise(zeros(size(f)),'gaussian',0,0.001)
figure(3),imshow(pixeldup(noise,8),[])
%gΪ�����������˶�ģ��֮���ͼ��
g=gb+noise
figure(4),imshow(pixeldup(g,8),[])
%frΪԼ������С���˷��������˲�
fr=deconvreg(g,PSF,4)
figure(5),imshow(pixeldup(fr,8),[])
fr2=deconvreg(g,PSF,0.04,[1e-7 1e7])
figure(6),imshow(pixeldup(fr2,8),[])