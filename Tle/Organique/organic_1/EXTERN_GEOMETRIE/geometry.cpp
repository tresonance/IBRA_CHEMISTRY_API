
#include "./geometry.hpp"


//* * * * * * * * * * * * * * * * * * * * * * * */
//*   THE DIFFERENTS FONT USE FOR Sfml Text class
//* * * * * * * * * * * * * * * * * * * * * * * */  
const char *MY_EXTERN_FONTS[] = {"arial.ttf", "Pacifico-Regular.ttf"};


//MP4 files to display (videos files build from MANIM)
const char *MP4_FILES_ARRAY[] = {
   //INTROS VIDEOS
    "/Volumes/DiskE/VIDEOS-1ere-Maths-mp4/mp4_trigo/PreviewVideosSeriesTrigo1ere.mp4",
    //COURSES VIDEOS  
     /*1st group*/
    "/Volumes/DiskE/VIDEOS-Tle-Chemistry-mp4/AlcololScene.mp4",
    
};

const char *TEST_SINGLE_MP4_FILE = "/Users/ibrahimatraore/COURSES/MY_CHANELS_CHEMISTRY/Tle/Organique/organic_1/EXTERN_GEOMETRIE/single_test_mp4/AlcololScene.mp4";

//SOUND FILES
const char *MP3_FILES_ARRAY[] =  {
    //"/Users/whodunit/Downloads/ambientloop-30657.mp3"
     "/Volumes/DiskE/MP3_FILES/bluetreeaudio_preview.ogg",
    "/Volumes/DiskE/MP3_FILES/ambientloop-30657.ogg",

     "/Volumes/DiskE/MP3_FILES/bluetreeaudio_preview.mp3",
    "/Volumes/DiskE/MP3_FILES/ambientloop-30657.mp3"
};



/* **************************************************************** */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/* ***************************************************************  */
ext::ExternCenterMenu::ExternCenterMenu(){

    int shift[] = {60, 0.50f*WIDTH, 260, 100, 160, 80};
    sf::Vector2f scales[] = {  
        sf::Vector2f(1.2f, 1.2f), sf::Vector2f(0.87f,0.95f),
        sf::Vector2f(1.2f, 1.2f),
        sf::Vector2f(1.2f, 0.9f),
        sf::Vector2f(1.2f, 1.1f),
        sf::Vector2f(1.1f, 1.1f)
    };

     std::string center_menu_trigo("/Volumes/DiskE/MY_CHANELS_VIDEOS_ICONS/CENTER_MENU_TRIGO_IMAGES/");

    /*
    if (1 == MATHS_VIDEO_INDEX ){
        if( !this->course_texture_vector[0].loadFromFile(center_menu_trigo + std::string(TRIGO_IMAGES[MATHS_VIDEO_INDEX - 1]) )){ std::cout << "[ERROR]: Unable to load course text texture "+std::string(TRIGO_IMAGES[MATHS_VIDEO_INDEX - 1]); exit(1);}
        if( !this->course_texture_vector[1].loadFromFile(center_menu_trigo + std::string(TRIGO_IMAGES[MATHS_VIDEO_INDEX]) ) ){ std::cout << "[ERROR]: Unable to load course text texture "+std::string(TRIGO_IMAGES[MATHS_VIDEO_INDEX]); exit(1);}
        
       
        this->course_texture_sprite[0].setTexture(this->course_texture_vector[0]);
        this->course_texture_sprite[1].setTexture(this->course_texture_vector[1]);

        this->course_texture_sprite[0].setScale(scales[MATHS_VIDEO_INDEX - 1]);
        this->course_texture_sprite[1].setScale(scales[MATHS_VIDEO_INDEX]);

        this->course_texture_sprite[0].setPosition(sf::Vector2f( 0.5f*(0.5*WIDTH - this->course_texture_sprite[0].getGlobalBounds().width),80));
        this->course_texture_sprite[1].setPosition(sf::Vector2f(shift[MATHS_VIDEO_INDEX] + 0.5f*(0.5*WIDTH - this->course_texture_sprite[0].getGlobalBounds().width),80));
     
    }
    else if ( (MATHS_VIDEO_INDEX >= 2) && (MATHS_VIDEO_INDEX <= 5) ){
        if( !this->course_texture_vector[0].loadFromFile(center_menu_trigo + TRIGO_IMAGES[MATHS_VIDEO_INDEX] ) ){ std::cout << "[ERROR]: Unable to load course text texture "+std::string(TRIGO_IMAGES[MATHS_VIDEO_INDEX]); exit(1);}   

        this->course_texture_sprite[0].setTexture(this->course_texture_vector[0]);

        this->course_texture_sprite[0].setScale(scales[MATHS_VIDEO_INDEX]);
        this->course_texture_sprite[0].setPosition(sf::Vector2f( 0.5f*(WIDTH - this->course_texture_sprite[0].getGlobalBounds().width),80));
    }
    else {
        std::cout << "[WARNING - FROM ExternCenterMenu ]: MATHS_VIDEO_INDEX  image not found\n";
    } */
   
}

