cmake_minimum_required(VERSION 3.0.0)
project(ImageStitching VERSION 0.1.0)

message("Project Name: " ${PROJECT_NAME})
# 设置C/C++标准
# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# set(CMAKE_CXX_STANDARA 17)
# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_COMPILE_FEATURES "g++")

# 64位
# if(CMAKE_SYSTEM_NAME MATCHES "Linux")
#   message(STATUS "Linux platorm!")
# elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
# if(CMAKE_CL_64)
#   message(STATUS "Windows Win64 platform!")
#   else()
#     message(STATUS "Windows Win32 platform!")
#   endif(CMAKE_CL_64)
# elseif(CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
#   message(STATUS "FreeBSD platform!")
# else()
#   message(STATUS "other platform!")
# endif(CMAKE_SYSTEM_NAME MATCHES "Linux")
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	message(STATUS "Linux platorm!")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
	message(STATUS "Windows!")
	if (CMAKE_CL_64)
		# 64位
		# 设置 可执行程序输出目录
		message(STATUS "Windows Win64 platform!")
		# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/debugx64)
		# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/releasex64)
		# Copy DLL files to output directory
		if (CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE EQUAL "None" OR NOT CMAKE_BUILD_TYPE)
    		message(STATUS "CMAKE_BUILD_TYPE is Debug")
			# 设置 可执行程序输出目录
			set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/debugX64)
			# 设置库文件输出目录
			set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/debugX64)
		elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    		message(STATUS "CMAKE_BUILD_TYPE is Release")
			# 设置 可执行程序输出目录
			set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/releaseX64)
			# 设置库文件输出目录
			set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/releaseX64)
		endif(CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE EQUAL "None" OR NOT CMAKE_BUILD_TYPE)
		set(PROJECT_NAME ${PROJECT_NAME}_64)

	else()
		# 32位
		message(STATUS "Windows Win32 platform!")
		# 设置 可执行程序输出目录
		# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/debugX86)
		# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/releaseX86)

		# 设置库文件输出目录
		# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/debugX86)
		# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/releaseX86)
		if (CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE EQUAL "None" OR NOT CMAKE_BUILD_TYPE)
			message(STATUS "CMAKE_BUILD_TYPE is Debug")
			# 设置 可执行程序输出目录
			set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/debugX86)
			# 设置库文件输出目录
			set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/debugX86)
		elseif (CMAKE_BUILD_TYPE MATCHES "Release")
			message(STATUS "CMAKE_BUILD_TYPE is Release")
			# 设置 可执行程序输出目录
			set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/releaseX86)
			# 设置库文件输出目录
			set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/releaseX86)
		endif(CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE EQUAL "None" OR NOT CMAKE_BUILD_TYPE)
		set(PROJECT_NAME ${PROJECT_NAME}_32)

	endif(CMAKE_CL_64)
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

#设置编译参数
set(CMAKE_C_FLAGS "-g -Wall")

#设置执行文件输出目录
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 添加头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)



# 添加库文件路径
# link_directories(${PROJECT_SOURCE_DIR}/3dparty/opencv2/lib)
set(LINK_DIRECTORIES ${PROJECT_SOURCE_DIR}/3rdparty/opencv2/lib)
LINK_DIRECTORIES(${LINK_DIRECTORIES})

set(LINK_CV_LIBS opencv_highgui2413d opencv_core2413d opencv_features2d2413d opencv_nonfree2413d opencv_legacy2413d  opencv_flann2413d opencv_imgproc2413d opencv_calib3d2413d)

set(PROJECT_DLL_Dir ${PROJECT_SOURCE_DIR}/3rdparty/opencv2/dll)
# 递归获取目录下所有的C/C++文件
FILE(GLOB_RECURSE Cpp_files ${PROJECT_SOURCE_DIR}/src/*.cpp)

# 生成执行文件
add_executable(${PROJECT_NAME} ${Cpp_files})

# target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/3rdparty/opencv2/lib)

# target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/3rdparty/opencv2/lib/opencv_highgui2413d.lib ${PROJECT_SOURCE_DIR}/3rdparty/opencv2/lib/opencv_core2413d.lib)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${LINK_CV_LIBS})

# 复制目录下的全部内容
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_DLL_Dir}"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
