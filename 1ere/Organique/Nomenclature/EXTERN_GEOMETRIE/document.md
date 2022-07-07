


### PATH
```
cd /MY_CHANNELS_MATHS/1ere/Geometry/VIDEO-1ere-PRO-SCALAIRE-1-2-3-4
```

### HOW TO RUN (to see running manim videos): 

````
cd /Users/whodunit/MY_CHANNELS_MATHS/1ere/Geometry/VIDEO-1ere-PRO-SCALAIRE-1-2-3-4/EXTERN_GEOMETRIE
````

```
make clean && make fclean && make
```

```
if No new data for ./EXTERN_GEOMETRIE, you can go to 
cd /Users/whodunit/MY_CHANNELS_MATHS/1ere/Geometry/VIDEO-1ere-PRO-SCALAIRE-1-2-3-4/MANIM and run 

make or make re
```

##### HOW TO BUILD MANIM PRESENTATION VIDEO COURSE 

```
1- cd /Users/whodunit/MY_CHANNELS_MATHS/1ere/Geometry/VIDEO-1ere-PRO-SCALAIRE-1-2-3-4/MANIM
```

```
2- Start your docker engine (from Desktop),
2-a)To know manim scipt Usage 
   source run.sh 
2-b)To remove old container 
    source run.sh down 
2-c)To copy mp4 files to /Volumes/Disk E/VIDEOS-1ere-Maths/produit_scalaire
    source run.sh save

    Nota: Please be on superUser status, if not inside /Volumes/Disk E/VIDEOS-1ere-Maths/produit_scalaire, you won't see any data.
2-d)To build a new manim video, run 
    source run.sh my_manim_script.py

Infos: All course image are also saved in Volumes folder:
- icons (menu icons): Volumes/Disk E/MY_CHANELS_VIDEOS_ICONS
- center menu (course images like exercice or screen capture ...): /Volumes/Disk E/VIDEOS-1ere-Maths
```



```
3- manim will put presentation course inside docker container directory named /manim
but as we set volume between /manim (directory inside container) and working directory ./MANIM.
new directory ./MANIM/media will be created.

so run this command inside ./MANIM directory:
open  media/videos/videos_prodsca_series_intro/1080p60/PreviewVideosSeriesProSca1ere.mp4
```


```
Example, 
if you run manim python script (aka the first video)
After a couple of minutes, manim will put the built video inside docker container: /manim/media/videos/video_prodsca_all_courses/1080p60/FormuleAlkhashi_3.mp4

but as this container volume /manim/
is share with working directory
run this command to open video:

open media/videos/video_prodsca_all_courses/1080p60/FormuleAlkhashi_3.mp4
```

#### API CLASS DOCUMENTATION 
#####1-LineWithThickness
```
This class takes two points and build a sf::Quad (rectangle) base on those two points and thickness.
#define SCREEN_STROKE_THICKNESS 2.15

Inside screen, this class is:
mpc::math::LineWithThickness lwt;

this class instance is called  by MyOpencl class. This opencl class will call a kernel "getCourbePoint"
to set easily LineWithThickness.
```
#####2-Myopencl
```


```

##### CONVERT VIDEOS TO gif (Abandon for sfeMovies)
Go to the following website and convert video to GIF.
Please, not that videos in directory:

```
https://www.zamzar.com/uploadComplete.php?session=5111fb3e3738c3a399ab6b6d77266e98&tcs=Z85
```

##### INTEGRATE gif TO MY SFML API 

```
Now,add the gif files to the below repository and add its name inside this array(in board-gpu.cpp):

const char *GIF_FILES[] = {
    "../MANIM/GIFS/PreviewVideosSeriesProSca1ere.gif",
    ......... ,
    .........
};
```

###### Utils
```
AnimatedGIFS: code source origin:
    https://github.com/SFML/SFML/wiki/Source:-Animated-GIF
```