ext::ExternCenterMenu::~ExternCenterMenu(){}


void ext::ExternCenterMenu::draw(sf::RenderWindow *window){
    if ( (MATHS_VIDEO_INDEX >= 1) && (MATHS_VIDEO_INDEX <= 5) ){
        window->draw( this->course_texture_sprite[0] );

        if (MATHS_VIDEO_INDEX == 1){ // because in this video, we have two sprite image (two capture image )
        window->draw( this->course_texture_sprite[1] );
        }
    }
    
}


//-------------- Animated SFE MOVIES  -------------------------------//
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//*   This class is to implement the GIF class with method and attributes
//*   to manage GIF (the mp4 file converted to GIF)
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ext::AnimatedSFE_MOVIES::AnimatedSFE_MOVIES() //this will be movies instance class in main.cpp
{  
    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
        
        //set font
        std::string volume_font_abs_path(MY_FONTS_PATH);
        if (!this->font.loadFromFile( volume_font_abs_path + MY_EXTERN_FONTS[MYFONTS_INDEX] )){ std::cout << "Error arial not loaded"; exit(2);}
        if (!this->domain_font.loadFromFile( volume_font_abs_path + MY_EXTERN_FONTS[DOMAIN_FONT_INDEX] )){ std::cout << "Error arial not loaded"; exit(2);}
        

        //set  media file
        if (DO_NOT_USE_DISKE)
            this->mediaFile = std::string(TEST_SINGLE_MP4_FILE);
        else 
            this->mediaFile = std::string(MP4_FILES_ARRAY[MATHS_VIDEO_INDEX]);
        
        //this->mediaFile = std::string()
        if (DO_NOT_USE_DISKE)
            this->mp4_files_number = 1;
        else 
            this->mp4_files_number = sizeof(MP4_FILES_ARRAY)/sizeof(MP4_FILES_ARRAY[0]);;
        this->clickedNumber = (int)MATHS_VIDEO_INDEX;
        if (!this->movie.openFromFile(this->mediaFile)){
            my_pause();
            //return 1;
        }
        //this->movie.setPlayingOffset(sf::milliseconds(1000 * (int)TIME_OFFSET_BEFORE_PLAYING_MOVIES));
        
        this->fullscreen = false;
        this->stop_playing = true;
        this->desktopMode = sf::VideoMode::getDesktopMode();
        this->width = std::min(static_cast<float>(this->desktopMode.width), this->movie.getSize().x);
        this->height = std::min(static_cast<float>(this->desktopMode.height), this->movie.getSize().y);

        // For audio files, there is no frame size, set a minimum:
        //printf("//////////////this->width: %f\n", this->width); --> 1280
        //printf("//////////////this->height: %f\n", this->height); --> 720

        if (this->width * this->height < 1.f){
            this->width = std::max(this->width, 250.f);
            this->height = std::max(this->height, 40.f);
        } 

        this->VIDEO_INITIAL_WIDTH = this->width;
        this->VIDEO_INITIAL_HEIGHT = this->height;

        //this->movie.fit(0, 0, this->width, this->height);
        //this->movie.fit(sf::FloatRect(0, 0, this->width, this->height));
        //this->movie.fit(sf::FloatRect(0.5f*(WIDTH - this->width), 0.5f*(HEIGHT - this->height), this->width, this->height));
        this->movie.fit(sf::FloatRect(0.5f*(WIDTH - this->width), 0.5f*(HEIGHT - this->height), SUBDIVISE_SCREEN_WIDTH_FACTOR_FOR_MOVIES*this->width, SUBDIVISE_SCREEN_HEIGHT_FACTOR_FOR_MOVIES*this->height));
        //this->movie.fit(sf::FloatRect(0, 0, WIDTH, HEIGHT));
        
        //set backward and forward buttons
        float shift = 0.0f;
        this->button_video_backward = sf::CircleShape(BACKWARD_FORWARD_BUTTONS_RADIUS, 3);
        //this->button_video_backward.setFillColor(BACKWARD_FORWARD_BUTTONS_FILL_COLOR);
        this->button_video_backward.setFillColor(CYAN);
        this->button_video_backward.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
        this->button_video_backward.setScale(sf::Vector2f(BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR, BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR));
        this->button_video_backward.setRotation(-90) ;
        this->button_video_backward.setPosition(sf::Vector2f(
           sc.lm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().left + 0.5f*sc.lm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().width  - 0.5f*sc.lm.reset_container.getGlobalBounds().width + shift, sc.lm.reset_container.getGlobalBounds().top + sc.lm.reset_container.getGlobalBounds().height + 0.95*LEFT_MENU_SPRIT_ESPACEMENT )
        );

        this->button_video_forward = sf::CircleShape(BACKWARD_FORWARD_BUTTONS_RADIUS, 3);
        this->button_video_forward.setFillColor(BACKWARD_FORWARD_BUTTONS_FILL_COLOR);
        this->button_video_forward.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
        this->button_video_forward.setScale(sf::Vector2f(BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR, BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR));
        this->button_video_forward.setRotation(90) ;
        this->button_video_forward.setPosition(sf::Vector2f(
           sc.lm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().left + 0.5f*sc.lm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().width  + 0.5f*sc.lm.reset_container.getGlobalBounds().width + shift , sc.lm.reset_container.getGlobalBounds().top + sc.lm.reset_container.getGlobalBounds().height + 0.98*LEFT_MENU_SPRIT_ESPACEMENT )
        );

        //set video number text 
        this->numberVideo.setFont(this->font);
        this->numberVideo.setString(TOP_MENU_MPC_TITLE); 
        this->numberVideo.setString(std::to_string(MATHS_VIDEO_INDEX)); 
        this->numberVideo.setCharacterSize(static_cast< float >(DEFAULT_TOP_MENU_MPC_TITLE_TEXT_CHARACTER_SIZE)); // in pixels, not points!
        this->numberVideo.setLetterSpacing(1.5f);
        this->numberVideo.setFillColor(TEXT_VIDEO_NUMBER_FILL_COLOR);
        this->numberVideo.setOutlineColor(TEXT_VIDEO_NUMBER_OUTLINE_COLOR);
        this->numberVideo.setPosition(
             sc.lm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().left + 0.5f*sc.lm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().width  - 0.5f*sc.lm.reset_container.getGlobalBounds().width + shift, sc.lm.reset_container.getGlobalBounds().top + sc.lm.reset_container.getGlobalBounds().height + 2*0.95*LEFT_MENU_SPRIT_ESPACEMENT 
        );

        //set share screen (see the display at the bottom of right menu)
        shift = 5.0f;
        this->share_screen_width_coef = (float)SUBDIVISE_SCREEN_WIDTH_FACTOR_FOR_MOVIES;
        this->share_screen_height_coef = (float)SUBDIVISE_SCREEN_HEIGHT_FACTOR_FOR_MOVIES;

        this->button_video_share_screen_vertically = sf::CircleShape(BACKWARD_FORWARD_BUTTONS_RADIUS, 3);
        //this->button_video_backward.setFillColor(BACKWARD_FORWARD_BUTTONS_FILL_COLOR);
        this->button_video_share_screen_vertically.setFillColor(CYAN);
        this->button_video_share_screen_vertically.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
        this->button_video_share_screen_vertically.setScale(sf::Vector2f(BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR, BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR));
        this->button_video_share_screen_vertically.setRotation(-90) ;
        this->button_video_share_screen_vertically.setPosition(sf::Vector2f(
           sc.rm.colorsContainer_vector[0].getPosition().x - 2.0f*sc.rm.colorsContainer_vector[0].getRadius() , sc.rm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().top + sc.rm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().height + 1.5f*(float)RIGHT_MENU_CIRCLE_ESPACEMENT )
        );

        this->button_video_share_screen_horizontally = sf::CircleShape(BACKWARD_FORWARD_BUTTONS_RADIUS, 3);
        this->button_video_share_screen_horizontally.setFillColor(BACKWARD_FORWARD_BUTTONS_FILL_COLOR);
        this->button_video_share_screen_horizontally.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
        this->button_video_share_screen_horizontally.setScale(sf::Vector2f(BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR, BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR));
        this->button_video_share_screen_horizontally.setRotation(90) ;
        this->button_video_share_screen_horizontally.setPosition(sf::Vector2f(
          sc.rm.colorsContainer_vector[0].getPosition().x + 3.0f*sc.rm.colorsContainer_vector[0].getRadius()+1.5*shift, sc.rm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().top + sc.rm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().height + 1.5f*(float)RIGHT_MENU_CIRCLE_ESPACEMENT - 3.3*shift )
        );
        
    }
}

