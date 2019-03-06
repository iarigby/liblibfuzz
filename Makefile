simple: trace-pc-guard-test.cpp stack.cpp
	clang++ trace-pc-guard-test.cpp stack.cpp
guards: trace-pc-guard-test.cpp trace-pc-guard-cb.cc stack.cpp
	./trace-pc-guard-script.sh
