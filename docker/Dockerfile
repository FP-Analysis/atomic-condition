FROM ubuntu:18.04

RUN apt-get update && apt-get install -y --no-install-recommends apt-utils

RUN apt-get install -y \
  ca-certificates \
  git \
  build-essential \
  clang-3.9 \
  llvm-3.9

RUN git clone https://github.com/FP-Analysis/atomic-condition.git atom && \
  cd atom

# Build necessary objects.
WORKDIR /atom
RUN make

# Build GSL first.
RUN tar xf gsl-2.5.tar.gz
WORKDIR /atom/gsl-2.5
RUN ./configure --prefix=/atom/gslbuild CC=clang-3.9
RUN make -j4
RUN ln -s /atom/misc/compile-gsl-sf.sh /atom/gsl-2.5/specfunc
RUN /atom/gsl-2.5/specfunc/compile-gsl-sf.sh

# Build Solver.
WORKDIR /atom
RUN make solver


