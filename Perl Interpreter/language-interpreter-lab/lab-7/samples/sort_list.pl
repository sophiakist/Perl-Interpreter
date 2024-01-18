my @unsorted = (51, 22, 19, 33, 44);
my $swapped = 1;

while ($swapped) {
    $swapped = 0;
     for my $i (1 .. @unsorted) {
         if (@unsorted[$i - 1] > @unsorted[$i]) {
             my $temp = @unsorted[$i - 1];
             @unsorted[$i - 1] = @unsorted[$i];
             @unsorted[$i] = $temp;
             $swapped = 1;
         }
     }
}

 print @unsorted;


