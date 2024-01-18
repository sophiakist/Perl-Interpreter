# Flex Scanner

Create a scanner for your sample programs.
See the [example lab for Python](https://gitlab.cs.wallawalla.edu/cptr354/language-interpreter-lab-python).

## Language Scanner

Add the tokens needed to scan your sample code files.

In addition include the following:

* All the math operations for your language (+_/* etc.)
* ...

## Build Process

To build the `scanner.c` run the following **flex** command.

```sh
flex -o scanner.c scanner.flex
```

Then build the `main.c` and `scanner.c` using **gcc**.

```sh
g++ main.c scanner.c
```

## Grading Rubric

The grading will be over the following categories.

Points      Description
----------- ------------------------------------
30 points   Ability to scan — Hello world
30 points   Ability to scan — Quadratic equation
30 points   Ability to scan — Integer sorting
10 points   Report formatting and readability

## Turn In

Please submit the URL of your gitlab project to D2L's Brightspace with your report.
On gitlab update the `lab-3` folder to have your report and code snippets before the due date.
