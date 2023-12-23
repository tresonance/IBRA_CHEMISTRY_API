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
WHITE='\033[0;37m'        # White

# Background
ONBLACK='\033[40m'       # Black
ONRED='\033[41m'         # Red
ONGREEN='\033[42m'       # Green
ONYELLOW='\033[43m'      # Yellow
ONBLUE='\033[44m'        # Blue
ONPURPLE='\033[45m'      # Purple
ONCYAN='\033[46m'        # Cyan
ONWHITE='\033[47m'       # WHITE

# set color variable
COLOR_COMMAND=$CYAN
ONCOLOR_FAILED=$ONRED
ONCOLOR_SUCCESS=$ONCYAN

# level
class_level="Tle"
#class_level="Tle"

# set image  name
my_manim_image="physic_image"
# set container name
my_manim_container_name="my-physic-tle-container"

# Suject name in DISKE (where we must save this videos )
#Exemple "Physic" in /Volumes/DiskE/VIDEOS-1ere-Physic-mp4
diske_topic="Physics" 

#  variable GIT_MY_CHANEL_NAME, #Exemple: GIT_MY_CHANNELS_PHYSICS
GIT_MY_CHANEL_NAME=$(pwd | cut -d "/" -f 4) 

# save python script file
PYTHON_SCRIPT_FILE=""

#only board symbolinl link name
ONLY_BOARD_SYMLINK="ONLY_BOARD_SYMLINK"

# recall Usage
if [ "$#" -eq 0 ]; then
    echo -e "$RED [Usage] : $CYAN source run_manim_script.sh my_python_manim_script.py $RESET \n"

elif [[ "$1" == *.py ]]; then 
    echo -e "#####################################################################\n
    #\n\
    #\t\t [API PHYSICS] Start building manim Scene image from python file \n\
    #\n\\t\t You must chck the result inside media directory \n
    #
    ##################################################\n"
  
    # ............... Remove unexpected directory .............
    # $(rm -rf $HOME/GIT_ONLY_BOARD_GPU/ONLY_PHYSICS/ONLY_PHYSICS > /dev/null 2>&1)
    # .............. SET THE LESSON TITLE .................... #
    LECON_TITLE=$(cat $1 | grep -i TOP_MENU_LECON_TITLE_FROM_MANIM_PYTHON_FILE | awk -F "=" '{print $2}')
    # Example of result: "CARDINAL D'UN ENSEMBLE "
    result1=$?
    

    LECON_TITLE_LINE_NUMBER=$( cat -n ../main.cpp | sed -n "/sc.tm.leconTitle.setString/p" | awk '{print $1}' )
    result2=$?

    if [ "$result1" != 0  ];
    then 
        echo -e "\033[0;31m [WARNING]: Unable to find lesson title from your python script to main.cpp  \033[0m \n"
    else
        echo -e "\033[0;35m COURSE_TITLE = $LECON_TITLE \033[0m \n"

        $(sed -i -e "s/.*sc.tm.leconTitle.setString.*/sc.tm.leconTitle.setString\( ${LECON_TITLE} \);/" main.cpp )
        
        if [ "$?" != 0  ];
        then
            echo -e "\033[0;31m [WARNING]: Unable to set LECON_TITLE = $LECON_TITLE  inside  main.cpp script  \033[0m \n"		
            
        fi
    fi

    # ......................................................... #
fi


#................. GET BACKGROUND COLOR .........................#
BACKGROUND_CHOSEN_COLOR=$(cat ./geometry.hpp | grep "#define BACKGROUND_CHOSEN_COLOR" | sed -e 's/^[[:space:]]*//' | cut -d ' ' -f3)
echo
if [[ "$BACKGROUND_CHOSEN_COLOR" == "BLUE" ]] 
then
    echo -e "${ONBLUE} MANIM BACKGROUND COLOR ${RESET} ${ONBLUE} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [[ "$BACKGROUND_CHOSEN_COLOR" == "BLACK" ]] 
then 
    echo -e "${ONBLACK} MANIM BACKGROUND COLOR ${RESET} ${ONBLACK} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [[ "$BACKGROUND_CHOSEN_COLOR" == "WHITE" ]] 
then
    echo -e "${ONWHITE} MANIM BACKGROUND COLOR ${RESET} ${ONWHITE} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [[ "$BACKGROUND_CHOSEN_COLOR" == "RED" ]] 
then
    echo -e "${ONRED} MANIM BACKGROUND COLOR ${RESET} ${ONRED} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [[ "$BACKGROUND_CHOSEN_COLOR" == "GREEN" ]] 
then
    echo -e "${ONGREEN} MANIM BACKGROUND COLOR ${RESET} ${ONGREEN} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [[ "$BACKGROUND_CHOSEN_COLOR" == "YELLOW" ]] 
then
    echo -e "${ONYELLOW} MANIM BACKGROUND COLOR ${RESET} ${ONYELLOW} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [[ "$BACKGROUND_CHOSEN_COLOR" == "PURPLE" ]] 
then
    echo -e "${ONPURPLE} MANIM BACKGROUND COLOR ${RESET} ${ONPURPLE} $BACKGROUND_CHOSEN_COLOR ${RESET} \n"
elif [[ "$BACKGROUND_CHOSEN_COLOR" == "CYAN" ]] 
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
    $(docker cp ./geometry.hpp  $my_manim_container_name:/manim/geometry.hpp 2> /dev/null )
    echo -e "${ONCOLOR_SUCCESS} new CONTAINER $my_manim_container_name created and it is running ${RESET}\n"
elif  [[ "$CONTAINER_STATUS" == "running" ]]; # if container exist but it is not running
then
    # remove the following directories from your current directory 
    rm -rf _pycache__/ media/ 
    echo -e "${ONYELLOW} CONTAINER $my_manim_container_name is not yet running ${RESET}\n"
    $( docker run -d -it --rm --name $my_manim_container_name  -v "$(pwd):/manim/"  $my_manim_image 2> /dev/null )
    # remove old geometry.hpp
    $(docker exec -it $my_manim_container_name rm manim/geometry.hpp 2> /dev/null )
    # copy new updated main
    $(docker cp .  $my_manim_container_name:/manim/ 2> /dev/null)
    echo -e "${ONCOLOR_SUCCESS} new CONTAINER $my_manim_container_name is now running ${RESET}\n"
else 
    # so container is running
    echo -e "${ONCOLOR_SUCCESS} CONTAINER $my_manim_container_name is still running ${RESET}\n"
fi

# if container is now running, build video mp4 (from python script)
#CONTAINER_STATUS="$( docker container inspect -f '{{.State.Running}}' $my_manim_container_name > /dev/null)"

if [[ "$( docker inspect -f '{{.State.Status}}' $my_manim_container_name  2> /dev/null)" == "running" ]];
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