ext::AnimatedSFE_MOVIES::AnimatedSFE_MOVIES(int mp3_music_index) //This will be audio instance class in main.cpp
{  
    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
        std::string volume_font_abs_path(MY_FONTS_PATH);

        if (!this->font.loadFromFile( volume_font_abs_path + MY_EXTERN_FONTS[MYFONTS_INDEX] )){ std::cout << "Error arial not loaded"; exit(2);}
        if (!this->domain_font.loadFromFile( volume_font_abs_path + MY_EXTERN_FONTS[DOMAIN_FONT_INDEX] )){ std::cout << "Error arial not loaded"; exit(2);}
        
        this->mediaFile = DO_NOT_USE_DISKE == false ? std::string(MP3_FILES_ARRAY[mp3_music_index]): std::string("/Users/ibrahimatraore/COURSES/ONLY_BOARD_MATHS/single-music-mp3/bluetreeaudio_preview.ogg");

        try
        {
            if (DO_NOT_USE_DISKE)
                this->mp4_files_number = 1;
            else
                this->mp4_files_number = sizeof(MP4_FILES_ARRAY)/sizeof(MP4_FILES_ARRAY[0]);
            this->clickedNumber = mp3_music_index;
            if (!this->movie.openFromFile(this->mediaFile)){
                my_pause();
                std::cout << "[ERROR] : Unable to open MP3 music file\n";
                //return 1;
            }else std::cout << "MP3 File OPENED ..................OK\n";
            //this->movie.setPlayingOffset(sf::milliseconds(1000 * (int)TIME_OFFSET_BEFORE_PLAYING_MOVIES));
        }
        catch (std::exception& e)
        {
            my_pause();
            std::cout << "[ERROR] : Unable to open MP3 music file\n";
            std::cout << "[WHICH ERROR]: " <<  e.what() << '\n';
        }

        /*if (!this->movie.openFromFile(this->mediaFile)){
            my_pause();
            std::cout << "[ERROR] : Unable to open MP3 music file\n";
            //return 1;
        } */

        if ( movie.getSize().x && movie.getSize().y ){
        this->fullscreen = false;
        this->stop_playing = true;
        this->desktopMode = sf::VideoMode::getDesktopMode();
        this->width = std::min(static_cast<float>(this->desktopMode.width), this->movie.getSize().x);
        this->height = std::min(static_cast<float>(this->desktopMode.height), this->movie.getSize().y);
        }
        // For audio files, there is no frame size, set a minimum:
        //printf("CCC//////////////this->width: %f\n", this->width); --> 0.0f
        //printf("CCC//////////////this->height: %f\n", this->height); --> 0.0f

        if (this->movie.getSize().x && this->movie.getSize().y && (this->width * this->height < 1.f)  ){
            this->width = std::max(this->width, 250.f);
            this->height = std::max(this->height, 40.f);
        
            //this->movie.fit(0, 0, this->width, this->height);
            //this->movie.fit(sf::FloatRect(0, 0, this->width, this->height));
            this->movie.fit(sf::FloatRect(0.5f*(WIDTH - this->width), 0.5f*(HEIGHT - this->height), SUBDIVISE_SCREEN_WIDTH_FACTOR_FOR_MOVIES*this->width, SUBDIVISE_SCREEN_HEIGHT_FACTOR_FOR_MOVIES*this->height));
            //this->movie.fit(sf::FloatRect(0, 0, WIDTH, HEIGHT));
        }
         //set backward and forward buttons
        float shift = 0.0f;
        this->button_video_backward = sf::CircleShape(BACKWARD_FORWARD_BUTTONS_RADIUS, 3);
        //this->button_video_backward.setFillColor(BACKWARD_FORWARD_BUTTONS_FILL_COLOR);
        this->button_video_backward.setFillColor(CYAN);
        this->button_video_backward.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
        this->button_video_backward.setScale(sf::Vector2f(BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR, BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR));
        this->button_video_backward.setRotation(-90) ;
        this->button_video_backward.setPosition(sf::Vector2f(
           sc.lm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().left + 0.5f*sc.lm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().width  - 0.5f*sc.lm.reset_container.getGlobalBounds().width + shift , sc.lm.reset_container.getGlobalBounds().top + sc.lm.reset_container.getGlobalBounds().height + 0.95*LEFT_MENU_SPRIT_ESPACEMENT )
        );

        this->button_video_forward = sf::CircleShape(BACKWARD_FORWARD_BUTTONS_RADIUS, 3);
        this->button_video_forward.setFillColor(BACKWARD_FORWARD_BUTTONS_FILL_COLOR);
        this->button_video_forward.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
        this->button_video_forward.setScale(sf::Vector2f(BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR, BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR));
        this->button_video_forward.setRotation(-90) ;
        this->button_video_forward.setPosition(sf::Vector2f(
           sc.lm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().left + 0.5f*sc.lm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().width  + 0.5f*sc.lm.reset_container.getGlobalBounds().width + shift, sc.lm.reset_container.getGlobalBounds().top + sc.lm.reset_container.getGlobalBounds().height + 0.98*LEFT_MENU_SPRIT_ESPACEMENT )
        );  

        //set video number text 
        this->numberVideo.setFont(this->font);
        this->numberVideo.setString(TOP_MENU_MPC_TITLE); 
        this->numberVideo.setString(std::to_string(MYFONTS_INDEX)); 
        this->numberVideo.setCharacterSize(static_cast< float >(DEFAULT_TOP_MENU_MPC_TITLE_TEXT_CHARACTER_SIZE)); // in pixels, not points!
        this->numberVideo.setLetterSpacing(1.5f);
        this->numberVideo.setFillColor(TEXT_VIDEO_NUMBER_FILL_COLOR);
        this->numberVideo.setOutlineColor(TEXT_VIDEO_NUMBER_OUTLINE_COLOR);
        this->numberVideo.setPosition(
            sc.lm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().left + 0.5f*sc.lm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().width  - 0.5f*sc.lm.reset_container.getGlobalBounds().width + shift, sc.lm.reset_container.getGlobalBounds().top + sc.lm.reset_container.getGlobalBounds().height + 2*0.95*LEFT_MENU_SPRIT_ESPACEMENT 
        ); 

        //set share screen (see the display at the bottom of right menu)
        shift = 5.0f;
        this->share_screen_width_coef = (float)SUBDIVISE_SCREEN_WIDTH_FACTOR_FOR_MOVIES;
        this->share_screen_height_coef = (float)SUBDIVISE_SCREEN_HEIGHT_FACTOR_FOR_MOVIES;

        this->button_video_share_screen_horizontally = sf::CircleShape(BACKWARD_FORWARD_BUTTONS_RADIUS, 3);
        //this->button_video_backward.setFillColor(BACKWARD_FORWARD_BUTTONS_FILL_COLOR);
        this->button_video_share_screen_horizontally.setFillColor(PINK);
        this->button_video_share_screen_horizontally.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
        this->button_video_share_screen_horizontally.setScale(sf::Vector2f(BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR, BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR));
        this->button_video_share_screen_horizontally.setRotation(-90) ;
        this->button_video_share_screen_horizontally.setPosition(sf::Vector2f(
           sc.rm.colorsContainer_vector[0].getPosition().x - 2.0f*sc.rm.colorsContainer_vector[0].getRadius() , sc.rm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().top + sc.rm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().height + 1.5f*(float)RIGHT_MENU_CIRCLE_ESPACEMENT )
        );

        this->button_video_share_screen_vertically = sf::CircleShape(BACKWARD_FORWARD_BUTTONS_RADIUS, 3);
        this->button_video_share_screen_vertically.setFillColor(BROWN);
        this->button_video_share_screen_vertically.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
        this->button_video_share_screen_vertically.setScale(sf::Vector2f(BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR, BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR));
        this->button_video_share_screen_vertically.setRotation(90) ;
        this->button_video_share_screen_vertically.setPosition(sf::Vector2f(
          sc.rm.colorsContainer_vector[0].getPosition().x + 3.0f*sc.rm.colorsContainer_vector[0].getRadius(), sc.rm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().top + sc.rm.container[sc.bm.currentRenderWindowNumber].getGlobalBounds().height + 1.5f*(float)RIGHT_MENU_CIRCLE_ESPACEMENT + shift )
        );     
    }
}

