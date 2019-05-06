################################################################################
#                                   Makefile                                   
# This file contains the entire structure of the project along
# with all necessary commands 
################################################################################

CC := clang++

### DIRECTORIES ###
# source files, 
SRCDIR := src

# object files. The results from the command for $(SOURCES) will be compiled here
BUILDDIR := build
# extension for source files that should be compiled to object files.
# There are 2 that will be exempt in this stage. You can view more details in SPECIAL FILES section 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# 
MAINFILE := $(SRCDIR)/main.cc

TARGET := bin/main
GUARDS_TARGET := bin/guards
TEST_OBJECT := stack


CFLAGS := -g -w -Wall -Wextra -Werror
LIB := examples/$(TEST_OBJECT).cpp
INC := -I include
INSERTED_GUARDS := bin/inserted-guards.o
SANITIZERFLAGS := -fsanitize=address ./src/trace-pc-guard-cb.cc


$(TARGET): $(OBJECTS) $(MAINFILE)
	@echo " Linking..."
	$(CC) $(INC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(INSERTED_GUARDS): examples/$(TEST_OBJECT).cpp
	clang++ -c -g -o $(INSERTED_GUARDS) examples/$(TEST_OBJECT).cpp \
		-fsanitize-coverage=trace-pc-guard 

guards: $(OBJECTS) $(INSERTED_GUARDS) $(MAINFILE)
	@echo " Linking..."
	$(CC) $(INC) $(SANITIZERFLAGS) $^ -o $(GUARDS_TARGET)

run-guards: guards
	ASAN_OPTIONS=strip_path_prefix=`pwd`/ ./$(GUARDS_TARGET)

### TEST ###
TESTDIR := test
# test files end with 'test' before the extension
TESTEXT := -test.$(SRCEXT)
TEST_SOURCES := $(shell find $(TESTDIR) -type f -name *$(TESTEXT))
TEST_OBJECTS := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(TEST_SOURCES:.$(SRCEXT)=.o))

# This file is used to compile the catch2 library separately so the compilation is sped up
TEST_MAIN := $(TESTDIR)/catch2-main.cpp

TEST_LIB := bin/catch2-main.o

TEST_TARGET := bin/test

$(TEST_LIB): $(TEST_MAIN)
	$(CC) -c $(TEST_MAIN) -o $(TEST_LIB)

$(TEST_TARGET): $(TEST_OBJECTS) $(OBJECTS)
	@echo " Linking tests..."
	$(CC) $^  $(TEST_LIB) -o $(TEST_TARGET) $(LIB)

$(BUILDDIR)/%-test.o: $(TESTDIR)/%$(TESTEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

INTEGRATION_TEST := integrationTest
INTEGRATION_TEST_CLASS_FILE := $(TESTDIR)/$(INTEGRATION_TEST)Class.cc
INTEGRATION_TEST_GUARDS := $(BUILDDIR)/$(INTEGRATION_TEST)-guards.o
INTEGRATION_TEST_FILE := $(TESTDIR)/$(INTEGRATION_TEST).cc

$(INTEGRATION_TEST_GUARDS): $(INTEGRATION_TEST_CLASS_FILE)
	clang++ -c -g -o $(INTEGRATION_TEST_GUARDS) $(INTEGRATION_TEST_CLASS_FILE) \
		-fsanitize-coverage=trace-pc-guard 

integration-test: $(INTEGRATION_TEST_GUARDS) $(OBJECTS) $(INTEGRATION_TEST_FILE)
	@echo " Linking integration test..."
	$(CC) $(INC) $(SANITIZERFLAGS) $(TEST_LIB) $^ -o bin/integration-test

integration-test-run: integration-test
	ASAN_OPTIONS=strip_path_prefix=`pwd`/ ./bin/integration-test

# 	generate pdf documentation
docs: 	Doxyfile
# 	use Doxyfile configuration to generate latex output for each class and recipe for compiling
	doxygen Doxyfile
#	compile latex files and create pdf file
	make -C latex

test: $(TEST_TARGET) $(TEST_LIB)
	./$(TEST_TARGET)
clean:
	@echo " Cleaning..."
	$(RM) -r $(INSERTED_GUARDS) $(BUILDDIR) $(TARGET)

.PHONY: clean inserted_guards
