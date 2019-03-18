simple: trace-pc-guard-test.cpp stack.cpp
	clang++ trace-pc-guard-test.cpp stack.o

insert-guards: trace-pc-guard-test.cpp trace-pc-guard-cb.cc stack.cpp
	clang++ -o inserted-guards -g -fsanitize-coverage=trace-pc-guard stack.cpp -c
guards: insert-guards
	clang++ -o guards trace-pc-guard-cb.cc trace-pc-guard-test.cpp stack.o -fsanitize=address 
run: guards
	./guards

debug: insert-guards
	clang++ -g -o guards trace-pc-guard-cb.cc trace-pc-guard-test.cpp stack.o -fsanitize=address


.PHONY: test
test: combinationGenerator.cpp combinationGenerator-test.cpp functionPointerMap.cpp functionPointerMap-test.cpp
	clang++ -o tests combinationGenerator-test.cpp functionPointerMap-test.cpp && ./test

