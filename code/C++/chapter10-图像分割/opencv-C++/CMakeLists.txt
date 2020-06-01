# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(chapter08 LANGUAGES CXX)

#dubug 模式
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

set(OpenCV_DIR "/usr/local/share/OpenCV") 

#这是cmake用来查找opencv包用的，不用改  
FIND_PACKAGE( OpenCV REQUIRED )   
 
add_executable(project01 ch8_ex8_2.cpp)
add_executable(project02 ch8_ex8_3.cpp)

#这是我们链接到OpenCV库的环节，
#我们只要更改前面第一个参数位我们的工程项目名即可
TARGET_LINK_LIBRARIES(project01 ${OpenCV_LIBS})  
TARGET_LINK_LIBRARIES(project02 ${OpenCV_LIBS})  