#include <iostream>
#include <string>
#include <cstdlib>
#include "image_stiching.h"
#include "utils.h"

int main(int argc, char const *argv[])
{
    std::cout << "**********************************"<<std::endl;
    std::cout << "********Stitch Two Images********"<<std::endl;
    std::cout << "The input params are two images path,such as:"<<std::endl;
    std::cout << "ImageStitching.exe test1.jpg test2.jpg"<<std::endl;
    std::cout << "**********************************"<<std::endl;
    // string img_path = "E:/VSCodeWorkSpace/ImageStitching/resouce/test.jpg";
    // show_image(img_path);
    std::string file_path = "E:/VSCodeWorkSpace/ImageStitching/resouce/test.txt";
    // std::vector<Mat> img = load_images(file_path);
    std::vector<std::string> images_list;
    read_txt(file_path,images_list);
    image_stiching(images_list);
    
    // system("pause");

    return 0;
}

