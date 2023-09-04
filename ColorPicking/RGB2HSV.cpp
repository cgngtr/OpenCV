/*
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Scalar colorRGB(0,7,247);

    // RGB'den HSV'ye dönüşüm
    Mat colorRGBMat(1, 1, CV_8UC3, Scalar(colorRGB[2], colorRGB[1], colorRGB[0]));
    Mat colorHSVMat;
    cvtColor(colorRGBMat, colorHSVMat, COLOR_BGR2HSV);
    Vec3b colorHSV = colorHSVMat.at<Vec3b>(0, 0);

    int hue = colorHSV[0];
    int saturation = colorHSV[1];
    int value = colorHSV[2];

    // Renk bileşenlerini yazdır
    std::cout << hue <<","<< saturation <<","<< value << std::endl;

    return 0;
}
*/
