#include <iostream>
#include <fstream>
#include "image_stiching.h"
#include "utils.h"

void show_image(string image_path)
{
    if (is_file_exists(image_path))
    {
        Mat image = imread(image_path, 1);
        imshow("image", image);
        waitKey(0);
    }
    else
    {
        std::cout << "the input image is not exist." << std::endl;
    }
}

void show_image(string title, Mat img_data)
{
    imshow(title, img_data);
    waitKey(0);
    // destroyWindow(title);
}

// vector<Mat> load_images(string file_path)
// {
//     //输入txt文件，文件中记录图片路径
//     // std::vector<std::string> &images_path={};
//     // read_txt(file_path, images_path);
//     vector<Mat> images;
//     std::ifstream infile;
//     infile.open(file_path.data());
//     //将文件流对象与文件连接起来
//     assert(infile.is_open());
//     //若失败,则输出错误消息,并终止程序运行
//     std::string image;
//     std::cout << "the input image are:" << std::endl;
//     while (getline(infile, image))
//     {
//         std::cout << image << "\t";
//         Mat img = imread(image);
//         images.push_back(img);
//     }
//     infile.close();
//     //关闭文件输入流
//     std::cout << std::endl;
//     std::cout << "加载图像完成" << std::endl;
//     return images;
// }

void load_images(vector<string> &image_list, vector<Mat> &images)
{
    // 输入字符串数组
    // vector<Mat> images;
    // std::cout << "the input image are:" << std::endl;
    // for (auto image : image_list)
    // {
    //     std::cout << image << "\t";

    //     Mat img = imread(image);
    //     images.push_back(img);
    // }
    // return images;

    for (size_t i = 0; i < image_list.size(); i++)
    {
        images[i] = imread(image_list[i]);
    }
}

Mat grayscale_convert(Mat &image)
{
    //灰度转换
    Mat gray_image;
    cvtColor(image, gray_image, CV_RGB2GRAY);
    return gray_image;
}

vector<KeyPoint> extract_keyPoint(Mat &image, int keyPoint_nums)
{
    //提取特征点
    SurfFeatureDetector Detector(keyPoint_nums);
    vector<KeyPoint> key_point;
    Detector.detect(image, key_point);
    return key_point;
}

Mat keyPoint_descriptor(Mat &image, vector<KeyPoint> &Key_point)
{
    //特征点描述，为下边的特征点匹配做准备
    SurfDescriptorExtractor Descriptor;
    Mat image_desc;
    Descriptor.compute(image, Key_point, image_desc);
    return image_desc;
}

vector<vector<Point2f>> keyPoint_match(vector<Mat> &image_desc, vector<Mat> &images, vector<vector<KeyPoint>> &Key_point)
{
    FlannBasedMatcher matcher;
    vector<vector<DMatch>> matchePoints;
    vector<DMatch> GoodMatchePoints;

    vector<Mat> train_desc(1, image_desc[0]);
    matcher.add(train_desc);
    matcher.train();

    matcher.knnMatch(image_desc[1], matchePoints, 2);
    std::cout << "total match points: " << matchePoints.size() << std::endl;

    // Lowe's algorithm,获取优秀匹配点
    for (int i = 0; i < matchePoints.size(); i++)
    {
        if (matchePoints[i][0].distance < 0.4 * matchePoints[i][1].distance)
        {
            GoodMatchePoints.push_back(matchePoints[i][0]);
        }
    }

    Mat first_match;
    drawMatches(images[1], Key_point[1], images[0], Key_point[0], GoodMatchePoints, first_match);
    // show_image("first_match ", first_match);
    imwrite("first_match.jpg", first_match);

    vector<vector<Point2f>> image_points(2);
    for (size_t i = 0; i < GoodMatchePoints.size(); i++)
    {

        image_points[0].push_back(Key_point[0][GoodMatchePoints[i].trainIdx].pt);
        image_points[1].push_back(Key_point[1][GoodMatchePoints[i].queryIdx].pt);
    }
    return image_points;
}

four_corners_t calc_corners(const Mat &H, const Mat &src)
{
    four_corners_t corners;
    double v2[] = {0, 0, 1};          //左上角
    double v1[3];                     //变换后的坐标值
    Mat V2 = Mat(3, 1, CV_64FC1, v2); //列向量
    Mat V1 = Mat(3, 1, CV_64FC1, v1); //列向量

    V1 = H * V2;
    //左上角(0,0,1)
    std::cout << "V2: " << V2 << std::endl;
    std::cout << "V1: " << V1 << std::endl;
    corners.left_top.x = v1[0] / v1[2];
    corners.left_top.y = v1[1] / v1[2];

    //左下角(0,src.rows,1)
    v2[0] = 0;
    v2[1] = src.rows;
    v2[2] = 1;
    V2 = Mat(3, 1, CV_64FC1, v2);
    //列向量
    V1 = Mat(3, 1, CV_64FC1, v1);
    //列向量
    V1 = H * V2;
    corners.left_bottom.x = v1[0] / v1[2];
    corners.left_bottom.y = v1[1] / v1[2];

    //右上角(src.cols,0,1)
    v2[0] = src.cols;
    v2[1] = 0;
    v2[2] = 1;
    V2 = Mat(3, 1, CV_64FC1, v2);
    //列向量
    V1 = Mat(3, 1, CV_64FC1, v1);
    //列向量
    V1 = H * V2;
    corners.right_top.x = v1[0] / v1[2];
    corners.right_top.y = v1[1] / v1[2];

    //右下角(src.cols,src.rows,1)
    v2[0] = src.cols;
    v2[1] = src.rows;
    v2[2] = 1;
    V2 = Mat(3, 1, CV_64FC1, v2);
    //列向量
    V1 = Mat(3, 1, CV_64FC1, v1);
    //列向量
    V1 = H * V2;
    corners.right_bottom.x = v1[0] / v1[2];
    corners.right_bottom.y = v1[1] / v1[2];

    return corners;
}

