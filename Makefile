compile_object=clang++ -c -o ./build

coverage-reporter: coverageReporter.cpp
	${compile_object}/coverageReporter.o coverageReporter.cpp

permutation-generator: permutationGenerator.cpp
	${compile_object}/permutationGenerator.o permutationGenerator.cpp

insert-guards: stack.cpp
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