//backward - forward
int ext::AnimatedSFE_MOVIES::is_backward_forward_buttons_clicked(sf::Vector2f &cursorPos){
    this->button_video_forward.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
    this->button_video_backward.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);

    this->button_video_forward.setFillColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
    this->button_video_backward.setFillColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);

    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
    if(this->button_video_backward.getGlobalBounds().contains(cursorPos)){ 
        --this->clickedNumber;
         //printf("LEFT-------> %d", this->clickedNumber);
        this->button_video_backward.setFillColor(MAGENTA);
     }
    else if(this->button_video_forward.getGlobalBounds().contains(cursorPos)){ 
        ++this->clickedNumber; 
        this->button_video_forward.setFillColor(ORANGE);
         //printf("RIGHT-------> %d", this->clickedNumber);
    }
    if (DO_NOT_USE_DISKE) return 1;
    return (this->mp4_files_number + this->clickedNumber%this->mp4_files_number)%this->mp4_files_number;
    }
    return -1;
}



bool ext::AnimatedSFE_MOVIES::handleBackwardForwardButtonPressed(sf::Event event, sf::Vector2f &cursorPos){
    if ( (false == this->button_video_backward.getGlobalBounds().contains(cursorPos)) && 
    (false == this->button_video_forward.getGlobalBounds().contains(cursorPos)) )
        return false;

    int mp4_file_index = this->is_backward_forward_buttons_clicked( cursorPos );
    if (DO_NOT_USE_DISKE){ mp4_file_index = 1; }
    if (SHOW_ANIMATED_SFE_MOVIES_VIDEO && mp4_file_index >= 0){
        
        //this->mediaFile = std::string(MP4_FILES_ARRAY[mp4_file_index]);
        if (DO_NOT_USE_DISKE)
            this->mediaFile = std::string(TEST_SINGLE_MP4_FILE);
        else 
            this->mediaFile = std::string(MP4_FILES_ARRAY[mp4_file_index]);
        try
        {
            if(!this->movie.openFromFile(this->mediaFile)){
                my_pause(); 
                printf("\n-->>[Error:] Unable to open MP4_FILES_ARRAY[%d]\n", mp4_file_index);
                printf("%s\n\n", this->mediaFile.c_str());
                //return 1;
            }else { 
                //this->movie.stop();
                this->numberVideo.setString(std::to_string(mp4_file_index));
                this->movie.fit(sf::FloatRect(0.5f*(WIDTH - this->width), 0.5f*(HEIGHT - this->height), SUBDIVISE_SCREEN_WIDTH_FACTOR_FOR_MOVIES*this->width, SUBDIVISE_SCREEN_HEIGHT_FACTOR_FOR_MOVIES*this->height));
                this->movie.play();
                if (DO_NOT_USE_DISKE){ printf("\nopened TEST_SINGLE_MP4_FILE: %s .......... OK\n",TEST_SINGLE_MP4_FILE ); }
                else {
                    printf("\nopened MP4_FILES_ARRAY[%d] .......... OK\n",mp4_file_index ); 
                    printf("%s\n\n", this->mediaFile.c_str());
                }
            }
            sf::sleep(sf::milliseconds(10));
            return true;
        }
        catch (std::exception& e)
        {   
            if (DO_NOT_USE_DISKE){ printf("\n-->>[Error:] Unable to open TEST_SINGLE_MP4_FILE: %s\n", TEST_SINGLE_MP4_FILE); }
            else {
                printf("\n-->>[Error:] Unable to open MP4_FILES_ARRAY[%d]\n", mp4_file_index);
                printf("%s\n\n", this->mediaFile.c_str());
            }
            std::cout << "[WHICH ERROR]: " <<  e.what() << '\n';
            return false;
        }
    } 
    return false;
}


