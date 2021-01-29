# 参考资料：https://www.cnblogs.com/my-love-is-python/p/10406038.html
import os
import cv2
import numpy as np
import matplotlib.pyplot as plt
import math
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

def FFT(image):
    """

    """
    # 对图像进行傅立叶变换，fft是一个三维数组，fft[:,:,0]为实数部分，fft[:,:,1]为虚数部分
    # cv2.DFT_COMPLEX_OUTPUT表示傅立叶变化的方法

    # 使用cv2.dft进行傅立叶变化
    dft_img = cv2.dft(np.float32(image), flags=cv2.DFT_COMPLEX_OUTPUT)
    
    #得到中心像素
    dft_img_ce = np.fft.fftshift(dft_img)

    img_dft = 20 * np.log(cv2.magnitude(dft_img_ce[:,:, 0], dft_img_ce[:,:, 1]))
    
    # 第六步：进行画图操作
    plt.subplot(121)
    plt.imshow(image, cmap='gray')
    plt.subplot(122)
    plt.imshow(img_dft, cmap='gray')
    plt.show()

# 低通滤波，因为高频表示一些细节，即图像的轮廓和边缘，失去了高频部分，图像就容易变得模糊
def lowFilter(image):
    """
    使用掩模只保留低通
    :param image: 输入图像
    :param radius: 半径
    :return: 滤波结果
    """
    # 对图像进行傅立叶变换，fft是一个三维数组，fft[:,:,0]为实数部分，fft[:,:,1]为虚数部分
    # cv2.DFT_COMPLEX_OUTPUT表示傅立叶变化的方法

    # 第二步：进行数据类型转换，使用cv2.dft进行傅立叶变化
    dft_img = cv2.dft(np.float32(image), flags=cv2.DFT_COMPLEX_OUTPUT)
    
    # 第三步：使用np.fft.fftshift将低频转移到图像中心
    dft_center = np.fft.fftshift(dft_img)

    # 第四步：定义掩模：生成的掩模中间为1周围为0
    crow, ccol = int(image.shape[0] / 2), int(image.shape[1] / 2)  # 求得图像的中心点位置
    mask = np.zeros((image.shape[0], image.shape[1], 2), np.uint8)
    mask[crow - 30:crow + 30, ccol - 30:ccol + 30] = 1
    
    # 第五步：将掩模与傅立叶变换后图像相乘，保留中间部分
    mask_img = dft_center * mask

    # 第六步：使用np.fft.ifftshift（将低频移动到原来的位置）
    img_idf = np.fft.ifftshift(mask_img)

    # 第七步：使用np.fft.ifftshift(将低频移动到原来的位置)
    img_idf = cv2.idft(img_idf)
    
    # 第八步：使用cv2.magnitude转化为空间域内
    img_idf = cv2.magnitude(img_idf[:,:, 0], img_idf[:,:, 1])
    
    # 第九步：进行绘图操作
    plt.subplot(121)
    plt.imshow(image, cmap='gray')
    plt.subplot(122)
    plt.imshow(img_idf, cmap='gray')
    plt.show()

# 高通滤波，因为高频表示一些细节，即图像的轮廓和边缘，失去了高频部分，图像就容易变得模糊
def highFilter(image):
    """
    使用掩模只保留高通
    :param image: 输入图像
    """
    # 对图像进行傅立叶变换，fft是一个三维数组，fft[:,:,0]为实数部分，fft[:,:,1]为虚数部分
    # cv2.DFT_COMPLEX_OUTPUT表示傅立叶变化的方法

    # 第二步：进行数据类型转换，使用cv2.dft进行傅立叶变化
    dft_img = cv2.dft(np.float32(image), flags=cv2.DFT_COMPLEX_OUTPUT)
    
    # 第三步：使用np.fft.fftshift将低频转移到图像中心
    dft_center = np.fft.fftshift(dft_img)

    # 第四步：定义掩模：生成的掩模中间为0周围为1
    crow, ccol = int(image.shape[0] / 2), int(image.shape[1] / 2)  # 求得图像的中心点位置
    mask = np.ones((image.shape[0], image.shape[1], 2), np.uint8)
    mask[crow - 30:crow + 30, ccol - 30:ccol + 30] = 0
    
    # 第五步：将掩模与傅立叶变换后图像相乘，保留中间部分
    mask_img = dft_center * mask

    # 第六步：使用np.fft.ifftshift（将低频移动到原来的位置）
    img_idf = np.fft.ifftshift(mask_img)

    # 第七步：使用np.fft.ifftshift(将低频移动到原来的位置)
    img_idf = cv2.idft(img_idf)
    
    # 第八步：使用cv2.magnitude转化为空间域内
    img_idf = cv2.magnitude(img_idf[:,:, 0], img_idf[:,:, 1])
    
    # 第九步：进行绘图操作
    plt.subplot(121)
    plt.imshow(image, cmap='gray')
    plt.subplot(122)
    plt.imshow(img_idf, cmap='gray')
    plt.show()

if __name__ == "__main__":
    # 读取图片
    image = cv2.imread("scene.jpeg", 0)
    FFT(image)
    lowFilter(image)
    highFilter(image)