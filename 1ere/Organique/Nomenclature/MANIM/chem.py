from manim import *
from chanim import *

class ChanimScene(Scene):
    def construct(self):
        ## ChemWithName creates a chemical diagram with a name label
        chem = ChemWithName("*6((=O)-N(-CH_3)-*5(-N=-N(-CH_3)-=)--(=O)-N(-H_3C)-)", "Caffeine")

        self.play(chem.creation_anim())
        self.wait()