
#include "./geometry.hpp"


//* * * * * * * * * * * * * * * * * * * * * * * */
//*   THE DIFFERENTS FONT USE FOR Sfml Text class
//* * * * * * * * * * * * * * * * * * * * * * * */  
const char *MY_EXTERN_FONTS[] = {"arial.ttf", "Pacifico-Regular.ttf"};


const char *TRIGO_IMAGES[] = { //FOR THIS EXTERN CENTER MENU
    "circle_trigo_geogebra.png", "tableau_trigo.png", //first Video (video 1)
    "circle_trigo_geogebra_v2.png", //Second video
    "circle_trigo_exercices.png", //Third video
    "circle_approfondissement.png", //Fourth video
    "trigo_chapitre5.png", //Fifth video

    "circle_x_tan.png",             
    "courbe_sin.png"                
};


//MP4 files to display (videos files build from MANIM)
const char *MP4_FILES[] = {
    //INTROS VIDEOS
    "/Volumes/DiskE/VIDEOS-1ere-Maths-mp4/mp4_produit_scalaire/PreviewVideosSeriesProSca1ere.mp4",
    //COURSES VIDEOS
    //"/Volumes/Disk E/VIDEOS-1ere-Chemistry-mp4/mp4_produit_scalaire/RappelNormU_1.mp4",
    "/Volumes/DiskE/VIDEOS-1ere-Chemistry-mp4//ChanimScene.mp4"
};  

//SOUND FILES
const char *MP3_FILES[] =  {
    //"/Users/whodunit/Downloads/ambientloop-30657.mp3"
     "/Volumes/DiskE/MP3_FILES/bluetreeaudio_preview.ogg",
    "/Volumes/DiskE/MP3_FILES/ambientloop-30657.ogg",

     "/Volumes/DiskE/MP3_FILES/bluetreeaudio_preview.mp3",
    "/Volumes/DiskE/MP3_FILES/ambientloop-30657.mp3"
};


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

    /*if (1 == TRIGONOMETRIE_VIDEO_INDEX ){
        if( !this->course_texture_vector[0].loadFromFile(center_menu_trigo + std::string(TRIGO_IMAGES[TRIGONOMETRIE_VIDEO_INDEX - 1]) )){ std::cout << "[ERROR]: Unable to load course text texture "+std::string(TRIGO_IMAGES[TRIGONOMETRIE_VIDEO_INDEX - 1]); exit(1);}
        if( !this->course_texture_vector[1].loadFromFile(center_menu_trigo + std::string(TRIGO_IMAGES[TRIGONOMETRIE_VIDEO_INDEX]) ) ){ std::cout << "[ERROR]: Unable to load course text texture "+std::string(TRIGO_IMAGES[TRIGONOMETRIE_VIDEO_INDEX]); exit(1);}
        
       
        this->course_texture_sprite[0].setTexture(this->course_texture_vector[0]);
        this->course_texture_sprite[1].setTexture(this->course_texture_vector[1]);

        this->course_texture_sprite[0].setScale(scales[TRIGONOMETRIE_VIDEO_INDEX - 1]);
        this->course_texture_sprite[1].setScale(scales[TRIGONOMETRIE_VIDEO_INDEX]);

        this->course_texture_sprite[0].setPosition(sf::Vector2f( 0.5f*(0.5*WIDTH - this->course_texture_sprite[0].getGlobalBounds().width),80));
        this->course_texture_sprite[1].setPosition(sf::Vector2f(shift[TRIGONOMETRIE_VIDEO_INDEX] + 0.5f*(0.5*WIDTH - this->course_texture_sprite[0].getGlobalBounds().width),80));
     
    }
    else if ( (TRIGONOMETRIE_VIDEO_INDEX >= 2) && (TRIGONOMETRIE_VIDEO_INDEX <= 5) ){
        if( !this->course_texture_vector[0].loadFromFile(center_menu_trigo + TRIGO_IMAGES[TRIGONOMETRIE_VIDEO_INDEX] ) ){ std::cout << "[ERROR]: Unable to load course text texture "+std::string(TRIGO_IMAGES[TRIGONOMETRIE_VIDEO_INDEX]); exit(1);}   

        this->course_texture_sprite[0].setTexture(this->course_texture_vector[0]);

        this->course_texture_sprite[0].setScale(scales[TRIGONOMETRIE_VIDEO_INDEX]);
        this->course_texture_sprite[0].setPosition(sf::Vector2f( 0.5f*(WIDTH - this->course_texture_sprite[0].getGlobalBounds().width),80));
    }
    else {
        std::cout << "[WARNING - FROM ExternCenterMenu ]: TRIGONOMETRIE_VIDEO_INDEX  image not found\n";
    }  */
   
}

