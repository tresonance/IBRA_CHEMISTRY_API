
#include "./geometry.hpp"


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
    "/Volumes/Disk E/VIDEOS-1ere-Maths-mp4/mp4_produit_scalaire/PreviewVideosSeriesProSca1ere.mp4",
    //COURSES VIDEOS
    //"/Volumes/Disk E/VIDEOS-1ere-Chemistry-mp4/mp4_produit_scalaire/RappelNormU_1.mp4",
    "/Volumes/Disk E/VIDEOS-1ere-Chemistry-mp4//ChanimScene.mp4"
};  

//SOUND FILES
const char *MP3_FILES[] =  {
    //"/Users/whodunit/Downloads/ambientloop-30657.mp3"
     "/Volumes/Disk E/MP3_FILES/bluetreeaudio_preview.ogg",
    "/Volumes/Disk E/MP3_FILES/ambientloop-30657.ogg",

     "/Volumes/Disk E/MP3_FILES/bluetreeaudio_preview.mp3",
    "/Volumes/Disk E/MP3_FILES/ambientloop-30657.mp3"
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

     std::string center_menu_trigo("/Volumes/Disk E/MY_CHANELS_VIDEOS_ICONS/CENTER_MENU_TRIGO_IMAGES/");

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
        this->mediaFile = std::string(MP4_FILES[CHEMISTRY_VIDEO_INDEX]);
        //this->mediaFile = std::string()
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
                
    }
}

ext::AnimatedSFE_MOVIES::AnimatedSFE_MOVIES(int mp3_music_index)
{  
    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
        this->mediaFile = std::string(MP3_FILES[mp3_music_index]);
        try
        {
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
                
    }
}
