#include <iostream>
#include <string>
#include <cstdlib>
#include "image_stiching.h"


using namespace std;
int main(int, char**) {
    std::cout << "Hello, world!\n";
    string img_path = "E:/VSCodeWorkSpace/ImageStitching/resouce/test.jpg";
    show_image(img_path);
    system("pause");
}
