#OBJS specifies which files to compile as part of the project
OBJS =  game.cpp  

AUX_OBJS = gameObject.o Texture.o maze.o
AUX_OBJS_cpp = gameObject.cpp Texture.cpp maze.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = game.out

#This is the target that compiles our executable

all:
	@echo "Compiling"
	@make clean
	@make run

run : $(OBJS)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c $(AUX_OBJS_cpp)
	$(CC) $(AUX_OBJS) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)


# maze.o: maze.cpp
# 		$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c maze.cpp

# Texture.o: Texture.cpp
# 		$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Texture.cpp

# gameObject.o: gameObject.cpp
# 		$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c gameObject.cpp


clean:
	@rm -rf *.o *.out