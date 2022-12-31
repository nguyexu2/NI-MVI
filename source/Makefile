#CXX = g++
CFLAGS =-Wall -pedantic -O2 -g -std=c++17

#change compilation name here
PROGRAM_NAME = main

#important, use . if for current directory, dont leave empty
SOURCE = .
BUILD = build

all: $(PROGRAM_NAME)

run: $(PROGRAM_NAME)
	./$< ../data/pret60_25.cnf ../config/best.conf

debug: $(PROGRAM_NAME)
	valgrind --leak-check=full ./$< ../data/pret60_25.cnf

$(PROGRAM_NAME): $(BUILD)/$(PROGRAM_NAME).o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILD)/%.o: $(SOURCE)/%.cpp | $(BUILD)
	$(CXX) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(BUILD):
	mkdir -p $@

.PHONY : clean
clean :
	-rm $(BUILD)/*.o $(PROGRAM_NAME)

#$< 1st prereq
#$^ all prereq
#$@ var before ":"
