//Include board 
#include "../ONLY_BOARD/board-gpu.hpp"
#include "../ONLY_BOARD/board-gpu-kernels.hpp"


//include opencl 
//include external 
#ifndef  DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE 
    #define DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE (256 * WIDTH * HEIGHT * 4) //this number must be divide by local=256
#endif
#include "../MY_OPENCL/myopencl.hpp"
#include "./geometry.hpp"

//include library 
#include <cstdio>
#include <string>
#include <thread>
#include <pthread.h>

//SOUND FILES
/*const char *MP3_FILES[] =  {
    //"/Users/whodunit/Downloads/ambientloop-30657.mp3"
     "/Volumes/Disk E/MP3_FILES/bluetreeaudio_preview.mp3",
    "/Volumes/Disk E/MP3_FILES/ambientloop-30657.mp3"
};*/

#define EXTERN_TOTAL_PLOT_POINTS_NUMBERS  1000

//----------------------------------------- SET PARSSER ------------------------------------------------//


//------------------------------------------------------------------------------------------------------//


int main(){
    int ext_index = -1;
    float distanceCumul = 0;
    sf::Vector2f cursorPos;
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "MATHS PHYSIC CODE - MATH-BOARD", sf::Style::Close | sf::Style::Resize);

    window->setFramerateLimit(WINDOW_FRAME_LIMIT_100);
    window->setVerticalSyncEnabled(true);
   

    //-------- architecture info -------------//
    OpenclPlatformsInfos();
    OpenclDevicesInfos();
    //----------------------------------------//



    //-------------- EXTERN -------------------//
    sf::Sprite frame_sprite;

    //-------------------------------------------//

    cl_uint platformCount;
    cl_platform_id* platforms;
    cl_uint deviceCount;
    cl_device_id* devices;
    cl_int err;
    cl_int err1;
    cl_int err2;
    cl_int err3;
    cl_int err4;
    cl_int err5;
    cl_int err6;
    cl_int err7;
    cl_int err8;
    cl_int err9;
    cl_context context;  
    cl_command_queue commands;          // compute command queue
    cl_program program;                 // compute program
    cl_kernel kernel; 
    cl_kernel kernel_coordinates; 
    
    size_t global;                      // global domain size for our calculation
    size_t local;                       // local domain size for our calculation

    // Set NDRange dimensions
    size_t dim = OPENCL_DIMENSION;
    int gpu = (int)CHOSEN_DEVICE;

    size_t global_offset[dim] ;
    size_t global_size[dim];
    size_t local_size[dim];
   
   if ( 1 == dim ){

        global_offset[0] =  0;
        global_size[0] = KERNEL_VECTOR_SIZE;  //board-gpu-kernels.hpp
        local_size[0] = 1;
   }
   else if (2 == dim) {

        global_offset[0] =  0;
        global_offset[1] =  0;

        global_size[0] =  1 ;
        global_size[1] =   1 ;

        local_size[0] =  1;
        local_size[1] = 1;

   } else if (3 == dim) {

        global_offset[0] =  0;
        global_offset[1] =  0;
        global_offset[2] =  0;
        

        global_size[0] =  1;
        global_size[1] =  1;
        global_size[2] =  1;

        local_size[0] =  1;
        local_size[1] =  1;
        local_size[2] =  1;

   } else {

       printf("\n\n[ERROR] : dimension must be  1, 2 or 3\n");
       printf("exit(1);");
       exit(1);

   }
                  
    //OPENCL CL FILES
    /* cl kernel */
    const char *kernel_file[TOTAL_CL_FILES] = {"../ONLY_BOARD/board-gpu-kernels.cl", "../MY_OPENCL/myopencl_auxilary.cl", "../MY_OPENCL/myopencl_kernels.cl" };

   //const char *all_cl_files[] = {"kernels.cl", "auxilary.cl" };
    char *kernel_source_string[TOTAL_CL_FILES] = {NULL, NULL, NULL};

    //load_many_cl_files(all_cl_files);
    size_t kernel_length[TOTAL_CL_FILES];


    // get all platforms
    clGetPlatformIDs(0, NULL, &platformCount);
    platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
    clGetPlatformIDs(platformCount, platforms, NULL);

   // Choose first platform (here Apple) and get all devices 
   clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
   devices = (cl_device_id*) malloc(sizeof(cl_device_id) * deviceCount);

    //Intel HD Graphics 6000 1536 MB
    //err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);
    err = clGetDeviceIDs(platforms[0], gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 1, &devices[gpu ? 1 : 0], &deviceCount);
    if (err != CL_SUCCESS)
    {
        printf("\n\n[ERROR]: Failed to create a device group! exit(2)\n");
        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }

        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[2] ............ OK\n");}

        exit(2);
    }
  
    // Create a compute context
    //context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
    context = clCreateContext(0, 1, &devices[gpu ? 1:0], NULL, NULL, &err);
    if (err != CL_SUCCESS)
    {
        printf("\n\n[ERROR]: Failed to create a compute context! exit(3)\n");
        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }

        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[2] ............ OK\n");}
        exit(3);
    }

    // Create a command commands
    //commands = clCreateCommandQueue(context, device_id, 0, &err);
    commands = clCreateCommandQueue(context, devices[gpu ? 1:0], 0, &err);
    if (err != CL_SUCCESS)
    {
        printf("\n\n[ERROR]: Failed to create a command commands! exit(4)\n");

        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }
        if(context) {  clReleaseContext(context); printf("Sorry, free context ........  OK\n"); } 

        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[2] ............ OK\n");}
       
        exit(4);
    }
  

    // Create the compute program from the source buffer
    int read_return[TOTAL_CL_FILES];

    read_return[0] = loadProgramSource(kernel_file[0], &kernel_source_string[0], &kernel_length[0]);
    if (1 == read_return[0]){
        printf("\n\n[ERROR]; Unable to open  %s\n\n", kernel_file[0] );
        exit(-1);
    }
    if (2 == read_return[0]){
        printf("\n\n[ERROR]:Unable to read  %s\n\n", kernel_file[0] );
        exit(-1);
    }

    if ( TOTAL_CL_FILES > 1){
        read_return[1] = loadProgramSource(kernel_file[1], &kernel_source_string[1], &kernel_length[1]);
        
        if (1 == read_return[1]){
            printf("\n\n[ERROR]: Unable to open  %s\n\n", kernel_file[1] );
            exit(-1);
        }
        if (2 == read_return[1]){
            printf("\n\n[ERROR]: Unable to read  %s\n\n", kernel_file[1] );
            exit(-1);
        }
    }

    //load the window stroke drawer
    if ( TOTAL_CL_FILES > 2){
    read_return[2] = loadProgramSource(kernel_file[2], &kernel_source_string[2], &kernel_length[2]);
    
        if (1 == read_return[2]){
            printf("\n\n[ERROR]: Unable to open  %s\n\n", kernel_file[2] );
            exit(-1);
        }
        if (2 == read_return[2]){
            printf("\n\n[ERROR]: Unable to read  %s\n\n", kernel_file[2] );
            exit(-1);
        }
    }

     //program = clCreateProgramWithSource(context, 1, (const char **)&kernel_source_string[1], (const size_t *)&kernel_length[1], &err);
    
    
    program = clCreateProgramWithSource(context, TOTAL_CL_FILES, (const char **)kernel_source_string, (const size_t *)kernel_length, &err);

    if (err != CL_SUCCESS)
    {
        printf("\n\n[ERROR]: Failed to create compute program! exit(5) \n");

        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }

        if(commands){ clReleaseCommandQueue(commands); printf("Sorry, free commands ........  OK\n"); } 
        if(context) {  clReleaseContext(context); printf("Sorry, free context ........  OK\n"); } 
        
        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[3] ............ OK\n");}

        exit(5);
    }
    
    // Build the program executable
    //err = clBuildProgram(program, gpu, &devices[gpu ? 1:0], NULL, NULL, NULL);
     err = clBuildProgram(program, gpu, &devices[gpu ? 1:0], "-I ../MY_OPENCL/cl.hpp", NULL, NULL);
    if (err != CL_SUCCESS)
    {
        size_t len;
        char buffer[2048];
        
        printf("\n\n[ERROR]: Failed to build stroke and extern program executable! exit(6)\n");
        printf("ERROR_CODE: %s\n", getErrorString(err));
        clGetProgramBuildInfo(program, devices[gpu ? 1 : 0], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        printf("%s\n", buffer);

        printf("\n");
        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }

        if(commands){ clReleaseCommandQueue(commands); printf("Sorry, free commands ........  OK\n"); } 
        if(context) {  clReleaseContext(context); printf("Sorry, free context ........  OK\n"); } 
        if(program){  clReleaseProgram(program);  printf("Sorry, free program ........  OK\n"); }  
        
        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[2] ............ OK\n");}
        
        exit(6);
    }


    // Create the compute kernel (for window stroke managing )

    kernel = clCreateKernel(program, "calculateAntializing", &err);
    if (err != CL_SUCCESS)
    {
        printf("\n\n[ERROR]: Failed to create compute stroke kernel! exit(7)\n");
        printf("\n");
        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }

        if(commands){ clReleaseCommandQueue(commands); printf("Sorry, free commands ........  OK\n"); } 
        if(context) {  clReleaseContext(context); printf("Sorry, free context ........  OK\n"); } 
        if(program){  clReleaseProgram(program);  printf("Sorry, free program ........  OK\n"); }  
        
        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[2] ............ OK\n");}
        exit(7);
    }

    //Create the input and output arrays in device memory for the calculation
    sc.opencl.inputsX_buffer = clCreateBuffer(context,  CL_MEM_READ_ONLY,  sizeof(float) * DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE * SCREEN_ANTIALISING_DIVS, NULL, &err1);
    sc.opencl.inputsY_buffer = clCreateBuffer(context,  CL_MEM_READ_ONLY,  sizeof(float) * DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE * SCREEN_ANTIALISING_DIVS, NULL, &err2);
    sc.opencl.inputsCodeColors_buffer = clCreateBuffer(context,  CL_MEM_READ_ONLY,  sizeof(int) * DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE * SCREEN_ANTIALISING_DIVS, NULL, &err3);
    sc.opencl.inputsShowPoints_buffer = clCreateBuffer(context,  CL_MEM_READ_ONLY,  sizeof(int) * DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE * SCREEN_ANTIALISING_DIVS, NULL, &err4);

    sc.opencl.outputsX_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE*SCREEN_ANTIALISING_DIVS, NULL, &err5);
    sc.opencl.outputsY_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE*SCREEN_ANTIALISING_DIVS, NULL, &err6);
    sc.opencl.outputsCodeColors_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE*SCREEN_ANTIALISING_DIVS, NULL, &err7);
    sc.opencl.outputsShowPoints_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE*SCREEN_ANTIALISING_DIVS, NULL, &err8); 

    if ( (err1 != CL_SUCCESS) ||  (err2 != CL_SUCCESS) || (err3 != CL_SUCCESS)  || (err4 != CL_SUCCESS) ||
    (err5 != CL_SUCCESS) ||  (err6 != CL_SUCCESS) || (err7 != CL_SUCCESS)  || (err8 != CL_SUCCESS) )
    {   
        printf("\n\n[ERROR]: Failed to create buffer for kernel coordinate! exit(8)\n");
        if(sc.opencl.inputsX_buffer){ clReleaseMemObject(sc.opencl.inputsX_buffer); printf("Sorry, free sc.opencl.inputsX_buffer ........  OK\n"); } 
        if(sc.opencl.inputsY_buffer){ clReleaseMemObject(sc.opencl.inputsY_buffer); printf("Sorry, free sc.opencl.inputsY_buffer ........  OK\n"); } 
        if(sc.opencl.inputsCodeColors_buffer){ clReleaseMemObject(sc.opencl.inputsCodeColors_buffer); printf("Sorry, free sc.opencl.inputsCodeColors_buffer ........  OK\n"); } 
        if(sc.opencl.inputsShowPoints_buffer){ clReleaseMemObject(sc.opencl.inputsShowPoints_buffer); printf("Sorry, free sc.opencl.inputsShowPoints_buffer ........  OK\n"); } 

        if(sc.opencl.outputsX_buffer){ clReleaseMemObject(sc.opencl.outputsX_buffer); printf("Sorry, free sc.opencl.outputsX_buffer ........  OK\n"); } 
        if(sc.opencl.outputsY_buffer){ clReleaseMemObject(sc.opencl.outputsY_buffer); printf("Sorry, free sc.opencl.outputsY_buffer ........  OK\n"); } 
        if(sc.opencl.outputsCodeColors_buffer){ clReleaseMemObject(sc.opencl.outputsCodeColors_buffer); printf("Sorry, free sc.opencl.ioutputsCodeColors_buffer ........  OK\n"); } 
        if(sc.opencl.outputsShowPoints_buffer){ clReleaseMemObject(sc.opencl.outputsShowPoints_buffer); printf("Sorry, free sc.opencl.outputsShowPoints_buffer ........  OK\n"); } 


        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }

        if(commands){ clReleaseCommandQueue(commands); printf("Sorry, free commands ........  OK\n"); } 
        if(context) {  clReleaseContext(context); printf("Sorry, free context ........  OK\n"); } 
        if(program){  clReleaseProgram(program);  printf("Sorry, free program ........  OK\n"); }  
        if(kernel) {  clReleaseKernel(kernel); printf("Sorry, free kernel........  OK\n"); } 
        
        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[1] ............ OK\n");}

        exit(8);
    } 

    //------------------------------------ EXTERN -----------------------------------//
    //----------------------------------------------------------------------------------//
    //ext::ExternCenterMenu ext_cent_menu = ext::ExternCenterMenu();

    //----------------------------------------------------------------------------------//
    //----------------------------------------------------------------------------------//
    
    //FOR X
    float x_global_start_coordinates = 0.5f * WIDTH - 5.0f;
    float x_global_end_coordinates = 0.97*WIDTH;

    float x_local_start_coordinates = -10.0f;
    float x_local_end_coordinates = 10.0f;

    int  number_points_x_axes = NOMBER_OF_DIVISIONS_X_AXE; //ne pas confondre avec les graduations du repere car ici on peut subdiviser ceux du repre pour avoir exemple 1.3, 5.8 etc ...
    float x_local_divisions_width = (x_local_end_coordinates - x_local_start_coordinates )/ ( (float)number_points_x_axes );
    float x_global_divisions_width = (x_global_end_coordinates - x_global_start_coordinates )/ ( (float)number_points_x_axes );

    float x_local_coordinates_points[number_points_x_axes]; //like -1.4, 4.7, 0 etc ..., 
    float x_global_coordinates_points[number_points_x_axes]; //like -1.4*division_width, 4.7*division_width,  etc ..., 

    x_local_coordinates_points[0] = x_local_start_coordinates;
    
    for(int i=1; i<number_points_x_axes;i++){
        x_local_coordinates_points[i] = x_local_coordinates_points[i-1] + x_local_divisions_width;
        //printf("x[%d]: %f ", i, x_local_coordinates_points[i]);
    }
    
    //FOR Y
    float y_global_start_coordinates = 60;
    float y_global_end_coordinates = 0.97*HEIGHT;

    float y_local_start_coordinates = -10.0f;
    float y_local_end_coordinates = 13.0f;

    int  number_points_y_axes = NOMBER_OF_DIVISIONS_Y_AXE; //ne pas confondre avec les graduations du repere car ici on peut subdiviser ceux du repre pour avoir exemple 1.3, 5.8 etc ...
    float y_local_divisions_width = (y_local_end_coordinates - y_local_start_coordinates )/ ( (float)number_points_y_axes );
    float y_global_divisions_width = (y_global_end_coordinates - y_global_start_coordinates )/ ( (float)number_points_y_axes);
    
    float y_global_coordinates_points[number_points_y_axes]; //like -1.4, 4.7, 0 etc ..., 
   
    //KERNEL
    kernel_coordinates = clCreateKernel(program, "getCourbePoint", &err);
    if (err != CL_SUCCESS)
    {
        printf("\n\n[ERROR]: Failed to create kernel coordinates!\n");
        printf("\n");
        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }
        if(kernel){ clReleaseKernel(kernel); printf("\nSoory, free kernels"); }
   
        if(commands){ clReleaseCommandQueue(commands); printf("Sorry, free commands ........  OK\n"); } 
        if(context) {  clReleaseContext(context); printf("Sorry, free context ........  OK\n"); } 
        if(program){  clReleaseProgram(program);  printf("Sorry, free program ........  OK\n"); }  
        
        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[2] ............ OK\n");}
        exit(9);
    }


    //Create the input and output arrays in device memory for the calculation
    cl_mem x_local_coordinates_buffer = clCreateBuffer(context,  CL_MEM_READ_ONLY,  sizeof(float) * number_points_x_axes, NULL, &err1);
    cl_mem x_global_coordinates_buffer = clCreateBuffer(context,  CL_MEM_WRITE_ONLY,  sizeof(float) * number_points_x_axes, NULL, &err2);
    cl_mem y_global_coordinates_buffer = clCreateBuffer(context,  CL_MEM_WRITE_ONLY,  sizeof(float) * number_points_x_axes, NULL, &err3);

    if ( (err1 != CL_SUCCESS) ||  (err2 != CL_SUCCESS) || (err3 != CL_SUCCESS) )
    {   
        printf("\n\n[ERROR]: Failed to create buffer for extern ! exit(10)\n");
        printf("\n");
        if(sc.opencl.inputsX_buffer){ clReleaseMemObject(sc.opencl.inputsX_buffer); printf("Sorry, free sc.opencl.inputsX_buffer ........  OK\n"); } 
        if(sc.opencl.inputsY_buffer){ clReleaseMemObject(sc.opencl.inputsY_buffer); printf("Sorry, free sc.opencl.inputsY_buffer ........  OK\n"); } 
        if(sc.opencl.inputsCodeColors_buffer){ clReleaseMemObject(sc.opencl.inputsCodeColors_buffer); printf("Sorry, free sc.opencl.inputsCodeColors_buffer ........  OK\n"); } 
        if(sc.opencl.inputsShowPoints_buffer){ clReleaseMemObject(sc.opencl.inputsShowPoints_buffer); printf("Sorry, free sc.opencl.inputsShowPoints_buffer ........  OK\n"); } 

        if(sc.opencl.outputsX_buffer){ clReleaseMemObject(sc.opencl.outputsX_buffer); printf("Sorry, free sc.opencl.outputsX_buffer ........  OK\n"); } 
        if(sc.opencl.outputsY_buffer){ clReleaseMemObject(sc.opencl.outputsY_buffer); printf("Sorry, free sc.opencl.outputsY_buffer ........  OK\n"); } 
        if(sc.opencl.outputsCodeColors_buffer){ clReleaseMemObject(sc.opencl.outputsCodeColors_buffer); printf("Sorry, free sc.opencl.ioutputsCodeColors_buffer ........  OK\n"); } 
        if(sc.opencl.outputsShowPoints_buffer){ clReleaseMemObject(sc.opencl.outputsShowPoints_buffer); printf("Sorry, free sc.opencl.outputsShowPoints_buffer ........  OK\n"); } 

        if(x_local_coordinates_buffer){ clReleaseMemObject(x_local_coordinates_buffer); printf("Sorry, free x_local_coordinates_buffer ........  OK\n"); } 
        if(x_global_coordinates_buffer){ clReleaseMemObject(x_global_coordinates_buffer); printf("Sorry, free x_global_coordinates_buffer ........  OK\n"); } 
        if(y_global_coordinates_buffer){ clReleaseMemObject(y_global_coordinates_buffer); printf("Sorry, free y_global_coordinates_buffer ........  OK\n"); } 
        
        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }

        if(commands){ clReleaseCommandQueue(commands); printf("Sorry, free commands ........  OK\n"); } 
        if(context) {  clReleaseContext(context); printf("Sorry, free context ........  OK\n"); } 
        if(program){  clReleaseProgram(program);  printf("Sorry, free program ........  OK\n"); }  
        if(kernel) {  clReleaseKernel(kernel); printf("Sorry, free kernel........  OK\n"); } 
        
        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[1] ............ OK\n");}

        exit(10);
    } 

    // Copy the Buffer A and B to the device
    err = clEnqueueWriteBuffer(commands, x_local_coordinates_buffer, CL_TRUE, 0,   number_points_x_axes * sizeof(float)  , x_local_coordinates_points,  0, NULL, NULL);
    //err |= clEnqueueWriteBuffer(commands, x_global_coordinates_buffer, CL_TRUE, 0,  sizeof(float)*SIZE, &output_x,  0, NULL, NULL);
    //err |= clEnqueueWriteBuffer(commands, x_global_coordinates_buffer, CL_TRUE, 0,  sizeof(float)*SIZE, &output_y,  0, NULL, NULL);
    if (err != CL_SUCCESS)
    {   
       printf("\n\n[ERROR]: Failed to copy data towards extern buffer for extern ! exit(11)\n");
        printf("\n");
        if(sc.opencl.inputsX_buffer){ clReleaseMemObject(sc.opencl.inputsX_buffer); printf("Sorry, free sc.opencl.inputsX_buffer ........  OK\n"); } 
        if(sc.opencl.inputsY_buffer){ clReleaseMemObject(sc.opencl.inputsY_buffer); printf("Sorry, free sc.opencl.inputsY_buffer ........  OK\n"); } 
        if(sc.opencl.inputsCodeColors_buffer){ clReleaseMemObject(sc.opencl.inputsCodeColors_buffer); printf("Sorry, free sc.opencl.inputsCodeColors_buffer ........  OK\n"); } 
        if(sc.opencl.inputsShowPoints_buffer){ clReleaseMemObject(sc.opencl.inputsShowPoints_buffer); printf("Sorry, free sc.opencl.inputsShowPoints_buffer ........  OK\n"); } 

        if(sc.opencl.outputsX_buffer){ clReleaseMemObject(sc.opencl.outputsX_buffer); printf("Sorry, free sc.opencl.outputsX_buffer ........  OK\n"); } 
        if(sc.opencl.outputsY_buffer){ clReleaseMemObject(sc.opencl.outputsY_buffer); printf("Sorry, free sc.opencl.outputsY_buffer ........  OK\n"); } 
        if(sc.opencl.outputsCodeColors_buffer){ clReleaseMemObject(sc.opencl.outputsCodeColors_buffer); printf("Sorry, free sc.opencl.ioutputsCodeColors_buffer ........  OK\n"); } 
        if(sc.opencl.outputsShowPoints_buffer){ clReleaseMemObject(sc.opencl.outputsShowPoints_buffer); printf("Sorry, free sc.opencl.outputsShowPoints_buffer ........  OK\n"); } 

        if(x_local_coordinates_buffer){ clReleaseMemObject(x_local_coordinates_buffer); printf("Sorry, free x_local_coordinates_buffer ........  OK\n"); } 
        if(x_global_coordinates_buffer){ clReleaseMemObject(x_global_coordinates_buffer); printf("Sorry, free x_global_coordinates_buffer ........  OK\n"); } 
        if(y_global_coordinates_buffer){ clReleaseMemObject(y_global_coordinates_buffer); printf("Sorry, free y_global_coordinates_buffer ........  OK\n"); } 
        
        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }

        if(commands){ clReleaseCommandQueue(commands); printf("Sorry, free commands ........  OK\n"); } 
        if(context) {  clReleaseContext(context); printf("Sorry, free context ........  OK\n"); } 
        if(program){  clReleaseProgram(program);  printf("Sorry, free program ........  OK\n"); }  
        if(kernel) {  clReleaseKernel(kernel); printf("Sorry, free kernel........  OK\n"); } 
        
        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[1] ............ OK\n");}

        exit(11);
    }

    //Not buffered variables
    float x_global_middle = 0.5f * (x_global_start_coordinates + x_global_end_coordinates);
    float y_global_middle = 0.5f * (y_global_start_coordinates + y_global_end_coordinates);
    float x_global_division_width = x_global_divisions_width;
    float y_global_division_width = y_global_divisions_width;

    //Set argument 
    err  = clSetKernelArg(kernel_coordinates, 0, sizeof(cl_mem), (void *)&x_local_coordinates_buffer);
    err  |= clSetKernelArg(kernel_coordinates, 1, sizeof(cl_mem), (void *)&x_global_coordinates_buffer);
    err  |= clSetKernelArg(kernel_coordinates, 2, sizeof(cl_mem), (void *)&y_global_coordinates_buffer);
    err  |= clSetKernelArg(kernel_coordinates, 3, sizeof(float), (void *)&x_global_middle);
    err  |= clSetKernelArg(kernel_coordinates, 4, sizeof(float), (void *)&y_global_middle);
    err  |= clSetKernelArg(kernel_coordinates, 5, sizeof(float), (void *)&x_global_division_width);
    err  |= clSetKernelArg(kernel_coordinates, 6, sizeof(float), (void *)&y_global_division_width);
    err  |= clSetKernelArg(kernel_coordinates, 7, sizeof(int), (void *)&number_points_x_axes);
    
    if (err != CL_SUCCESS)
    {
        printf("\n\n[ERROR]: Failed to set extern parameter to kernel! exit(12)\n");
        printf("\n");
        if(sc.opencl.inputsX_buffer){ clReleaseMemObject(sc.opencl.inputsX_buffer); printf("Sorry, free sc.opencl.inputsX_buffer ........  OK\n"); } 
        if(sc.opencl.inputsY_buffer){ clReleaseMemObject(sc.opencl.inputsY_buffer); printf("Sorry, free sc.opencl.inputsY_buffer ........  OK\n"); } 
        if(sc.opencl.inputsCodeColors_buffer){ clReleaseMemObject(sc.opencl.inputsCodeColors_buffer); printf("Sorry, free sc.opencl.inputsCodeColors_buffer ........  OK\n"); } 
        if(sc.opencl.inputsShowPoints_buffer){ clReleaseMemObject(sc.opencl.inputsShowPoints_buffer); printf("Sorry, free sc.opencl.inputsShowPoints_buffer ........  OK\n"); } 

        if(sc.opencl.outputsX_buffer){ clReleaseMemObject(sc.opencl.outputsX_buffer); printf("Sorry, free sc.opencl.outputsX_buffer ........  OK\n"); } 
        if(sc.opencl.outputsY_buffer){ clReleaseMemObject(sc.opencl.outputsY_buffer); printf("Sorry, free sc.opencl.outputsY_buffer ........  OK\n"); } 
        if(sc.opencl.outputsCodeColors_buffer){ clReleaseMemObject(sc.opencl.outputsCodeColors_buffer); printf("Sorry, free sc.opencl.ioutputsCodeColors_buffer ........  OK\n"); } 
        if(sc.opencl.outputsShowPoints_buffer){ clReleaseMemObject(sc.opencl.outputsShowPoints_buffer); printf("Sorry, free sc.opencl.outputsShowPoints_buffer ........  OK\n"); } 

        if(x_local_coordinates_buffer){ clReleaseMemObject(x_local_coordinates_buffer); printf("Sorry, free x_local_coordinates_buffer ........  OK\n"); } 
        if(x_global_coordinates_buffer){ clReleaseMemObject(x_global_coordinates_buffer); printf("Sorry, free x_global_coordinates_buffer ........  OK\n"); } 
        if(y_global_coordinates_buffer){ clReleaseMemObject(y_global_coordinates_buffer); printf("Sorry, free y_global_coordinates_buffer ........  OK\n"); } 
        
        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }

        if(commands){ clReleaseCommandQueue(commands); printf("Sorry, free commands ........  OK\n"); } 
        if(context) {  clReleaseContext(context); printf("Sorry, free context ........  OK\n"); } 
        if(program){  clReleaseProgram(program);  printf("Sorry, free program ........  OK\n"); }  
        if(kernel) {  clReleaseKernel(kernel); printf("Sorry, free kernel........  OK\n"); } 
        
        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[1] ............ OK\n");}

        exit(11);
    }

    // Execute the kernel over the entire range of our 1d input data set
     err = clEnqueueNDRangeKernel(commands, kernel_coordinates, dim, global_offset, global_size, local_size, 0, NULL, NULL);
    if(err < 0) {
        printf("\n\n[ERROR]: Failed to enqueue  kernel coordinates! exit(13)\n");
        printf("\n");
        if(sc.opencl.inputsX_buffer){ clReleaseMemObject(sc.opencl.inputsX_buffer); printf("Sorry, free sc.opencl.inputsX_buffer ........  OK\n"); } 
        if(sc.opencl.inputsY_buffer){ clReleaseMemObject(sc.opencl.inputsY_buffer); printf("Sorry, free sc.opencl.inputsY_buffer ........  OK\n"); } 
        if(sc.opencl.inputsCodeColors_buffer){ clReleaseMemObject(sc.opencl.inputsCodeColors_buffer); printf("Sorry, free sc.opencl.inputsCodeColors_buffer ........  OK\n"); } 
        if(sc.opencl.inputsShowPoints_buffer){ clReleaseMemObject(sc.opencl.inputsShowPoints_buffer); printf("Sorry, free sc.opencl.inputsShowPoints_buffer ........  OK\n"); } 

        if(sc.opencl.outputsX_buffer){ clReleaseMemObject(sc.opencl.outputsX_buffer); printf("Sorry, free sc.opencl.outputsX_buffer ........  OK\n"); } 
        if(sc.opencl.outputsY_buffer){ clReleaseMemObject(sc.opencl.outputsY_buffer); printf("Sorry, free sc.opencl.outputsY_buffer ........  OK\n"); } 
        if(sc.opencl.outputsCodeColors_buffer){ clReleaseMemObject(sc.opencl.outputsCodeColors_buffer); printf("Sorry, free sc.opencl.ioutputsCodeColors_buffer ........  OK\n"); } 
        if(sc.opencl.outputsShowPoints_buffer){ clReleaseMemObject(sc.opencl.outputsShowPoints_buffer); printf("Sorry, free sc.opencl.outputsShowPoints_buffer ........  OK\n"); } 

        if(x_local_coordinates_buffer){ clReleaseMemObject(x_local_coordinates_buffer); printf("Sorry, free x_local_coordinates_buffer ........  OK\n"); } 
        if(x_global_coordinates_buffer){ clReleaseMemObject(x_global_coordinates_buffer); printf("Sorry, free x_global_coordinates_buffer ........  OK\n"); } 
        if(y_global_coordinates_buffer){ clReleaseMemObject(y_global_coordinates_buffer); printf("Sorry, free y_global_coordinates_buffer ........  OK\n"); } 
        
        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }

        if(commands){ clReleaseCommandQueue(commands); printf("Sorry, free commands ........  OK\n"); } 
        if(context) {  clReleaseContext(context); printf("Sorry, free context ........  OK\n"); } 
        if(program){  clReleaseProgram(program);  printf("Sorry, free program ........  OK\n"); }  
        if(kernel) {  clReleaseKernel(kernel); printf("Sorry, free kernel........  OK\n"); } 
        
        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[1] ............ OK\n");}

        exit(13);
    }

    // Read back the results from the device
    err = clEnqueueReadBuffer( commands, x_global_coordinates_buffer, CL_TRUE, 0, sizeof(float) * number_points_x_axes, (void *)&x_global_coordinates_points , 0, NULL, NULL );
    err |= clEnqueueReadBuffer( commands, y_global_coordinates_buffer, CL_TRUE, 0, sizeof(float) * number_points_x_axes , (void *)&y_global_coordinates_points , 0, NULL, NULL );
      
    if (err != CL_SUCCESS)
    {
        printf("\n\n[ERROR]: Failed to read back kernel  coordinates result coordinates! exit(14)\n");
        printf("\n");
        if(sc.opencl.inputsX_buffer){ clReleaseMemObject(sc.opencl.inputsX_buffer); printf("Sorry, free sc.opencl.inputsX_buffer ........  OK\n"); } 
        if(sc.opencl.inputsY_buffer){ clReleaseMemObject(sc.opencl.inputsY_buffer); printf("Sorry, free sc.opencl.inputsY_buffer ........  OK\n"); } 
        if(sc.opencl.inputsCodeColors_buffer){ clReleaseMemObject(sc.opencl.inputsCodeColors_buffer); printf("Sorry, free sc.opencl.inputsCodeColors_buffer ........  OK\n"); } 
        if(sc.opencl.inputsShowPoints_buffer){ clReleaseMemObject(sc.opencl.inputsShowPoints_buffer); printf("Sorry, free sc.opencl.inputsShowPoints_buffer ........  OK\n"); } 

        if(sc.opencl.outputsX_buffer){ clReleaseMemObject(sc.opencl.outputsX_buffer); printf("Sorry, free sc.opencl.outputsX_buffer ........  OK\n"); } 
        if(sc.opencl.outputsY_buffer){ clReleaseMemObject(sc.opencl.outputsY_buffer); printf("Sorry, free sc.opencl.outputsY_buffer ........  OK\n"); } 
        if(sc.opencl.outputsCodeColors_buffer){ clReleaseMemObject(sc.opencl.outputsCodeColors_buffer); printf("Sorry, free sc.opencl.ioutputsCodeColors_buffer ........  OK\n"); } 
        if(sc.opencl.outputsShowPoints_buffer){ clReleaseMemObject(sc.opencl.outputsShowPoints_buffer); printf("Sorry, free sc.opencl.outputsShowPoints_buffer ........  OK\n"); } 

        if(x_local_coordinates_buffer){ clReleaseMemObject(x_local_coordinates_buffer); printf("Sorry, free x_local_coordinates_buffer ........  OK\n"); } 
        if(x_global_coordinates_buffer){ clReleaseMemObject(x_global_coordinates_buffer); printf("Sorry, free x_global_coordinates_buffer ........  OK\n"); } 
        if(y_global_coordinates_buffer){ clReleaseMemObject(y_global_coordinates_buffer); printf("Sorry, free y_global_coordinates_buffer ........  OK\n"); } 
        
        if(platforms){ free(platforms); printf("\n\nSorry, free platforms ........  OK\n"); }
        if(devices) { free(devices); printf("Sorry, free devices ........  OK\n"); }

        if(commands){ clReleaseCommandQueue(commands); printf("Sorry, free commands ........  OK\n"); } 
        if(context) {  clReleaseContext(context); printf("Sorry, free context ........  OK\n"); } 
        if(program){  clReleaseProgram(program);  printf("Sorry, free program ........  OK\n"); }  
        if(kernel) {  clReleaseKernel(kernel); printf("Sorry, free kernel........  OK\n"); } 
        
        if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
        if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
        if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[1] ............ OK\n");}

        exit(14);
    }
    
    //print x_global 
    //for(int i=0; i< number_points_x_axes; i++){ printf("x[%d]: %f\n", i,x_global_coordinates_points[i] );}
    //printf("\n--------------\n");
    //for(int i=0; i< number_points_x_axes; i++){ printf("y[%d]: %f\n", i,y_global_coordinates_points[i] );}
    printf("\033[0;32m");
    printf("MPC is RUNNING ........... OK\n");
    printf("\033[0m");

    //------------ FOR REPERE (to draw opencl compute points: exemple for sin function) ----//
    sc.coords.setCoordinatesFromopencl(x_global_coordinates_points, y_global_coordinates_points, (unsigned int)number_points_x_axes);
    sc.rep.set_graduation(number_points_x_axes, number_points_y_axes );
    //----------------------------------------------------------------------------------//
    //----------------------------------------------------------------------------------//
    //----------------------------------------------------------------------------------//
    
    int screenAntialisingDivs = (int)SCREEN_ANTIALISING_DIVS;
   
    std::string str;
    /////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////// SFE_MOVIES ///////////////////////////////////////////////
    ext::AnimatedSFE_MOVIES anim_movies;
    ext::AnimatedSFE_MOVIES mymusic(CHEMISTRY_MUSIC_INDEX);

    UserInterface *ui = NULL;
    StreamSelector *selector_video = NULL;
    StreamSelector *selector_audio = NULL;

    

    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
        anim_movies.movie.fit(0.5*(WIDTH - anim_movies.width), 0.5*(HEIGHT - anim_movies.height), anim_movies.width, anim_movies.height);
        mymusic.movie.setVolume(DEFAULT_MUSIC_VOLUME);

        ui = new UserInterface(*window, anim_movies.movie);
        selector_video = new StreamSelector(anim_movies.movie);
        selector_audio = new StreamSelector(mymusic.movie);

        displayShortcuts();
      
        anim_movies.movie.play();
        mymusic.movie.play();
    }


    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////

    //set argument
    sf::Clock clock;
    float duration = 0;

    while(window->isOpen()){

        sf::Time dt = clock.restart();
        duration += dt.asSeconds();

        sf::Event event;
        

        while(window->pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window->close();
                    break;

                case sf::Event::TextEntered:
                    //Extern 
                    if ((event.text.unicode > 30 && (event.text.unicode < 128 || event.text.unicode > 159))){
                        
                    }
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape){
                        window->close();
                        //break;
                    }
                    else if( event.key.code == sf::Keyboard::Backspace ){  
                        //Extern               
                        
                    }
                    else if( event.key.code == sf::Keyboard::Return ){
                        //Extern
                   
                    }
                    else if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
                        
                        if(event.key.code == sf::Keyboard::Space) {
                            if (anim_movies.movie.getStatus() == sfe::Playing){
                                anim_movies.movie.pause();
                                if (mymusic.movie.getStatus() == sfe::Playing){
                                mymusic.movie.pause();
                                }
                            }
                            else{
                                anim_movies.movie.play();
                                mymusic.movie.play();
                            }
                            
                        }
                        else if (event.key.code == sf::Keyboard::A ) {
                            if (event.key.alt){
                                //selector_video->selectNextStream(sfe::Audio);
                                selector_audio->selectNextStream(sfe::Audio);//Cause segmentation fault
                            }
                        }
                        else if (event.key.code == sf::Keyboard::P ) { //Volume +
                            if (event.key.alt)
                                mymusic.movie.setVolume( std::min(mymusic.movie.getVolume() + KEYPRESS_VOLUME_TO_ADD, (float)MUSIC_MAX_VOLUME));
                        }
                        else if (event.key.code == sf::Keyboard::R ) { //Reset
                           anim_movies.movie.stop();
                           anim_movies.movie.play();

                           mymusic.movie.stop();
                           mymusic.movie.play();
                        }
                        else if (event.key.code == sf::Keyboard::M ) { //Volume -
                            if (event.key.alt)
                                mymusic.movie.setVolume( std::max( mymusic.movie.getVolume() - KEYPRESS_VOLUME_TO_ADD, (float)MUSIC_MIN_VOLUME));
                        }
                        else if(event.key.code == sf::Keyboard::F ) {
                                 anim_movies.fullscreen = !anim_movies.fullscreen;
                                if (anim_movies.fullscreen)
                                    window->create(anim_movies.desktopMode, "sfeMovie Player", sf::Style::Fullscreen);
                                else
                                    window->create(sf::VideoMode(anim_movies.width, anim_movies.height), "sfeMovie Player",
                                          sf::Style::Close | sf::Style::Resize);
                        
                            window->setFramerateLimit(WINDOW_FRAME_LIMIT_60);
                            window->setVerticalSyncEnabled(true);
                            anim_movies.movie.fit(0.5*(WIDTH - (float)window->getSize().x), 0.5*(HEIGHT - (float)window->getSize().y ), (float)window->getSize().x, (float)window->getSize().y);
                            ui->applyProperties(); 
                        }//else if 
                        else if(event.key.code == sf::Keyboard::H ) { //toogle video control menu
                            ui->toggleVisible(); 
                        }//else if
                        else if(event.key.code == sf::Keyboard::I ) { //display media info
                            displayMediaInfo(anim_movies.movie, mymusic.movie );
                        }//else if
                        else if(event.key.code == sf::Keyboard::S ) {
                            if (event.key.alt){
                                selector_video->selectNextStream(sfe::Subtitle);
                            }
                            else {
                                anim_movies.movie.stop();
                                mymusic.movie.stop();
                            }
                        }//else if
                        else if(event.key.code == sf::Keyboard::V ) {
                            if (event.key.alt){
                                selector_video->selectNextStream(sfe::Video);
                                selector_audio->selectNextStream(sfe::Audio);
                            }
                        }//else if
                    }//else if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO )
                    break;
                case sf::Event::MouseButtonPressed:
                    cursorPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
                    sc.handleScreenMouseButtonPressed(event, cursorPos);
                    //Extern 
                    if ( ext_index >= 0 ){
                        //0 : Do nothing 
                        if ( ext_index == 0 ){ 
                            
                            
                            
                        }
                        //1 : Add node at last
                        if ( ext_index == 1 ){ 
                            
                        }
                    }
                    /*if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
                        int xPos = 0;
                        xPos = event.mouseButton.x;

                        float ratio = static_cast<float>(xPos) / window->getSize().x;
                        sf::Time targetTime = ratio * anim_movies.movie.getDuration();
                        anim_movies.movie.setPlayingOffset(targetTime);
                    }*/
                    break;
                case sf::Event::MouseMoved:
                    cursorPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
                    sc.handleScreenMouseMoved(event, cursorPos);

                    /*if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO && sf::Mouse::isButtonPressed(sf::Mouse::Left)  ){
                        int xPos = 0;
                    
                        if (event.type == sf::Event::MouseMoved)
                            xPos = event.mouseMove.x;
                    
                        float ratio = static_cast<float>(xPos) / window->getSize().x;
                        sf::Time targetTime = ratio * anim_movies.movie.getDuration();
                        anim_movies.movie.setPlayingOffset(targetTime);
                    }*/
                    
                    break;
                case sf::Event::MouseButtonReleased:
                    cursorPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
                    sc.handleScreenMouseButtonReleased(event, cursorPos);
                   
                    break;
                case sf::Event::MouseWheelMoved:
                    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
                        float volume = anim_movies.movie.getVolume() + 10 * event.mouseWheel.delta;
                       
                        volume = std::min(volume, 100.f);
                        volume = std::max(volume, 0.f);
                        anim_movies.movie.setVolume(volume);
                        std::cout << "Volume changed to " << int(volume) << "%" << std::endl;  
                    }
                    break;
                case sf::Event::Resized:
                    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
                        anim_movies.movie.fit(0.5*(WIDTH - (float)window->getSize().x), 0.5*(HEIGHT - (float)window->getSize().y ), (float)window->getSize().x, (float)window->getSize().y);
                        //anim_movies.movie.fit(0, 0, window->getSize().x, window->getSize().y);
                        window->setView(sf::View(sf::FloatRect(0, 0, (float)window->getSize().x, (float)window->getSize().y)));
                    }
                    break;
                default:
                    break;
            }// switch(event.type)

        }//while(window.pollEvent(event))
         
        //UPDATE MOVIES
        if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){ anim_movies.movie.update(); }
        
        if ( PLAY_MUSIC_SFE_MOVIES_VIDEO && (mymusic.movie.getPlayingOffset().asSeconds() >= anim_movies.movie.getDuration().asSeconds())  ){ 
         
            mymusic.movie.stop();
            
        }
        if (PLAY_MUSIC_SFE_MOVIES_VIDEO)
            mymusic.movie.play();
        /*if ( -mymusic.movie.getPlayingOffset().asSeconds() + anim_movies.movie.getDuration().asSeconds() <= 8.0f ){ printf("ok ");
                mymusic.movie.setVolume( std::max( mymusic.movie.getVolume() - 0.006f, (float)MUSIC_MIN_VOLUME));
        }*/

        window->clear(SCREEN_BACKGROUND_COLOR);

        if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
          
            window->draw(anim_movies.movie);
            ui->draw();
        }
    
        if ( SHOW_CENTER_MENU_SPRITE ){ /*draw function for external sprite (screen capture, exercices, geogebra ...)*/ }
     
        //update 
        //The following function updateAllStrokeGpuCpuAntiallising called LineWithThickness class
        //so that all the sf::Quad built by this LineWithThickness are computed inside opencl kernel
        //Called "__kernel void getCourbePoint " The kernel computed points are given back to host
        //So that the stroke can be drawn.
        sc.opencl.updateAllStrokeGpuCpuAntiallising(platforms, devices, &commands, &program, &kernel, gpu, local, global);

        //draw menus and grids
        sc.lm.draw(window); //screen object left menu
        sc.rm.draw(window); //screen object right menu
       
        sc.tm.draw(window); //screen TITLE AND LESSON
        sc.grid.draw(window); //screen object draw
  
        
        

        if ( DRAW_REPERE ){
             sc.rep.draw_only_repere(window); //COORDINATE SYSTEM

             if ( DRAW_GRADUATIONS ){ sc.rep.draw_graduations(window); }
             if ( DRAW_COURBE ){ sc.coords.draw(window);  }
        }
        //if(DRAW_REPERE){sc.rep.draw(window); }

        //draw stroke
        //sc.opencl.drawAllStrokeVector(window);
   
        for (int i=0; i<sc.opencl.geometryRectangleShapeVector.size();i++){
            window->draw(sc.opencl.geometryRectangleShapeVector[i]);
        }
        
        //-------------------------- EXTERN -------------------------------//
        //draw menu 
        
        //draw video 
        
       
        
        //------------------------------------------------------------------//

         //draw stroke
        sc.opencl.drawCurrentStroke(window); //draw stroke 
        sc.opencl.drawAllStrokeVector(window);
        
        window->display();
            
    }//while(window->isOpen())
    delete window;  
    std::cout << "deleted window\n"; 

    if(platforms){free(platforms); std::cout << "deleted platform\n";}  
    if(devices) {free(devices);  std::cout << "deleted devices\n";}
        
    clReleaseMemObject(sc.opencl.inputsX_buffer);  
    clReleaseMemObject(sc.opencl.inputsY_buffer); 
    clReleaseMemObject(sc.opencl.inputsCodeColors_buffer); 
    clReleaseMemObject(sc.opencl.inputsShowPoints_buffer);  

    clReleaseMemObject(sc.opencl.outputsX_buffer); 
    clReleaseMemObject(sc.opencl.outputsY_buffer); 
    clReleaseMemObject(sc.opencl.outputsCodeColors_buffer);  
    clReleaseMemObject(sc.opencl.outputsShowPoints_buffer);  


    clReleaseProgram(program); 
    clReleaseKernel(kernel); 
    clReleaseKernel(kernel_coordinates); 
    clRetainCommandQueue(commands); 
    clRetainContext(context); 
   
    sc.opencl.handLines.clear();
    sc.opencl.showPoints.clear();
    
  
    for(int i=0; i< sc.opencl.handLinesVector.size(); i++){ sc.opencl.handLinesVector[i].clear();}
    sc.opencl.handLinesVector.clear();

    for(int i=0; i< sc.opencl.showPointsVector.size();i++){sc.opencl.showPointsVector[i].clear();}
    sc.opencl.showPointsVector.clear();

    sc.opencl.geometryRectangleShapeVector.clear();
    //std::cout << "deleted all opencl objects\n";

    //----------- EXTERN ------------------//
    clReleaseMemObject(x_local_coordinates_buffer); 
    clReleaseMemObject(x_global_coordinates_buffer); 

    //clReleaseMemObject(y_local_coordinates_buffer); 
    clReleaseMemObject(y_global_coordinates_buffer); 
    //-------------------------------------//
    //if(mpc::math::sc.ext_graphicN){delete mpc::math::sc.ext_graphicN;}
    if(kernel_source_string[0]){free(kernel_source_string[0]); printf("free kernel_source_string[0] ............ OK\n");}
    if(kernel_source_string[1]){free(kernel_source_string[1]); printf("free kernel_source_string[1] ............ OK\n");}
    if(kernel_source_string[2]){free(kernel_source_string[2]); printf("free kernel_source_string[2] ............ OK\n");}
           
    
    std::cout << "\n[delete opencl  memories ......... OK]\n";

    std::cout << "... DELETE MOVIES  utils ....\n";

    delete ui;
    std::cout << "Delete ui\n"; 

    delete selector_video;
    delete selector_audio;
    std::cout << "Delete selectors video and audio\n"; 

    std::cout << "\n[delete opencl  memories ......... OK]\n";

    return EXIT_SUCCESS;
}

