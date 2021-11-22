cmake_minimum_required(VERSION 3.0.0)
project(ImageStitching VERSION 0.1.0)

message("Project Name: " ${PROJECT_NAME})

# 设置C/C++标准
# 显式要求指明支持C标准
set(CMAKE_C_STANDARD_REQUIRED True)
# 启动对C11标准的支持
set(CMAKE_C_STANDARD 11)
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
# set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c99")
# 设置指定的C++编译器版本是必须的，
# 如果不设置，则指定版本不可用时，会使用上一版本。
set(CMAKE_CXX_STANDARD_REQUIRED True)
# 指定为C++11 版本
set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARA 14)
# set(CMAKE_CXX_STANDARA 17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# 操作系统
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "Linux platorm!")
	# 设置编译器选项
	set(CMAKE_C_COMPILER "gcc -g -Wall")
    set(CMAKE_CXX_COMPILER "g++ -g -Wall")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--whole-archive") 
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "Windows platorm!")
	SET(CMAKE_CXX_COMPILER "D:/Msys2/mingw64/bin/g++") 
	SET(CMAKE_C_COMPILER "D:/Msys2/mingw64/bin/gcc") 
	# set(CMAKE_CXX_COMPILER "Visual Studio 14 2015")
	# set(CMAKE_CXX_COMPILER "Visual Studio 15 2017")
	# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /WHOLEARCHIVE")
	# 设置MT/MTD
	# set(CMAKE_C_FLAGS_RELEASE "/MT")
    # set(CMAKE_C_FLAGS_DEBUG "/MTd")
	# set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    # set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
	# if (MSVC)
    # set(CompilerFlags
    #     CMAKE_CXX_FLAGS
    #     CMAKE_CXX_FLAGS_DEBUG
    #     CMAKE_CXX_FLAGS_RELEASE
    #     CMAKE_C_FLAGS
    #     CMAKE_C_FLAGS_DEBUG
    #     CMAKE_C_FLAGS_RELEASE
    #     )
    # foreach(CompilerFlag ${CompilerFlags})
    #     string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    # endforeach()
# endif(MSVC)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "Darwin platorm!")
elseif(CMAKE_SYSTEM_NAME MATCHES "Android")
    message(STATUS "Android platorm!")
endif()


# # 取消CMake默认生成的工程选项，仅保留Debug与Release（只对msvc这样的多样化构建ide有效）
# if(CMAKE_CONFIGURATION_TYPES)
#     set(CMAKE_CONFIGURATION_TYPES Debug Release)
#     set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
#         "Reset the configurations to what we need"
#         FORCE)
# endif()

# 64/32位
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "64bit platform")
	# 设置 可执行程序输出目录
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/x64)
	# 设置库文件输出目录
	set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/x64)
	# 添加库文件路径
	set(LINK_DIRECTORIES ${PROJECT_SOURCE_DIR}/3rdparty/opencv2/lib/x64)
	set(PROJECT_DLL_Dir ${PROJECT_SOURCE_DIR}/3rdparty/opencv2/dll/x64)	
else()
    message(STATUS "32bit platform")
	# 设置可执行程序输出目录
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/x86)
	# 设置库文件输出目录
	set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/x86)
	# 添加库文件路径
	set(LINK_DIRECTORIES ${PROJECT_SOURCE_DIR}/3rdparty/opencv2/lib/x86)
	set(PROJECT_DLL_Dir ${PROJECT_SOURCE_DIR}/3rdparty/opencv2/dll/x86)
endif()

# 设置Release/Debug选项
set(CMAKE_BUILD_TYPE Release)
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    message(STATUS "MAKE_BUILD_TYPE is Debug")
	# 设置可执行程序输出目录
	# set(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/debug)
	# 设置库文件输出目录
	# set(LIBRARY_OUTPUT_PATH ${LIBRARY_OUTPUT_PATH}/debug)
	set(LINK_CV_LIBS opencv_highgui2413d opencv_core2413d opencv_features2d2413d opencv_nonfree2413d opencv_legacy2413d  opencv_flann2413d opencv_imgproc2413d opencv_calib3d2413d)
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    message(STATUS "CMAKE_BUILD_TYPE is Release")
	# set(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/release)
	# set(LIBRARY_OUTPUT_PATH ${LIBRARY_OUTPUT_PATH}/release)
	set(LINK_CV_LIBS opencv_highgui2413 opencv_core2413 opencv_features2d2413 opencv_nonfree2413 opencv_legacy2413  opencv_flann2413 opencv_imgproc2413 opencv_calib3d2413)
elseif (CMAKE_BUILD_TYPE MATCHES "RelWitchDebInfo")
    message(STATUS "CMAKE_BUILD_TYPE is RelWitchDebInfo")
elseif (CMAKE_BUILD_TYPE MATCHES "MinSizeRel")
    message(STATUS " CMAKE_BUILD_TYPE is MinSizeRel")
else ()
    message(STATUS "unknown CMAKE_BUILD_TYPE = " ${CMAKE_BUILD_TYPE})
endif ()

# 添加头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 添加库文件路径
LINK_DIRECTORIES(${LINK_DIRECTORIES})

# 添加参与编译的子目录 
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/src/image_stiching)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/src/utils)

# 递归获取目录下所有的C/C++文件,编译main
FILE(GLOB_RECURSE Cpp_files ${PROJECT_SOURCE_DIR}/src/*.cpp)
# 生成执行文件
add_executable(${PROJECT_NAME} ${Cpp_files})

# 链接库文件
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${LINK_CV_LIBS})

# 复制目录下的全部动态库文件
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_DLL_Dir}"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)


