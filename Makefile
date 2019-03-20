compile_object=clang++ -c -o ./build

simple: main.cpp stack.cpp
	clang++ -c stack.cpp
	clang++ main.cpp stack.o

coverage-reporter: coverageReporter.cpp
	${compile_object}/coverageReporter.o coverageReporter.cpp

combination-generator: combinationGenerator.cpp
	${compile_object}/combinationGenerator.o combinationGenerator.cpp

insert-guards: stack.cpp
	${compile_object}/inserted-guards.o -g stack.cpp -fsanitize-coverage=trace-pc-guard 

guards: insert-guards coverage-reporter combination-generator
	clang++ -fsanitize=address trace-pc-guard-cb.cc main.cpp ./build/coverageReporter.o build/combinationGenerator.o ./build/inserted-guards.o  

run: guards
	./a.out

debug: insert-guards
	clang++ -g -o guards.o -fsanitize=address trace-pc-guard-cb.cc main.cpp coverageReporter.o combinationGenerator.o inserted-guards.o 

# TODO have main test file included in all tests
# .PHONY: test
# test: combinationGenerator.cpp combinationGenerator-test.cpp functionPointerMap.cpp functionPointerMap-test.cpp
# 	clang++ -o tests combinationGenerator-test.cpp functionPointerMap-test.cpp && ./test