vector<Mat> image_match(vector<vector<Point2f>> &image_points, vector<Mat> images, four_corners_t &corners)
{
    //获取图像1到图像2的投影映射矩阵 尺寸为3*3
    Mat homo = findHomography(image_points[0], image_points[1], CV_RANSAC);
    //也可以使用getPerspectiveTransform方法获得透视变换矩阵，不过要求只能有4个点，效果稍差
    //Mat homo=getPerspectiveTransform(imagePoints1,imagePoints2);
    std::cout << "The transformation matrix is: " << std::endl;
    std::cout << homo << std::endl;
    //输出映射矩阵

    //计算配准图的四个顶点坐标
    corners = calc_corners(homo, images[0]);
    std::cout << "left_top: " << corners.left_top << std::endl;
    std::cout << "left_bottom: " << corners.left_bottom << std::endl;
    std::cout << "right_top: " << corners.right_top << std::endl;
    std::cout << "right_bottom: " << corners.right_bottom << std::endl;

    //图像配准
    Mat image_transform;
    warpPerspective(images[0], image_transform, homo, Size(MAX(corners.right_top.x, corners.right_bottom.x), images[1].rows));
    //warpPerspective(image01, imageTransform2, adjustMat*homo, Size(image02.cols*1.3, image02.rows*1.8));
    // show_image("Directly through the perspective matrix transformation", image_transform);
    // imwrite("image_transform.jpg", image_transform);

    //创建拼接后的图,需提前计算图的大小
    int dst_width = image_transform.cols;
    //取最右点的长度为拼接图的长度
    int dst_height = images[1].rows;
    Mat dst(dst_height, dst_width, CV_8UC3);
    dst.setTo(0);

    image_transform.copyTo(dst(Rect(0, 0, image_transform.cols, image_transform.rows)));
    images[1].copyTo(dst(Rect(0, 0, images[1].cols, images[1].rows)));
    // show_image("before_opt_dst", dst);
    // imwrite("before_opt_dst.jpg", dst);
    vector<Mat> match_res = {image_transform, dst};
    return match_res;
}

//优化两图的连接处，使得拼接自然
void optimize_seam(Mat &images, Mat &trans, Mat &dst, four_corners_t &corners)
{

    int start = MIN(corners.left_top.x, corners.left_bottom.x);
    //开始位置，即重叠区域的左边界

    double processWidth = images.cols - start;
    //重叠区域的宽度
    int rows = dst.rows;
    int cols = images.cols;
    //注意，是列数*通道数
    double alpha = 1;
    //images中像素的权重
    for (int i = 0; i < rows; i++)
    {
        uchar *p = images.ptr<uchar>(i);
        //获取第i行的首地址
        uchar *t = trans.ptr<uchar>(i);
        uchar *d = dst.ptr<uchar>(i);
        for (int j = start; j < cols; j++)
        {
            //如果遇到图像trans中无像素的黑点，则完全拷贝img1中的数据
            if (t[j * 3] == 0 && t[j * 3 + 1] == 0 && t[j * 3 + 2] == 0)
            {
                alpha = 1;
            }
            else
            {
                //img1中像素的权重，与当前处理点距重叠区域左边界的距离成正比，实验证明，这种方法确实好
                alpha = (processWidth - (j - start)) / processWidth;
            }

            d[j * 3] = p[j * 3] * alpha + t[j * 3] * (1 - alpha);
            d[j * 3 + 1] = p[j * 3 + 1] * alpha + t[j * 3 + 1] * (1 - alpha);
            d[j * 3 + 2] = p[j * 3 + 2] * alpha + t[j * 3 + 2] * (1 - alpha);
        }
    }
}

void image_stiching(vector<string> image_list, int image_nums, int keyPoint_nums)
{
    vector<Mat> images(image_nums);
    load_images(image_list, images);

    vector<Mat> gray_image(image_nums);

    vector<vector<KeyPoint>> Key_point(image_nums);

    vector<Mat> image_desc(image_nums);

    for (size_t i = 0; i < image_nums; i++)
    {
        show_image("input_image", images[i]);
        gray_image[i] = grayscale_convert(images[i]);
        Key_point[i] = extract_keyPoint(gray_image[i], keyPoint_nums);
        image_desc[i] = keyPoint_descriptor(gray_image[i], Key_point[i]);
    }
    vector<vector<Point2f>> image_points = keyPoint_match(image_desc, images, Key_point);
    four_corners_t corners;
    vector<Mat> match_res = image_match(image_points, images, corners);

    show_image("Directly through the perspective matrix transformation", match_res[0]);
    imwrite("image_transform.jpg", match_res[0]);

    show_image("before_opt_dst", match_res[1]);
    imwrite("before_opt_dst.jpg", match_res[1]);

    optimize_seam(images[1], match_res[0], match_res[1], corners);

    show_image("after_opt_dst", match_res[1]);
    imwrite("after_opt_dst.jpg", match_res[1]);
}