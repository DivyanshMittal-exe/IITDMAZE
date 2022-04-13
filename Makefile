#OBJS specifies which files to compile as part of the project
OBJS =  game.cpp  

AUX_OBJS =  ECS.o maze.o Vector2D.o Texture.o 
AUX_OBJS_cpp = ECS.cpp maze.cpp  Vector2D.cpp  Texture.cpp 

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lenet

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = game.out

#This is the target that compiles our executable

all:
	@echo "Compiling"
	@make clean
	@make run
	./$(OBJ_NAME)

host:
	@echo "Compiling"
	@make clean
	@make run
	./$(OBJ_NAME) 192.168.0.102

run : $(OBJS)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c -g $(AUX_OBJS_cpp)
	$(CC) $(AUX_OBJS) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -g -o $(OBJ_NAME)
	


# maze.o: maze.cpp
# 		$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c maze.cpp

# Texture.o: Texture.cpp
# 		$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Texture.cpp

# gameObject.o: gameObject.cpp
# 		$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c gameObject.cpp


clean:
	@rm -rf *.o *.out