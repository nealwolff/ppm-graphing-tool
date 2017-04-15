all: image

image: run
	eog graph.ppm

run: compile
	./ppmgraph
compile:
	gcc ppmgraph.c -lm -o ppmgraph
