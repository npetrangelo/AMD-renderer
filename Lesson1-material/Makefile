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

utility.o:
	gcc -c utility.c -o bin/utility.o

buffer.o:
	gcc -c buffer.c -o bin/buffer.o -framework OpenGL -framework GLUT

point.o:
	gcc -c point.c -o bin/point.o

vector.o:
	gcc -c vector.c -o bin/vector.o

mesh.o:
	gcc -c mesh.c -o bin/mesh.o

main.o:
	gcc -c main.c -o bin/main.o

buffer: utility.o vector.o point.o buffer.o mesh.o main.o
	gcc -o bin/buffer bin/main.o bin/utility.o bin/buffer.o bin/point.o bin/vector.o bin/mesh.o -framework OpenGL -framework GLUT

clean:
	-rm *.o $(objects)
	-rm bin/*