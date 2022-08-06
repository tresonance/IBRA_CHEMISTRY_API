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
class_level="1ere"
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
    echo -e "${RED} ........................ U S A G E .................... ${RESET}\n"
    echo -e "${ONPURPLE} PLEASE, MOUNT YOUR DiskE BEFORE ${RESET}\n"
    echo -e "${ONCYAN} Info: To removed container run: ./run.sh down \t\t\t ${RESET}\n"
    echo -e "${ONPURPLE} Info: To save videos to volume:  run: ./run.sh save \t\t ${RESET}\n"
    echo -e "${ONCYAN} Info: To build MANIM videos ./run.sh  my-python_script.py \t ${RESET}\n"
    echo -e "${ONPURPLE} Info: To build corresponding docker image:  run: ./run.sh build ${RESET}\n"
    echo -e "${ONCYAN} Info: To create ONLY_BOARD symlink:  run: ./run.sh symlink \t ${RESET}\n"
    echo -e "${RED} .......................END  U S A G E .................... ${RESET}\n"

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
elif [ "$1" == "symlink" ]
then 
    #$(rm -rf EXTERN_GEOMETRIE/ONLY_BOARD && rm -rf ../ONLY_BOARD)
    #$(ln -s /Users/whodunit/GIT_ONLY_BOARD_GPU/ ONLY_BOARD > /dev/null 2>&1)
    $(ln -s /Users/whodunit/GIT_ONLY_BOARD_GPU/ ONLY_BOARD )
    $(rm -rf ../ONLY_BOARD && ../EXTERN_GEOMETRIE/ONLY_BOARD > /dev/null 2>&1 )
    $(mv ONLY_BOARD ../ > /dev/null 2>&1 )
    
    echo -e "${ONBLUE} ONLY_BOARD@ link has been created ${RESET} \n"
    result=$(ls -lrt ../| grep ONLY_BOARD)
    echo -e "${CYAN} ${result} ${RESET}\n"
    return 
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

