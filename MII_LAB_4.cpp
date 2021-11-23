#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
using namespace cv;
using namespace std;
const string name = "Lukasz Niedzwiadek";
Mat grayImage;
Mat srcImage = imread("J.jpg");

int main()
{
    if (!srcImage.data)
        cout << "blad";
    else
        cout << "hello";

    namedWindow(name);
    moveWindow(name, 0, 0);
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    Mat resizedImage(900, 800, grayImage.type());
    resize(grayImage, resizedImage, resizedImage.size());

    Rect rLB(0,resizedImage.size().height /2, resizedImage.size().width / 2, resizedImage.size().height / 2);
    Rect rRB(resizedImage.size().width / 2, resizedImage.size().height / 2, resizedImage.size().width / 2, resizedImage.size().height / 2);
    Rect rLT(0, 0, resizedImage.size().width / 2, resizedImage.size().height / 2);
    Rect rRT(resizedImage.size().width / 2, 0, resizedImage.size().width / 2, resizedImage.size().height / 2);

    Mat resizedImage_LB(resizedImage, rLB);
    Mat resizedImage_RB(resizedImage, rRB);
    Mat resizedImage_LT(resizedImage, rLT);
    Mat resizedImage_RT(resizedImage, rRT);

    vector<Point2f> corners_LT;
    vector<Point2f> corners_RT;
    vector<Point2f> corners_LB;
    vector<Point2f> corners_RB;

    Size patternsize_LT(4, 6); //dostosować w zależności od zdjęcia
    Size patternsize_RT(4, 5);
    Size patternsize_LB(4, 6);
    Size patternsize_RB(4, 4);

    bool patternfound_LT = findChessboardCorners(resizedImage_LT, patternsize_LT, corners_LT,
        CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
        + CALIB_CB_FAST_CHECK);

    if (patternfound_LT)
        cornerSubPix(resizedImage_LT, corners_LT, Size(11, 11), Size(-1, -1),
            TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

    bool patternfound_RT = findChessboardCorners(resizedImage_RT, patternsize_RT, corners_RT,
        CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
        + CALIB_CB_FAST_CHECK);

    if (patternfound_RT)
        cornerSubPix(resizedImage_RT, corners_RT, Size(11, 11), Size(-1, -1),
            TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

    bool patternfound_LB = findChessboardCorners(resizedImage_LB, patternsize_LB, corners_LB,
        CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
        + CALIB_CB_FAST_CHECK);

    if (patternfound_LB)
        cornerSubPix(resizedImage_LB, corners_LB, Size(11, 11), Size(-1, -1),
            TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

    bool patternfound_RB = findChessboardCorners(resizedImage_RB, patternsize_RB, corners_RB,
        CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
        + CALIB_CB_FAST_CHECK);

    if (patternfound_RB)
        cornerSubPix(resizedImage_RB, corners_RB, Size(11, 11), Size(-1, -1),
            TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

    drawChessboardCorners(resizedImage_LT, patternsize_LT, Mat(corners_LT), patternfound_LT);
    drawChessboardCorners(resizedImage_RT, patternsize_RT, Mat(corners_RT), patternfound_RT);
    drawChessboardCorners(resizedImage_LB, patternsize_LB, Mat(corners_LB), patternfound_LB);
    drawChessboardCorners(resizedImage_RB, patternsize_RB, Mat(corners_RB), patternfound_RB);

    imshow("LT", resizedImage_LT);
    imshow("RT", resizedImage_RT);
    imshow("LB", resizedImage_LB);
    imshow("RB", resizedImage_RB);

    imshow(name, resizedImage);
    moveWindow(name, 300, 300);
    imwrite("J_GRAY_OUT_3.jpg", resizedImage);

    waitKey();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
