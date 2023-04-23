#!/bin/bash

# Reset
RESET='\033[0m'       # Text Reset

# Regular Colors
BLACK='\033[0;30m'        # Black
RED='\033[0;31m'          # Red
GREEN='\033[0;32m'        # Green
YELLOW='\033[0;33m'       # Yellow
BLUE='\033[0;34m'         # Blue
PURPLE='\033[0;35m'       # Purple
CYAN='\033[0;36m'         # Cyan
GREEN='\033[0;37m'        # GREEN

# Background
ONBLACK='\033[40m'       # Black
ONRED='\033[41m'         # Red
ONGREEN='\033[42m'       # Green
ONYELLOW='\033[43m'      # Yellow
ONBLUE='\033[44m'        # Blue
ONPURPLE='\033[45m'      # Purple
ONCYAN='\033[46m'        # Cyan
ONGREEN='\033[47m'       # GREEN

# set color variable
COLOR_COMMAND=$CYAN
ONCOLOR_FAILED=$ONRED
ONCOLOR_SUCCESS=$ONCYAN
# level
class_level="Tle"
#class_level="Tle"

# set image name (see Dockerfile)
my_manim_image="chemistry_image"
# set container name
my_manim_container_name="my-chemistry-tle-container"

# Suject name in DISKE (where we must save this videos )
#Exemple "Physic" in /Volumes/DiskE/VIDEOS-1ere-Physic-mp4
diske_topic="Chemistry" 

#  variable GIT_MY_CHANEL_NAME, #Exemple: GIT_MY_CHANNELS_MATHS
GIT_MY_CHANEL_NAME=$(pwd | cut -d "/" -f 4) 

# save python script file
PYTHON_SCRIPT_FILE=""

# recall Usage
if [ "$#" -eq 0 ]; 
then 
    #echo -e "\n${ONCOLOR_FAILED} [To run python script] Usage ./runs.sh my_python_file.py ${RESET}\n\n${ONCOLOR_FAILED} [To exit from container ] Usage  ./runs.sh down ${RESET} \n\n${ONCOLOR_FAILED}[To save videos to Volume  ] Usage  ./runs.sh save ${RESET} \n"
    echo 
    echo -e "${YELLOW} .+.+..................... U S A G E ..................+.+. ${RESET}\n"
    echo -e "${ONPURPLE} PLEASE, MOUNT YOUR DiskE BEFORE ${RESET}\n"
    echo -e "${ONCYAN} Info: To removed container run: ./run.sh down \t\t\t ${RESET}\n"
    echo -e "${ONPURPLE} Info: To save videos to volume:  run: ./run.sh save \t\t ${RESET}\n"
    echo -e "${ONCYAN} Info: To build MANIM videos ./run.sh  my-python_script.py \t ${RESET}\n"
    echo -e "${ONPURPLE} Info: To build corresponding docker image:  run: ./run.sh build ${RESET}\n"
    echo -e "${ONCYAN} Info: To create ONLY_BOARD_MATHS symlink:  run: ./run.sh symlink_ol or ./run.sh symol \t ${RESET}\n"
    echo -e "${ONPURPLE} Info: To run make command:  run: ./run.sh make \t OR \t run inside EXTERN_GEOMETRIE directory: make re${RESET}\n"
    echo -e "${ONYELLOW} Info: To create libsfe_movie_bin.so symlink:  run: ./run.sh symlink_lib or ./run.sh symlib \t ${RESET}\n"
    echo -e "${ONCYAN} Info: To clean binary ceated object:  run: ./run.sh clean \t OR \t run inside EXTERN_GEOMETRIE directory: make fclean && make clean ${RESET}\n"
    echo -e "${ONPURPLE} Info: To clean binray object and run make re:  run: ./run.sh makec \t OR \t run inside EXTERN_GEOMETRIE directory : make clean && make fclean && make re ${RESET}\n"
    echo -e "${YELLOW} .......................END  U S A G E INFO.................... ${RESET}\n"

    return 
fi 

if [ "$1" == "down" ]; 
then 
    docker stop $my_manim_container_name > /dev/null 
    docker rm -f  $my_manim_container_name > /dev/null 
    echo -e "${ONPURPLE} Container $my_manim_container_name stopped and removed  ${RESET} \n"
    return 
