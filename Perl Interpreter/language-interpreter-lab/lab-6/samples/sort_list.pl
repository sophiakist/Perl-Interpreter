#!/usr/bin/perl


my @unsorted = (5, 2, 9, 3, 4);
my $n = @unsorted;
my $swapped;

do {
    $swapped = 0;
    for my $i (1 .. $n - 1) {
        if ($unsorted[$i - 1] > $unsorted[$i]) {
            my $temp = $unsorted[$i - 1];
            $unsorted[$i - 1] = $unsorted[$i];
            $unsorted[$i] = $temp;
            $swapped = 1;
        }
    }
} while($swapped)

print ("Sorted array: @unsorted");
