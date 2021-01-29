// #include <iostream>
// #include "opencv2/imgproc.hpp"
// #include "opencv2/imgcodecs.hpp"
// using namespace cv;
// using namespace std;
// void help();
// void calcPSF(Mat& outputImg, Size filterSize, int R);
// void fftshift(const Mat& inputImg, Mat& outputImg);
// void filter2DFreq(const Mat& inputImg, Mat& outputImg, const Mat& H);
// void calcWnrFilter(const Mat& input_h_PSF, Mat& output_G, double nsr);
// const String keys =
// "{help h usage ? |             | print this message   }"
// "{image          |original.JPG | input image name     }"
// "{R              |53           | radius               }"
// "{SNR            |5200         | signal to noise ratio}"
// ;

// #define DEBUG_BY_TTZ  1

// int main(int argc, char *argv[])
// {
// 	help();
// #if !DEBUG_BY_TTZ   
//     CommandLineParser parser(argc, argv, keys);
//     if (parser.has("help"))
//     {
//         parser.printMessage();
//         return 0;
//     }
//     int R = parser.get<int>("R");
//     int snr = parser.get<int>("SNR");
//     string strInFileName = parser.get<String>("image");
//     if (!parser.check())
//     {
//         parser.printErrors();
//         return 0;
//     }
// #else
// 	string strInFileName = "./original.jpg";
// 	int R = 53;
// 	int snr = 5200;
// #endif
	
//     Mat imgIn;
//     imgIn = imread(strInFileName, IMREAD_GRAYSCALE);
//     if (imgIn.empty()) //check whether the image is loaded or not
//     {
//         cout << "ERROR : Image cannot be loaded..!!" << endl;
//         return -1;
//     }
//     Mat imgOut;
//     // it needs to process even image only
//     Rect roi = Rect(0, 0, imgIn.cols & -2, imgIn.rows & -2);
//     //Hw calculation (start)
//     Mat Hw, h;
//     calcPSF(h, roi.size(), R);
//     calcWnrFilter(h, Hw, 1.0 / double(snr));
//     //Hw calculation (stop)
//     // filtering (start)
//     filter2DFreq(imgIn(roi), imgOut, Hw);
//     // filtering (stop)
//     imgOut.convertTo(imgOut, CV_8U);
//     normalize(imgOut, imgOut, 0, 255, NORM_MINMAX);
//     imwrite("result.jpg", imgOut);
//     return 0;
// }
// void help()
// {
//     cout << "2018-07-12" << endl;
//     cout << "DeBlur_v8" << endl;
//     cout << "You will learn how to recover an out-of-focus image by Wiener filter" << endl;
// }
// void calcPSF(Mat& outputImg, Size filterSize, int R)
// {
//     Mat h(filterSize, CV_32F, Scalar(0));
//     Point point(filterSize.width / 2, filterSize.height / 2);
//     circle(h, point, R, 255, -1, 8);
//     Scalar summa = sum(h);
//     outputImg = h / summa[0];
// }
// void fftshift(const Mat& inputImg, Mat& outputImg)
// {
//     outputImg = inputImg.clone();
//     int cx = outputImg.cols / 2;
//     int cy = outputImg.rows / 2;
//     Mat q0(outputImg, Rect(0, 0, cx, cy));
//     Mat q1(outputImg, Rect(cx, 0, cx, cy));
//     Mat q2(outputImg, Rect(0, cy, cx, cy));
//     Mat q3(outputImg, Rect(cx, cy, cx, cy));
//     Mat tmp;
//     q0.copyTo(tmp);
//     q3.copyTo(q0);
//     tmp.copyTo(q3);
//     q1.copyTo(tmp);
//     q2.copyTo(q1);
//     tmp.copyTo(q2);
// }
// void filter2DFreq(const Mat& inputImg, Mat& outputImg, const Mat& H)
// {
//     Mat planes[2] = { Mat_<float>(inputImg.clone()), Mat::zeros(inputImg.size(), CV_32F) };
//     Mat complexI;
//     merge(planes, 2, complexI);
//     dft(complexI, complexI, DFT_SCALE);
//     Mat planesH[2] = { Mat_<float>(H.clone()), Mat::zeros(H.size(), CV_32F) };
//     Mat complexH;
//     merge(planesH, 2, complexH);
//     Mat complexIH;
//     mulSpectrums(complexI, complexH, complexIH, 0);
//     idft(complexIH, complexIH);
//     split(complexIH, planes);
//     outputImg = planes[0];
// }
// void calcWnrFilter(const Mat& input_h_PSF, Mat& output_G, double nsr)
// {
//     Mat h_PSF_shifted;
//     fftshift(input_h_PSF, h_PSF_shifted);
//     Mat planes[2] = { Mat_<float>(h_PSF_shifted.clone()), Mat::zeros(h_PSF_shifted.size(), CV_32F) };
//     Mat complexI;
//     merge(planes, 2, complexI);
//     dft(complexI, complexI);
//     split(complexI, planes);
//     Mat denom;
//     pow(abs(planes[0]), 2, denom);
//     denom += nsr;
//     divide(planes[0], denom, output_G);
// }


