#include "cam_neican.h"
using namespace std;
using namespace cv;
std::mutex mut;
cam_neican::cam_neican()
{
}
bool cam_neican::findCorners()
{
th_corner=new std::thread(&cam_neican::corner_thread,this);
}

Mat cam_neican::drawChessboardCornersimg(std::string idx)
{
    for (int i = 0; i < imagePaths.size(); i++)
    {
        if (imagePaths[i] == idx)
        {
            Mat colorImage = imread(this->imagePaths[i], IMREAD_COLOR);
            drawChessboardCorners(colorImage, boardSize, imagePointsSeq[i], true);
            return colorImage;
        }
    }
}
void cam_neican::calicamera()
{
th=new std::thread(&cam_neican::calirate_thread,this);
}

void cam_neican::calirate_thread()
{
    mut.lock();
    calibrate_flag=0;
    std::vector<std::vector<cv::Point3f>> objectPointsSeq_;
    std::vector<std::vector<cv::Point2f>> imagePointsSeq_;
    for(int i = 0; i < objectPointsSeq.size(); i++)
    {
        if(conerfindseq[i])
        {
            objectPointsSeq_.push_back(objectPointsSeq[i]);
            imagePointsSeq_.push_back(imagePointsSeq[i]);
        }
    }
    ret =calibrateCamera(objectPointsSeq_, imagePointsSeq_, imageSize, mtx, dist, rvecs, tvecs);
    mut.unlock();
    calibrate_flag=1;
}

void cam_neican::corner_thread()
{
    mut.lock();
    corner_flag=0;
    for (int i = 0; i < imagePaths.size(); i++)
    {
        vector<Point2f> corners;
        Mat grayImage = imread(this->imagePaths[i], IMREAD_GRAYSCALE);
        bool isCornersFound = findChessboardCorners(grayImage, boardSize, corners);
        if (isCornersFound)
        {
            cornerSubPix(grayImage, corners, cv::Size(11, 11), cv::Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 30, 0.001));
            imagePointsSeq.push_back(corners);
            conerfindseq.push_back(1);
        }
        else
        {
            imagePointsSeq.push_back(std::vector<cv::Point2f>());
            conerfindseq.push_back(0);
        }
        vector<Point3f> objectPoints;
        for (int i = 0; i < boardSize.height; i++)
            for (int j = 0; j < boardSize.width; j++)
                objectPoints.push_back(Point3f(j * squareSize, i * squareSize, 0));
        objectPointsSeq.push_back(objectPoints);
    }
    corner_flag=1;
    mut.unlock();
}
