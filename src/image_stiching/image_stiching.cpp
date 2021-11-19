#include <iostream>  
#include "image_stiching.h"
#include "utils.h"


void show_image(std::string img_path)
{   if (is_file_exists(img_path))
    {
    std::cout<<"the input image is exist."<<std::endl;
	Mat image = imread(img_path, 1);
    imshow("image", image);
}
else
{
	std::cout<<"the input image is not exist."<<std::endl;
}

    
}