#include <opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>

//This demo shows the effect of processing out-of-focus image using Wiener filter.
using namespace cv;
int R=20;
int snr=1000;
Mat img;
char dstWin[]="dstwindow";
void calcPSF(Mat& dst,Size filterSize){
    Mat circularPSF(filterSize,CV_32F,Scalar(0));
    Point point(filterSize.width/2,filterSize.height/2);
    circle(circularPSF,point,R,255,-1,8);
    Scalar summa=sum(circularPSF);
    dst=circularPSF/summa[0];
}
void FFTShift(const Mat& src,Mat& dst){
    dst=src.clone();
    int cx=dst.cols/2;
    int cy=dst.rows/2;
    Mat q0(dst,Rect(0,0,cx,cy));
    Mat q1(dst,Rect(cx,0,cx,cy));
    Mat q2(dst,Rect(0,cy,cx,cy));
    Mat q3(dst,Rect(cx,cy,cx,cy));
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}
void filter2DFreq(const Mat& src,Mat& dst,const Mat& H){
    Mat planes[2]={Mat_<float>(src.clone()), Mat::zeros(src.size(),CV_32F)};
    Mat complexI;
    merge(planes,2,complexI);
    Mat planesH[2]={Mat_<float>(H.clone()),Mat::zeros(H.size(),CV_32F)};
    Mat complexH;
    merge(planesH,2,complexH);
    Mat complexIH;
    mulSpectrums(complexI,complexH,complexIH,0);//give the result of multiplication of two Fourier spectrums.
    idft(complexIH,complexIH);
    split(complexIH,planes);
    dst=planes[0];
}
//_snr is the inverse of SNR
void calcWienerFilter(const Mat& PSF, Mat& dst,double _snr=1.0/(double)snr){
    Mat PSF_shifted;
    FFTShift(PSF,PSF_shifted);
    Mat planes[2]={Mat_<float>(PSF_shifted.clone()),Mat::zeros(PSF_shifted.size(),CV_32F)};
    Mat complexI;
    merge(planes,2,complexI);
    dft(complexI,complexI);
    split(complexI,planes);
    Mat denom;
    pow(abs(planes[0]),2,denom);
    denom+=_snr;
    divide(planes[0],denom,dst);
}
void deblur(int,void*){
    Mat src=img.clone();
    Mat outputImg;
    Rect roi=Rect(0,0,src.cols&-2,src.rows&-2);
    //calculate Hw
    Mat Hw,psf;
    calcPSF(psf,roi.size());
    calcWienerFilter(psf,Hw);
    //filter prepared
    filter2DFreq(src(roi),outputImg,Hw);
    outputImg.convertTo(outputImg,CV_8U);
    normalize(outputImg,outputImg,0,255,NORM_MINMAX);
    imshow(dstWin,outputImg);
}

int main(){
    img=imread("./original.jpg",IMREAD_GRAYSCALE);
    namedWindow(dstWin);
    createTrackbar("R-adjust",dstWin,&R,100,deblur,0);
    createTrackbar("SNR-adjust",dstWin,&snr,10000,deblur,0);
    deblur(0,0);
    waitKey();
    return 0;
}