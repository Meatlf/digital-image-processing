// 移动平均阈值分割
// 参考资料: [移动平均阈值分割](https://blog.csdn.net/qq_34510308/article/details/93162142)
#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

/*
对输入图像作移动平均分割
src为单通道灰度图像
num表示计算平均的点数
b是常数
*/
void movingThreshold(IplImage *src, IplImage *dst, int num, float b)
{
  assert(src->nChannels == 1 && dst->nChannels == 1);
  assert(src->height == dst->height && src->width == dst->width);

  uchar *dstdata = (uchar *)dst->imageData;
  uchar *data = (uchar *)src->imageData;
  int w = src->width, h = src->height;
  int step = src->widthStep;
  float n = (float)num;
  float m_pre = data[0] / n;
  float m_now = 0.0;

  cout << "data[0]" << data[0] << "m_pre:" << m_pre << endl;
  cout << w << "   " << step << endl;

  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      int index = i * step + j;

      float dif;
      if (index < num + 1)
        dif = data[index];
      else
        dif = data[index] - data[index - num - 1];

      dif *= 1 / n;
      m_now = m_pre + dif;
      m_pre = m_now;
      //cout << m_now << endl;
      if (data[index] > cvRound(b * m_now))
        dstdata[index] = 255;
      else
        dstdata[index] = 0;
    }
  }
}

int main()
{
  cout << "移动平均阈值分割!" << endl;
  // IplImage *srcImage = cvLoadImage("Picture1.png", CV_LOAD_IMAGE_GRAYSCALE);
  IplImage *srcImage = cvLoadImage("spot_shaded_text_image.tif", CV_LOAD_IMAGE_GRAYSCALE);
  IplImage *dstImage0 = cvCreateImage(cvGetSize(srcImage), 8, 1);
  IplImage *dstImage1 = cvCreateImage(cvGetSize(srcImage), 8, 1);

  int num = 10;
  float b = 0.8;

  cvThreshold(srcImage, dstImage0, 230, 255, THRESH_TRUNC);
  movingThreshold(srcImage, dstImage1, num, b);

  cvShowImage("src", srcImage);
  cvShowImage("dst0", dstImage0);
  cvShowImage("dst1", dstImage1);
  cvWaitKey(0);
  return 0;
}
