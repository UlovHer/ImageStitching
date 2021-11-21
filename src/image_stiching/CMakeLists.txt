# INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src/utils LIB_SRCS)
AUX_SOURCE_DIRECTORY(. LIB_SRCS)
# 添加当前目录下所有的源文件
# LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdparty/opencv2/lib/x64)
# set(LINK_CV_LIBS opencv_highgui2413 opencv_core2413 opencv_features2d2413 opencv_nonfree2413 opencv_legacy2413  opencv_flann2413 opencv_imgproc2413 opencv_calib3d2413)

#生成动态库  静态库则 STATIC
ADD_LIBRARY(image_stiching SHARED ${LIB_SRCS})
#静态库不能写为image_stiching，否则会被动态库覆盖
ADD_LIBRARY(libimage_stiching STATIC ${LIB_SRCS})


#给静态库重命名为image_stiching，最后会生成libimage_stiching
# SET_TARGET_PROPERTIES(image_stiching PROPERTIES OUTPUT_NAME "image_stiching")

# VERSION指代动态库版本，SOVERSION指代API版本。
SET_TARGET_PROPERTIES (image_stiching PROPERTIES VERSION 1.2 SOVERSION 1)
SET_TARGET_PROPERTIES (libimage_stiching PROPERTIES VERSION 1.2 SOVERSION 1)

# 指定链接库输出路径
# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# Debug库带“d”后缀
set_target_properties(image_stiching PROPERTIES DEBUG_POSTFIX d)
TARGET_LINK_LIBRARIES(image_stiching PUBLIC ${LINK_CV_LIBS})
TARGET_LINK_LIBRARIES(libimage_stiching PUBLIC ${LINK_CV_LIBS})
# 安装库文件
# INSTALL(TARGETS image_stiching libimage_stiching
# 	LIBRARY DESTINATION lib
# 	ARCHIVE DESTINATION lib)

# 安装头文件
# INSTALL(FILES ${PROJECT_SOURCE_DIR}/include/image_stiching.h DESTINATION include)
# INSTALL(FILES ${PROJECT_SOURCE_DIR}/include/image_stiching.h DESTINATION ${PROJECT_SOURCE_DIR}/lib/include)
# file(COPY ${PROJECT_SOURCE_DIR}/include/image_stiching.h DESTINATION ${PROJECT_SOURCE_DIR}/lib/include)