ext::ExternCenterMenu::~ExternCenterMenu(){}


void ext::ExternCenterMenu::draw(sf::RenderWindow *window){
    /*if ( (TRIGONOMETRIE_VIDEO_INDEX >= 1) && (TRIGONOMETRIE_VIDEO_INDEX <= 5) ){
        window->draw( this->course_texture_sprite[0] );

        if (TRIGONOMETRIE_VIDEO_INDEX == 1){ // because in this video, we have two sprite image (two capture image )
        window->draw( this->course_texture_sprite[1] );
        }
    } */
    
}



//-------------- Animated SFE MOVIES  -------------------------------//
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//*   This class is to implement the GIF class with method and attributes
//*   to manage GIF (the mp4 file converted to GIF)
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ext::AnimatedSFE_MOVIES::AnimatedSFE_MOVIES()
{  
    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
        
        //set font
        std::string volume_font_abs_path("/Volumes/DiskE/MY_CHANELS_VIDEOS_ICONS/MY_FONTS/");
        if (!this->font.loadFromFile( volume_font_abs_path + MY_EXTERN_FONTS[MYFONTS_INDEX] )){ std::cout << "Error arial not loaded"; exit(2);}
        if (!this->domain_font.loadFromFile( volume_font_abs_path + MY_EXTERN_FONTS[DOMAIN_FONT_INDEX] )){ std::cout << "Error arial not loaded"; exit(2);}
        

        //set  media file
        this->mediaFile = std::string(MP4_FILES[CHEMISTRY_VIDEO_INDEX]);
        //this->mediaFile = std::string()
        this->mp4_files_number = sizeof(MP4_FILES)/sizeof(MP4_FILES[0]);;
        this->clickedNumber = (int)CHEMISTRY_VIDEO_INDEX;
        if (!this->movie.openFromFile(this->mediaFile)){
            my_pause();
            //return 1;
        }
        this->fullscreen = false;
        this->desktopMode = sf::VideoMode::getDesktopMode();
        this->width = std::min(static_cast<float>(this->desktopMode.width), this->movie.getSize().x);
        this->height = std::min(static_cast<float>(this->desktopMode.height), this->movie.getSize().y);

        // For audio files, there is no frame size, set a minimum:
        if (this->width * this->height < 1.f){
            this->width = std::max(this->width, 250.f);
            this->height = std::max(this->height, 40.f);
        } 
        this->movie.fit(0, 0, this->width, this->height);
        //set backward and forward buttons
        float shift = 0.0f;
        this->button_video_backward = sf::CircleShape(BACKWARD_FORWARD_BUTTONS_RADIUS, 3);
        //this->button_video_backward.setFillColor(BACKWARD_FORWARD_BUTTONS_FILL_COLOR);
        this->button_video_backward.setFillColor(CYAN);
        this->button_video_backward.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
        this->button_video_backward.setScale(sf::Vector2f(BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR, BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR));
        this->button_video_backward.setRotation(-90) ;
        this->button_video_backward.setPosition(sf::Vector2f(
           sc.lm.container.getGlobalBounds().left + 0.5f*sc.lm.container.getGlobalBounds().width  - 0.5f*sc.lm.container_resetAll.getGlobalBounds().width + shift, sc.lm.container_resetAll.getGlobalBounds().top + sc.lm.container_resetAll.getGlobalBounds().height + 0.95*LEFT_MENU_SPRIT_ESPACEMENT )
        );

        this->button_video_forward = sf::CircleShape(BACKWARD_FORWARD_BUTTONS_RADIUS, 3);
        this->button_video_forward.setFillColor(BACKWARD_FORWARD_BUTTONS_FILL_COLOR);
        this->button_video_forward.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
        this->button_video_forward.setScale(sf::Vector2f(BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR, BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR));
        this->button_video_forward.setRotation(90) ;
        this->button_video_forward.setPosition(sf::Vector2f(
           sc.lm.container.getGlobalBounds().left + 0.5f*sc.lm.container.getGlobalBounds().width  + 0.5f*sc.lm.container_resetAll.getGlobalBounds().width + shift , sc.lm.container_resetAll.getGlobalBounds().top + sc.lm.container_resetAll.getGlobalBounds().height + 0.98*LEFT_MENU_SPRIT_ESPACEMENT )
        );

        //set video number text 
        this->numberVideo.setFont(this->font);
        this->numberVideo.setString(TOP_MENU_MPC_TITLE); 
        this->numberVideo.setString(std::to_string(CHEMISTRY_VIDEO_INDEX)); 
        this->numberVideo.setCharacterSize(static_cast< float >(DEFAULT_TOP_MENU_MPC_TITLE_TEXT_CHARACTER_SIZE)); // in pixels, not points!
        this->numberVideo.setLetterSpacing(1.5f);
        this->numberVideo.setFillColor(TEXT_VIDEO_NUMBER_FILL_COLOR);
        this->numberVideo.setOutlineColor(TEXT_VIDEO_NUMBER_OUTLINE_COLOR);
        this->numberVideo.setPosition(
             sc.lm.container.getGlobalBounds().left + 0.5f*sc.lm.container.getGlobalBounds().width  - 0.5f*sc.lm.container_resetAll.getGlobalBounds().width + shift, sc.lm.container_resetAll.getGlobalBounds().top + sc.lm.container_resetAll.getGlobalBounds().height + 2*0.95*LEFT_MENU_SPRIT_ESPACEMENT 
        );

        
    }
}

