//Include board 
#include "./MY_CHANELS_GENERIC_SYMLINK/ONLY_BOARD_SYMLINK/board-only.hpp"
#include "./MY_CHANELS_GENERIC_SYMLINK/ONLY_BOARD_SYMLINK/board-ext-geometry.hpp"
#include "./MY_CHANELS_GENERIC_SYMLINK/ONLY_BOARD_SYMLINK/board-gpu-kernels.hpp"

// Dear imgui 
#include "MY_CHANELS_GENERIC_SYMLINK/SFE_SFML_IMGUI_LIBS_SYMLINK/basic_imgui/imgui_headers/imgui-SFML.hpp"
#include "MY_CHANELS_GENERIC_SYMLINK/SFE_SFML_IMGUI_LIBS_SYMLINK/basic_imgui/imgui_headers/imgui.hpp"
#include "MY_CHANELS_GENERIC_SYMLINK/SFE_SFML_IMGUI_LIBS_SYMLINK/basic_text_editor/TextEditor/TextEditor.hpp"


//include opencl 
//include external 
#ifndef  DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE 
    #define DEFAULT_OPENCL_KERNEL_INPUT_DATA_SIZE (256 * WIDTH * HEIGHT * 4) //this number must be divide by local=256
#endif
#include "./MY_CHANELS_GENERIC_SYMLINK/MY_OPENCL/myopencl.hpp"


//include library 
#include <cstdio>
#include <string>
#include <thread>
#include <pthread.h>



#define EXTERN_TOTAL_PLOT_POINTS_NUMBERS  1000

//#undef SHOW_ANIMATED_SFE_MOVIES_VIDEO
//    #define SHOW_ANIMATED_SFE_MOVIES_VIDEO true //Play video or not

#undef PLAY_MUSIC_SFE_MOVIES_VIDEO
    #define PLAY_MUSIC_SFE_MOVIES_VIDEO false //play music or not (this macro is not yet used)

//----------------------------------------- SET PARSSER ------------------------------------------------//


//------------------------------------------------------------------------------------------------------//

