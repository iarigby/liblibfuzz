#using https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
#made some modifications
#added my own guards and test scripts

CC := clang++
# CC := clang++ --analyze
SRCDIR := src
BUILDDIR := build
MAINFILE := src/main.cc
TARGET := bin/main
TEST_OBJECT := stack
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
LIB := examples/$(TEST_OBJECT).cpp
INC := -I include
INSERTED_GUARDS := bin/inserted-guards.o
SANITIZERFLAGS := -fsanitize=address ./src/trace-pc-guard-cb.cc

TEST_SOURCES := $(shell find test -type f -name *test.$(SRCEXT))
TEST_OBJECTS := $(patsubst test/%,$(BUILDDIR)/%,$(TEST_SOURCES:.$(SRCEXT)=.o))
TEST_TARGET := bin/test
TEST_LIB := catch2/tests-main.o

$(TARGET): $(OBJECTS) $(MAINFILE)
	@echo " Linking..."
	$(CC) $(INC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(INSERTED_GUARDS): examples/$(TEST_OBJECT).cpp
	clang++ -c -g -o $(INSERTED_GUARDS) examples/$(TEST_OBJECT).cpp -fsanitize-coverage=trace-pc-guard 

guards: $(OBJECTS) $(INSERTED_GUARDS) $(MAINFILE)
	@echo " Linking..."
	$(CC) $(INC) $(SANITIZERFLAGS) $^ -o bin/guards

tests-main: test/tests-main.cpp
	$(CC) -c test/tests-main.cpp -o $(TEST_LIB)

$(TEST_TARGET): $(TEST_OBJECTS) $(OBJECTS)
	@echo " Linking tests..."
	$(CC) $^  $(TEST_LIB) -o $(TEST_TARGET) $(LIB)

$(BUILDDIR)/%test.o: test/%test.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

test: $(TEST_TARGET)
	./$(TEST_TARGET)
clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(INSERTED_GUARDS) $(BUILDDIR) $(TARGET)"; $(RM) -r $(INSERTED_GUARDS) $(BUILDDIR) $(TARGET)

.PHONY: clean inserted_guards