ext::AnimatedSFE_MOVIES::AnimatedSFE_MOVIES(int mp3_music_index)
{  
    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
        std::string volume_font_abs_path("/Volumes/DiskE/MY_CHANELS_VIDEOS_ICONS/MY_FONTS/");

        if (!this->font.loadFromFile( volume_font_abs_path + MY_EXTERN_FONTS[MYFONTS_INDEX] )){ std::cout << "Error arial not loaded"; exit(2);}
        if (!this->domain_font.loadFromFile( volume_font_abs_path + MY_EXTERN_FONTS[DOMAIN_FONT_INDEX] )){ std::cout << "Error arial not loaded"; exit(2);}
     
        this->mediaFile = std::string(MP3_FILES[mp3_music_index]);
        try
        {
            this->mp4_files_number = sizeof(MP4_FILES)/sizeof(MP4_FILES[0]);
            this->clickedNumber = mp3_music_index;
            if (!this->movie.openFromFile(this->mediaFile)){
                my_pause();
                std::cout << "[ERROR] : Unable to open MP3 music file\n";
                //return 1;
            }else std::cout << "MP3 File OPENED ..................OK\n";
             
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

        this->fullscreen = false;
        this->desktopMode = sf::VideoMode::getDesktopMode();
        this->width = std::min(static_cast<float>(this->desktopMode.width), this->movie.getSize().x);
        this->height = std::min(static_cast<float>(this->desktopMode.height), this->movie.getSize().y);

        // For audio files, there is no frame size, set a minimum:
        if (this->width * this->height < 1.f){
            this->width = std::max(this->width, 250.f);
            this->height = std::max(this->height, 40.f);
        } 
        this->movie.fit(0, 0, this->width, this->height);

         //set backward and forward buttons
        float shift = 0.0f;
        this->button_video_backward = sf::CircleShape(BACKWARD_FORWARD_BUTTONS_RADIUS, 3);
        //this->button_video_backward.setFillColor(BACKWARD_FORWARD_BUTTONS_FILL_COLOR);
        this->button_video_backward.setFillColor(CYAN);
        this->button_video_backward.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
        this->button_video_backward.setScale(sf::Vector2f(BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR, BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR));
        this->button_video_backward.setRotation(-90) ;
        this->button_video_backward.setPosition(sf::Vector2f(
           sc.lm.container.getGlobalBounds().left + 0.5f*sc.lm.container.getGlobalBounds().width  - 0.5f*sc.lm.container_resetAll.getGlobalBounds().width + shift , sc.lm.container_resetAll.getGlobalBounds().top + sc.lm.container_resetAll.getGlobalBounds().height + 0.95*LEFT_MENU_SPRIT_ESPACEMENT )
        );

        this->button_video_forward = sf::CircleShape(BACKWARD_FORWARD_BUTTONS_RADIUS, 3);
        this->button_video_forward.setFillColor(BACKWARD_FORWARD_BUTTONS_FILL_COLOR);
        this->button_video_forward.setOutlineColor(BACKWARD_FORWARD_BUTTONS_OUTLINE_COLOR);
        this->button_video_forward.setScale(sf::Vector2f(BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR, BACKWARD_FORWARD_BUTTONS_SCALEX_FACTOR));
        this->button_video_forward.setRotation(-90) ;
        this->button_video_forward.setPosition(sf::Vector2f(
           sc.lm.container.getGlobalBounds().left + 0.5f*sc.lm.container.getGlobalBounds().width  + 0.5f*sc.lm.container_resetAll.getGlobalBounds().width + shift, sc.lm.container_resetAll.getGlobalBounds().top + sc.lm.container_resetAll.getGlobalBounds().height + 0.98*LEFT_MENU_SPRIT_ESPACEMENT )
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
             sc.lm.container.getGlobalBounds().left + 0.5f*sc.lm.container.getGlobalBounds().width  - 0.5f*sc.lm.container_resetAll.getGlobalBounds().width + shift, sc.lm.container_resetAll.getGlobalBounds().top + sc.lm.container_resetAll.getGlobalBounds().height + 2*0.95*LEFT_MENU_SPRIT_ESPACEMENT 
        );      
    }
}

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
    
    return (this->mp4_files_number + this->clickedNumber%this->mp4_files_number)%this->mp4_files_number;
    }
    return -1;
}



