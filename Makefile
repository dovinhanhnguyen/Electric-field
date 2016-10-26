CC = g++
CCSW = -O3 -Wno-deprecated-declarations
PLATFORM = `uname`

field: field_dynamics.o field_graphics.o
	@if [ ${PLATFORM} = "Linux" ]; \
	then $(CC) -o field field_dynamics.o field_graphics.o ${CCSW} -lGL -lGLU -lglut; \
	echo Linking for Linux; \
	elif [ ${PLATFORM} = "Darwin" ]; \
	then $(CC) -o field field_dynamics.o field_graphics.o ${CCSW} -lSOIL -framework GLUT -framework OpenGL; \
	echo Linking for Mac OS X; \
	fi

field_dynamics.o field_graphics.o: field.h

.cpp.o:
	$(CC) ${CCSW} -c $<

clean:
	echo cleaning up; /bin/rm -f core *.o field

all:	field

