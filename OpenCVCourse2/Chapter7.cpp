/*
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgGray, imgBlur, imgCanny, imgDil;

vector<vector<Point>> contours;
vector<vector<Point>> conPoly;
vector<Vec4i> hierarchy;
vector<Rect> boundRect;

void getContours(Mat imgDil, Mat img)
{
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    conPoly.resize(contours.size());
    boundRect.resize(contours.size());
    string objectType;

    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        cout << area << endl;

        if (area > 1000)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
            cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]);
            rectangle(img,boundRect[i].tl(), boundRect[i].br(),Scalar(0,255,0),3);

            int objCor = (int)conPoly[i].size();

            if(objCor == 3) {objectType = "Triangle";}
            if(objCor == 4)
            {
                float aspRatio = (float)boundRect[i].width/(float)boundRect[i].height;
                cout << "@" <<aspRatio << endl;
                if(aspRatio > 0.90 && aspRatio < 1.05)
                {
                    objectType = "Square";
                }
                else
                {
                    objectType = "Rectangle";
                }
            }
            if(objCor > 4) {objectType = "Circle";}



            putText(img, objectType, Point(boundRect[i].x,boundRect[i].y-8), 2,0.75, Scalar(255,255,0),2);
        }
    }
}

int main()
{
    string filePath = "/home/reveck/Pictures/save/icons/shapes1.jpg";
    Mat img = imread(filePath);

    // Preprocessing img.
    resize(img, img, Size(400, 400));
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgBlur, Size(5, 5), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);

    getContours(imgDil, img);

    imshow("Image", img);
    waitKey();
}
*/
