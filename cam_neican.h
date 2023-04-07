#ifndef CAM_NEICAN_H
#define CAM_NEICAN_H
#include <string>
#include <opencv2/opencv.hpp>
#include <QString>
#include<thread>
#include<mutex>
class cam_neican
{
public:
    cam_neican();

public:
    cv::Size boardSize;
    float squareSize=0;
    cv::Size imageSize;
    std::vector<std::vector<cv::Point3f>> objectPointsSeq;
    std::vector<std::int8_t> conerfindseq;
    std::vector<std::string> imagePaths;
    std::vector<std::vector<cv::Point2f>> imagePointsSeq;

    double ret;
    cv::Mat mtx;
    cv::Mat dist;
    cv::Size imgsize;
    std::vector<cv::Mat> rvecs;
    std::vector<cv::Mat> tvecs;

public:
    void setBoardSize(int row, int col)
    {
        boardSize = cv::Size(row - 1, col - 1);
    }
    void setSquareSize(float mmVal)
    {
     //   squareSize = cv::Size(mmVal, mmVal);
        squareSize=mmVal;
    }
    void setImageSize(cv::Size size)
    {
        imageSize = size;
    }
    void clear()
    {
        //imagePaths.clear();
        imagePointsSeq.clear();
        objectPointsSeq.clear();
        ret = 0;
        mtx = cv::Mat();
        rvecs.clear();
        tvecs.clear();
        dist = cv::Mat();
        // corners.clear();
    }
    bool findCorners();
    cv::Mat drawChessboardCornersimg(std::string idx);
    void calicamera();
    std::thread* th;
    std::thread* th_corner;
    void calirate_thread();
    void corner_thread();
    bool corner_flag=0;
    bool calibrate_flag=0;
};

//class thread_obj
//{
//    public:
//    void operator()(std::vector<std::vector<cv::Point3f>> a,std::vector<std::vector<cv::Point2f>> b, cv::Size imageSize);
//};
#endif // CAM_NEICAN_H
