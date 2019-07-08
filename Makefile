CXX=clang++-3.9
LD=clang++-3.9
CXXFLAGS=-std=c++11 -O2 -fPIC -fno-rtti

CLANG=clang-3.9
OPT=opt-3.9
CLANGFLAGS=-fPIC -fno-rtti

LLVMCFG=llvm-config-3.9
LLVMCXXFLAGS=$(shell $(LLVMCFG) --cxxflags)
LLVMCXXFLAGS+=-fPIC -fno-rtti
LLVMLDFLAGS=$(shell $(LLVMCFG) --ldflags)

GSLCFG=/atom/gslbuild/bin/gsl-config
GSLCXXFLAGS=$(CXXFLAGS) $(shell $(GSLCFG) --cflags)
GSLLDFLAGS=-static $(shell $(GSLCFG) --libs)

OS_NAME=$(shell uname -s)
ifeq ($(OS_NAME), Darwin)
	# For MacOS: https://stackoverflow.com/questions/37210682/building-and-using-a-pass-for-llvm-3-8-on-osx
	LLVMLDFLAGS+=-Wl,-flat_namespace -Wl,-undefined -Wl,suppress
endif

GREEN=$(shell tput setaf 2)
NOCOLOR=$(shell tput sgr0)


define MSG
	@tput setaf 2
	@echo [DONE]$1
	@tput sgr0
endef

DEPS = src/fpUtil.h src/communicator.h src/opcode.h

.PHONY: clean handler util target solver

all: handler util target

# The handler start
handler: build/handlers.o
	$(call MSG, "The Operation Handler Compiled (but not linked): $<")
build/handlers.o: src/handlers.cpp $(DEPS)
	@mkdir -p build
	$(CXX) -c $(CXXFLAGS) -o $@ $<
# The handler finish

util: build/fpUtil.o
	$(call MSG, "The FpUtil Compiled (but not linked): $<")
build/fpUtil.o: src/fpUtil.cpp src/fpUtil.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile the target under analysis start.
targetObjs = build/targetExample.o
target: build/all_target.a
	$(call MSG, "The Target Compiled: $^")
build/all_target.a: $(targetObjs)
	ar crv $@ $(targetObjs)
build/targetExample.o: src/targetExample.c lib/libPassModule.so
	@mkdir -p build
	$(CLANG) -S -emit-llvm -g -o build/targetExample.ll $<
	$(OPT) -S -load lib/libPassModule.so -funcpass -o build/targetExample_i.ll build/targetExample.ll
	$(CLANG) $(CLANGFLAGS) -c -o $@ build/targetExample_i.ll
# Compile the target under analysis finish.

# Generate GSL Solver
solver: bin/gslSolver.out
	$(call MSG, "The GSL Solver Binary: $^")
bin/gslSolver.out: build/gslSolver.o build/fpUtil.o build/handlers.o build/all_target.a
	@mkdir -p bin
	$(LD) -o $@ $^ $(GSLLDFLAGS)
build/gslSolver.o: src/gslSolver.cpp $(DEPS)
	@mkdir -p build
	$(CXX) $(GSLCXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.so *.out
	rm -f *.ll *.bc *.s
	rm -f *.dwo
	rm -rf *.dSYM
	rm -rf build/
	rm -rf bin/
	rm -rf data/
	rm -rf pdfs/
