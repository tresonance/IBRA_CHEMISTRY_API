#pragma OPENCL EXTENSION cl_APPLE_SetMemObjectDestructor : enable
#pragma OPENCL EXTENSION cl_APPLE_ContextLoggingFunctions : enable
#pragma OPENCL EXTENSION cl_APPLE_clut : enable
#pragma OPENCL EXTENSION cl_APPLE_query_kernel_names : enable
#pragma OPENCL EXTENSION cl_APPLE_clut : enable
#pragma OPENCL EXTENSION cl_APPLE_query_kernel_names : enable

#pragma OPENCL EXTENSION cl_khr_fp64 : enable  

#if defined cl_intel_printf 
    #pragma OPENCL EXTENSION cl_intel_printf :enable 
#else 
    #pragma OPENCL EXTENSION cl_amd_printf :enable 
#endif 


#define PRINT_INT(n) printf("%d", n) 
// use FOREACH 


__kernel void getCourbePoint  ( 
    __global float *x_local_coordinates,
    __global float *x_global_coordinates,
    __global float *y_global_coordinates,
    float x_global_middle,
    float y_global_middle,
    float x_global_division_width,
    float y_global_division_width,
    int numberPoins
) {  
    int id = get_global_id(0);
    float PI = 3.1415926535897932;

    float x;
    float v;
    if(id < numberPoins){
        x = x_local_coordinates[id];
        v = PI * x / 180.0;
        //y_global_coordinates[id] = -x*x - 3;
        y_global_coordinates[id] = sin(v);
        if ( x_local_coordinates[id] < 0){
            x_global_coordinates[id] = x_global_middle + x_local_coordinates[id] *  x_global_division_width;
        } else {
             x_global_coordinates[id] = x_global_middle + x_local_coordinates[id] *  x_global_division_width;
        }

        if ( y_global_coordinates[id] < 0){
            y_global_coordinates[id] = y_global_middle - y_global_coordinates[id] *  y_global_division_width;
        } else {
             y_global_coordinates[id] = y_global_middle - y_global_coordinates[id] *  y_global_division_width;
        }
        //barrier(CLK_GLOBAL_MEM_FENCE);
    }//end if(id < numberPoins)
      
}



