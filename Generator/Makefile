LIBS = -lglut -lGLU -lGL

run: link
	./generator

link: model.o ponto.o triangulo.o sphere.o cone.o box.o plane.o generator.o
	g++ generator.o sphere.o cone.o box.o plane.o model.o triangulo.o ponto.o $(LIBS) -o generator

model.o:
	g++ -o model.o -c -Wall -g src/Model.cpp

ponto.o:
	g++ -o ponto.o -c -Wall -g src/Ponto3D.cpp

triangulo.o:
	g++ -o triangulo.o -c -Wall -g src/Triangulo.cpp

sphere.o:
	g++ -o sphere.o -c -Wall -g src/Sphere.cpp

cone.o:
	g++ -o cone.o -c -Wall -g src/Cone.cpp

box.o:
	g++ -o box.o -c -Wall -g src/Box.cpp

plane.o:
	g++ -o plane.o -c -Wall -g src/Plane.cpp

generator.o:
	g++ -o generator.o -c -Wall -g src/main.cpp $(LIBS)

clean:
	rm *.o