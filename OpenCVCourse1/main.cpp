#include <iostream>
#include <cstdio>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace std;

/*cv::Mat CreateImage(int width, int height, int blue, int green, int red) {

    cv::Mat image(height, width, CV_8UC3);
    image = cv::Scalar(blue, green, red);
    cv::imshow("Window1", image);
    cv::waitKey();
} */

cv::Mat CropImage(string filePath, int x, int y, int width, int height) {
    cv::namedWindow("Window2");
    cv::Mat image2 = cv::imread(filePath);
    cv::imshow("Window2", image2); // normal image outputs
    cv::waitKey();
    cv::Mat croppedImage;
    image2.copyTo(croppedImage);
    croppedImage = cv::Mat(croppedImage, cv::Rect(x, y, width, height));
    return croppedImage;

}

cv::Mat DrawLine(string filePath, int x1, int x2, int y1, int y2, int m, int y, int k, int thickness) {
    cv::Mat originalImage = cv::imread(filePath);
    cv::Mat DrawnImage;
    originalImage.copyTo(DrawnImage);
    cv::line(DrawnImage, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(m, y, k), thickness);
    return DrawnImage;

}

cv::Mat DrawRect(string filePath) {
    cv::Mat image = cv::imread(filePath);
    cv::rectangle(image, cv::Point(0, 0), cv::Point(300, 300), cv::Scalar(0, 0, 255), 3);
    return image;
}


cv::Mat PutText(string filePath, string text) {
    cv::Mat originalImage = cv::imread(filePath);
    cv::Mat ImageWithText;
    originalImage.copyTo(ImageWithText);
    cv::Point p(15, 15);
    cv::Scalar s(0, 0, 255);
    cv::putText(ImageWithText, text, p, cv::HersheyFonts::FONT_HERSHEY_SIMPLEX, 2, s, 4);
    return ImageWithText;
}

cv::Mat DrawCircle(string filePath) {
    cv::Mat OriginalImage = cv::imread(filePath);
    cv::Mat ImageWithCircle;
    OriginalImage.copyTo(ImageWithCircle);
    cv::Point p(50, 50);
    cv::Scalar s(128, 0, 128);
    cv::circle(ImageWithCircle, p, 50, s, 3);

    return ImageWithCircle;
}

void readColorValues(string filePath) {
    cv::Mat image = cv::imread(filePath);
    cv::Mat processedImage;
    image.copyTo(processedImage);
    cv::imshow("Window", image);
    cv::waitKey();

    uchar blue, green, red;

    for (int x = 0; x < image.cols; x++) {
        for (int y = 0; y < image.rows; y++) {
            blue = processedImage.at<cv::Vec3b>(cv::Point(x, y))[0];

            if (blue <= 255 || blue >= 150) {
                blue = 0;
                processedImage.at<cv::Vec3b>(cv::Point(x, y))[0] = blue;
            }
        }
    }
    cv::imshow("Image with 0 blue value", processedImage);
    cv::waitKey();
    return;
}

//void copyImage(cv::Mat image, cv::Mat &copiedImage) {
//    cv::Mat copiedImage = cv::Mat(cv::Size(image.cols, image.rows), CV_8UC3);
//
//    for (int x = 0; x < copiedImage.cols; x++){
//        for (int y = 0; y < copiedImage.rows; y++) {
//
//        }
//    }
//}

cv::Mat ResizeB(cv::Mat image, int amplifierFactor = 2) { // function to expand image to bigger res.
    int newWidth = image.cols * amplifierFactor;
    int newHeight = image.rows * amplifierFactor;

    cv::Mat resizedImage(cv::Size(newWidth, newHeight), CV_8UC3); // resized empty image
    cv::Vec3b bgr;

    for (int i = 0; i < image.cols; i++) {
        for (int j = 0; j < image.rows; j++) {
            bgr = image.at<cv::Vec3b>(cv::Point(i, j));

            int startX = i * amplifierFactor;
            int startY = j * amplifierFactor;
            int endX = startX + amplifierFactor;
            int endY = startY + amplifierFactor;

            for (int x = startX; x < endX; x++) {
                for (int y = startY; y < endY; y++) {
                    resizedImage.at<cv::Vec3b>(cv::Point(x, y)) = bgr;
                }
            }
        }
    }

    return resizedImage;

}

