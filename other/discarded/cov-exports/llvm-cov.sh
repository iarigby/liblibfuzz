#!/bin/bash
filename="$1"
/usr/bin/clang++ -fprofile-instr-generate -fcoverage-mapping $filename.cpp -o $filename
LLVM_PROFILE_FILE="$filename.profraw" ./$filename
llvm-profdata merge -sparse $filename.profraw -o $filename.profdata
llvm-cov show ./$filename -instr-profile=$filename.profdata
llvm-cov report ./$filename -instr-profile=$filename.profdata
#llvm-cov export ./$filename -instr-profile=$filename.profdata > export.json
