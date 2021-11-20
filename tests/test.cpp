// void features_matcher(std::vector<Mat> iamges)
// {
//     Ptr<FeaturesFinder> finder;
//     //定义特征寻找器
//     finder = new SurfFeaturesFinder();
//     //应用SURF方法寻找特征
//     //finder = new OrbFeaturesFinder();
//     //应用ORB方法寻找特征
//     std::vector<ImageFeatures> features(num_images);
//     //表示图像特征
//     for (int i = 0; i < num_images; i++)
//     {
//         (*finder)(iamges[i], features[i]);
//     }
//     std::cout << "特征提取完毕" << std::endl;
//      //特征检测
//     std::vector<MatchesInfo> pairwise_matches;
//     //表示特征匹配信息变量
//     BestOf2NearestMatcher matcher(false, 0.35f, 6, 6);
//     //定义特征匹配器，2NN方法
//     matcher(features, pairwise_matches);
//     //进行特征匹配
//     std::cout << "特征匹配完成" << std::endl;
// }