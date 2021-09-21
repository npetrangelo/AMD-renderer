all:
	make clean
	make foo
	make point
	make life

foo:
	gcc foo.c -o foo -framework OpenGL -framework GLUT

point:
	gcc point.c -o point -framework OpenGL -framework GLUT

life:
	gcc life.c -o life -framework OpenGL -framework GLUT

clean:
	-rm *.o $(objects) foo point life