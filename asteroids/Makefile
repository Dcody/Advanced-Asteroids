CFLAGS = -I ./include -g
LIB    = ./lib/fmod/libfmodex64.so ./libggfonts.so
LFLAGS = $(LIB) -lrt -lX11 -lGLU -lGL -pthread -lm -g -o3 #-lXrandr

all: asteroids

asteroids: asteroids.cpp fmod.c ppm.c ajS.cpp drewC.cpp joannT.cpp
	g++ $(CFLAGS) asteroids.cpp ajS.cpp drewC.cpp joannT.cpp ppm.c fmod.c -Wall -Wextra $(LFLAGS) -o asteroids

clean:
	rm -f asteroids 
	rm -f *.o