int main(){
    int ext_index = -1;
    float distanceCumul = 0;
    sf::Vector2f cursorPos;

    //ext::Extern_Screen *ex_sc = new ext::Extern_Screen();
   
    //sf::RenderWindow *sc.currentRenderWindow = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "MATHS PHYSIC CODE - -BOARD", sf::Style::Close | sf::Style::Resize);
    for (int i = static_cast<int>( NUM_RENDER_WINDOWS) - 1; i >= 0 ; i--){
        sc.renderWindows[i] = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), std::string("MPC Board ")+std::to_string(i), sf::Style::Close | sf::Style::Resize);
        if (i == 0){ //set first board to Active
        sc.renderWindows[i]->setActive(true); //for OpenGL
        } else {
            sc.renderWindows[i]->setActive(false); //for OpenGL
        }
    }

    //sf::RenderWindow *sc.currentRenderWindow = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "MATHS MATHS CODE - MATHS-BOARD", sf::Style::Close | sf::Style::Resize);
    //sc.renderWindows[ sc.bm.currentRenderWindowNumber ] = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Main Board", sf::Style::Close | sf::Style::Resize);
    sc.renderWindows[ sc.bm.currentRenderWindowNumber ] = sc.renderWindows[0];
    //sc.renderWindows[ ex_sc.bm.currentRenderWindowNumber ]->setActive(true); //for openGL
    sf::WindowHandle myhandle = sc.renderWindows[ sc.bm.currentRenderWindowNumber ]->getSystemHandle();
    sf::ContextSettings mysettings = sc.renderWindows[ sc.bm.currentRenderWindowNumber ]->getSettings();
    sc.currentRenderWindow = sc.renderWindows[sc.bm.currentRenderWindowNumber];
    // Scale movie to the window drawing area and enable VSync
    sc.currentRenderWindow->setFramerateLimit(WINDOW_FRAME_LIMIT_100);
    sc.currentRenderWindow->setVerticalSyncEnabled(true);

        
    int screenAntialisingDivs = (int)SCREEN_ANTIALISING_DIVS;
   
    std::string str;
    
   

    //------------------------------------ EXTERN -----------------------------------//
    //----------------------------------------------------------------------------------//
    ext::ExternCenterMenu ext_cent_menu = ext::ExternCenterMenu();

    //----------------------------------------------------------------------------------//
    
    /////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////// SFE_MOVIES ///////////////////////////////////////////////
    ext::AnimatedSFE_MOVIES anim_movies = ext::AnimatedSFE_MOVIES("chemistry");
    ext::AnimatedSFE_MOVIES mymusic = ext::AnimatedSFE_MOVIES(MATHS_MUSIC_INDEX);
    bool IS_MUSIC_PLAYING = true;

    UserInterface *ui = NULL;
    StreamSelector *selector_video = NULL;
    StreamSelector *selector_audio = NULL;

    
    const char *menu = "\n\n ================= MENU ======================= \n\
    Shortcuts: SFE-MOVIES\n\
	.... Space - Play / pause \n\
	.... S - Stop \n\
	.... R - Reset \n\
	.... H - Hide / show user controls and mouse cursor\n\
	.... F - Toggle fullscreen \n\
	.... I - Log media info and current state \n\
	.... Alt + V - Select next video stream \n\
	.... Alt + A - Select next audio stream \n\
	.... Alt + S - Select next subtitle stream \n\
	.... Alt + P - Music Volume + \n\
	.... Alt + M - Music Volume - \n\
    .... [No Shortcut for timeline]:simply click inside and move mouse cursor\n\
    ======================================================= \n\n\
    ";
    /* Update Screen background Color */
    sc.lm.container[0].setOutlineColor(  EXTERN_BACKGROUND_CHOSEN_COLOR );
    sc.lm.container[0].setFillColor(  EXTERN_BACKGROUND_CHOSEN_COLOR );
    //sc.lm.scrennBackgroundColor = EXTERN_BACKGROUND_CHOSEN_COLOR;
    /* Update right menu containers colors */
    sc.rm.container[0].setOutlineColor(  EXTERN_BACKGROUND_CHOSEN_COLOR );
    sc.rm.container[0].setFillColor(  EXTERN_BACKGROUND_CHOSEN_COLOR );
    /* Update eraser mobile colors */
    sc.lm.eraser_icon.setFillColor(CYAN);
    sc.lm.eraser_mobile_icon.setFillColor(CYAN);
    /* Update default stroke color */
    sc.currentStrokeDefaultColor[sc.bm.currentRenderWindowNumber] = SCREEN_DEFAULT_STROKE_COLOR;

    /* ************************************************* */
    /*                     DEAR IMGUI                    */
    /* ************************************************* */

     // Initialisez ImGui
    ImGui::CreateContext();
    ImGuiContext* context = ImGui::GetCurrentContext();
    ImGui::SetCurrentContext(context);
    ImGui::SFML::Init(*sc.currentRenderWindow);
    // Augmentez la taille des caractères de 50%
    ImGui::GetIO().FontGlobalScale = static_cast<float>(IMGUI_EDITOR_CHARACTER_SIZE);

     // Variables pour la saisie de texte
    static char inputCodeFromFileBuffer[1024] = "";
    static char inputCodeFromTexEnteredBuffer[1024] = "";
    static bool inputTextIsActive = false;
    static bool inputTextHasFocus = false;
   
    std::string code_compiled_result = "";

    // Load Fonts
	// (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
	ImVec4 clear_col = ImColor(114, 144, 154);

    //Result after compiled Imgui-SFML code 
    sf::Font font;
    font.loadFromFile("./MY_CHANELS_GENERIC_SYMLINK/ONLY_BOARD_SYMLINK/MY_FONTS/arial.ttf");

    sf::Text result("----[Run Result]---- :\n", font, 16);
    result.setPosition(100, 250);
    result.setFillColor(sf::Color::Green);

    ///////////////////////////////////////////////////////////////////////
	// TEXT EDITOR SAMPLE
	TextEditor editor;
	auto lang = TextEditor::LanguageDefinition::CPlusPlus();

    static const char* fileToEdit = "MY_CHANELS_GENERIC_SYMLINK/SFE_SFML_IMGUI_LIBS_SYMLINK/basic_text_editor/fakeScript/code.cpp";
    std::ifstream t(fileToEdit);
    if (t.good())
    {
        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        editor.SetText(str);
    }


     //mpc::math::Screen sc2 = mpc::math::Screen( WHITE, BLACK, BLACK );

    /* ************************************************* */
    /*                 ANIMATED VIDEO                    */
    /* ************************************************* */
    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
        anim_movies.movie.fit(0.5*(WIDTH - anim_movies.width), 0.5*(HEIGHT - anim_movies.height), anim_movies.width, anim_movies.height);
        mymusic.movie.setVolume(DEFAULT_MUSIC_VOLUME);

        ui = new UserInterface(*sc.currentRenderWindow, anim_movies.movie);
        selector_video = new StreamSelector(anim_movies.movie);
        selector_audio = new StreamSelector(mymusic.movie);

        //displayShortcuts();
        //anim_movies.movie.setPlayingOffset(sf::milliseconds(1000 * (int)TIME_OFFSET_BEFORE_PLAYING_MOVIES));
        //anim_movies.movie.play(); PLD
        anim_movies.movie.play();
        
        //if (PLAY_MUSIC_SFE_MOVIES_VIDEO)
            //mymusic.movie.play();
    }
    
    /* ************************************************* */
    /*                 SET CHILDS SCREENNS               */
    /* ************************************************* */
    //CHILD WINDOWS - VIDEOS
    /* CHILD WINDOWS */
   
   /*
    sf::RenderWindow* ChildsRenderWindows[NUM_CHILD_WINDOWS] = {
        new sf::RenderWindow(sf::VideoMode(CHILD_WINDOW_WIDTH, CHILD_WINDOW_HEIGHT), "1", sf::Style::Close | sf::Style::Resize),
        new sf::RenderWindow(sf::VideoMode(CHILD_WINDOW_WIDTH, CHILD_WINDOW_HEIGHT), "2", sf::Style::Close | sf::Style::Resize),
        new sf::RenderWindow(sf::VideoMode(CHILD_WINDOW_WIDTH, CHILD_WINDOW_HEIGHT), "3", sf::Style::Close | sf::Style::Resize),
        new sf::RenderWindow(sf::VideoMode(CHILD_WINDOW_WIDTH, CHILD_WINDOW_HEIGHT), "4", sf::Style::Close | sf::Style::Resize)
    }; */
   
    //sf::RenderWindow childRenderWindow1(sf::VideoMode(CHILD_WINDOW_WIDTH, CHILD_WINDOW_HEIGHT), "1", sf::Style::Close | sf::Style::Resize);
   
    /*childRenderWindow1.setPosition(
        sf::Vector2i(
            80,//childsScrennInstance.ChildsScreenSingleContainer[0].getGlobalBounds().left,
            80//childsScrennInstance.ChildsScreenSingleContainer[0].getGlobalBounds().top
        )
    );*/
    //ext::ChildScreens childsScrennInstance = ext::ChildScreens(&childRenderWindow1);
    
    //childRenderWindow1.setVisible(true);
    //childsScrennInstance.movies[0].play();
    
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////

    //set argument
    sf::Clock clock;
    sf::Clock deltaClock;
    float duration = 0;

    // #  SET TOP MENU TITLE (Because we cannot set it from GIT_ONLY_BOARD_GPU)   # //
 
