OBJS =  game.cpp  

AUX_OBJS =  ECS.o maze.o Vector2D.o Texture.o 
AUX_OBJS_cpp = ECS.cpp maze.cpp  Vector2D.cpp  Texture.cpp 


COMPILER_FLAGS = -O3 -w
LINKER_FLAGS = -lSDL2 -lSDL2_image -lenet -lSDL2_ttf -lSDL2_mixer


all: ./game.out
	

host:./game.out
	./game.out 127.0.0.1

one: ./game.out
	./game.out 1

two:./game.out
	./game.out 2

./game.out : $(OBJS)
	g++ $(COMPILER_FLAGS) $(LINKER_FLAGS) -c $(AUX_OBJS_cpp)
	g++ $(AUX_OBJS) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o game.out
	

clean:
	@rm -rf *.o *.out