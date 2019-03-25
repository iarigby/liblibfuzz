#using https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/

CC := clang++
SRCDIR := src
BUILDDIR := build
TARGET := bin/runner

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
LIB := examples/stack.cpp
INC := -I include

$(TARGET): $(OBJECTS)
	echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester


test: tester
	./bin/tester
clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean


compile_object=clang++ -c -o ./build

coverage-reporter: coverageReporter.cpp
	${compile_object}/coverageReporter.o coverageReporter.cpp

permutation-generator: permutationGenerator.cpp
	${compile_object}/permutationGenerator.o permutationGenerator.cpp

insert-guards: 
	${compile_object}/inserted-guards.o -g stack.cpp -fsanitize-coverage=trace-pc-guard 

guards: insert-guards coverage-reporter permutation-generator
	clang++ -fsanitize=address trace-pc-guard-cb.cc main.cpp ./build/coverageReporter.o build/permutationGenerator.o ./build/inserted-guards.o  

simple: coverage-reporter permutation-generator
	clang++ main.cpp stack.cpp ./build/coverageReporter.o build/permutationGenerator.o

run: guards
	./a.out

debug: insert-guards
	clang++ -g -o guards.o -fsanitize=address trace-pc-guard-cb.cc main.cpp coverageReporter.o permutationGenerator.o inserted-guards.o 

# TODO have main test file included in all tests
# .PHONY: test
# test: permutationGenerator.cpp permutationGenerator-test.cpp functionPointerMap.cpp functionPointerMap-test.cpp
# 	clang++ -o tests combinationGenerator-test.cpp functionPointerMap-test.cpp && ./test