//Share Screen
void ext::AnimatedSFE_MOVIES::handleShareScreenHorizontallyVerticallydButtonPressed(sf::Event event, sf::Vector2f &cursorPos){
    this->button_video_share_screen_vertically.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
    this->button_video_share_screen_horizontally.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);

    this->button_video_share_screen_vertically.setFillColor(BROWN);
    this->button_video_share_screen_horizontally.setFillColor(PINK);
    bool must_share_screen = false;
    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
        if(this->button_video_share_screen_horizontally.getGlobalBounds().contains(cursorPos)){ 
            this->share_screen_width_coef *= 0.5f;
            if (this->share_screen_width_coef < LIMIT_SHARE_SCREEN_FRACTION){ this->share_screen_width_coef = (float)SUBDIVISE_SCREEN_WIDTH_FACTOR_FOR_MOVIES;}
            this->button_video_share_screen_horizontally.setFillColor(CYAN);
            must_share_screen = true;
        }
        else if(this->button_video_share_screen_vertically.getGlobalBounds().contains(cursorPos)){ 
            this->share_screen_height_coef *= 0.5f;
            if (this->share_screen_height_coef < LIMIT_SHARE_SCREEN_FRACTION){ this->share_screen_height_coef = (float)SUBDIVISE_SCREEN_HEIGHT_FACTOR_FOR_MOVIES;}
            this->button_video_share_screen_vertically.setFillColor(WHITE_SMOKE);
            must_share_screen = true;
        }
        if (must_share_screen)
            this->movie.fit(sf::FloatRect(0.5f*(WIDTH - this->width), 0.5f*(HEIGHT - this->height), this->share_screen_width_coef*this->width, this->share_screen_height_coef*this->height));
    }

}


