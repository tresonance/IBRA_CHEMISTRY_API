#------------------------------------------------------------------#

CHANIM_GITHUB

https://github.com/kilacoda/chanim


CHEMFIG_DOCUMENTATION:

http://ctan.imsc.res.in/macros/generic/chemfig/chemfig-en.pdf

TRICK TO:
Convert a video file from mp4 to webm:

ffmpeg -i input.mp4 output.webm
Copy
Convert an audio file from mp3 to ogg:

ffmpeg -i input.mp3 output.ogg


CHANIM GITHUB:
https://github.com/kilacoda/chanim/tree/master/chanim

#------------------------------------------------------------------------#
### PATH
```
cd /Users/whodunit/MY_CHANELS_CHEMISTRY
```
## DOCUMENTATION:
manim: https://github.com/Matheart/manim-physics

### HOW TO RUN (to see running manim videos): 
Note: this software must be integrated to External application like Prodsca, trigo, chemistry, physic ...
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
2-e)To build custom docker image for a course (like for chemistry but not for prodsca, trigo ...)
    source run.sh build
    why? because trigo, prodsca ... use manim image but chemistry use custom Dockerfile image 

Infos: All course image are also saved in Volumes folder:
- icons (menu icons): Volumes/Disk E/MY_CHANELS_VIDEOS_ICONS
- center menu (course images like exercice or screen capture ...): /Volumes/Disk E/VIDEOS-1ere-Maths or /Volumes/Disk E/VIDEOS-1ere-Chemistry or /Volumes/Disk E/VIDEOS-1ere-Physic
```



```
3- manim will put presentation course inside docker container directory named /manim
but as we set volume between /manim (directory inside container) and working directory ./MANIM.
new directory ./MANIM/media will be created after you run: source run.sh my_python_file.sh

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


#---------------------------------------------------------------------------------#
## Vecteezy vecteezy 
https://www.vecteezy.com/free-vector/mouth



## ###############
video youtube: https://www.youtube.com/watch?v=19DtaSXm4Qk&list=PL_xB68jLOLYsdtRDrpscuPn4Eliue-ih4&index=9

de Olivier Juprelle 

1- Accroche 
Sur Youtube vous avez entre 5 et 10 secondes pour captiver l’attention. Je vous ai déjà expliqué comment faire pour augmenter le nombre de vues sur Youtube : Cliquez ici pour en savoir plus. Je pars du principe que vous avez déjà vu cette vidéo. Le titre de votre vidéo sera donc une question. Reprenez cette question dans votre accroche et partagez votre promesse : « dans cette vidéo je partage avec vous 3 astuces simples pour y parvenir » !

2- Generique 
Une fois votre accroche terminée c’est le moment de lancer une partie souvent sous-estimée et d’une importance pourtant cruciale : votre générique ! Sur Youtube les génériques sont beaucoup, beaucoup plus courts. 4 à 5 secondes peut-être 6 secondes grand max. Le générique vous permet d’être reconnu dès le premier coup d‘oreille, de rester dans les mémoires. Un peu comme une madeleine de Proust. Mes conseils pour créer un générique efficace sont ici. 
3- Intro 

Vous devez toujours penser que les gens vous voient pour la première fois. C’est bien de vous présenter. Vous montrez que vous êtes polis, c’est du personal branding, votre nom circule. C’est bien aussi de présenter votre chaîne, d’expliquer son contenu, ça donnera déjà envie à certains de s’abonner. Vous avez 15 secondes pour faire tout ça. Terminez avec votre premier appel à action. Il doit être en lien avec votre objectif pour cette vidéo. 

4- Contenu
C’est le moment tant attendu par ceux qui ont cliqués pour voir votre vidéo. Votre contenu doit être de grande qualité. Vous devez vraiment aider ceux qui vous regardent avec vos MEILLEURS conseils. Ne soyez pas avars, donnez tout, tant que ce n’est pas trop long ! La qualité de votre contenu va convaincre vos spectateurs de rester jusqu’au bout et c’est ça aussi qui va faire qu’ils s’abonnent à votre chaîne. Juste après avoir partagé votre contenu, je vous invite à poser une question

5- Question 

Posez une question
En posant une question à votre audience, il y a plus de chances que celle-ci se décide à laisser un commentaire que si vous ne le faisiez pas. Youtube est un réseaux social. Demandez-leur s’ils ont d’autres astuces, des conseils à donner, une expérience à partager. Vous pouvez aussi leur proposer un exercice.


6- Outro 
Juste après ça c’est le moment de les remercier :  « merci d’avoir regardé cette vidéo ». Et d’enchaîner avec vos appels à action : « laissez-moi un pouce bleu si elle vous a aidé, abonnez-vous pour en voir d’autres. N’oubliez pas que vous pouvez recevoir gratuitement mon guide … A bientôt, Ciao ! » Votre manière de dire aurevoir peut également être une phrase d’accroche ! Soyez bref parce que ça entre en considération dans la durée moyenne de visionnage et dès que les gens entendent « merci d’avoir regardé cette vidéo » ils s’en vont ! Certains YouTubers s’interdisent la phrase « voila c’est tout pour cette vidéo ». En effet, quand les gens sentent que vous avez terminé ils s’en vont. Pas étonnant de voir 50% de personne en moins juste après ces mots… Du coup, au plus c’est court, au moins ça compte sur votre durée moyenne de visionnage.

7- Penneau Titre

## ##### image unsplash 
## music soundsrtrip

## #################################################################################
######## ISTOCK : https://www.istockphoto.com/fr/video-editor/publish/6236a4dc8942f72a5d0f4873
