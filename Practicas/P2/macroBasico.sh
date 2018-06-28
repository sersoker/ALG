#!/bin/csh -vx
@ i = 100
while ( $i < 20000000 )
./algoritmoBasico $i >> basico.dat
@ i += 100000
end
