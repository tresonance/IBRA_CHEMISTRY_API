from manim import *
from chanim import *

"""
class ChanimScene(Scene):
    def construct(self):
        ## ChemWithName creates a chemical diagram with a name label
        chem = ChemWithName("*6((=O)-N(-CH_3)-*5(-N=-N(-CH_3)-=)--(=O)-N(-H_3C)-)", "Caffeine")

        self.play(chem.creation_anim())
        self.wait()
"""

class AlcololScene(Scene):
    def construct(self):
        ## ChemWithName creates a chemical diagram with a name label
        chem =  ChemObject("H-C(-[2]H)(-[6]H)-C(=[1]O)-[7]H")
        
        chem[0][1].set_color(RED)
        chem[0][2].set_color(PURPLE)
        chem[0][3].set_color(TEAL)
        chem[0][4].set_color(BLUE)
        chem[0][5].set_color(ORANGE)
        chem[0][6].set_color(LIGHT_BROWN)
        chem[0][7].set_color(PINK)
        chem[0][9].set_color(YELLOW)
       
        
        
        self.play(FadeIn(chem))
        #self.play(.find("=") ].animate.set_color(YELLOW))
        
        self.wait()