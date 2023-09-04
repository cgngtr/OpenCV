/*#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    string filePath = "/media/reveck/DATA/save/icons/image1.jpg";
    Mat img = imread(filePath);
    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny,50,100);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3)); // dilation amount.
    dilate(imgCanny,imgDil,kernel);
    erode(imgDil,imgErode,kernel);

    imshow("Image", img);
    //imshow("Gray Image", imgGray);
    //imshow("Blur Image", imgBlur);
    imshow("Canny Image(NB)", imgCanny);
    imshow("Dilated image", imgDil);
    imshow("Eroded image", imgErode);



    waitKey();
}*/