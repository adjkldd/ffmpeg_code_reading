# this file should be placed in directory ffmpeg_clion/
cmake_minimum_required(VERSION 2.8)

project(ffmpeg C)

include_directories(..)
include_directories(../libav)

aux_source_directory(../libav libav_SRC)

add_library(av ${libav_SRC})

set(COMMON_SRC ../rmenc.c ../mpegmux.c ../asfenc.c ../jpegenc.c ../swfenc.c ../udp.c ../formats.c ../grab.c)

add_executable(ffmpeg ../ffmpeg.c ${COMMON_SRC})
target_link_libraries(ffmpeg av m)

add_executable(ffserver ../ffserver.c ${COMMON_SRC})
target_link_libraries(ffserver av pthread m)

