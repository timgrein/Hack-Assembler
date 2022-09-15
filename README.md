### About the Project

This repository contains an assembler, which translates the <b>nand2tetris assembly language</b> to the <b>Hack machine language</b> used in the [nand2tetris course](https://www.nand2tetris.org).
The assembler is written in <b>C++</b> and uses <b>bazel</b> for building the assembler.

For a detailed description of the assembler visit [nand2tetris Project 6](https://www.nand2tetris.org/project06).

### Building the assembler
Make sure bazel is installed ([Installing Bazel](https://docs.bazel.build/versions/main/install.html)).

Build the main target (from root directory), which is a simple CLI for the assembler:
```shell
bazel build src//main
```

### Running the assembler
Locate the <b>main</b> executable and call it with an input file (.asm extension) and a location for the output file (.hack extension):

```shell
./main hack-programs/add100.asm hack-programs/add100.hack
```

### Running the tests
I've used GoogleTest for unit testing ([GoogleTest](https://github.com/google/googletest)). 

To run all tests simply run in the root directory:
```shell
bazel test --test_output=all ...
```