#!/bin/bash

read -p "Do you need to convert Facebook HTML messages into plaintext (1 for true and 0 for false): " conversion_check
read -p "Enter first file to be processed: " start
read -p "Enter last file to be processed: " end 

rm -rf output
mkdir output

if [ "$conversion_check" == 1 ]; then
    read -p "Enter Username on Facebook: " name
    for i in `seq $start $end`; do
        if [ $(($i % 16)) == 0 ]; then
            echo $i
        fi
        cat input/$i.html | perl -MHTML::Entities -pe 'decode_entities($_);' > output/ENCODED_$i.html
        python converter.py output/ENCODED_$i.html output/$i.txt $name 
    done
elif [ "$conversion_check" == 0 ]; then
    for i in `seq $start $end`; do
        if [ -f input/$i.html ]; then
            cp input/$i.html output/$i.txt
        fi
        if [ -f input/$i.txt ]; then
            cp input/$i.txt output/
        fi
    done
fi

g++ -std=c++11 "Markov Chain.cpp" -o "Markov Chain.out"
./"Markov Chain.out" $start $end

rm -r output/
rm "Markov Chain.out"