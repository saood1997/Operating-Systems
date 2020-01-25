#!/usr/bin/gnuplot -persist

set terminal pdf

set output "N_Time.pdf"

set title "Gnuploting"

set xlabel "Number"

set ylabel "Time"

set grid

plot "out.txt" using 1:3 smooth acsplines
