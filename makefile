main: backtrack.o
	g++ -Wall -g -o main backtrack.o

GeneticAlgorithm.o : GeneticAlgorithm.cpp GeneticAlgorithm.h
	g++ -Wall -g -c GeneticAlgorithm.cpp

backtrack.o : backtrack.cpp backtrack.h
	g++ -Wall -g -c backtrack.cpp

clean :
	rm -f main.o GeneticAlgorithm.o *.out