#include "utils.h"
#include <sys/stat.h>
#include <fstream>
#include <cassert>
#include <iostream>


bool is_file_exists(std::string &name) {
  struct stat buffer;   
  return (stat(name.c_str(), &buffer) == 0); 
}


void read_txt(std::string file_path,std::vector<std::string> &images_list)
{
    std::ifstream infile; 
    infile.open(file_path.data());   
    //将文件流对象与文件连接起来 
    assert(infile.is_open());   
    //若失败,则输出错误消息,并终止程序运行 
    std::string image;
    std::cout<<"The input image are:"<<std::endl;
    while(getline(infile,image))
    {
        std::cout<<image<<"\t";
        images_list.push_back(image);
    }
    infile.close();  
    //关闭文件输入流
    std::cout<<std::endl;            
}

