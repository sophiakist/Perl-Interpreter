#!/usr/bin/perl

use strict;
use warnings;

# Define the quadratic function
sub quadratic {
    my ($a, $b, $c, $x) = @_;
    my $result = $a * $x**2 + $b * $x + $c;
    return $result;
}

# Coefficients of the quadratic equation
my $a = 2;
my $b = -3;
my $c = 1;

# Input value for x
my $x = 4;

# Calculate the result
my $result = quadratic($a, $b, $c, $x);

# Print the result
print "Result for f($x) = $a*x^2 + $b*x + $c is: $result\n";