elif [ "$1" == "save" ];
then 
        # Mount Volume 
        MOUNT_FILES="$(mount -t /dev/disk2s1 && ls  "/Volumes/DiskE"  )"
        if [ "$?" != 0 ];
        then 
            echo -e "${ONCOLOR_FAILED} [ERROR]: DiskE not found ${RESET} \n"
            return 
        fi 
       
        #VOLUME_VIDEOS_PATH="/Volumes/DiskE/VIDEOS-1ere-Maths-mp4/mp4_trigo"
        VOLUME_VIDEOS_PATH="/Volumes/DiskE/VIDEOS-${class_level}-${diske_topic}-mp4/"
        #MANIM_VIDEOS_BASE_PATH="/Users/whodunit/MY_CHANNELS_MATHS/1ere/Geometry/VIDEO-1ere-PRO-SCALAIRE-1-2-3-4/MANIM/media/videos"
        #MANIM_VIDEOS_BASE_PATH="/Users/whodunit/${GIT_MY_CHANEL_NAME}/${class_level}/MANIM/media/videos"
        MANIM_VIDEOS_BASE_PATH="$(pwd)/media/videos"

        #MP4_FILES_BASE_NAME=$(find ${MANIM_VIDEOS_BASE_PATH} -type f -name "[a-zA-Z]*.mp4" | while read line; do basename $line ;done )
        MP4_FILES_ABSOLUTE_NAME=$(find ${MANIM_VIDEOS_BASE_PATH} -type f -name "[a-zA-Z]*.mp4" )
        #MP4= $(echo ${MP4_FILES_ABSOLUTE_NAME} | while read line; do set a=$(basename $line); echo $a ;done  )
        if  [ "$?" == 0 ];
        then
            for i in "${!MP4_FILES_ABSOLUTE_NAME[@]}"; do 
                MP4_FILE_BASENAME=$(basename ${MP4_FILES_ABSOLUTE_NAME[$i]} )
                $(cp  ${MP4_FILES_ABSOLUTE_NAME[$i]} "${VOLUME_VIDEOS_PATH}/${MP4_FILE_BASENAME}" )
                
                if  [ "$?" == 0 ];
                then
                    CHECK_FILES_IN_VOLUME=$(ls $VOLUME_VIDEOS_PATH )
                    echo -e "[Volumes]: $CHECK_FILES_IN_VOLUME > /dev/null 2>&1"

                else 
                    echo -e "\n${ONCOLOR_FAILED} Unable to copy file to volumes ${RESET} \n"
                fi

            done
            echo -e "${ONBLUE} VIDEOS HAS BEEN SAVED TO VOLUME : "${VOLUME_VIDEOS_PATH}/${MP4_FILE_BASENAME}" ${RESET} \n"
        else 
            echo -e "\n${ONCOLOR_FAILED} [FAILED TO SAVE VIDEOS TO VOLUME] ${RESET}\n"
        fi
        return 
elif [ "$1" == "build" ]; #this is specific for chemistry because it is our own created image
then 
    echo -e "${ONBLUE} START BUILDING DOCKER CONTAINER IMAGE ${my_manim_image}  ${RESET} \n"
    $(docker build -t $my_manim_image .)
    echo -e "...............Finish created New Physic docker image ............\n"
    $(docker images | grep $my_manim_image)
    return
elif [[ "$1" == "symol" || "$1" == "symlink_ol" ]]; #symlink_onlyboard
then 
    #$(rm -rf EXTERN_GEOMETRIE/ONLY_BOARD && rm -rf ../ONLY_BOARD)
    #$(ln -s /Users/ibrahimatraore/COURSES/GIT_ONLY_BOARD_GPU/ ONLY_BOARD > /dev/null 2>&1)
    $(rm -rf ../EXTERN_GEOMETRIE/ONLY_BOARD_MATHS  > /dev/null 2>&1 )
    # create new
    $(ln -s /Users/ibrahimatraore/COURSES/ONLY_BOARD_MATHS ONLY_BOARD_MATHS > /dev/null 2>&1 )
    $(mv ./ONLY_BOARD_MATHS  ../EXTERN_GEOMETRIE/ > /dev/null 2>&1 )
    # remove recursive untracked dir in ONLY_DIR (the original not he link)
    $(rm -rf /Users/ibrahimatraore/COURSES/ONLY_BOARD_MATHS/ONLY_BOARD_MATHS > /dev/null 2>&1)
    
    echo -e "${ONBLUE} ONLY_BOARD_MATHS@ link has been created with ONLY_BOARD_MATHS DIRECTORY${RESET} \n"
    result=$(ls -lrt ../EXTERN_GEOMETRIE | grep ONLY_BOARD_MATHS)
    echo -e "${CYAN} ${result} ${RESET}\n"
    return 
