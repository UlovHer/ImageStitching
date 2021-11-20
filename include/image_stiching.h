#pragma once
#ifndef _IMAGE_STICHING_
#define _IMAGE_STICHING_
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
}four_corners_t;



void show_image(std::string iamge_path);
std::vector<Mat> load_images(std::string file_path);
std::vector<Mat> load_images(std::vector<std::string> &iamge_list);
void features_matcher(std::vector<Mat> iamges);
void image_stiching(vector<string> image_list, int image_nums = 2, int keyPoint_nums = 2000);
#endif
