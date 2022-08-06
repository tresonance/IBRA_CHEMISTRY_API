
char    details_tolower2(char c){
    if( (c >= 'A')  && (c <= 'Z') ){
        return (c + 'a' - 'A');
    }
    return c;
}




__kernel void sfml_image_pixel1  ( 
    __global uchar *pixels,
    int WIDTH
) {                                                          
    
    int x = get_global_id(0);
    int y = get_global_id(1);

    unsigned int  color  = 0xFFFF00FF; // RGBA for sfml
    pixels[(y * WIDTH + x)*4] = (color >> 24) & 0xff; //OPACITY 100% OR 255 
    pixels[(y * WIDTH + x)*4 + 1] = (color >> 16) & 0xff; // THE AMOUNT OF RED
    pixels[(y * WIDTH + x)*4 + 2] = (color >> 8) & 0xff; // THE AMOUNT OF GREEN
    pixels[(y * WIDTH + x)*4 + 3] = color & 0xff; //THE AMOUNT OF BLUE
                        
}



__kernel void sfml_image_pixel0  ( 
    __global uchar *pixels,
    int WIDTH
) {                                                          
    
    
    int x = get_global_id(0);
    int y = get_global_id(1);
     
    pixels[(y * WIDTH + x)*4] =  0xff; //OPACITY 100% OR 255 
    pixels[(y * WIDTH + x)*4 + 1] = (x & 255) << 16; // the greater x, the more red we use
    pixels[(y * WIDTH + x)*4 + 2] = 0xff; // 
    pixels[(y * WIDTH + x)*4 + 3] = (y & 255) ; //the greater y, the more blue we use

    if((x <= WIDTH) && (y == 0)) 
        printf("pixels[(y * WIDTH + x)*4 + 1] %d = %d\n", x, pixels[(y * WIDTH + x)*4 + 1]);              
}



