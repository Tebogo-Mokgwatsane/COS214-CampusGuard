CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
LDFLAGS  =

# Two entry points, so they are not linked together.
MAINS       = main.cpp main_interactive.cpp

# Everything else (patterns, units, facade, ...) is picked up automatically,
# so new files such as EmergencyFacade.cpp need no Makefile change.
LIB_SOURCES = $(filter-out $(MAINS),$(wildcard *.cpp))
LIB_OBJECTS = $(LIB_SOURCES:.cpp=.o)

INTERACTIVE = campusguard
FF          = campusguard_ff

DEPS = $(LIB_OBJECTS:.o=.d) main.d main_interactive.d

.PHONY: all compile interactive ff run run-ff valgrind clean rebuild

all: $(INTERACTIVE) $(FF)

compile: all

interactive: $(INTERACTIVE)
ff: $(FF)

$(INTERACTIVE): main_interactive.o $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Built $@ successfully."

$(FF): main.o $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Built $@ successfully."

# Each .cpp produces a .o in the same directory
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the interactive program
run: $(INTERACTIVE)
	./$(INTERACTIVE)

# Run the automated (non-interactive) test program
run-ff: $(FF)
	./$(FF)

# Memory-leak check (automated program, since it needs no input)
valgrind: $(FF)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(FF)

# Remove build artefacts
clean:
	rm -f *.o *.d $(INTERACTIVE) $(FF)
	clear
	@echo "Cleaned."

# Rebuild from scratch
rebuild: clean all