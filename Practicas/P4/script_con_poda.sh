#!/bin/bash
for ((P=10;P<=26;P=P+1))
do
  ./equiposConPodaModificado $P >> conPoda.dat
done