/* *********************************************************************** */
/*                                                                         */
/*                        EXTERN_Screen classs                             */
/*                                                                         */
/*    This class inherit from ONLY_BOARD Screen class and rewrite some     */
/*    members functions to take account movie offet time                   */
/*    This will permit us to hide/display handwritting corresponding stroke       */
/*    while moving timeline cursor                                         */
/*                                                                         */ 
/* *********************************************************************** */

ext::Extern_Screen::Extern_Screen():mpc::math::Screen(SCREEN_BACKGROUND_COLOR(EXTERN_BACKGROUND_CHOSEN_COLOR), BLACK, WHITE){
    
}

//The GOAL of this function is to initialize differents inputs buffer (aka inputsX, inputsY, inputsColors, inputTimes)
//for opencl
void ext::Extern_Screen::prepareStrokeforGpuCpu(){ 

    this->DATA_SIZE = 0; //the total number of all stroke line point (line is obtained from mouse down to mouse up) inside handLinesVector

    for(int m=0; m<this->opencl.handLinesVector[this->bm.currentRenderWindowNumber].size(); m++){ //loop over all the stroke lines obtained by handwritting
      this->opencl.DATA_SIZE += this->opencl.handLinesVector[this->bm.currentRenderWindowNumber][m].size(); //sum the current stroke line 
      this->opencl.vectorLength[this->bm.currentRenderWindowNumber].push_back(this->opencl.handLinesVector[this->bm.currentRenderWindowNumber][m].size()); //save each stroke line size
    }//for 

    //INITIALIZE ALL OPENCL INPUT BUFFER  with default values
    this->opencl.screenAntialisingDivs = (int)SCREEN_ANTIALISING_DIVS; //subdivision for each pixel to make antializing (default is 30, s each pixel will be subdivize to 30)
    for(int k=0; k<static_cast<int>( NUM_RENDER_WINDOWS) ;k++){
        for (int i=0;i<DATA_SIZE * SCREEN_ANTIALISING_DIVS; i++){ //loop over the total number of points (obtained with yhe previous antiallizing)
            this->opencl.inputsX[k][i]=0;//with the previous antiallizing value, loop over reserve inputX size (and initialize the point absciss to 0)
            this->opencl.inputsY[k][i]=0; //with the previous antiallizing value, loop over reserve inputX size (and initialize the point ordonnee to 0)
            this->opencl.inputsCodeColors[k][i] = 9;// hide the point by setting their color (index color) to  background color index
            this->opencl.inputsShowPoints[k][i] = 0; //flag to no show the point for this moment
            this->opencl.inputsvideoOffsetTimes[k][i] = 0.0f;
        }
    }
    unsigned int shift = 0; //as its name indicatd, it is to shift , it will help to shift from  handLines to following handLines
    //Now loop over all lines stroke 
    for(int m=0; m<this->opencl.handLinesVector[this->bm.currentRenderWindowNumber].size(); m++)
    {
        //set current stroke line  (vector of points)
        std::vector<sf::Vertex> current_handLines = this->opencl.handLinesVector[this->bm.currentRenderWindowNumber][m];

        for(int i=0; i<current_handLines.size(); i++){
            //NOW  INITIALIZE ALL OPENCL BUFFER WITH corresponding values
            this->opencl.inputsX[this->bm.currentRenderWindowNumber][shift + i] = current_handLines[i].position.x; //copy each line vector absciss inside inputX(for information, inputX will be given to opencl to perform stroke thickness )
            this->opencl.inputsY[this->bm.currentRenderWindowNumber][shift + i] = current_handLines[i].position.y; //copy each line vector ordonnee inside inputX(for information, inputX will be given to opencl to perform stroke thickness )

            this->opencl.inputsShowPoints[this->bm.currentRenderWindowNumber][shift + i] = this->opencl.showPointsVector[this->bm.currentRenderWindowNumber][m][i] ? 1 : 0; //save the points status, if 0 or 1 (aka 0 means point must not be seen), 

            this->opencl.inputsCodeColors[this->bm.currentRenderWindowNumber][shift + i] = setColorsIndex(this->opencl.handLinesVector[this->bm.currentRenderWindowNumber][m][i].color) ; //copy handlinesVector points 
            
            this->opencl.inputsvideoOffsetTimes[this->bm.currentRenderWindowNumber][shift + i] =this->opencl.videoOffsetTimesVector[this->bm.currentRenderWindowNumber][m][i].asSeconds();
        }
        shift += this->opencl.handLinesVector[this->bm.currentRenderWindowNumber][m].size();
    }
}


