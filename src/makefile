CC = g++

COMPILER_FLAGS = -g

DEPS = game.cpp window.cpp pong.cpp texture.cpp player.cpp ball.cpp support.cpp

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OUTPUT = pong.o

pong : ${DEPS}
	${CC} ${COMPILER_FLAGS} ${DEPS} ${LINKER_FLAGS} -o ${OUTPUT}

clean:
	rm -f *.o