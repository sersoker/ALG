#!/bin/csh -vx
@ i = 100
while ( $i < 1000000000 )
./algoritmoDivide $i >> divide.dat
@ i += 10000000
end
