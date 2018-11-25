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
- cpp files (not headers) need to be in fuzz file

## thoughts
- functions could be independently tested for inputs


## commands
- run with fuzzer: `clang++ $linked-files -fsanitize=address,fuzzer $filename`
- format: `clang-format -i $filename`
- check: `clang-tidy $filename -checks=*,clang-analyzer=*`

## fuzzer options
- `-print_pcs` logs when new function is discovered
<br>subsequent code coverage in the function is not reported
- `-runs=`number of inputs tested
- `-max_total_time=` duration of testing
- `-print_final_stats` show summary in the end
<br> right now don't understand what they mean
- `-only_ascii` self explanatory