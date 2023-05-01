#ifndef __GEOMETRY_HPP__
#define __GEOMETRY_HPP__

//#include "generalHeader.hpp"
#include "/Users/ibrahimatraore/COURSES/ONLY_BOARD_MATHS/board-gpu.hpp"
//TEST_WITH_SINGLE_MP4_FILE: if we do not want DiskE, 
//Just only want to quickly test
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */
#undef DO_NOT_USE_DISKE //because it is defined in ONLY_BOARD
#define DO_NOT_USE_DISKE true
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */

#undef LEFT_MENU_ICONS_PATH
#define LEFT_MENU_ICONS_PATH ( ((DO_NOT_USE_DISKE) == false ) ? "/Volumes/DiskE/MY_CHANELS_VIDEOS_ICONS/LEFT_MENU_ICONS/" : "/Users/ibrahimatraore/COURSES/ONLY_BOARD_MATHS/LEFT_MENU_ICONS//")
#undef MY_FONTS_PATH
#define MY_FONTS_PATH ( ((DO_NOT_USE_DISKE) == false )  ? "/Volumes/DiskE/MY_CHANELS_VIDEOS_ICONS/MY_FONTS/" : "/Users/ibrahimatraore/COURSES/ONLY_BOARD_MATHS/MY_FONTS//")
#undef TOP_MENU_ICONS_PATH
#define TOP_MENU_ICONS_PATH ( ((DO_NOT_USE_DISKE) == false )? "/Volumes/DiskE/MY_CHANELS_VIDEOS_ICONS/TOP_MENU_ICONS/" : "/Users/ibrahimatraore/COURSES/ONLY_BOARD_MATHS/TOP_MENU_ICONS//")
#define MP3_FILE_PATH ( ((DO_NOT_USE_DISKE) == false )? "/Volumes/DiskE/MP3_FILES/" : "/Users/ibrahimatraore/COURSES/ONLY_BOARD_MATHS/single-music-mp3//")

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
#define EXTERN_BACKGROUND_CHOSEN_COLOR BLACK

//----------------- UNSET THE MACRO DEFINE FROM GIT_ONLY_BOARD -------------//
//------------------ REDEFINE IT 
#undef SCREEN_DEFAULT_STROKE_COLOR
#define SCREEN_DEFAULT_STROKE_COLOR  WHITE
 

#undef SCREEN_BACKGROUND_COLOR
#define SCREEN_BACKGROUND_COLOR(x) ( ((x) == BLACK) ? sf::Color( 1, 1,  1 ) : ((x) == WHITE) ? sf::Color(255, 255, 255)  :  (x) ) 
//#define SCREEN_BACKGROUND_COLOR(x) ( ((x) == BLACK || (x) == WHITE || (x) == RED || (x) == GREEN || (x) == BLUE || (x) == YELLOW || (x) == MAGENTA || (x) == TRANSPARENT || (x) == PURPLE || (x) == ORANGE || (x) == CYAN || (x) == GREY || (x) == PINK || (x) == BROWN ) ? (x)    :  sf::Color( ((x) & 0xFF000000) >> 24, ((x) & 0x00FF0000) >> 16, ((x) & 0x0000FF00) >> 8) ) 


//++++++++++++++++++++++++++++++++++++++

#undef  TOP_MENU_LECON_TITLE
#define TOP_MENU_LECON_TITLE " EQUATIONS PARAMETRIQUES " //current lesson title 
//-------------------------------------------------------------------------//


#define NUMBER_CENTER_MENU_IMAGE 2 //because in trigometry first course we have two images(like some others videos)

//Share Screen movies  coefficient
#define SHARE_SCREEN_MOVIES_BUTTONS_FILL_COLOR MAGENTA
#define SHARE_SCREEN_MOVIES_BUTTONS_OUTLINE_COLOR YRED

#define TEXT_VIDEO_NUMBER_FILL_COLOR  CYAN //color for the video number , see left menu bottom
#define TEXT_VIDEO_NUMBER_OUTLINE_COLOR YELLOW

