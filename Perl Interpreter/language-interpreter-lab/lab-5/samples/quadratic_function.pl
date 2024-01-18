#!/usr/bin/perl

use strict;
use warnings;

# Coefficients of the quadratic equation
my $a = 2;
my $b = -3;
my $c = 1;

# Input value for x
my $x = 4;

# Calculate the result
my $result = $a * $x ** 2 + $b * $x + $c;

# Print the result
print ("Result for f($x) = $a*x^2 + $b*x + $c is: $result");