void ext::Extern_Screen::updateAllStrokeVectorAntiallising(sf::RenderWindow *window)
{
   sf::Vertex lines[2];
    sf::Vector2f t;
    sf::Vector2f dir;;
    float dist;
    sf::Vertex newPoint;
    std::vector<sf::Vertex> vtmp;
    std::vector<bool> vtmp2;

    if (!SCREEN_ANTIALISING){return;}
   
 
    if (this->opencl.handLines[this->bm.currentRenderWindowNumber].size() >= 2) 
    {
        //---------- opencl 
        //loop over all handLinesVector and get each handLines size and get total size (aka total number of points)
        for(int m=0; m < this->opencl.handLinesVector[this->bm.currentRenderWindowNumber].size(); m++)
        {
            //get the total of points (all point vector)
           this->opencl.DATA_SIZE += this->opencl.handLinesVector[this->bm.currentRenderWindowNumber][m].size();
            //Save each handline size
            this->opencl.vectorLength[this->bm.currentRenderWindowNumber].push_back(this->opencl.handLinesVector[this->bm.currentRenderWindowNumber][m].size());
        }

        //----------- opencl
        for(int m=0; m < this->opencl.handLinesVector[this->bm.currentRenderWindowNumber].size(); m++)
        {   
            // get the current handLines
            std::vector<sf::Vertex> current_handLines = this->opencl.handLinesVector[this->bm.currentRenderWindowNumber][m];
            // get the points status list (hidden/show)
            std::vector<bool> current_handLines_showPoints = this->opencl.showPointsVector[this->bm.currentRenderWindowNumber][m];
            //get the points  time 
            std::vector<sf::Time> videoOffsetTimes = this->opencl.videoOffsetTimesVector[this->bm.currentRenderWindowNumber][m];

            //Now loop over each point, starting by index=1
            for(int i=1; i< current_handLines.size(); i++)
            {
                //get the previous point and current point
                lines[0] = current_handLines[i-1];
                lines[1] = current_handLines[i];

                bool previous_point_status = current_handLines_showPoints[i-1];
                bool current_point_status = current_handLines_showPoints[i];

                if ( previous_point_status  &&   current_point_status )
                {
                    //Now use antialising factor to subdivize line and save result inside Vector2f
                    t = sf::Vector2f( 
                    (lines[1].position.x - lines[0].position.x) / ((float)SCREEN_ANTIALISING_DIVS),
                    (lines[1].position.y - lines[0].position.y) / ((float)SCREEN_ANTIALISING_DIVS));

                    //Get vector director coordinate between two points
                    dir = sf::Vector2f(lines[1].position.x - lines[0].position.x, lines[1].position.y - lines[0].position.y );
                    dist = sqrt(dir.x*dir.x + dir.y*dir.y);
                    //Normalize vector director
                    dir = sf::Vector2f(dir.x/(float)dist, dir.y/(float)dist);
                    
                    float tt=0.0f;     
                    for(int j=0;j<SCREEN_ANTIALISING_DIVS;j++)
                    {
                        newPoint = sf::Vertex(sf::Vector2f(
                            lines[0].position.x + tt*dir.x, 
                            lines[0].position.y + tt*dir.y 
                        ), lines[0].color);
                        vtmp.push_back(newPoint);
                        vtmp2.push_back(true);
                        this->opencl.handLines[this->bm.currentRenderWindowNumber].insert(this->opencl.handLines[this->bm.currentRenderWindowNumber].begin()+ i, newPoint);
                        
                        this->opencl.showPoints[this->bm.currentRenderWindowNumber].insert(this->opencl.showPoints[this->bm.currentRenderWindowNumber].begin()+i, true);
                        
                        this->opencl.videoOffsetTimes[this->bm.currentRenderWindowNumber].insert(this->opencl.videoOffsetTimes[this->bm.currentRenderWindowNumber].begin()+i, videoOffsetTimes[i] );

                        tt += 0.1f;
                    }
                }
            }
        }
    }

}



