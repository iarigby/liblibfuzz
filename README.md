# liblibfuzz

## TODO
- try having integer input for functions and calling other ones based on mod or something

## questions
- creating a map of pointers to functions that have different type signatures
- getting the call sequence 

## notes
- maybe coverage is not very accurate now because of optimization

## commands
- run with fuzzer: `clang++ $linked-files -fsanitize=address,fuzzer $filename`
- format: `clang-format -i $filename`
- check: `clang-tidy $filename -checks=*,clang-analyzer=*`
