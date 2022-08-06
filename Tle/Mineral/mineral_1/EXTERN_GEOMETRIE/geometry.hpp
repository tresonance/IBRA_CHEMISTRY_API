#ifndef __GEOMETRY_HPP__
#define __GEOMETRY_HPP__

//#include "generalHeader.hpp"
#include "../ONLY_BOARD/board-gpu.hpp"


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

#define NUMBER_CENTER_MENU_IMAGE 2 //because in trigometry first course we have two images(like some others videos)

///Backward - Forward buttons  (these buttons are inside leftMenu)
#define BACKWARD_FORWARD_BUTTONS_RADIUS  10
//#define BACKWARD_FORWARD_BUTTONS_FILL_COLOR YSCREEN_BACKGROUND_COLOR

//Backward - forward
#define BACKWARD_FORWARD_BUTTONS_FILL_COLOR YELLOW 
#define BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR RED
#define BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR 0.82f
#define BACKWARD_FORWARD_BUTTONS_SCALEY_FACTOR 0.72f

//Share Screen movies  coefficient
#define SHARE_SCREEN_MOVIES_BUTTONS_FILL_COLOR MAGENTA
#define SHARE_SCREEN_MOVIES_BUTTONS_OUTLINE_COLOR YRED

#define TEXT_VIDEO_NUMBER_FILL_COLOR  CYAN //color for the video number , see left menu bottom
#define TEXT_VIDEO_NUMBER_OUTLINE_COLOR YELLOW

#define SUBDIVISE_SCREEN_WIDTH_FACTOR_FOR_MOVIES 1.0f //[1: fuull screen width, 0.5: hafl screen ..]subdivise window width for movies
#define SUBDIVISE_SCREEN_HEIGHT_FACTOR_FOR_MOVIES 1.0f //[1: fuull screen height, 0.5: hafl screen ..]subdivise window width for movies
#define LIMIT_SHARE_SCREEN_FRACTION 0.5f //share screen in 4 part
/*********************************************************************/
#define SHOW_ANIMATED_SFE_MOVIES_VIDEO true //show animation
#define PLAY_MUSIC_SFE_MOVIES_VIDEO true //play music

#define  MATHS_VIDEO_INDEX 0 //0:intro, 1: first viedo, 2: second video, ...5
#define  MATHS_MUSIC_INDEX 0  //[0, 1]
#define  TIME_OFFSET_BEFORE_PLAYING_MOVIES 4
#define SHOW_CENTER_MENU_SPRITE false // if true, we can see course images(like screen capture of exercices, from geobebra, from Mathex ...)
/*********************************************************************/


namespace ext{
    class ExternCenterMenu {
        public:
            ExternCenterMenu();
            bool is_centerMenu_clicked; //this must be true to handle this class attributes or methods
            sf::Texture course_texture_vector[2]; //png images 'texture (like liked list course png image i did )
            sf::Sprite course_texture_sprite[2]; //png image spirit
            

            void draw(sf::RenderWindow *window);
            ~ExternCenterMenu();
    };

    //---------------------------------//
    //   Manim converted gif
    // See the name of  website which convert manim video mp4 to GIF
    //---------------------------------//
    class AnimatedSFE_MOVIES {
        public:
            AnimatedSFE_MOVIES();
            AnimatedSFE_MOVIES(int mp3_music_index);

            std::string mediaFile;
            sfe::Movie movie;

            bool fullscreen;
            sf::VideoMode desktopMode;
            float width;
            float height; 

            //forwar or backward video (see their button inside left menu container while running the script )
            sf::CircleShape button_video_backward;//to select previous video
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


   
}//ext



#endif
