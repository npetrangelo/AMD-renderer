all:
	make clean
	make foo
	make point
	make life
	make line

foo:
	gcc foo.c -o bin/foo -framework OpenGL -framework GLUT

point:
	gcc point.c -o bin/point -framework OpenGL -framework GLUT

life:
	gcc life.c -o bin/life -framework OpenGL -framework GLUT

line:
	gcc line.c -o bin/line -framework OpenGL -framework GLUT

turtle:
	gcc line.c -o bin/line turtle.c bresenham.c xiaolin.c -framework OpenGL -framework GLUT

clean:
	-rm *.o $(objects)
	-rm bin/*