# The following lines of boilerplate have to be in your project's CMakeLists 
# in this exact order for cmake to work correctly

cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(real_time_stats)


# Source Configuration

idf_component_register(
	SRCS 
		"Core/main.c" 
		"Core/Rtos/freertos.c"
		"Core/System/utils.c"
	INCLUDE_DIRS
		"."
		"Core/System" 
		"Middlewares/FreeRTOS/Source/CMSIS_RTOS_V2"
)
