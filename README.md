# liblibfuzz

## TODO
- try having integer input for functions and calling other ones based on mod or something
- try this on stack (maybe provide manual implementation when pop on empty stack causes exception or somethig)
- next step: [providing dictionaries](https://chromium.googlesource.com/chromium/src/+/master/testing/libfuzzer/efficient_fuzzer.md)
- turn the map interface into vector instead?

## current challenges
- getting the correct type for input
- determining how many parameters the function needs  
I think we would need to generate inputs first

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


- try using different signatures, and try it out on std::vector
- 


- move semantics and left semantics


## inbox

- more about [code <colgroup></colgroup>verage](https://clang.llvm.org/docs/SourceBasedCodeCoverage.html)
- 