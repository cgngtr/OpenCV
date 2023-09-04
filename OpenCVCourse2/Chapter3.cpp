/*
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;

int main() {
    string filePath = "/home/reveck/Pictures/save/icons/image1.jpg";
    Mat img = imread(filePath);
    cout << img.size() << endl; // 564x564
    Mat imgResize, imgCrop;

    resize(img,imgResize,Size(400,400));
    resize(img,imgResize,Size(),0.5,0.5); // another way to resize. multiplies it by 0.5

    Rect roi(314,314,250,250);
    imgCrop = img(roi);

    imshow("Image" ,img);
    imshow("Resized Image" ,imgResize);
    imshow("Cropped Image" ,imgCrop);
    waitKey();
}
*/
