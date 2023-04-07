#ifndef RESULT_VERIFY_H
#define RESULT_VERIFY_H

#include <iostream>
#include <opencv2/opencv.hpp>
//using namespace std;
//void getTheoreticalUVl(float* theoryUV, const vector<float> &intrinsic, const vector<float> &extrinsic, double x, double y, double z) {
//    // set the intrinsic and extrinsic matrix
//    double matrix1[3][3] = {{intrinsic[0], intrinsic[1], intrinsic[2]}, {intrinsic[3], intrinsic[4], intrinsic[5]}, {intrinsic[6], intrinsic[7], intrinsic[8]}};
//    double matrix2[3][4] = {{extrinsic[0], extrinsic[1], extrinsic[2], extrinsic[3]}, {extrinsic[4], extrinsic[5], extrinsic[6], extrinsic[7]}, {extrinsic[8], extrinsic[9], extrinsic[10], extrinsic[11]}};
//    double matrix3[4][1] = {x, y, z, 1};

//    // transform into the opencv matrix
//    cv::Mat matrixIn(3, 3, CV_64F, matrix1);
//    cv::Mat matrixOut(3, 4, CV_64F, matrix2);
//    cv::Mat coordinate(4, 1, CV_64F, matrix3);

//    // calculate the result of u and v
//    cv::Mat result = matrixIn*matrixOut*coordinate;
//    float u = result.at<double>(0, 0);
//    float v = result.at<double>(1, 0);
//    float depth = result.at<double>(2, 0);

//    theoryUV[0] = u / depth;
//    theoryUV[1] = v / depth;
//}


#endif // RESULT_VERIFY_H
