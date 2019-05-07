################################################################################
#                                   Makefile                                   # 
# This file contains the entire structure of the project along                 #
# with all necessary commands. Each recipe is followed by an @echo statement   #
# that explains what it does.						       #
################################################################################



# The user should replace th
# with the name of the class and its location
# and the include directory for the header file
# The rest of the file is relevant only for developers
TEST_TARGET_FILE := examples/stack.cpp
TEST_TARGET_INC := -I examples

### COMPILER ###
CC := clang++
CFLAGS := -g -w -Wall -Wextra -Werror
INC := -I include


### DIRECTORIES ###
# source files, 
SRCDIR := src

# object files. The results from the command for $(SOURCES) will be
# compiled here
BUILDDIR := build
# extension for source files that should be compiled to object files.
# There are 2 that will be exempt in this stage
# because they require to be compiled/included separately  
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

MAINFILE := $(SRCDIR)/main.cc
TARGET := bin/guards

INSERTED_GUARDS := bin/inserted-guards.o
SANITIZERFLAGS := -fsanitize=address ./src/trace-pc-guard-cb.cc

.DEFAULT_GOAL := $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "\t \e[96mCompiling object\e[90m"
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(INSERTED_GUARDS): $(TEST_TARGET_FILE)
	@echo "\t \e[96mCompiling the test target class with guards\e[90m"
	clang++ -c -g -o $@ $^ \
		-fsanitize-coverage=trace-pc-guard 

$(TARGET): $(OBJECTS) $(INSERTED_GUARDS) $(MAINFILE)
	@echo "\t \e[96m Linking with sanitizer coverage\e[90m"
	$(CC) $(INC) $(TEST_TARGET_INC) $(SANITIZERFLAGS) $^ -o $@

run: $(TARGET)
	@echo "\t \e[96m Testing combinations for $(TEST_TARGET_FILE)\e[90m"
	ASAN_OPTIONS=strip_path_prefix=`pwd`/ ./$(TARGET)

### TEST ###
TESTDIR := test

# This file is used to compile the catch2 library separately
# so the compilation is sped up
TEST_MAIN := $(TESTDIR)/catch2-main.cpp
TEST_LIB := bin/catch2-main.o
$(TEST_LIB): $(TEST_MAIN)
	@echo "\t \e[96m Compiling the test library\e[90m"
	$(CC) -c $^ -o $@

# test files end with 'test' before the extension
TESTEXT := -test.$(SRCEXT)
TEST_SOURCES := $(shell find $(TESTDIR) -type f -name *$(TESTEXT))
TEST_OBJECTS := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(TEST_SOURCES:.$(SRCEXT)=.o))

TEST_TARGET := bin/test
$(TEST_TARGET): $(TEST_OBJECTS) $(OBJECTS) $(TEST_LIB)
	@echo "\t \e[96mLinking tests\e[90m"
	$(CC) $^ -o $(TEST_TARGET) 

$(BUILDDIR)/%-test.o: $(TESTDIR)/%$(TESTEXT)
	@echo "\t \e[96mCompiling unit test\e[90m"
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

test: $(TEST_TARGET)
	@echo "\t \e[96mRunning unit tests\e[90m"
	./$(TEST_TARGET)

INTEGRATION_TEST := combinationTester-test
INTEGRATION_TEST_CLASS := integrationTestClass
INTEGRATION_TEST_FILE := $(TESTDIR)/$(INTEGRATION_TEST).cc
INTEGRATION_TEST_TARGET := bin/integration-test

# compile the integration test class with sanitizer flag
INTEGRATION_TEST_CLASS_FILE := $(TESTDIR)/$(INTEGRATION_TEST_CLASS).cc
INTEGRATION_TEST_GUARDS := $(BUILDDIR)/$(INTEGRATION_TEST_CLASS)-guards.o
$(INTEGRATION_TEST_GUARDS): $(INTEGRATION_TEST_CLASS_FILE)
	@echo "\t \e[96mCompiling the integration test class with guards\e[90m"
	@mkdir -p $(BUILDDIR)
	clang++ -c -g $^ -fsanitize-coverage=trace-pc-guard -o $@

$(INTEGRATION_TEST_TARGET): $(INTEGRATION_TEST_GUARDS) $(TEST_LIB) \
$(OBJECTS) $(INTEGRATION_TEST_FILE)
	@echo "\t \e[96mLinking integration test...\e[90m"
	$(CC) $(INC) $(SANITIZERFLAGS) $^ -o $@

integration-test-run: $(INTEGRATION_TEST_TARGET)
	@echo "\t \e[96mRunning the integration test with $(INTEGRATION_TEST_CLASS)\e[90m"
	ASAN_OPTIONS=strip_path_prefix=`pwd`/ ./bin/integration-test

test-all: test integration-test-run

# 	generate pdf documentation
docs: 	Doxyfile myrefman.tex
# 	use Doxyfile configuration to generate latex output for each class
	doxygen Doxyfile
#	compile my latex file that includes doxygen ones and create pdf file
	pdflatex myrefman.tex

clean:
	@echo "\t \e[96mCleaning...\e[90m"
	$(RM) -r $(INSERTED_GUARDS) $(BUILDDIR) $(TARGET) $(TEST_LIB)

.PHONY: clean