elif [[ "$1" == "symlib" || "$1" == "symlink_lib" ]];
then 
    #$(rm -rf EXTERN_GEOMETRIE/ONLY_BOARD && rm -rf ../ONLY_BOARD)
    #$(ln -s /Users/ibrahimatraore/COURSES/GIT_ONLY_BOARD_GPU/ ONLY_BOARD > /dev/null 2>&1)
    $(rm -rf ../EXTERN_GEOMETRIE/libsfe_movie_bin.so  > /dev/null 2>&1 )
    # create new
    $(ln -s /Users/ibrahimatraore/COURSES/SFE_SFML_LIBS/basic_sfe/libsfe_movie_bin.so libsfe_movie_bin.so > /dev/null 2>&1 )
    $(mv ./libsfe_movie_bin.so  ../EXTERN_GEOMETRIE/ > /dev/null 2>&1 )
    # remove recursive untracked dir in ONLY_DIR (the original not he link)
     $(rm -rf /Users/ibrahimatraore/COURSES/MY_CHANELS_MATHS/DYNAMIC/MANIM/libsfe_movie_bin.so)
    $(rm -rf /Users/ibrahimatraore/COURSES/libsfe_movie_bin.so/libsfe_movie_bin.so > /dev/null 2>&1)
    
    echo -e "${ONGREEN} libsfe_movie_bin.so@ link has been created with SFE_SFML_LIBS DIRECTORY${RESET}\n"
    $(ln -s /Users/ibrahimatraore/COURSES/SFE_SFML_LIBS/basic_sfe/libsfe_movie_bin.so   libsfe_movie_bin.so)
    result=$(ls -lrt ../EXTERN_GEOMETRIE | grep libsfe_movie_bin.so)
    echo -e "${CYAN} ${result} ${RESET}\n"
    return 
elif [ "$1" == "make" ]
then 
    echo "cd ../EXTERN_GEOMETRIE/ && make re && cd -"
    echo
    $(cd ../EXTERN_GEOMETRIE/ && make re && cd -)
     $(rm -rf /Users/ibrahimatraore/COURSES/GIT_ONLY_BOARD_GPU/ONLY_MATHS/ONLY_MATHS > /dev/null 2>&1)
    return 
elif [ "$1" == "clean" ]
then 
    echo "cd ../EXTERN_GEOMETRIE/ && make fclean && make clean && cd - > /dev/null 2>&1"
    echo
    $(cd ../EXTERN_GEOMETRIE/ && make fclean && make clean && cd - > /dev/null 2>&1)
     $(rm -rf /Users/ibrahimatraore/COURSES/GIT_ONLY_BOARD_GPU/ONLY_MATHS/ONLY_MATHS > /dev/null 2>&1)
    return 
elif [ "$1" == "makec" ]
then 
    $(rm -rf /Users/ibrahimatraore/COURSES/GIT_ONLY_BOARD_GPU/ONLY_MATHS/ONLY_MATHS > /dev/null 2>&1)
    echo "cd ../EXTERN_GEOMETRIE/ && make clean && make fclean && make re && cd -"
    echo
    echo -e "\n${ONWHITE} ${ONCYAN}......... Program MATHS is running ....... ${RESET}\n"
    $(cd ../EXTERN_GEOMETRIE/ && make fclean && make clean && make re && cd -  > /dev/null 2>&1)
    
    return 
elif [[ "$1" == *.py ]]
then 
    # ............... Remove unexpected directory .............
     $(rm -rf /Users/ibrahimatraore/COURSES/GIT_ONLY_BOARD_GPU/ONLY_MATHS/ONLY_MATHS > /dev/null 2>&1)
    # .............. SET THE LESSON TITLE .................... #
    LECON_TITLE=$(cat $1 | grep -i TOP_MENU_LECON_TITLE_FROM_MANIM_PYTHON_FILE | awk -F "=" '{print $2}')
    # Example of result: "CARDINAL D'UN ENSEMBLE "
    result1=$?

    LECON_TITLE_LINE_NUMBER=$( cat -n ../EXTERN_GEOMETRIE/main.cpp | sed -n "/sc.tm.leconTitle.setString/p" | awk '{print $1}' )
    result2=$?

    if [ "$result1" != 0  ];
    then 
        echo -e "\033[0;31m [WARNING]: Unable to find lesson title from your python script to main.cpp  \033[0m \n"
    else
        echo -e "\033[0;35m COURSE_TITLE = $LECON_TITLE \033[0m \n"

        $(sed -i -e "s/.*sc.tm.leconTitle.setString.*/sc.tm.leconTitle.setString\( ${LECON_TITLE} \);/" ../EXTERN_GEOMETRIE/main.cpp )
        
        if [ "$?" != 0  ];
        then
            echo -e "\033[0;31m [WARNING]: Unable to set LECON_TITLE = $LECON_TITLE  inside  EXTERN_GEOMETRY/main.cpp script  \033[0m \n"		
            
        fi
    fi

    # ......................................................... #
