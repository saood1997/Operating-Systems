#!/bin/bash


b=1
while [ $b -lt 11 ]
do
	gcc assig 1.c -o output
	./output>>out.txt
	b=`expr $b + 1`
	
	
done
cat out.txt
gnuplot graph.plt

awk ' function abs(x){ if(x<0) return x*=-1
else return x}{print abs(s1 = s2 - 3.14156)'out.txt > out1.txt

awk ' function abs(x){ if(x<0) return x*=-1
else return x}{print abs(s1 = (s2 - 3.14156)/3.14156)'out.txt > out2.txt

gnuplot graph1.plt

