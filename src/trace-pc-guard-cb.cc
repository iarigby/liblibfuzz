// trace-pc-guard-cb.cc
// https://clang.llvm.org/docs/SanitizerCoverage.html
#include <map>
#include <sanitizer/coverage_interface.h>
#include <stdint.h>
#include <stdio.h>
#include <vector>
#include "../include/coverageReporter.h"

extern CoverageReporter coverageReporter;
extern bool started;
extern bool outputMessages;

int i = 0;
extern "C" void __sanitizer_cov_trace_pc_guard_init(uint32_t *start,
                                                    uint32_t *stop) {
  static uint64_t N;
  if (start == stop || *start)
    return;
  printf("INIT: %p %p\n", start, stop);
  for (uint32_t *x = start; x < stop; x++) {
    *x = ++N;
    i++;
  }
}

extern "C" void __sanitizer_cov_trace_pc_guard(uint32_t *guard) {
  if (!*guard)
    return;
  void *PC = __builtin_return_address(0);
  char PcDescr[1024];
  __sanitizer_symbolize_pc(PC, "%p %F %L", PcDescr, sizeof(PcDescr));
  if (started) {
    coverageReporter.addPCForCombination(std::string(PcDescr));
    if(outputMessages) printf("adding to the list: ");
  }
  if (outputMessages) printf("guard: %p %x PC %s\n", guard, *guard, PcDescr);
}
