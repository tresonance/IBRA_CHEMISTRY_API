BLACK		=	\033[30;1m
RED			=	\033[31;1m
GREEN		=	\033[32;1m
YELLOW		=	\033[33;1m
BLUE		=	\033[34;1m
PURPLE		=	\033[35;1m
CYAN		=	\033[36;1m
WHITE		=	\033[37;1m
RESET		=	\033[0m
CLEAR		=	\033[H\e[J

NAME		= video-course-chemistry

EXT_BASE_DIR = ./
EXT_OBJ_DIR		=	$(EXT_BASE_DIR)obj/
EXT_BIN = EXT_BIN 

ONLY_BOARD_BASE_DIR = ../ONLY_BOARD/
ONLY_BOARD_OBJ_DIR = $(ONLY_BOARD_BASE_DIR)obj/
ONLY_BOARD_BIN = ONLY_BOARD_BIN

MY_OPENCL_BASE_DIR = ../MY_OPENCL/
MY_OPENCL_OBJ_DIR = $(MY_OPENCL_BASE_DIR)obj/
MY_OPENCL_BIN = MY_OPENCL_BIN

CFLAGS = -I/Library/Frameworks/sfeMovie.framework/Versions/2.0/Headers  -I/usr/local/Cellar/sfml/2.5.1_1/include -framework OpenCL

LIBS		= -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXX := g++ 

TITLE=Ibrahima

all: $(NAME)
.PHONY : all

# only_board bin
$(ONLY_BOARD_OBJ_DIR)%.o : $(ONLY_BOARD_BASE_DIR)%.cpp
		@mkdir -p $(ONLY_BOARD_OBJ_DIR)
		@$(CXX) -c $< -o $@

$(ONLY_BOARD_OBJ_DIR)%.o : $(ONLY_BOARD_OBJ_DIR)%.hpp
		@$(CXX) -c $< -o $@

# myopencl bin
$(MY_OPENCL_OBJ_DIR)%.o : $(MY_OPENCL_BASE_DIR)%.cpp 
		@mkdir -p $(MY_OPENCL_OBJ_DIR)
		@$(CXX) -c $< -o $@

$(MY_OPENCL_OBJ_DIR)%.o : $(MY_OPENCL_BASE_DIR)%.hpp
		@$(CXX) -c $< -o $@

# extern geometry bin
$(EXT_OBJ_DIR)%.o : $(EXT_BASE_DIR)%.cpp
		@mkdir -p $(EXT_OBJ_DIR)
		@$(CXX) -c $< -o $@

$(EXT_OBJ_DIR)%.o : $(EXT_BASE_DIR)%.hpp $(MY_OPENCL_BASE_DIR)*.hpp $(ONLY_BOARD_OBJ_DIR)*.hpp
		@$(CXX) -c $< -o $@


# executable
$(NAME):  $(ONLY_BOARD_OBJ_DIR)board-gpu.o  $(ONLY_BOARD_OBJ_DIR)board-sfe-MediaInfo.o $(ONLY_BOARD_OBJ_DIR)board-sfe-StreamSelector.o $(ONLY_BOARD_OBJ_DIR)board-sfe-UserInterface.o $(MY_OPENCL_OBJ_DIR)myopencl.o  $(EXT_OBJ_DIR)geometry.o  $(EXT_OBJ_DIR)main.o 
	@echo ""
	@echo "$(GREEN) [MOUNT VOLUME FILE LIST] $(RESET)"
	MOUNT_FILES="$(shell mount -t /dev/disk2s1 && ls  "/Volumes/Disk E"  )"
	@echo "$(CYAN) $(MOUNT_FILES) $(RESET)"

	SYMLINK="$(shell ln -s /Users/whodunit/GIT_ONLY_BOARD_GPU  ONLY_BOARD)"
	@echo "$(YELLOW) SYMLINK USED: $(RESET) $(BLUE) ONLY_BOARD@ -> /Users/whodunit/GIT_ONLY_BOARD_GPU \n$(RESET)"
	
	
	@echo "$(GREEN) MAKE ** Building the executable ** $(RESET)"
	@$(CXX) $(CFLAGS) -o $(NAME) $(ONLY_BOARD_OBJ_DIR)board-gpu.o  $(ONLY_BOARD_OBJ_DIR)board-sfe-MediaInfo.o $(ONLY_BOARD_OBJ_DIR)board-sfe-StreamSelector.o $(ONLY_BOARD_OBJ_DIR)board-sfe-UserInterface.o $(EXT_OBJ_DIR)main.o $(MY_OPENCL_OBJ_DIR)myopencl.o  $(EXT_OBJ_DIR)geometry.o   $(LIBS) /Library/Frameworks/sfeMovie.framework/Versions/2.0/sfeMovie && ./$(NAME)
	@echo ""


.PHONY: clean
clean:	
	@echo "\033[48;5;15;38;5;25;1mMAKE ** Removing object files and executable... $(RESET)"
	@rm -rf $(NAME)   $(EXT_OBJ_DIR)*.o $(ONLY_BOARD_OBJ_DIR)*.o $(MY_OPENCL_OBJ_DIR)*.o


fclean: 
	@echo "$(YELLOW)CLEAN ALL OBJECTS DIRECTORIES FILES$(GREEN)			[ OK ]$(RESET)"
	@rm -rf $(EXT_OBJ_DIR)
	@rm -rf $(ONLY_BOARD_OBJ_DIR)
	@rm -rf $(MY_OPENCL_OBJ_DIR)
	@rm -rf $(NAME)
	@rm -rf EXT_BIN
	@rm -rf MY_OPENCL_BIN
	@rm -rf ONLY_BOARD_BIN
	@echo "$(YELLOW)Clean	$(NAME)$(GREEN)			[ OK ]$(RESET)"

re: fclean all


install:
	@echo '** Installing...'
	cp $(NAME) /usr/bin/


uninstall:
	@echo '** Uninstalling...'
	$(RM) /usr/bin/$(NAME)
 