#define SUBDIVISE_SCREEN_WIDTH_FACTOR_FOR_MOVIES 1.0f //[1: fuull screen width, 0.5: hafl screen ..]subdivise window width for movies
#define SUBDIVISE_SCREEN_HEIGHT_FACTOR_FOR_MOVIES 1.0f //[1: fuull screen height, 0.5: hafl screen ..]subdivise window width for movies
#define LIMIT_SHARE_SCREEN_FRACTION 0.5f //share screen in 4 part
/*********************************************************************/
//#define SUBDIVISE_CHILD_SCREEN_WIDTH_FACTOR_FOR_MOVIES 0.5f //[1: fuull screen width, 0.5: hafl screen ..]subdivise window width for movies
//#define SUBDIVISE_CHILD_SCREEN_HEIGHT_FACTOR_FOR_MOVIES 0.5f //[1: fuull screen height, 0.5: hafl screen ..]subdivise window width for movies
//#define LIMIT_CHILD_SHARE_SCREEN_FRACTION 0.25f //share screen in 4 part
/*********************************************************************/
#define SHOW_ANIMATED_SFE_MOVIES_VIDEO true //show animation
#define PLAY_MUSIC_SFE_MOVIES_VIDEO false //play music

#define  MATHS_VIDEO_INDEX 0 //0:intro, 1: first viedo, 2: second video, ...5
#define  MATHS_MUSIC_INDEX 0  //[0, 1]
#define  TIME_OFFSET_BEFORE_PLAYING_MOVIES 4
#define SHOW_CENTER_MENU_SPRITE false // if true, we can see course images(like screen capture of exercices, from geobebra, from Mathex ...)
/*********************************************************************/
#undef LEFT_MENU_DEFAULT_MOUSE_MOVE_RECTANGLE_FILL_WRAPPER_COLOR
#define LEFT_MENU_DEFAULT_MOUSE_MOVE_RECTANGLE_FILL_WRAPPER_COLOR  SCREEN_BACKGROUND_COLOR(EXTERN_BACKGROUND_CHOSEN_COLOR)

#undef LEFT_MENU_DEFAULT_MOUSE_MOVE_RECTANGLE_OUTLINE_WRAPPER_COLOR
#define LEFT_MENU_DEFAULT_MOUSE_MOVE_RECTANGLE_OUTLINE_WRAPPER_COLOR   LEFT_MENU_DEFAULT_MOUSE_MOVE_RECTANGLE_FILL_WRAPPER_COLOR

#undef LEFT_MENU_MOUSE_MOVE_RECTANGLE_OUTLINE_WRAPPER_COLOR
#define LEFT_MENU_MOUSE_MOVE_RECTANGLE_OUTLINE_WRAPPER_COLOR  CYAN //color when moving rectangle
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

#define PREVIOUS_SCRENN_CLICK_BUTTON_COLOR EXTERN_BACKGROUND_CHOSEN_COLOR
#define NEXT_SCRENN_CLICK_BUTTON_COLOR GREEN EXTERN_BACKGROUND_CHOSEN_COLOR


/*************************************************************************/
/*                                                                       */
/*                   DEBUT                                               */
/*                                                                       */
/*************************************************************************/
namespace ext{
 
    /* **************************************************************** */
    /*                                                                  */
    /*                                                                  */
    /*                                                                  */
    /*                                                                  */
    /* ***************************************************************  */
    class ExternCenterMenu {
        public:
            ExternCenterMenu();
            bool is_centerMenu_clicked; //this must be true to handle this class attributes or methods
            sf::Texture course_texture_vector[2]; //png images 'texture (like liked list course png image i did )
            sf::Sprite course_texture_sprite[2]; //png image spirit
            

            void draw(sf::RenderWindow *window);
            ~ExternCenterMenu();
    };

    //* *********************************************************************** */
    /*                                                                         */
    /*                       AnimatedSFE_MOVIES                                */
    /*                                                                         */
    /*    this class implement methods to process manim video                  */
    /*    deal with event such as : change video, forward/backward video,      */
    /*    reduce video size on screen etc ....                                 */
    /*    Note: those video are created in python script                       */
    /*                                                                         */ 
    /* *********************************************************************** */

