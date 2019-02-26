# blacklist="-fsanitize-blacklist=trace-pc-guard-blacklist.txt"
# /usr/bin/clang++ -g  -fsanitize-coverage=trace-pc-guard trace-pc-guard-test.cpp -c
# /usr/bin/clang++ trace-pc-guard-cb.cc trace-pc-guard-test.o -fsanitize=address $blacklist

# /usr/bin/clang++ -g  -fsanitize-coverage=trace-pc-guard trace-pc-guard-test.cpp -c
# /usr/bin/clang++ trace-pc-guard-cb.cc trace-pc-guard-test.o -fsanitize=address $blacklist

/usr/bin/clang++ -g  -fsanitize-coverage=trace-pc-guard stack-nontemplate.cpp -c
/usr/bin/clang++ -g trace-pc-guard-cb.cc trace-pc-guard-test.cpp stack-nontemplate.o -fsanitize=address $blacklist

# ASAN_OPTIONS=strip_path_prefix=`pwd`/ ./a.out $2 $3
