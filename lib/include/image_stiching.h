#pragma once
#ifndef _IMAGE_STICHING_
#define _IMAGE_STICHING_
#define EXPORT_DLL __declspec(dllexport)
#include <string>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/legacy/legacy.hpp"

using namespace cv;

typedef struct
{
    Point2f left_top;
    Point2f left_bottom;
    Point2f right_top;
    Point2f right_bottom;
} four_corners_t;


void show_image(std::string title, Mat img_data);
//void load_images(std::string file_path,std::vector<Mat> &image);
void load_images(std::vector<std::string> &iamge_list, std::vector<Mat> &image);
Mat grayscale_convert(Mat &image);
// void features_matcher(std::vector<Mat> iamges);
std::vector<KeyPoint> extract_keyPoint(Mat &image, int keyPoint_nums = 2000);
Mat keyPoint_descriptor(Mat &image, std::vector<KeyPoint> &Key_point);
Mat keyPoint_descriptor(Mat &image, std::vector<KeyPoint> &Key_point);
std::vector<std::vector<Point2f>> keyPoint_match(std::vector<Mat> &image_desc, std::vector<Mat> &images, std::vector<std::vector<KeyPoint>> &Key_point);
four_corners_t calc_corners(const Mat &H, const Mat &src);
std::vector<Mat> image_match(std::vector<std::vector<Point2f>> &image_points, std::vector<Mat> images, four_corners_t &corners);
void optimize_seam(Mat &images, Mat &trans, Mat &dst, four_corners_t &corners);
extern "C"
{
    EXPORT_DLL void show_image(std::string iamge_path);
    EXPORT_DLL void  image_stiching(std::vector<std::string> image_list, int image_nums = 2, int keyPoint_nums = 2000);
}
#endif
