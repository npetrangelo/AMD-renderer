all:
	make clean
	make foo
	make lesson1
	make life
	make line
	make buffer

foo:
	gcc foo.c -o bin/foo -framework OpenGL -framework GLUT

lesson1:
	gcc lesson1.c -o bin/lesson1 -framework OpenGL -framework GLUT

life:
	gcc life.c -o bin/life -framework OpenGL -framework GLUT

line:
	gcc line.c -o bin/line -framework OpenGL -framework GLUT

turtle:
	gcc line.c -o bin/line turtle.c bresenham.c xiaolin.c -framework OpenGL -framework GLUT

buffer:
	gcc main.c -o bin/buffer utility.c buffer.c point.c vector.c -framework OpenGL -framework GLUT

clean:
	-rm *.o $(objects)
	-rm bin/*