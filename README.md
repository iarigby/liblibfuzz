# liblibfuzz

## TODO
- try having integer input for functions and calling other ones based on mod or something
- try this on stack (maybe provide manual implementation when pop on empty stack causes exception or somethig)
- next step: [providing dictionaries](https://chromium.googlesource.com/chromium/src/+/master/testing/libfuzzer/efficient_fuzzer.md)

## questions
- creating a map of pointers to functions that have different type signatures
- getting the call sequence 

## challenges
- getting the input summary from libfuzz to see patterns in interesting cases

## notes
- maybe coverage is not very accurate now because of compiler optimization for small functions

## thoughts
- functions could be independently tested for inputs


## commands
- run with fuzzer: `clang++ $linked-files -fsanitize=address,fuzzer $filename`
- format: `clang-format -i $filename`
- check: `clang-tidy $filename -checks=*,clang-analyzer=*`
