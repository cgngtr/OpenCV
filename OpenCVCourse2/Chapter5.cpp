/*
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;

int main() {

    Mat matrix, imgWarp;
    string filePath = "/home/reveck/Pictures/save/icons/cardsonatable2.jpg";
    Mat img = imread(filePath);

    float w = 150, h = 230;
    Point2f src[4] = { {150,185}, {184,76}, {455,213}, {460,101} };
    Point2f dst[4] = { {0.0f,0.0f}, {w,0.0f}, {0.0f,h}, {w,h} };

    matrix = getPerspectiveTransform(src,dst);
    warpPerspective(img,imgWarp,matrix,Point(w,h)); // warpPerspective() is the function that applies the perspective transformation to an image.

    for(int i = 0 ; i < 4 ; i++)
    {
        circle(img, src[i], 10, Scalar(0,69,255),FILLED);
    }

    imshow("Image",img);
    imshow("Image Warp",imgWarp);


    waitKey();
}
*/
