CC = g++
CCSW = -O3 -Wno-deprecated-declarations
PLATFORM = `uname`

field: charge.o graphics.o
	@if [ ${PLATFORM} = "Linux" ]; \
	then $(CC) -o field charge.o graphics.o ${CCSW} -lGL -lGLU -lglut; \
	echo Linking for Linux; \
	elif [ ${PLATFORM} = "Darwin" ]; \
	then $(CC) -o field charge.o graphics.o ${CCSW} -lSOIL -framework GLUT -framework OpenGL; \
	echo Linking for Mac OS X; \
	fi

charge.o graphics.o: electric_field.h charge.h graphics.h vector2d.h

.cpp.o:
	$(CC) ${CCSW} -c $<

clean:
	echo cleaning up; /bin/rm -f core *.o field

all:	field

