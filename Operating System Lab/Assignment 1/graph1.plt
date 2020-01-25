#!/usr/bin/gnuplot -persist

set terminal pdf

set output "Time.pdf"

set title "Gnuploting"

set xlabel "Number"

set ylabel "Time"

set grid

plot "<paste out.txt out1.txt" using 1:2 smooth acsplines
