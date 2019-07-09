# Detecting Floating-Point Errors via Atomic Conditions

## Setup
The `docker` folder contains a Dockerfile that can be used to build our implementation.
```
docker build -t atomic .
docker run -it atomic /bin/bash
```
It may takes a few minutes for installing the necessary packages and compiling the whole GSL Library.

## Usage
After entering the interactive container, the working directory is at `/atom`.

### Play with Small examples
Run on the small example `foo`, defined in `src/targetExample.c`:
```
make
bin/gslSolver.out example
```

If you want to play with your own function, just modify the `foo` in `src/targetExample.c`, then
```
make
bin/gslSolver.out example
```

To run on more functions, define the functions in `src/targetExample.c`,
also changes correspondingly in `src/target.h` and `simpleFuncList` in `src/fpInterface.h`, then
```
make
bin/gslSolver.out example
```

### Run on GSL Functions
```
make
bin/gslSolver.out gsl
```