cv::Mat ResizeS(cv::Mat image, int dividerFactor = 2) { // function to collapse image to smaller res.
    int newWidth = image.cols / dividerFactor;
    int newHeight = image.rows / dividerFactor;

    cv::Mat resizedImage(cv::Size(newWidth, newHeight), CV_8UC3); // resized empty image

    cv::Vec3b bgrVec;

    for (int i = 0; i < newWidth; i++) {
        for (int j = 0; j < newHeight; j++) {

            bgrVec = image.at<cv::Vec3b>(cv::Point(i * dividerFactor, j * dividerFactor));
            resizedImage.at<cv::Vec3b>(cv::Point(i, j)) = bgrVec;
        }
    }

    return resizedImage;
}

bool isDrawing;
void mouseClick(int event, int x, int y, int flag, void* data)
{
    cv::Mat* image = (cv::Mat*)data;

    if (event == CV_EVENT_LBUTTONDOWN)
    {
        cout << "Pressed" << endl;
        isDrawing = true;
    }
    else if (event == CV_EVENT_LBUTTONUP)
    {
        cout << "Released" << endl;
        isDrawing = false;
    }
    cout << "x: " << x << " y: " << y << endl;

    if (isDrawing)
    {
        image->at<cv::Vec3b>(cv::Point(x, y))[0] = 255;
        image->at<cv::Vec3b>(cv::Point(x, y))[1] = 0;
        image->at<cv::Vec3b>(cv::Point(x, y))[2] = 0;
        cv::imshow("Window", *image);
    }


}

void mouseEvents() {
    string window = "Window";
    cv::Mat image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
    cv::imshow(window, image);
    // mouse click events
    cv::setMouseCallback(window, mouseClick, &image);

    cv::waitKey();


}

void mousePaint()
{
    string window = "Window";
    cv::Mat canvas = cv::Mat::zeros(cv::Size(1820, 720), CV_8UC3);
    cv::setMouseCallback(window, mouseClick, &canvas);
}

void colorSpaces(cv::Mat image)
{
    cv::Mat colorSpacedImage;

    cv::cvtColor(image, colorSpacedImage, CV_BGR2GRAY);
    cv::imshow("BGR2GRAY", colorSpacedImage);

    cv::cvtColor(image, colorSpacedImage, CV_BGR2HLS);
    cv::imshow("CV_BGR2HLS", colorSpacedImage);

    cv::cvtColor(image, colorSpacedImage, CV_BGR2HSV);
    cv::imshow("CV_BGR2HSV", colorSpacedImage);

    cv::cvtColor(image, colorSpacedImage, CV_BGR2Lab);
    cv::imshow("CV_BGR2Lab", colorSpacedImage);

}

void divideChannels(cv::Mat image)
{
    vector<cv::Mat> imageChannels;

    cv::split(image, imageChannels);

    for (int i = 0; i < imageChannels.size(); i++)
    {
        cv::imshow(to_string(i), imageChannels.at(i));
    }

    cv::waitKey();
}

void morphologyEX(cv::Mat sourceImage)
{
    cv::Mat processedImage;
    cv::Mat kernel = cv::getStructuringElement(CV_SHAPE_RECT, cv::Size(3, 3));

    cv::morphologyEx(sourceImage, processedImage, cv::MORPH_ERODE, kernel, cv::Point(-1, -1), 2);
    cv::imshow("Before", sourceImage);
    cv::imshow("After", processedImage);
}


int main()
{
    string filePath = "/media/reveck/DATA/save/icons/image1.jpg";

    /*cv::imshow("Window2", CropImage(filePath, 0, 0, 250, 250)); // cropped image output
    cv::imshow("Window3", DrawRect(filePath));
    cv::imshow("Window4", PutText(filePath, "OpenCV C++"));
    cv::imshow("Window5", DrawCircle(filePath));
    readColorValues(filePath);


    cv::Mat originalImage = cv::imread(filePath);
    cv::Mat resizedImage = ResizeS(originalImage, 2);

    cv::imshow("Original image", originalImage);
    cv::imshow("Resized image", resizedImage);

    cv::namedWindow("Window");
    cv::setWindowTitle("Window", "baslik"); // changing window name after initializing
    cv::imshow("Window", originalImage);
    cv::resizeWindow("Window", cv::Size(200, 200));*/

    //mouseEvents();

    cv::Mat resourceImage = cv::imread(filePath);

    //colorSpaces(resourceImage);
    //divideChannels(resourceImage);

    morphologyEX(resourceImage);

    cv::waitKey();
}