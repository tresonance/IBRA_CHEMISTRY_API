#ifndef __MYOPENCL_HPP__
#define __MYOPENCL_HPP__

#define CL_SILENCE_DEPRECATION
#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#if defined(__APPLE__) || defined(__MACOSX)
    #include <OpenCL/cl.h>
#else
    #include <CL/cl.h>
#endif



#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

//----------------- color 
#define PRINTF_BLACK \033[0;30m
#define PRINTF_RED \033[0;31m
#define PRINTF_GREEN \033[0;32m
#define PRINTF_YELLOW \033[0;33m
#define  PRINTF_BLUE \033[0;34m
#define  PRINTF_PURPLE \033[0;35m
#define  PRINTF_CYAN \033[0;36m
#define  PRINTF_WHITE \033[0;37m
#define  PRINTF_RESET \033[0m


// ----- window
//#define WIDTH 1472
//#define HEIGHT 960

#define  TOTAL_CL_FILES 3
#define CHOSEN_DEVICE 1  // 0 = CPU , 1 = GPU
#define OPENCL_DIMENSION 1

#define LOCAL_SIZE 256
//#define DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE (256 * WIDTH * 4) //this number must be divide by local=256
#define KERNEL_VECTOR_SIZE 524288

//#define ARRAY_MAX_SIZE (KERNEL_VECTOR_SIZE % LOCAL_SIZE ? (1 + (KERNEL_VECTOR_SIZE / LOCAL_SIZE))*LOCAL_SIZE : KERNEL_VECTOR_SIZE )
#define ARRAY_MAX_SIZE 8



int loadProgramSource(const char *filename, char **p_source_string, size_t *length);
int get_OpenclDevicesInfos(int chosen_device_number);
int get_OpenclPlatformsInfos();
const char *getErrorString(cl_int error);
void load_many_cl_files(const char *all_cl_files[]);


#endif