    class AnimatedSFE_MOVIES {
        public:
            AnimatedSFE_MOVIES();
            AnimatedSFE_MOVIES(int mp3_music_index);

            std::string mediaFile;
            sfe::Movie movie;

            bool  fullscreen;
            bool  stop_playing;
            sf::VideoMode desktopMode;
            float width;
            float height; 

            float VIDEO_INITIAL_WIDTH;
            float VIDEO_INITIAL_HEIGHT;

            //forwar or backward video (see their button inside left menu container while running the script )
            sf::CircleShape   button_video_backward;//to select previous video
            sf::CircleShape button_video_forward;//to select previous video
            sf::Text numberVideo; //you can see it at the bottom of left menu , when you click next/prev video
            sf::Font font;
            sf::Font domain_font;

            sf::CircleShape button_video_share_screen_vertically;//partager ecran verticallement (voir dans le container menu a droite en dessous )
            sf::CircleShape button_video_share_screen_horizontally; //partager ecran horizontalement (voir dans le container menu a droite en dessous )
            float share_screen_width_coef; //1=full screen, 0.5f=half, ...
            float share_screen_height_coef; //1=full screen, 0.5f=half, ...

            bool handleBackwardForwardButtonPressed(sf::Event event, sf::Vector2f &cursorPos);
            void handleShareScreenHorizontallyVerticallydButtonPressed(sf::Event event, sf::Vector2f &cursorPos);
            
            int clickedNumber; //clicked video number (in forward or backward event)
            int mp4_files_number;
        private:
            //int is_share_screen_vertically_horizontally_buttons_clicked(sf::Vector2f &cursorPos);
            int is_backward_forward_buttons_clicked(sf::Vector2f &cursorPos);
           
    }; //AnimatedSFE_MOVIES


    /* *********************************************************************** */
    /*                                                                         */
    /*                        EXTERN_Screen classs                             */
    /*                                                                         */
    /*    This class inherit from ONLY_BOARD Screen class and rewrite some     */
    /*    members functions to take account movie offet time                   */
    /*    This will permit us to strok handwritting corresponding stroke       */
    /*    while moving timeline cursor                                         */
    /*                                                                         */ 
    /* *********************************************************************** */


    class Extern_Screen: public mpc::math::Screen  {

        public:
            Extern_Screen();
            // The followinngs functions rewrite ONLY BOARD Screen class function to take accound the time
            //The time will help us to show corresponding handLines inside screen while
            // moving timeline cursor
            // So inside of saving point as sf::Vertex , we add time
            //void handleScreenMouseButtonPressed(sf::Event event, sf::Vector2f &cursorPos, sf::Time  video_frame_time );
            //void handleScreenMouseMoved(sf::Event event, sf::Vector2f &cursorPos, sf::Time video_frame_time );
            void updateAllStrokeVectorAntiallising(sf::RenderWindow *window);
            //void handleScreenMouseButtonReleased(sf::Event event, sf::Vector2f &cursorPos, sf::Time video_frame_time);
            void prepareStrokeforGpuCpu();

            //New function (previous function are already inside base class: Screen)
            void update_stroke_inside_screen( sf::Time targetTime);

            ~Extern_Screen();
    };

    /*class ChildScreens {
            public:
                ChildScreens(sf::RenderWindow *childWindow);
                // container around all child screen
                sf::RectangleShape ChildScreensContainersWrapper;
                //Single container for single Child
                std::vector<sf::RectangleShape> ChildsScreenSingleContainer;
                
                //Set The small windows 
                sf::VideoMode desktopMode;
                //float share_screen_width_coef;
                float movie_width;
                float movie_height;
                //RenderWindow 
                sf::RenderWindow *renderWindowPointer;
                sfe::Movie movies[NUM_CHILD_WINDOWS];
                void draw(sf::RenderWindow *window) ;
               
    }; */
   
}//ext

//extern ext::Extern_Screen ex_sc;

#endif
