BLACK		=	\033[30;1m
RED			=	\033[31;1m
GREEN		=	\033[32;1m
YELLOW		=	\033[33;1m
BLUE		=	\033[34;1m
PURPLE		=	\033[35;1m
CYAN		=	\033[36;1m
MAGENTA		=	\033[95;1m
GREEN		=	\033[37;1m
RESET		=	\033[0m
CLEAR		=	\033[H\e[J

# =====  ====== ====== ======= =====
NAME		= video-course-channels-chemistry-bin
# =====  ====== ====== ======= =====

ONLY_BOARD_SYMLINK=ONLY_BOARD_SYMLINK
# Only board to be linked 
# Attention ne pas enlever le shash a la fin de la ligne qui suit et l'ajouter avant obj/ de la ligne suivante
# sinon ça marche pas (je ne sais pas trop pouquoi)
ONLY_BOARD_BASE_DIR = $(ONLY_BOARD_SYMLINK)/
ONLY_BOARD_OBJ_DIR = $(ONLY_BOARD_BASE_DIR)obj/
ONLY_BOARD_BIN = ONLY_BOARD_BIN

# External base dir 
EXT_BASE_DIR = ./
EXT_OBJ_DIR		=	$(EXT_BASE_DIR)obj/
EXT_BIN = EXT_BIN 


# Library to be linked  
#SFE_SFML_IMGUI_LIBS=$(COURSES_DIR)/SFE_SFML_IMGUI_LIBS
SFE_SFML_IMGUI_LIBS=../SFE_SFML_IMGUI_LIBS
# Headers to be included
BASIC_SFE_DIR=$(SFE_SFML_IMGUI_LIBS)/basic_sfe
BASIC_ALL_IN_ONE_DIR=$(SFE_SFML_IMGUI_LIBS)/basic_all_in_one
SFE_HEADERS_DIR=$(BASIC_SFE_DIR)/sfe_headers
SFML_HEADERS_DIR=$(BASIC_SFE_DIR)/sfml_headers

OBJ_DIR		=	obj/

NO_WARNINGS_FLAGS=-Wno-deprecated -Wno-c++11-extensions -Wno-inconsistent-missing-override -lsfml-graphics -lsfml-window -lsfml-system
SFML_HEADERS_DIR=${BASIC_SFE_DIR}/sfml_headers 

# SO Library Name without prefix lib and extensio .so
SO_LIBRARY_NAME=sfe_movie_bin

CXXFLAGS=-std=c++11 $(NO_WARNINGS_FLAGS) -I$(SFML_HEADERS_DIR) -I$(FFmpeg_HEADERS_DIR) -I$(SFE_HEADERS_DIR) -framework OpenCL 
# ================================
# ================================

LIBS		= -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system 
CXX := g++ 


all: $(NAME)
.PHONY : all

#######################################################
# only_board bin
$(ONLY_BOARD_OBJ_DIR)%.o : $(ONLY_BOARD_BASE_DIR)%.cpp 
		@mkdir -p $(ONLY_BOARD_OBJ_DIR)
		@$(CXX) -c $< -o $@

$(ONLY_BOARD_OBJ_DIR)%.o : $(ONLY_BOARD_BASE_DIR)%.hpp 
		@$(CXX) -c $< -o $@

#######################################################
# extern geometry and main bin
$(EXT_OBJ_DIR)%.o : $(EXT_BASE_DIR)%.cpp
		@mkdir -p $(EXT_OBJ_DIR)
		@$(CXX) -c $< -o $@

$(EXT_OBJ_DIR)%.o : $(EXT_BASE_DIR)%.hpp $(ONLY_BOARD_OBJ_DIR)*.hpp
		@$(CXX) -c $< -o $@


# executable
$(NAME):  $(ONLY_BOARD_OBJ_DIR)board-only.o $(ONLY_BOARD_OBJ_DIR)board-ext-geometry.o   $(EXT_OBJ_DIR)ext-geometry.o  $(EXT_OBJ_DIR)main.o 
	
	@echo "\n\n\033[38m ====================================================== \n\033[0m"
	@echo "$(GREEN) MAKE ** Building the executable ** \033[0m"
	@echo "$(PURPLE) \n\t\t\t........................ \033[0m"
	@echo "$(MAGENTA) \t\t\t  EXTERN CHEMISTRY  \033[0m"
	@echo "$(PURPLE) \t\t\t........................\n \033[0m"
	@echo "\033[37m ========================================================== \033[0m\n"
	$(shell export  LD_LIBRARY_PATH=/xxxxx/xxxxxx/COURSES/SFE_SFML_IMGUI_LIBS/create_unique_library)
	@$(CXX) $(CXXFLAGS) -L`pwd` -l$(SO_LIBRARY_NAME) $(LIBS) -o $(NAME) $(ONLY_BOARD_OBJ_DIR)board-only.o $(ONLY_BOARD_OBJ_DIR)board-ext-geometry.o   $(EXT_OBJ_DIR)ext-geometry.o  $(EXT_OBJ_DIR)main.o   && ./$(NAME) 
	@echo ""



.PHONY: clean
clean:	
	@echo "\n\n\033[38m ====================================================== \033[0m\n"
	@echo "\033[48;5;15;38;5;25;1mMAKE ** Removing object files and executable... \033[0m\n"
	@rm -rf $(NAME)   $(EXT_OBJ_DIR)*.o $(ONLY_BOARD_OBJ_DIR)*.o
	


fclean: 
	@echo "\n\n\033[38m ====================================================== \033[0m\n"
	@echo "\033[36m-> -> CLEAN ALL OBJECTS DIRECTORIES FILES$(GREEN)			[ OK ]\033[0m"
	@rm -rf $(EXT_OBJ_DIR)
	@rm -rf $(ONLY_BOARD_OBJ_DIR)
	@rm -rf temp.cpp 
	@rm -rf temp
	@rm -rf $(NAME)
	@rm -rf EXT_BIN
	@rm -rf ONLY_BOARD_BIN
	@echo "$(YELLOW)-> -> Clean	binary $(NAME)$(GREEN)			[ OK ]\033[0m"

re: fclean all


install:
	@echo '** Installing...'
	cp $(NAME) /usr/bin/


uninstall:
	@echo '** Uninstalling...'
	$(RM) /usr/bin/$(NAME)


 