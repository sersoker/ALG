#!/bin/bash
for ((P=10;P<=26;P=P+1))
do
  ./equiposSinPodaModificado $P >> sinPoda.dat
done
