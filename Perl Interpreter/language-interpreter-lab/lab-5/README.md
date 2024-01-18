# Bison Parser

Create a scanner for your sample programs.
See the [example lab for Python](https://gitlab.cs.wallawalla.edu/cptr354/language-interpreter-lab-python).

## Build Process

To build the `scanner.c` run the following **flex** command.

```sh
flex -o scanner.c scanner.flex
```

The parser is built using **bison**.
Note this command also builds the `token.h`.

```sh
bison --defines=token.h --output=parser.c parser.bison
```

Then build the `main.c`, `parcer.c` and `scanner.c` using **gcc**.
Note that you may get a few warnings that can be ignored.

```sh
gcc main.c scanner.c  parser.c -o parser.out
```

Then execute the test suite using `./parser.out` and pass in the input from your sample program.
For example here is a command for `samples/program.c`

```sh
./parser.out < samples/program.c
```


## Assignment Steps

1. Start by testing the commands work for the sample code provided. 

1. Next copy over your `scanner.flex` and sample programs from lab 4.

1. Finally start working on your bison `parser.bison` file to define the rules of your language.


## Grading Rubric

The grading will be over the following categories.

Points      Description
----------- ------------------------------------
30 points   Ability to parse — Hello world
30 points   Ability to parse — Quadratic equation
30 points   Ability to parse — Integer sorting
10 points   Report formatting and readability


## Turn In

Please submit the URL of your gitlab project to D2L's Brightspace with your report.
On gitlab update the `lab-5` folder to have your report and code snippets before the due date.
