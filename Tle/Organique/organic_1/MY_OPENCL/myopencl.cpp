#include "myopencl.hpp"

//----------------- color 
/*#define PRINTF_BLACK \033[0;30m
#define PRINTF_RED \033[0;31m
#define PRINTF_GREEN \033[0;32m
#define PRINTF_YELLOW \033[0;33m
#define  PRINTF_BLUE \033[0;34m
#define  PRINTF_PURPLE \033[0;35m
#define  PRINTF_CYAN \033[0;36m
#define  PRINTF_GREEN \033[0;37m
#define  PRINTF_RESET \033[0m
*/

//-------------------------------------------------------------------------------------------------//
// The followings functions has been move to only-board.gpu/only-board.gpu.cpp 
// because i decided to all opencl conext and relatives function from
//main.cpp and from myopencl.hpp and myopencl.cpp 
//You cannsee their signature in only-board.gpu.hh and they
//definition in only-board.gpu.cpp at the bottom (the utils part)
//------------------------------------------------------------------------------

/*
int loadProgramSource(const char *filename, char **p_source_string, size_t *length)
{
    FILE *file;
    size_t source_length;

    file = fopen(filename, "rb");
    if(file == 0)
    {
        return 1;
    }

    fseek(file, 0, SEEK_END);
    source_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    *p_source_string = (char *)malloc(source_length + 1);
    if(fread(*p_source_string, source_length, 1, file) != 1)
    {
        fclose(file);
        free(*p_source_string);
        return 2;
    }

    fclose(file);
    *length = source_length;
    (*p_source_string)[source_length] = '\0';

    return 0;
}


void load_many_cl_files(const char **all_files){
    
}




int get_OpenclDevicesInfos(int chosen_device_number) {

    int i, j;
    char* value;
    size_t valueSize;
    cl_uint platformCount;
    cl_platform_id* platforms;
    cl_uint deviceCount;
    cl_device_id* devices;
    cl_uint maxComputeUnits;
    cl_ulong maxComputeUnitslong;
    cl_device_type dt;

    // get all platforms
    clGetPlatformIDs(0, NULL, &platformCount);
    platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
    clGetPlatformIDs(platformCount, platforms, NULL);

    for (i = 0; i < platformCount; i++) {

        // get all devices
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
        devices = (cl_device_id*) malloc(sizeof(cl_device_id) * deviceCount);
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

        // for each device print critical attributes
        for (j = 0; j < deviceCount; j++) {
            printf("\n|->  ");
            // print device name
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
            chosen_device_number == j ? printf("%d. Device: %s \t\t [You choose this device]\n", j+1, value) : printf("%d. Device: %s\n", j+1, value);
            free(value);

            // print hardware device version
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
            printf("\t %d.%d Hardware version: %s\n", j+1, 1, value);
            free(value);

            // print software driver version
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL);
            printf("\t %d.%d Software version: %s\n", j+1, 2, value);
            free(value);

            // print c version supported by compiler for device
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
            printf("\t %d.%d OpenCL C version: %s\n", j+1, 3, value);
            free(value);

            // print parallel compute units
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS,
                    sizeof(maxComputeUnits), &maxComputeUnits, NULL);
            printf("\t %d.%d Parallel compute units: %d\n", j+1, 4, maxComputeUnits);

            // print devices clock frequency
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY,
                    sizeof(maxComputeUnits), &maxComputeUnits, NULL);
            printf("\t %d.%d print devices clock frequency: %d\n", j+1, 5, maxComputeUnits);

            // print global mem size
            clGetDeviceInfo(devices[j], CL_DEVICE_GLOBAL_MEM_SIZE,
                    sizeof(cl_ulong), &maxComputeUnitslong, NULL);
            printf("\t %d.%d print devices global mem size: %llu\n", j+1, 6, maxComputeUnitslong);

            // print local mem size
            clGetDeviceInfo(devices[j], CL_DEVICE_LOCAL_MEM_SIZE,
                    sizeof(cl_ulong), &maxComputeUnitslong, NULL);
            printf("\t %d.%d print devices local mem size: %llu\n", j+1, 7, maxComputeUnitslong);

            // print device type
            clGetDeviceInfo(devices[j], CL_DEVICE_TYPE,
                    sizeof(cl_device_type), &dt, NULL);
            printf("\t %d %d %39s:%s%s%s%s\n", j+1, 8, "CL_DEVICE_TYPE",
			       dt & CL_DEVICE_TYPE_CPU ? " CPU" : "",
			       dt & CL_DEVICE_TYPE_GPU ? " GPU" : "",
			       dt & CL_DEVICE_TYPE_ACCELERATOR ? " ACCELERATOR" : "",
			       dt & CL_DEVICE_TYPE_DEFAULT ? " DEFAULT" : "");
            
            // printd Devices max work items dimensions
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
                    sizeof(maxComputeUnits), &maxComputeUnits, NULL);
            printf("\t %d.%d Devices max work items dimensions: %d\n", j+1, 9, maxComputeUnits);

            // print device max work item size
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_SIZES, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_SIZES, valueSize, value, NULL);
            printf("\t %d.%d device max work item size: %s\n", j+1, 10, value);
            free(value);

            // printd Devices adresse bits
            clGetDeviceInfo(devices[j], CL_DEVICE_ADDRESS_BITS,
                    sizeof(maxComputeUnits), &maxComputeUnits, NULL);
            printf("\t %d.%d Devices adresse bits: %d\n", j+1, 11, maxComputeUnits);

            // printd Devices Max work group size
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE,
                    sizeof(maxComputeUnits), &maxComputeUnits, NULL);
            printf("\t %d.%d Devices  Max work group size: %d\n", j+1, 12, maxComputeUnits);


        }

        free(devices);

    }
    printf("---------------------------------------------\n");
    free(platforms);
    return 0;

}


int get_OpenclPlatformsInfos() {

    int i, j;
    char* info;
    size_t infoSize;
    cl_uint platformCount;
    cl_platform_id *platforms;
    const char* attributeNames[5] = { "Name", "Vendor",
        "Version", "Profile", "Extensions" };
    const cl_platform_info attributeTypes[5] = { CL_PLATFORM_NAME, CL_PLATFORM_VENDOR,
        CL_PLATFORM_VERSION, CL_PLATFORM_PROFILE, CL_PLATFORM_EXTENSIONS };
    const int attributeCount = sizeof(attributeNames) / sizeof(char*);

    // get platform count
    clGetPlatformIDs(5, NULL, &platformCount);

    // get all platforms
    platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
    clGetPlatformIDs(platformCount, platforms, NULL);

    // for each platform print all attributes
    for (i = 0; i < platformCount; i++) {

        printf("\n %d. Platform \n", i+1);

        for (j = 0; j < attributeCount; j++) {

            // get platform attribute value size
            clGetPlatformInfo(platforms[i], attributeTypes[j], 0, NULL, &infoSize);
            info = (char*) malloc(infoSize);

            // get platform attribute value
            clGetPlatformInfo(platforms[i], attributeTypes[j], infoSize, info, NULL);

            printf("  %d.%d %-11s: %s\n", i+1, j+1, attributeNames[j], info);
            free(info);

        }

        printf("\n");

    }

    free(platforms);
    printf("---------------------------------------------\n");
    return 0;

}

//-------------------------- OPENCL ERROR_CODE ----------------------------
const char *getErrorString(cl_int error)
{
switch(error){
    // run-time and JIT compiler errors
    case 0: return "CL_SUCCESS";
    case -1: return "CL_DEVICE_NOT_FOUND";
    case -2: return "CL_DEVICE_NOT_AVAILABLE";
    case -3: return "CL_COMPILER_NOT_AVAILABLE";
    case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case -5: return "CL_OUT_OF_RESOURCES";
    case -6: return "CL_OUT_OF_HOST_MEMORY";
    case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case -8: return "CL_MEM_COPY_OVERLAP";
    case -9: return "CL_IMAGE_FORMAT_MISMATCH";
    case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case -11: return "CL_BUILD_PROGRAM_FAILURE";
    case -12: return "CL_MAP_FAILURE";
    case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case -15: return "CL_COMPILE_PROGRAM_FAILURE";
    case -16: return "CL_LINKER_NOT_AVAILABLE";
    case -17: return "CL_LINK_PROGRAM_FAILURE";
    case -18: return "CL_DEVICE_PARTITION_FAILED";
    case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

    // compile-time errors
    case -30: return "CL_INVALID_VALUE";
    case -31: return "CL_INVALID_DEVICE_TYPE";
    case -32: return "CL_INVALID_PLATFORM";
    case -33: return "CL_INVALID_DEVICE";
    case -34: return "CL_INVALID_CONTEXT";
    case -35: return "CL_INVALID_QUEUE_PROPERTIES";
    case -36: return "CL_INVALID_COMMAND_QUEUE";
    case -37: return "CL_INVALID_HOST_PTR";
    case -38: return "CL_INVALID_MEM_OBJECT";
    case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case -40: return "CL_INVALID_IMAGE_SIZE";
    case -41: return "CL_INVALID_SAMPLER";
    case -42: return "CL_INVALID_BINARY";
    case -43: return "CL_INVALID_BUILD_OPTIONS";
    case -44: return "CL_INVALID_PROGRAM";
    case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
    case -46: return "CL_INVALID_KERNEL_NAME";
    case -47: return "CL_INVALID_KERNEL_DEFINITION";
    case -48: return "CL_INVALID_KERNEL";
    case -49: return "CL_INVALID_ARG_INDEX";
    case -50: return "CL_INVALID_ARG_VALUE";
    case -51: return "CL_INVALID_ARG_SIZE";
    case -52: return "CL_INVALID_KERNEL_ARGS";
    case -53: return "CL_INVALID_WORK_DIMENSION";
    case -54: return "CL_INVALID_WORK_GROUP_SIZE";
    case -55: return "CL_INVALID_WORK_ITEM_SIZE";
    case -56: return "CL_INVALID_GLOBAL_OFFSET";
    case -57: return "CL_INVALID_EVENT_WAIT_LIST";
    case -58: return "CL_INVALID_EVENT";
    case -59: return "CL_INVALID_OPERATION";
    case -60: return "CL_INVALID_GL_OBJECT";
    case -61: return "CL_INVALID_BUFFER_SIZE";
    case -62: return "CL_INVALID_MIP_LEVEL";
    case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
    case -64: return "CL_INVALID_PROPERTY";
    case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
    case -66: return "CL_INVALID_COMPILER_OPTIONS";
    case -67: return "CL_INVALID_LINKER_OPTIONS";
    case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

    // extension errors
    case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
    default: return "Unknown OpenCL error";
    }
}
*/
