# Flex Scanner

Create a scanner for your sample programs.
See the [example lab for Python](https://gitlab.cs.wallawalla.edu/cptr354/language-interpreter-lab-python).

## Testing the Language Scanner

Write unit test for your sample code.
The sample program uses `utest.h` which is a simple c unit test framework.
The documentation can be found at <https://github.com/sheredom/utest.h>.

The `main.c` has been replaced with unit test code.
Your task is to create one unit test for each sample file.

When you submit the code to GitLab, the CI should automatically compile and run your test code.
To recieve full credit, the tests must pass when run through GitLab CI.

## Build Process

To build the `scanner.c` run the following **flex** command.

```sh
flex -o scanner.c scanner.flex
```

Then build the `main.c` and `scanner.c` using **gcc**.

```sh
gcc main_test.c scanner.c -o scanner_test.out
```

Then execute the test suite using `./a.out`.

```sh
./scanner_test.out
```

## Scanner Only


```sh
flex -o scanner.c scanner.flex
gcc main_test.c scanner.c -o scanner.out
./scanner.out
```


## Grading Rubric

The grading will be over the following categories.

Points      Description
----------- ------------------------------------
30 points   Ability to test — Hello world
30 points   Ability to test — Quadratic equation
30 points   Ability to test — Integer sorting
10 points   Passes continuous integration

## Turn In

Please submit the URL of your gitlab project to D2L's Brightspace with your report.
On gitlab update the `lab-4` folder to have your report and code snippets before the due date.
