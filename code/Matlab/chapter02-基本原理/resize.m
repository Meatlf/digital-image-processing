f=imread('Image1.bmp')
resizedImg=imresize(f,[15,640])
% resizedImg = rgb2gray(resizedImg)
imwrite(resizedImg,'resizedImg.bmp')
imshow(resizedImg,[])

