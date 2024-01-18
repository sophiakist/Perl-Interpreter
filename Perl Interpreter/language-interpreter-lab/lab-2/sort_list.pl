#!/usr/bin/perl

use strict;
use warnings;

sub bubble_sort {
    my @array = @_;
    my $n = @array;
    my $swapped;

    do {
        $swapped = 0;
        for my $i (1 .. $n - 1) {
            if ($array[$i - 1] > $array[$i]) {
                # Swap the elements
                my $temp = $array[$i - 1];
                $array[$i - 1] = $array[$i];
                $array[$i] = $temp;
                $swapped = 1;
            }
        }
    } while ($swapped);

    return @array;
}

# Example usage:
my @unsorted = (5, 2, 9, 3, 4);
my @sorted = bubble_sort(@unsorted);

print "Unsorted array: @unsorted\n";
print "Sorted array: @sorted\n";
