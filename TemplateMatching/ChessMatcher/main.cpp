#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Örtüşme alanını hesaplayan fonksiyon
float calculateOverlapArea(const Rect& rect1, const Rect& rect2)
{
    int x1 = max(rect1.x, rect2.x);
    int y1 = max(rect1.y, rect2.y);
    int x2 = min(rect1.x + rect1.width, rect2.x + rect2.width);
    int y2 = min(rect1.y + rect1.height, rect2.y + rect2.height);

    int width = max(0, x2 - x1);
    int height = max(0, y2 - y1);

    return width * height;
}

int main()
{
    Mat board = imread("/home/reveck/CLionProjects/TemplateMatching/ChessMatcher/full_board.png");
    Mat templateImage = imread("/home/reveck/CLionProjects/TemplateMatching/ChessMatcher/wp.png", IMREAD_UNCHANGED);
    int hh = templateImage.rows;
    int ww = templateImage.cols;

    Mat pawn, alpha;
    if (templateImage.channels() == 4)
    {
        vector<Mat> channels;
        split(templateImage, channels);
        pawn = channels[0];
        alpha = channels[3];
    }
    else
    {
        pawn = templateImage.clone();
        alpha = Mat(templateImage.size(), CV_8UC1, Scalar(255));
    }

    Mat imgGray;
    cvtColor(board, imgGray, COLOR_BGR2GRAY);

    Mat correlation;
    matchTemplate(imgGray, pawn, correlation, TM_CCORR_NORMED, alpha);

    double threshold = 0.89;
    Mat loc;
    findNonZero(correlation >= threshold, loc);

    vector<Rect> detections;
    for (int i = 0; i < loc.total(); ++i)
    {
        Point pt = loc.at<Point>(i);
        Rect rect(pt.x, pt.y, ww, hh);
        detections.push_back(rect);
    }

    vector<Rect> finalDetections;
    while (!detections.empty()) {
        Rect highestScoreRect = detections.front(); // first element of the vector
        finalDetections.push_back(highestScoreRect);
        detections.erase(detections.begin()); // başlangıç konumunu gösteren iteratoru siler

        // begin ve front arasındaki fark : front öğeye doğrudan erişirken begin, başlangıç konumunu gösteren bir iterator döndürür.

        detections.erase(remove_if(detections.begin(), detections.end(), [&](const Rect& rect)  // teke(rect) düşmesini sağlayan satır.
        {
            float overlapArea = calculateOverlapArea(highestScoreRect, rect);
            float overlapRatio = overlapArea / (rect.width * rect.height);
            float overlapThreshold = 0.5; // Örtüşme eşik değeri
            return overlapRatio > overlapThreshold;
        }), detections.end());
    }

    // Non-maximum suppression uygulanan sonuçları kullanarak işlemleri yapabilirsiniz
    for (const Rect& rect : finalDetections) {
        rectangle(board, rect, Scalar(0, 0, 255), 2);
    }

    imshow("Result", board);
    waitKey(0);
    destroyAllWindows();

    return 0;
}