fi

#................. GET BACKGROUND COLOR .........................#
BACKGROUND_CHOSEN_COLOR=$(cat ../EXTERN_GEOMETRIE/geometry.hpp | grep "#define BACKGROUND_CHOSEN_COLOR" | sed -e 's/^[[:space:]]*//' | cut -d ' ' -f3)
echo
if [ "$BACKGROUND_CHOSEN_COLOR" == "BLUE" ] 
then
    echo -e "${ONBLUE} MANIM BACKGROUND COLOR ${RESET} ${ONBLUE} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [ "$BACKGROUND_CHOSEN_COLOR" == "BLACK" ] 
then 
    echo -e "${ONBLACK} MANIM BACKGROUND COLOR ${RESET} ${ONBLACK} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [ "$BACKGROUND_CHOSEN_COLOR" == "WHITE" ] 
then
    echo -e "${ONWHITE} MANIM BACKGROUND COLOR ${RESET} ${ONWHITE} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [ "$BACKGROUND_CHOSEN_COLOR" == "RED" ] 
then
    echo -e "${ONRED} MANIM BACKGROUND COLOR ${RESET} ${ONRED} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [ "$BACKGROUND_CHOSEN_COLOR" == "GREEN" ] 
then
    echo -e "${ONGREEN} MANIM BACKGROUND COLOR ${RESET} ${ONGREEN} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [ "$BACKGROUND_CHOSEN_COLOR" == "YELLOW" ] 
then
    echo -e "${ONYELLOW} MANIM BACKGROUND COLOR ${RESET} ${ONYELLOW} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [ "$BACKGROUND_CHOSEN_COLOR" == "PURPLE" ] 
then
    echo -e "${ONPURPLE} MANIM BACKGROUND COLOR ${RESET} ${ONPURPLE} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [ "$BACKGROUND_CHOSEN_COLOR" == "CYAN" ] 
then
    echo -e "${ONCYAN} MANIM BACKGROUND COLOR ${RESET} ${ONCYAN} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
fi

# save python script file
PYTHON_SCRIPT_FILE=$1

if [ ! -f "$PYTHON_SCRIPT_FILE"  ];
then 
    echo -e "${ONCOLOR_FAILED} Please, Provide Python script file_name as argument ${RESET} \n"
    return 
fi 

#  get the status of container
CONTAINER_STATUS="$( docker inspect -f '{{.State.Status}}' $my_manim_container_name 2> /dev/null)"

# if command failed (aka container not exist yet, so rebuilt it)
if  [ "$?" != 0 ];
then
    # remove all directory
    rm -rf _pycache__/ media/ 
    echo -e "${ONYELLOW} CONTAINER $my_manim_container_name  not yet exist ${RESET}\n"
    $(docker run -d -it --rm  --name $my_manim_container_name  -v "$(pwd):/manim/"  $my_manim_image 2> /dev/null )
    # remove old geometry.hpp
    $(docker exec -it $my_manim_container_name rm manim/geometry.hpp 2> /dev/null )
    # copy new updated main (to overide and get background color from geometry.hpp)
    $(docker cp ../EXTERN_GEOMETRIE/geometry.hpp  $my_manim_container_name:/manim/geometry.hpp 2> /dev/null )
    echo -e "${ONCOLOR_SUCCESS} new CONTAINER $my_manim_container_name created and it is running ${RESET}\n"
