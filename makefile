SRCDIR      := src
SRC_NAMES   := Utils Sudoku SudokuGenerator Individual Backtrack GeneticAlgorithm SimulatedAnnealing 
SRC_O_FILES     := $(addprefix $(SRCDIR)/, $(addsuffix .o, $(SRC_NAMES))) 
SRC_H_FILES := $(addprefix $(SRCDIR)/, $(addsuffix .h, $(SRC_NAMES))) 

all: $(SRC_O_FILES)

$(SRC_O_FILES): | $(SRCDIR)


$(SRCDIR)/%.o : %.cpp
	g++ -Wall -g -c $<

$(SRCDIR):
	mkdir $(SRCDIR)

main : $(SRCDIR)/main.o $(SRC_O_FILES)
	g++ -Wall -g -o main $(SRCDIR)/main.o $(SRC_O_FILES)

$(SRCDIR)/main.o : main.cpp $(SRC_H_FILES)
	g++ -Wall -g -o $(SRCDIR)/main.o -c main.cpp

clean :
	rm -f main $(SRCDIR)/*.o