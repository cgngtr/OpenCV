#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

int main()
{
    // Resmi yükle
    Mat img = imread("/home/reveck/CLionProjects/ColorPicking/map1.png");

    // Kontrol edilecek renklerin RGB değerlerini tanımla
    std::vector<Scalar> colors;

    colors.push_back(Scalar(44, 100, 41));
    colors.push_back(Scalar(0, 7, 247));
    colors.push_back(Scalar(149, 177, 104));
    colors.push_back(Scalar(189, 217, 143));
    colors.push_back(Scalar(75, 139, 79));
    colors.push_back(Scalar(217, 69, 20));
    colors.push_back(Scalar(255, 109, 61));
    colors.push_back(Scalar(250,222,85));
    colors.push_back(Scalar(189,178,94));
    colors.push_back(Scalar(63,81,27));
    colors.push_back(Scalar(83,123,8));
    colors.push_back(Scalar(141,179,96));
    colors.push_back(Scalar(181,219,136));
    colors.push_back(Scalar(140,164,112));
    colors.push_back(Scalar(90,102,81));
    colors.push_back(Scalar(49,116,68));
    colors.push_back(Scalar(6,102,33));
    colors.push_back(Scalar(87,156,108));
    colors.push_back(Scalar(4,249,179));
    colors.push_back(Scalar(12,102,88));
    colors.push_back(Scalar(234,251,251));
    colors.push_back(Scalar(227,236,237));
    colors.push_back(Scalar(42,46,47));
    colors.push_back(Scalar(32,32,56));
    colors.push_back(Scalar(32,32,112));
    colors.push_back(Scalar(160,160,255));
    colors.push_back(Scalar(1,0,64));
    colors.push_back(Scalar(5,0,144));
    colors.push_back(Scalar(18,0,255));
    colors.push_back(Scalar(255,0,255));
    colors.push_back(Scalar(248,185,220));
    colors.push_back(Scalar(112,112,214));
    colors.push_back(Scalar(64, 64, 144));


    // Maske ve konturları saklamak için boş bir görüntü oluştur
    Mat mask(img.size(), CV_8UC1, Scalar(0));
    std::vector<std::vector<Point>> contours;

    // Her bir renk için konturları bul ve maskede biriktir
    for (const auto& color : colors)
    {
        // Resmi BGR renk uzayına dönüştür
        Mat bgr;
        cvtColor(img, bgr, COLOR_RGB2BGR);

        // Maske oluştur
        Mat colorMask;
        inRange(bgr, color, color, colorMask);

        // Maskelenmiş görüntü üzerinde konturları bul
        std::vector<std::vector<Point>> colorContours;
        findContours(colorMask, colorContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // Konturları maskede biriktir
        contours.insert(contours.end(), colorContours.begin(), colorContours.end()); // P1 = eklenecek yere başlangıç, (dst)
        // P2 = eklemeye nereden başlanacağı (src)
        // P3 = eklemenin nerede biteceği (src)

        // Renk maskesini orijinal maskeye ekle
        mask |= colorMask; //bitwise.
    }

    // Konturları çiz
    drawContours(img, contours, -1, Scalar(0, 0, 255), 1);

    // Görüntüyü göster
    imshow("Konturlar", img);
    waitKey(0);

    return 0;
}
