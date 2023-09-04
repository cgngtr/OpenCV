/*
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int hmin = 0, smin = 0, vmin = 0,
        hmax = 179, smax = 255, vmax = 255;

Mat imgHSV, mask;
Mat img;

vector<int> myColor{130, 179, 180, 255, 90, 226}; // red
vector<vector<Point>> contours;
vector<vector<Point>> conPoly;
vector<Rect> boundRect;
vector<Vec4i> hierarchy;

void getContours(Mat imgDil)
{
    conPoly.resize(contours.size());
    boundRect.resize(contours.size());
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        cout << area << endl;

        conPoly.resize(contours.size());
        boundRect.resize(contours.size());

        if (area > 1000)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

            cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]);

            drawContours(img, conPoly, i, Scalar(0, 0, 255), 2);
        }
    }
}

void findColor(Mat img)
{
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    for(int i = 0; i < myColor.size() ; i++)
    {
        Scalar lower(myColor[0], myColor[2], myColor[4]);
        Scalar upper(myColor[1], myColor[3], myColor[5]);
        inRange(imgHSV, lower, upper, mask);
        imshow(to_string(i), mask);
        getContours(mask);
    }

}

int main()
{
    VideoCapture cap(0);
    Mat img;

    while (true)
    {
        cap.read(img);
        findColor(img);

        imshow("Image",img);
        //imshow("Image", img);
        //imshow("Image Mask", mask);

        if (waitKey(1) == 27)
            break;
    }

    return 0;
}
*/