void ext::Extern_Screen::update_stroke_inside_screen( sf::Time targetTime){
     sf::Vector2f pos;
    for(int m=0; m<this->opencl.handLinesVector[this->bm.currentRenderWindowNumber].size(); m++){
        
         std::vector< sf::Vertex > current_handLinesVector = this->opencl.handLinesVector[this->bm.currentRenderWindowNumber][m];

        for(int i=0; i < current_handLinesVector.size(); i++){

           
            sf::Vertex point = current_handLinesVector[i];

            bool point_status = this->opencl.showPointsVector[this->bm.currentRenderWindowNumber][m][i];

            sf::Time point_time = this->opencl.videoOffsetTimesVector[this->bm.currentRenderWindowNumber][m][i];


            if(point_time > targetTime){
                if( point_status == true ){
                     this->opencl.handLinesVector[this->bm.currentRenderWindowNumber][m][i].color  = this->lm.eraser_mobile_icon.getFillColor();
                    this->opencl.showPointsVector[this->bm.currentRenderWindowNumber][m][i] = false;
                }else {
                    //this->opencl.handLinesVector[this->bm.currentRenderWindowNumber][m][i].color  = this->lm.eraser_mobile_icon.getFillColor();
                    this->opencl.showPointsVector[this->bm.currentRenderWindowNumber][m][i] = true;
                }
              
            } 

        }
    }
}

ext::Extern_Screen:: ~Extern_Screen(){}