elif  [ "$CONTAINER_STATUS" == "running" ]; # if container exist but it is not running
then
    # remove the following directories from your current directory 
    rm -rf _pycache__/ media/ 
    echo -e "${ONYELLOW} CONTAINER $my_manim_container_name is not yet running ${RESET}\n"
    $( docker run -d -it --rm --name $my_manim_container_name  -v "$(pwd):/manim/"  $my_manim_image 2> /dev/null )
    # remove old geometry.hpp
    $(docker exec -it $my_manim_container_name rm manim/geometry.hpp 2> /dev/null )
    # copy new updated main
    $(docker cp ../EXTERN_GEOMETRIE/geometry.hpp  $my_manim_container_name:/manim/geometry.hpp 2> /dev/null)
    echo -e "${ONCOLOR_SUCCESS} new CONTAINER $my_manim_container_name is now running ${RESET}\n"
else 
    # so container is running
    echo -e "${ONCOLOR_SUCCESS} CONTAINER $my_manim_container_name is still running ${RESET}\n"
fi

# if container is now running, build video mp4 (from python script)
#CONTAINER_STATUS="$( docker container inspect -f '{{.State.Running}}' $my_manim_container_name > /dev/null)"

if [ "$( docker inspect -f '{{.State.Status}}' $my_manim_container_name  2> /dev/null)" == "running" ];
then
    echo -e "${BLUE}Estimated time : 33m2.879s ${RESET}\n"
    #docker exec -it --user="$(id -u):$(id -g)" $my_manim_container_name  manim "/manim/$PYTHON_SCRIPT_FILE"
    #docker exec -it  ${my_manim_container_name} manim -p -qm --disable_caching $PYTHON_SCRIPT_FILE ChanimScene
    
    # check if package w3m already exists inside container
    
    docker exec -it  ${my_manim_container_name} manim -p -qm  $PYTHON_SCRIPT_FILE  2> /dev/null
    echo -e "\n"
else 
     echo -e "${ONCOLOR_FAILED} FAILED TO RUN CONTAINER ${RESET}\n"
fi




# save python script file
PYTHON_SCRIPT_FILE=$1

if [ ! -f "$PYTHON_SCRIPT_FILE"  ];
then 
    echo -e "${ONCOLOR_FAILED} Please, Provide Python script file_name as argument ${RESET} \n"
    return 
fi 

#  get the status of container
CONTAINER_STATUS="$( docker inspect -f '{{.State.Status}}' $my_manim_container_name 2>/dev/null)"

# if command failed (aka container not exist yet, so rebuilt it)
if  [ "$?" != 0 ];
then
    # remove all directory
    rm -rf _pycache__/ media/ 
    echo -e "${ONYELLOW} CONTAINER $my_manim_container_name  not yet exist ${RESET}\n"
    $(docker run -d -it --rm  --name $my_manim_container_name  -v "$(pwd):/manim/" $my_manim_image > /dev/null )
    echo -e "${ONCOLOR_SUCCESS} new CONTAINER $my_manim_container_name created and it is running ${RESET}\n"
elif  [ "$CONTAINER_STATUS" == "running" ]; # if container exist but it is not running
then
    # remove the following directories from your current directory 
    rm -rf _pycache__/ media/ 
    echo -e "${ONYELLOW} CONTAINER $my_manim_container_name is not yet running ${RESET}\n"
    $( docker run -d -it --rm --name $my_manim_container_name  -v "$(pwd):/manim/" $my_manim_image > /dev/null )
    echo -e "${ONCOLOR_SUCCESS} new CONTAINER $my_manim_container_name is now running ${RESET}\n"
else 
    # so container is running
    echo -e "${ONCOLOR_SUCCESS} CONTAINER $my_manim_container_name is still running ${RESET}\n"
fi

# if container is now running, build video mp4 (from python script)
#CONTAINER_STATUS="$( docker container inspect -f '{{.State.Running}}' $my_manim_container_name > /dev/null)"

if [ "$( docker inspect -f '{{.State.Status}}' $my_manim_container_name  2>/dev/null)" == "running" ];
then
    echo -e "${BLUE}Estimated time : 33m2.879s ${RESET}\n"
    #docker exec -it --user="$(id -u):$(id -g)" $my_manim_container_name  manim "/manim/$PYTHON_SCRIPT_FILE"
    #docker exec -it  ${my_manim_container_name} manim -p -qm --disable_caching $PYTHON_SCRIPT_FILE ChanimScene
    docker exec -it  ${my_manim_container_name} manim -p -qm  $PYTHON_SCRIPT_FILE ChanimScene
else 
     echo -e "${ONCOLOR_FAILED} FAILED TO RUN CONTAINER ${RESET}\n"
fi

