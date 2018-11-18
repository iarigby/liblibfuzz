# liblibfuzz

## questions
- creating a map of pointers to functions that have different type signatures
- getting the call sequence 

## notes
- maybe coverage is not very accurate now because of optimization

## commands
- format: `clang-format -i $filename`
- check: `clang-tidy $filename -checks=*,clang-analyzer=*`
