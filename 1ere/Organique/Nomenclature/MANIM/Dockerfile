FROM ubuntu

RUN apt-get update  \
&& apt-get install -y libglib2.0-dev  \
&& apt-get install -y ibpango1.0-dev  \
&& apt-get install -y  ffmpeg  \
&& apt install -y python3-pip && apt-get install -y git  \
&& printf "8\n37" | DEBIAN_FRONTEND='noninteractive' apt-get install -y texlive-fonts-extra  \
&& apt-get install -y -qq texlive-latex-extra \
&& apt-get install -y texlive-science \
#RUN apt-get install -y texlive-full  
&& apt-get install -y libcairo2-dev  \
&& apt-get install -y libjpeg-dev \
&& apt install -y libpango1.0-dev pkg-config python3-dev  

RUN pip3 install pybind11  &&  pip3 install manim  

#RUN pip3 install -y  Pillow
#RUN apt install -y libpango1.0-dev pkg-config python3-dev  

#RUN pip3 install manim  

RUN git clone https://github.com/kilacoda/chanim cloneChanim 

WORKDIR  /cloneChanim

RUN pip3 install wheel && pip3 install Cython && pip3 install manimpango
#RUN pip3 install Cython
#RUN pip3 install manimpango


RUN pip3 install -e .
#RUN pip3 install chanim
RUN sed -i'' -e "s/Union\[str, ChemObject, ComplexChemIon\]/Union/" "./chanim/chem_objects.py"

#RUN sed -i '203i\\t\tcation: Union,' "./chanim/chem_objects.py"
#RUN sed -i '204i\\t\tanion: Union,' "./chanim/chem_objects.py"

#RUN sed  '205,206d' "./chanim/chem_objects.py"
#RUN sed -i '206d' "./chanim/chem_objects.py"

#RUN sed -i "203s/Union[str, ChemObject, ComplexChemIon],/Union ,/g" "./chanim/chem_objects.py"
#RUN sed -i "204s/Union[str, ChemObject, ComplexChemIon],/Union ,/g" "./chanim/chem_objects.py"

WORKDIR  /manim 

COPY  . .

ENV LC_ALL=C.UTF-8 
ENV LANG=C.UTF-8  

RUN sed -i s/"from manim.mobject.types.vectorized_mobject import VGroup, VMobject"/"from manim import *"/ "../cloneChanim/chanim/chem_objects.py" \
&&  sed -i s/"from manim.mobject.text.tex_mobject import \*"/"from chanim import *"/ "../cloneChanim/chanim/chem_objects.py"

RUN sed "${15}q;d" "../cloneChanim/chanim/chem_objects.py" \
&& sed "${15}q;d" "../cloneChanim/chanim/chem_objects.py" \
&& sed "${15}q;d" "../cloneChanim/chanim/chem_objects.py" \
&& sed "${18}q;d" "../cloneChanim/chanim/chem_objects.py" \
&& sed "${15}q;d" "../cloneChanim/chanim/chem_objects.py" \
&& sed "${15}q;d" "../cloneChanim/chanim/chem_objects.py" \
&& sed "${15}q;d" "../cloneChanim/chanim/chem_objects.py" \
&& sed "${15}q;d" "../cloneChanim/chanim/chem_objects.py" \
&& sed "${15}q;d" "../cloneChanim/chanim/chem_objects.py" \
&& sed -n 13,14p "../cloneChanim/chanim/chem_objects.py" \
&& apt-get install -y vim 

#CMD [ "manim" , "-p", "-qm",  "test_chemistry.py",  "ChanimScene" ]
