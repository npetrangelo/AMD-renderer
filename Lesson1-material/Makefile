all:
	make clean
	make foo
	make point
	make life

foo:
	gcc foo.c -o bin/foo -framework OpenGL -framework GLUT

point:
	gcc point.c -o bin/point -framework OpenGL -framework GLUT

life:
	gcc life.c -o bin/life -framework OpenGL -framework GLUT

clean:
	-rm *.o $(objects)
	-rm bin/*