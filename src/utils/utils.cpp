#include "utils.h"
#include <sys/stat.h>

bool is_file_exists(std::string& name) {
  struct stat buffer;   
  return (stat(name.c_str(), &buffer) == 0); 
}