bool ext::AnimatedSFE_MOVIES::handleBackwardForwardButtonPressed(sf::Event event, sf::Vector2f &cursorPos){
    if ( (false == this->button_video_backward.getGlobalBounds().contains(cursorPos)) && 
    (false == this->button_video_forward.getGlobalBounds().contains(cursorPos)) )
        return false;

    int mp4_file_index = this->is_backward_forward_buttons_clicked( cursorPos );
    if (SHOW_ANIMATED_SFE_MOVIES_VIDEO && mp4_file_index >= 0){
        
        //this->mediaFile = std::string(MP4_FILES[mp4_file_index]);
        this->mediaFile = std::string(MP4_FILES[mp4_file_index]);
        try
        {
            if(!this->movie.openFromFile(this->mediaFile)){
                my_pause(); 
                printf("\n-->>[Error:] Unable to open MP4_FILES[%d]\n", mp4_file_index);
                printf("%s\n\n", this->mediaFile.c_str());
                //return 1;
            }else { 
                //this->movie.stop();
                this->numberVideo.setString(std::to_string(mp4_file_index));
                this->movie.play();
                printf("\nopened MP4_FILES[%d] .......... OK\n",mp4_file_index ); 
                printf("%s\n\n", this->mediaFile.c_str());
            }
            sf::sleep(sf::milliseconds(10));
            return true;
        }
        catch (std::exception& e)
        {
            printf("\n-->>[Error:] Unable to open MP4_FILES[%d]\n", mp4_file_index);
            printf("%s\n\n", this->mediaFile.c_str());
            std::cout << "[WHICH ERROR]: " <<  e.what() << '\n';
            return false;
        }
    } 
    return false;
}
