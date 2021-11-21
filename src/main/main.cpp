#include <iostream>
#include <string>
#include <cstdlib>
#include "image_stiching.h"
#include "utils.h"

int main(int argc, char const *argv[])
{
    std::cout << "**********************************" << std::endl;
    std::cout << "********Stitch Two Images********" << std::endl;
    std::cout << "The input params are two images path,such as:" << std::endl;
    std::cout << "ImageStitching.exe test1.jpg test2.jpg" << std::endl;
    std::cout << "**********************************" << std::endl;

    // string img_path = "./resouce/test.jpg";
    // show_image(img_path);
    // std::string file_path = "./resouce/test.txt";
    // read_txt(file_path,images_list);
    // std::vector<Mat> img = load_images(file_path);
    std::vector<std::string> images_list;
    for (size_t i = 1; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
        images_list.push_back(argv[i]);
    }

    image_stiching(images_list);

    // system("pause");

    return 0;
}
