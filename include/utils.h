#pragma once 
#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>

bool is_file_exists(std::string &name);
void read_txt(std::string file_path,std::vector<std::string> &images_list);
#endif