#!/bin/bash
echo "" >> squicksort.dat
$I= 1000
while ( $I < 100000 )
./quicksort $I >> squicksort.dat
$I += 1000
end