sc.tm.leconTitle.setString( "THE ALCOHOLS" );

    /*  UPDATE  ONLY_BOARD THE LEFT MENU CONTAINER COLORS(border and background) */
    //sc.lm.container.setFillColor(SCREEN_BACKGROUND_COLOR(EXTERN_BACKGROUND_CHOSEN_COLOR));
    //sc.lm.container.setOutlineColor(SCREEN_BACKGROUND_COLOR(EXTERN_BACKGROUND_CHOSEN_COLOR));


    /*  UPDATE MOBILE ERASER COLOR  */ 
    sc.lm.eraser_mobile_icon.setOutlineColor(SCREEN_BACKGROUND_COLOR(EXTERN_BACKGROUND_CHOSEN_COLOR));
    sc.lm.eraser_mobile_icon.setFillColor(SCREEN_BACKGROUND_COLOR(CYAN));

    //system("update_lecon_title.sh");
    sc.currentRenderWindow->setKeyRepeatEnabled(true);

    printf("%s", menu);
    int i = -1;
    //while(sc.currentRenderWindow->isOpen() && ChildsRenderWindows[++i]->isOpen() && ChildsRenderWindows[++i]->isOpen() && ChildsRenderWindows[++i]->isOpen() && ChildsRenderWindows[++i]->isOpen()){
    while(  sc.currentRenderWindow && sc.currentRenderWindow->isOpen() ){
        
        sf::Time dt = clock.restart();
        duration += dt.asSeconds();

        sf::Event event;
        
        while( sc.currentRenderWindow->pollEvent(event) ){
            switch(event.type){
                case sf::Event::Closed:
                    sc.currentRenderWindow->close();
                    //childRenderWindow1.close();
                    /*
                    ChildsRenderWindows[0]->close();
                    ChildsRenderWindows[1]->close();
                    ChildsRenderWindows[2]->close();
                    ChildsRenderWindows[3]->close(); */
                    break;

                case sf::Event::TextEntered:
                   //TODO : //Extern : SET THE TEXT ENTERED METHODS
                    if ((event.text.unicode > 30 && (event.text.unicode < 128 || event.text.unicode > 159))){}
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape){ 
                        sc.currentRenderWindow->close();
                        //childRenderWindow1.close();
                        /*ChildsRenderWindows[0]->close();
                        ChildsRenderWindows[1]->close();
                        ChildsRenderWindows[2]->close();
                        ChildsRenderWindows[3]->close();*/
                    } //Escape = close window
                    else if (!sc.IS_IMGUI_EDITOR_WINDOW_HOVERED_OR_CLICKED[sc.bm.currentRenderWindowNumber])
                    {
                        if( event.key.code == sf::Keyboard::Backspace ){  } //TODO: for  cleaning backwaed text entered
                        else if( event.key.code == sf::Keyboard::Return ){} //TODO: to validate text entered
                        else if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){ //IF we must show video
                            
                            if(event.key.code == sf::Keyboard::Space) { //Space = PAUSE
                                if (anim_movies.movie.getStatus() == sfe::Playing){ //If  video is already playing, pause it
                                    anim_movies.movie.pause();
                                    if (mymusic.movie.getStatus() == sfe::Playing){//If  music is already playing, pause it
                                    mymusic.movie.pause();
                                    }
                                }
                                else{
                                    anim_movies.stop_playing = true;
                                    anim_movies.movie.play();
                                    if ( (mymusic.movie.getStatus() == sfe::Stopped) ||  (mymusic.movie.getStatus() == sfe::Paused) ){
                                        mymusic.movie.play();
                                    }
                                }
                                IS_MUSIC_PLAYING = !IS_MUSIC_PLAYING; //Music boolean (to play or pause)
                                
                            }
                            else if (event.key.code == sf::Keyboard::A ) {
                                if (event.key.alt){selector_audio->selectNextStream(sfe::Audio);}//Cause segmentation fault
                            }
                            else if (event.key.code == sf::Keyboard::P ) { //Volume +
                                if (event.key.alt){ mymusic.movie.setVolume( std::min(mymusic.movie.getVolume() + KEYPRESS_VOLUME_TO_ADD, (float)MUSIC_MAX_VOLUME));}
                            }
                            else if (event.key.code == sf::Keyboard::M ) { //Volume -
                                if (event.key.alt){mymusic.movie.setVolume( std::max( mymusic.movie.getVolume() - KEYPRESS_VOLUME_TO_ADD, (float)MUSIC_MIN_VOLUME));}
                            }
                            else if (event.key.code == sf::Keyboard::R ) { //Reset ALL so restart again

                                anim_movies.movie.stop();
                                anim_movies.movie.fit(sf::FloatRect(0.5f*(WIDTH - anim_movies.VIDEO_INITIAL_WIDTH), 0.5f*(HEIGHT - anim_movies.VIDEO_INITIAL_HEIGHT), SUBDIVISE_SCREEN_WIDTH_FACTOR_FOR_MOVIES * anim_movies.VIDEO_INITIAL_WIDTH, SUBDIVISE_SCREEN_HEIGHT_FACTOR_FOR_MOVIES * anim_movies.VIDEO_INITIAL_HEIGHT));
                                anim_movies.movie.play();

                                mymusic.movie.stop();
                                mymusic.movie.play();
                            }
                            else if(event.key.code == sf::Keyboard::F ) { // Toggle Full Screen Mode
                                anim_movies.fullscreen = !anim_movies.fullscreen;
                                if (anim_movies.fullscreen){sc.currentRenderWindow->create(anim_movies.desktopMode, "Fullscreen mode Activated", sf::Style::Fullscreen);}
                                else{
                                    sc.currentRenderWindow->create(sf::VideoMode(anim_movies.width, anim_movies.height), "sfeMovie Player",
                                            sf::Style::Close | sf::Style::Resize);}
                            
                                sc.currentRenderWindow->setFramerateLimit(WINDOW_FRAME_LIMIT_60);
                                sc.currentRenderWindow->setVerticalSyncEnabled(true);
                                //Update timelime Postion
                                ui->m_background.setPosition(kHorizontalMargin, sc.currentRenderWindow->getSize().y - kTimelineBackgroundHeight - kVerticalMargin);
                                //Set video size and position
                                anim_movies.movie.fit(0.5*(WIDTH - (float)sc.currentRenderWindow->getSize().x), 0.5*(HEIGHT - (float)sc.currentRenderWindow->getSize().y ), (float)sc.currentRenderWindow->getSize().x, (float)sc.currentRenderWindow->getSize().y);
                                ui->applyProperties(); 
                            }//else if 
                            else if(event.key.code == sf::Keyboard::H ) {  ui->toggleVisible();}//Toggle HIDE/SHOW TumeLine
                            else if(event.key.code == sf::Keyboard::I ) {  displayMediaInfo(anim_movies.movie, mymusic.movie );}//I stand for Info, so display Media Info
                            else if(event.key.code == sf::Keyboard::S ) { //S tand for Stop
                                //if (event.key.alt){selector_video->selectNextStream(sfe::Subtitle);}
                                anim_movies.stop_playing = false;
                                anim_movies.movie.stop();
                                mymusic.movie.stop();
                            
                            
                            }//else if sf::Keyboard::S
                            else if( (event.key.code == sf::Keyboard::Right) && SHOW_ANIMATED_SFE_MOVIES_VIDEO  ) { //Forward or backward
                                // FOR VIDEO
                                anim_movies.movie.pause();
                                sf::Time targetTime =  anim_movies.movie.getPlayingOffset() + sf::seconds(VIDEO_NUMBER_SECOND_TO_JUMP) ;
                                anim_movies.movie.setPlayingOffset( targetTime.asSeconds() > anim_movies.movie.getDuration().asSeconds() ? anim_movies.movie.getDuration() : targetTime  );
                                // FOR AUDIO
                                mymusic.movie.pause();
                                targetTime =  anim_movies.movie.getPlayingOffset();
                                mymusic.movie.setPlayingOffset( targetTime.asSeconds() > mymusic.movie.getDuration().asSeconds() ? mymusic.movie.getDuration() : targetTime  );
                                //Update strokes on the screen
                                sc.update_stroke_inside_screen(targetTime);
                            } //else if sf::Keyboard::Right
                            else if ( (event.key.code == sf::Keyboard::Left) && SHOW_ANIMATED_SFE_MOVIES_VIDEO  )
                            {
                                anim_movies.movie.pause();
                                sf::Time targetTime =  anim_movies.movie.getPlayingOffset() - sf::seconds(VIDEO_NUMBER_SECOND_TO_JUMP) ;
                                anim_movies.movie.setPlayingOffset( targetTime.asSeconds() < sf::seconds(0.01f).asSeconds() ? sf::seconds(0.01f) : targetTime  );
                                // FOR AUDIO
                                mymusic.movie.pause();
                                targetTime =  anim_movies.movie.getPlayingOffset();
                                mymusic.movie.setPlayingOffset( targetTime.asSeconds() < sf::seconds(0.01f).asSeconds() ? sf::seconds(0.01f) : targetTime  );
                                //Update strokes on the screen
                                sc.update_stroke_inside_screen(targetTime);
                            }//else if sf::Keyboard::Left
                            else if(event.key.code == sf::Keyboard::V ) {
                                if (event.key.alt){
                                    selector_video->selectNextStream(sfe::Video);
                                    selector_audio->selectNextStream(sfe::Audio);
                                }
                            }//else if
                        }//else if ( SHOW_ANIMED_SFE_MOVIES_VIDEO )
                    }//if (!sc.IS_IMGUI_EDITOR_WINDOW_HOVERED_OR_CLICKED[sc.currentRenderWindowNumber])
                    break;
                case sf::Event::MouseButtonPressed:

                    //  Bouton pour chnager de video (en bas a gauche left menu)
                    cursorPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*sc.currentRenderWindow));

                    /********************************************************/
                    /* On verifie si on a clicke sur timeline, puis si on a clické  dans la fenetre imgui-Sfml */
                    /* Je traite ça ici car je ne peux pas passer ne namespace Imgui:: en parametre */
                    /* de la fonction handle (à voir                     )  */
                    /********************************************************/
                    

                    //TimeLine Management
                    if (  false == ui->isTimeLineContainerClicked(cursorPos) ){
                       
                        sc.handleScreenMouseButtonPressed_extern_imgui(event, cursorPos, anim_movies.movie.getPlayingOffset(), SCREEN_BACKGROUND_COLOR(EXTERN_BACKGROUND_CHOSEN_COLOR), context);
                        //Movies backward forward event 
                        if(true == anim_movies.handleBackwardForwardButtonPressed(event, cursorPos) ){
                            mymusic.movie.stop();
                        }
                        //Bouton pour rendre petit ou agrandir la video (  en bas à droite right menu) 
                        //anim_movies.handleShareScreenHorizontallyVerticallydButtonPressed(event, cursorPos);
                        
                        //Change windows (while click button management)
                        //before everything, be sure you're not in full mode (because it can crash)
                        if (anim_movies.fullscreen){
                            sc.renderWindows[ sc.bm.previousRenderWindowNumber ]->create(sf::VideoMode(anim_movies.width, anim_movies.height), std::string("MPC Board ") + std::to_string(sc.bm.previousRenderWindowNumber),
                                          sf::Style::Close | sf::Style::Resize);
                            anim_movies.fullscreen =  false;
                        }

                        sc.renderWindows[ sc.bm.previousRenderWindowNumber ]->setVerticalSyncEnabled(  false  ); 
                        sc.currentRenderWindow->setMouseCursorVisible(false );                   
                        sc.renderWindows[ sc.bm.previousRenderWindowNumber ]->setActive( false );
                        sc.currentRenderWindow = sc.renderWindows[ sc.bm.currentRenderWindowNumber ];
                        
                        sc.currentRenderWindow->requestFocus();
                        sc.currentRenderWindow->setVerticalSyncEnabled(true);
                        sc.currentRenderWindow->setMouseCursorVisible(true);
                        sc.currentRenderWindow->setActive(true); 

                        //Redraw TimeLine 
                         delete ui;
                         ui = NULL;
                         ui = new UserInterface(*sc.currentRenderWindow, anim_movies.movie);
                    } else { IS_MUSIC_PLAYING = !IS_MUSIC_PLAYING; }
                    break;
                case sf::Event::MouseMoved:
                    cursorPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*sc.currentRenderWindow));
                    if (  false == ui->isTimeLineContainerClicked(cursorPos) ){  
                        //sc.handleScreenMouseMoved(event, cursorPos);
                        sc.handleScreenMouseMoved_extern_imgui(event, cursorPos, anim_movies.movie.getPlayingOffset(), SCREEN_BACKGROUND_COLOR(EXTERN_BACKGROUND_CHOSEN_COLOR), context);
                    }
                    else if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO && sf::Mouse::isButtonPressed(sf::Mouse::Left)  ){ //Update the timeline cursor position and strokes on screen
                        int xPos = 0;
                    
                        if (event.type == sf::Event::MouseButtonPressed)
                            xPos = event.mouseButton.x;
                        else if (event.type == sf::Event::MouseMoved)
                            xPos = event.mouseMove.x;
                    
                        float ratio = static_cast<float>(xPos) / sc.currentRenderWindow->getSize().x;
                        sf::Time targetTime = ratio * anim_movies.movie.getDuration();
                        anim_movies.movie.setPlayingOffset(targetTime);
                        //UPDATE VISIBLE STROKE ON SCREEN 
                        sc.update_stroke_inside_screen(targetTime);
                    }
                    
                    break;
                case sf::Event::MouseButtonReleased:
                    cursorPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*sc.currentRenderWindow));
                    sc.handleScreenMouseButtonReleased_extern(event, cursorPos, anim_movies.movie.getPlayingOffset(), SCREEN_BACKGROUND_COLOR(EXTERN_BACKGROUND_CHOSEN_COLOR) );
                    //sc.handleScreenMouseButtonReleased(event, cursorPos);
                   
                    break;
                case sf::Event::MouseWheelMoved:
                    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
                        //Update volume
                        if(PLAY_MUSIC_SFE_MOVIES_VIDEO){
                            float volume = mymusic.movie.getVolume() + 10 * event.mouseWheel.delta;
                            volume = std::min(volume, 100.f);
                            volume = std::max(volume, 0.f);
                            mymusic.movie.setVolume(volume);
                            std::cout << "Volume changed to " << int(volume) << "%" << std::endl;  
                        }
                        //Update movies size (bigger/smaller size)
                        //Update movies size (bigger/smaller size)
                        //[Abandonned ]anim_movies.share_screen_height_coef = event.mouseWheel.delta <= 0.0f ? 0.5f : 1.1f ;

                        /*float video_width = anim_movies.movie.getSize().x;
                        float video_height = anim_movies.movie.getSize().y;

                       
                        if ( video_height *  video_height  < 1.f){
                            video_width = std::max(video_width, 250.f);
                            video_height = std::max(video_height, 40.f);
                        } 

                        video_width = video_width > (float)WIDTH ? (float)WIDTH : video_width;
                        video_height = video_height > (float)HEIGHT ? (float)HEIGHT : video_height;
                        //anim_movies.movie.pause();
                        anim_movies.movie.fit(sf::FloatRect(0.5f*(WIDTH -  std::max(video_width, 250.f)), 0.5f*(HEIGHT -   std::max(video_height, 40.f)),  anim_movies.share_screen_width_coef*video_width,   anim_movies.share_screen_width_coef*video_height ));
                        */
                        //anim_movies.movie.play();
                 
                    }//if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO

                    break;
                case sf::Event::Resized:
                    if ( SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
                        anim_movies.movie.fit(0.5*(WIDTH - (float)sc.currentRenderWindow->getSize().x), 0.5*(HEIGHT - (float)sc.currentRenderWindow->getSize().y ), (float)sc.currentRenderWindow->getSize().x, (float)sc.currentRenderWindow->getSize().y);
                        //anim_movies.movie.fit(0, 0, sc.currentRenderWindow->getSize().x, sc.currentRenderWindow->getSize().y);
                        sc.currentRenderWindow->setView(sf::View(sf::FloatRect(0, 0, (float)sc.currentRenderWindow->getSize().x, (float)sc.currentRenderWindow->getSize().y)));
                    }
                    break;
                default:
                    break;
            }// switch(event.type)

        }//while(window.pollEvent(event))

        /* ****************************************** */
        /*     DEBUT UPDATE    IMGUI        UPDATE       */
        /* ****************************************** */
        if (SHOW_IMGUI_TEXT_EDITOR){
            if (sc.bm.previousRenderWindowNumber != sc.bm.currentRenderWindowNumber){
                ImGui::EndFrame();
                ImGui::SFML::Init(*sc.currentRenderWindow);
            }
            ImGui::SFML::Update(*sc.currentRenderWindow, deltaClock.restart());
            // Positionner la fenêtre à un endroit précis
            //ImGui::SetNextWindowPos(ImVec2(WIDTH/2, 20));
            //dimensionner la fenetre
            ImGui::SetNextWindowSize(ImVec2(0.45*WIDTH, 0.75*HEIGHT)); // définir la taille de la fenêtre à 800x600 pixels
            auto cpos = editor.GetCursorPosition();
            ImGui::Begin("Code Editor", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar | ImGuiInputTextFlags_EnterReturnsTrue); //Si j'utilise cette ligne, le petit triangle qui me permet de reduire la fenetre n'apparait plus
            //ImGui::Begin("Code Editor");//, nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar | ImGuiInputTextFlags_EnterReturnsTrue);
        
            // Obtenir la position de la fenêtre ImGui-SFML
            //ImVec2 windowPos = ImGui::GetWindowPos();

            // Afficher la position de la fenêtre ImGui-SFML
            //std::cout << "( "+std::to_string(windowPos.x)+std::string(" ")+std::to_string(windowPos.y)+std::string(" )");
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("New", "Alt-N")){
                        inputTextIsActive = !inputTextIsActive;
                        inputTextHasFocus = true;
                        //std::cout << "Alt ACT° "; std::cout << inputTextIsActive; std::cout << std::endl;
                        //std::cout << "Alt FOC° "; std::cout << inputTextHasFocus; std::cout << std::endl;
                        memset(inputCodeFromFileBuffer, 0, sizeof(inputCodeFromFileBuffer));
                        editor.SetText(inputCodeFromFileBuffer);
                    }
                    if (ImGui::MenuItem("Save"))
                    {
                        strcpy(inputCodeFromFileBuffer ,editor.GetText().c_str());
                        /// save text....
                    }
                    if (ImGui::MenuItem("code.cpp"))
                    {
                        std::ifstream t(fileToEdit);
                        if (t.good())
                        {
                            std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
                            editor.SetText(str);
                        }
                    }
                    if (ImGui::MenuItem("Quit", "Alt-F4"))
                        break;
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Edit"))
                {
                    bool ro = editor.IsReadOnly();
                    if (ImGui::MenuItem("Read-only mode", false, &ro))
                        editor.SetReadOnly(ro);
                    ImGui::Separator();
                    if (ImGui::MenuItem("Undo", "ALT-Backspace", false, !ro && editor.CanUndo()))
                        editor.Undo();
                    if (ImGui::MenuItem("Redo", "Ctrl-Y", false, !ro && editor.CanRedo()))
                        editor.Redo();

                    ImGui::Separator();

                    if (ImGui::MenuItem("Copy", "Ctrl-C", false, editor.HasSelection()))
                        editor.Copy();
                    if (ImGui::MenuItem("Cut", "Ctrl-X", false, !ro && editor.HasSelection()))
                        editor.Cut();
                    if (ImGui::MenuItem("Delete", "Del", false, !ro && editor.HasSelection()))
                        editor.Delete();
                    if (ImGui::MenuItem("Paste", "Ctrl-V", false, !ro && ImGui::GetClipboardText() != nullptr))
                        editor.Paste();
                    

                    ImGui::Separator();

                    if (ImGui::MenuItem("Select all"))
                        editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("View"))
                {
                    if (ImGui::MenuItem("Dark palette"))
                        editor.SetPalette(TextEditor::GetDarkPalette());
                    if (ImGui::MenuItem("Light palette"))
                        editor.SetPalette(TextEditor::GetLightPalette());
                    if (ImGui::MenuItem("Retro blue palette"))
                        editor.SetPalette(TextEditor::GetRetroBluePalette());
                    ImGui::EndMenu();
                }

                ImGui::SameLine();
                if (ImGui::Button("RUN")  ) { 
                    if (strlen(inputCodeFromFileBuffer) ){ // If the showed script is from a file 
                        //std::cout << "inputCodeFromFileBuffer Copié: "; std::cout << inputCodeFromFileBuffer;std::cout << std::endl;
                        code_compiled_result = get_imgui_editor_code_result(inputCodeFromFileBuffer);
                        result.setString(code_compiled_result);
                        memset(inputCodeFromFileBuffer, 0, sizeof(inputCodeFromFileBuffer));
                    }
                    else {
                        editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));
                        strcpy(inputCodeFromTexEnteredBuffer, editor.GetText().c_str());
                        //std::cout << "inputCodeFromTexEnteredBuffer: "; std::cout << inputCodeFromTexEnteredBuffer; std::cout << std::endl;
                        if (strlen(inputCodeFromTexEnteredBuffer)){ //if the schowed script is not from file but from TextEntered
                            code_compiled_result = get_imgui_editor_code_result(inputCodeFromTexEnteredBuffer);
                            result.setString(code_compiled_result);
                            memset(inputCodeFromTexEnteredBuffer, 0, sizeof(inputCodeFromTexEnteredBuffer));
                        }
                    }
                }

                ImGui::SameLine();
                if (ImGui::Button("RESET")  ) { 
                    result.setString("");
                }

                ImGui::EndMenuBar();
            }

            ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
            editor.IsOverwrite() ? "Ovr" : "Ins",
            editor.CanUndo() ? "*" : " ",
            editor.GetLanguageDefinition().mName.c_str(), fileToEdit);
            
            if (inputTextIsActive)
            {
                //ImGui::InputText("##InputText", inputCodeFromFileBuffer, sizeof(inputCodeFromFileBuffer));
                ImGui::InputTextMultiline("##inputCodeFromTexEnteredBuffer", inputCodeFromTexEnteredBuffer, sizeof(inputCodeFromFileBuffer), ImVec2(-1, -1), ImGuiInputTextFlags_EnterReturnsTrue);

                ImGui::SetKeyboardFocusHere(1);
                inputTextHasFocus = ImGui::IsItemActive();
            }
            
            editor.Render("TextEditor");
            ImGui::EndMenu;
            ImGui::End();
        }//if (SHOW_IMGUI_TEXT_EDITOR)


        /* ****************************************** */
        /*      UPDATE     UPDATE        UPDATE       */
        /* ****************************************** */
        //UPDATE MOVIES
        if ( (sc.bm.currentRenderWindowNumber == 0) && SHOW_ANIMATED_SFE_MOVIES_VIDEO ){ //update mp4 video only for the first screen window
            anim_movies.movie.update(); 
            //mymusic.movie.setVolume(  (float)DEFAULT_MUSIC_VOLUME - (float)DEFAULT_MUSIC_VOLUME*anim_movies.movie.getPlayingOffset().asSeconds()/anim_movies.movie.getDuration().asSeconds() );
        }
        if ( (sc.bm.currentRenderWindowNumber == 0) && PLAY_MUSIC_SFE_MOVIES_VIDEO && (mymusic.movie.getPlayingOffset().asSeconds() >= anim_movies.movie.getDuration().asSeconds())  ){ 
            //mymusic.movie.stop(); 
        } 
        if ( (sc.bm.currentRenderWindowNumber == 0) && PLAY_MUSIC_SFE_MOVIES_VIDEO && anim_movies.stop_playing && IS_MUSIC_PLAYING)
            mymusic.movie.play();
        
       //if (sc.bm.currentRenderWindowNumber == 0)
       //     sc.currentRenderWindow->clear(SCREEN_BACKGROUND_COLOR(EXTERN_BACKGROUND_CHOSEN_COLOR));
       //else 
        sc.currentRenderWindow->clear( sc.tm.domainTitle.getOutlineColor() );


        if ( (sc.bm.currentRenderWindowNumber == 0) && SHOW_ANIMATED_SFE_MOVIES_VIDEO ){ //Play mp4 video only for the first scren window
            sc.currentRenderWindow->draw(anim_movies.movie);
            sc.currentRenderWindow->draw(anim_movies.numberVideo);
            
            ui->draw();
        }
    
        if ( SHOW_CENTER_MENU_SPRITE ){ ext_cent_menu.draw( sc.currentRenderWindow ); }
     
        //update 
        //The following function updateAllStrokeGpuCpuAntiallising called LineWithThickness class
        //so that all the sf::Quad built by this LineWithThickness are computed inside opencl kernel
        //Called "__kernel void getCourbePoint " The kernel computed points are given back to host
        //So that the stroke can be drawn.
        //sc.opencl.updateAllStrokeGpuCpuAntiallising(platforms, devices, &commands, &program, &kernel, gpu, local, global);

        //draw menus and grids
        sc.lm.draw(sc.currentRenderWindow); //screen object left menu
        sc.rm.draw(sc.currentRenderWindow); //screen object right menu
       
        sc.tm.draw(sc.currentRenderWindow); //screen TITLE AND LESSON
        sc.grid.draw(sc.currentRenderWindow); //screen object draw

        //Draw bottom menu buttons: the menu were we change window screen at the bottom
        //Aka button + button_text (Like 0, 1 and 2)
        for (int i=0; i< static_cast<int>(NUM_RENDER_WINDOWS); i++){
            sc.currentRenderWindow->draw( sc.bm.windows_buttons_number[sc.bm.currentRenderWindowNumber][i]);
            sc.currentRenderWindow->draw( sc.bm.windows_buttons_number_text[sc.bm.currentRenderWindowNumber][i]);
        }

        //Draw backward and forward video button
        sc.currentRenderWindow->draw(anim_movies.button_video_forward);
        sc.currentRenderWindow->draw(anim_movies.button_video_backward);


        //Draw share menu button
        //[Abandonned]
        //sc.currentRenderWindow->draw(anim_movies.button_video_share_screen_vertically);
        //sc.currentRenderWindow->draw(anim_movies.button_video_share_screen_horizontally);
        
        
        //draw stroke
        //sc.opencl.drawAllStrokeVector(sc.currentRenderWindow);
   
        for (int i=0; i<sc.opencl.geometryRectangleShapeVector.size();i++){
            sc.currentRenderWindow->draw(sc.opencl.geometryRectangleShapeVector[i]);
        }
        
        //-------------------------- EXTERN -------------------------------//
      
        //------------------------------------------------------------------//

         //draw stroke
        sc.opencl.drawCurrentStroke(sc.currentRenderWindow); //draw stroke 
        sc.opencl.drawAllStrokeVector(sc.currentRenderWindow);
        
        /* ****************************************** */
        /*                                            */
        /* ****************************************** */
        //Imgui editor Window
        if ( SHOW_IMGUI_TEXT_EDITOR && (sc.bm.currentRenderWindowNumber == 0) && SHOW_ANIMATED_SFE_MOVIES_VIDEO ){
            sc.currentRenderWindow->draw(result);
            ImGui::SFML::Render(*sc.currentRenderWindow);
        }
        sc.currentRenderWindow->display();
            
    }//while(sc.currentRenderWindow->isOpen())

    std::cout << "\n\n---------------------------------------\n-------- FREEING  RESSOURCES ----------\n---------------------------------------\n";
    std::cout << "Shut down imgui-SFML\n";
    ImGui::SFML::Shutdown();

    //delete window;
    for (int i = 0; i < static_cast<int>( NUM_RENDER_WINDOWS); i++){
        if (sc.renderWindows[i])
            delete sc.renderWindows[i] ;
            std::cout << "deleted window "; std::cout << i; std::cout << "\n" ;
        sc.renderWindows[i] = NULL;
    }
   
    sc.opencl.handLines.clear();
    sc.opencl.showPoints.clear();
    sc.opencl.videoOffsetTimes.clear();
    
  
    for(int i=0; i< sc.opencl.handLinesVector.size(); i++){ sc.opencl.handLinesVector[i].clear();}
    sc.opencl.handLinesVector.clear();

    for(int i=0; i< sc.opencl.showPointsVector.size();i++){sc.opencl.showPointsVector[i].clear();}
    sc.opencl.showPointsVector.clear();

    for(int i=0; i< sc.opencl.videoOffsetTimesVector.size();i++){sc.opencl.videoOffsetTimesVector[i].clear();}
    sc.opencl.videoOffsetTimesVector.clear();

    sc.opencl.geometryRectangleShapeVector.clear();

    std::cout << "... DELETE MOVIES  utils ....\n";
    delete ui;
    std::cout << "Delete ui\n"; 
    delete selector_video;
    std::cout << "Delete selector_video\n"; 
    delete selector_audio;
    std::cout << "Delete selector_audio\n"; 
    std::cout << "--------------------------------------\n--------------------------------------\n--------------------------------------\n";
    

    return EXIT_SUCCESS;
}