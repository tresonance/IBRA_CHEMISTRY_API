#ifndef __GEOMETRY_HPP__
#define __GEOMETRY_HPP__

//#include "generalHeader.hpp"
#include "./MY_CHANELS_GENERIC_SYMLINK/ONLY_BOARD_SYMLINK/board-only.hpp"
#include "./MY_CHANELS_GENERIC_SYMLINK/ONLY_BOARD_SYMLINK/board-ext-geometry.hpp"

//TEST_WITH_SINGLE_MP4_FILE: if we do not want DiskE, 
//Just only want to quickly test
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */

#undef LEFT_MENU_ICONS_PATH
#define LEFT_MENU_ICONS_PATH  "/Users/ibrahimatraore/COURSES/ONLY_BOARD/LEFT_MENU_ICONS//"
#undef MY_FONTS_PATH
#define MY_FONTS_PATH  "/Users/ibrahimatraore/COURSES/ONLY_BOARD/MY_FONTS//"
#undef TOP_MENU_ICONS_PATH
#define TOP_MENU_ICONS_PATH "/Users/ibrahimatraore/COURSES/ONLY_BOARD/TOP_MENU_ICONS//"
#define MP3_FILE_PATH  "/Users/ibrahimatraore/COURSES/ONLY_BOARD/single-music-mp3//"

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Shape.hpp>

//#include <SFE_MOVIES/sfeMovie/Movie.hpp> //uncomment if you need sfeMovies
//#include <SFE_MOVIES/sfeMovie/Visibility.hpp> /uncomment if you need sfeMovies


#include <functional>
#include <sstream>
#include <iostream>
#include <vector>




#include <iterator>
#include <tuple>
#include <cmath>

#define WIDTH 1420
#define HEIGHT 900


//----------------- UNSET THE MACRO DEFINE FROM GIT_ONLY_BOARD -------------//
//------------------ REDEFINE IT 
#undef SCREEN_DEFAULT_STROKE_COLOR
#define SCREEN_DEFAULT_STROKE_COLOR  WHITE
 

#undef SCREEN_BACKGROUND_COLOR
#define SCREEN_BACKGROUND_COLOR(x) ( ((x) == BLACK) ? sf::Color( 1, 1,  1 ) : ((x) == WHITE) ? sf::Color(255, 255, 255)  :  (x) ) 
//#define SCREEN_BACKGROUND_COLOR(x) ( ((x) == BLACK || (x) == WHITE || (x) == RED || (x) == GREEN || (x) == BLUE || (x) == YELLOW || (x) == MAGENTA || (x) == TRANSPARENT || (x) == PURPLE || (x) == ORANGE || (x) == CYAN || (x) == GREY || (x) == PINK || (x) == BROWN ) ? (x)    :  sf::Color( ((x) & 0xFF000000) >> 24, ((x) & 0x00FF0000) >> 16, ((x) & 0x0000FF00) >> 8) ) 


/*********************************************************************/
/*ChildScreens macros */

/*#define CHILDS_WINDOWS_CONTAINER_WIDTH 800
#define CHILDS_WINDOWS_CONTAINER_HEIGHT 250
#define CHILD_WINDOW_WIDTH ((CHILDS_WINDOWS_CONTAINER_WIDTH)/NUM_CHILD_WINDOWS)
#define CHILD_WINDOW_HEIGHT CHILDS_WINDOWS_CONTAINER_HEIGHT
#define CHILD_WINDOW_CONTAIINER_X_POS (WIDTH - CHILDS_WINDOWS_CONTAINER_WIDTH - 20)
#define CHILD_WINDOW_CONTAIINER_Y_POS  (HEIGHT -  CHILDS_WINDOWS_CONTAINER_HEIGHT - 10)
#define CHILD_WINDOW_OUTLINE_THICKNESS 1.5
#define CHILD_WINDOW_OUTLINE_COLOR YELLOW
#define CHILD_WINDOW_FILL_COLOR GREEN
#define SHOW_CHILDS_WINDOWS true */

#undef  TOP_MENU_LECON_TITLE
#define TOP_MENU_LECON_TITLE " EQUATIONS PARAMETRIQUES " //current lesson title 
//-------------------------------------------------------------------------//
/*********************************************************************/
#undef LEFT_MENU_DEFAULT_MOUSE_MOVE_RECTANGLE_FILL_WRAPPER_COLOR
#define LEFT_MENU_DEFAULT_MOUSE_MOVE_RECTANGLE_FILL_WRAPPER_COLOR  SCREEN_BACKGROUND_COLOR(EXTERN_BACKGROUND_CHOSEN_COLOR)

#undef LEFT_MENU_DEFAULT_MOUSE_MOVE_RECTANGLE_OUTLINE_WRAPPER_COLOR
#define LEFT_MENU_DEFAULT_MOUSE_MOVE_RECTANGLE_OUTLINE_WRAPPER_COLOR   LEFT_MENU_DEFAULT_MOUSE_MOVE_RECTANGLE_FILL_WRAPPER_COLOR

#undef LEFT_MENU_MOUSE_MOVE_RECTANGLE_OUTLINE_WRAPPER_COLOR
#define LEFT_MENU_MOUSE_MOVE_RECTANGLE_OUTLINE_WRAPPER_COLOR  CYAN //color when moving rectangle


/*************************************************************************/
/*                                                                       */
/*                   DEBUT                                               */
/*                                                                       */
/*************************************************************************/

#endif
