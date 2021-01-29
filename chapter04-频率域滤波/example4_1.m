[M,N]=size(f)
F=fft2(f)
sig=400
H=lpfilter('gaussian',M,N,sig)
G=H.*F
g=real(ifft2(G))
%imshow(f,[])
imshow(g,[])