#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap(0);
    Mat img;

    string filePath = "/home/reveck/Pictures/save/icons/carnumberplate.jpg";
    img = imread(filePath);

    CascadeClassifier plateCascade;
    plateCascade.load("/home/reveck/Pictures/save/icons/haarcascade"
                      "_russian_plate_number.xml");

    if(plateCascade.empty()) { cout << "XML file not loaded."  << endl;}

    vector<Rect> plates;

    while(true)
    {
        cap.read(img);

        plateCascade.detectMultiScale(img, plates, 1.1,10);

        for(int i = 0; i < plates.size() ; i++)
        {
            Mat imgCrop = img(plates[i]);
            imwrite("/home/reveck/Pictures/save/icons/plates/"
            + to_string(i) + ".png",imgCrop);
            rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255,0,255),3);
        }

        imshow("Image",img);
        waitKey(1);


    }

}