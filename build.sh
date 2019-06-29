#!/bin/bash

echo Renaming HTML files to number.html and placing them in input/
numberOfMessages=1

for i in input/messages/*/*/message_1.html; do
	cp "$i" "input/$numberOfMessages.html"
	numberOfMessages=$((numberOfMessages+1))
done

lastMessage=$((numberOfMessages-1))

echo Done! Converted $numberOfMessages conversations.
read -p "Do you need to convert Facebook HTML messages into plaintext (1 for true and 0 for false): " conversion_check

rm -rf output
mkdir output

if [ "$conversion_check" == 1 ]; then
    read -p "Enter your Facebook name exactly as it appears in conversations: " name
    for i in `seq 1 $lastMessage`; do
        if [ $(($i % 16)) == 0 ]; then
            echo $i
        fi
        cat input/$i.html | perl -MHTML::Entities -pe 'decode_entities($_);' > output/ENCODED_$i.html
        python converter.py output/ENCODED_$i.html output/$i.txt $name 
    done
elif [ "$conversion_check" == 0 ]; then
    for i in `seq 1 $lastMessage`; do
        if [ -f input/$i.html ]; then
            cp input/$i.html output/$i.txt
        fi
        if [ -f input/$i.txt ]; then
            cp input/$i.txt output/
        fi
    done
fi

g++ -std=c++11 "Markov Chain.cpp" -o "Markov Chain.out"
./"Markov Chain.out" 1 $lastMessage

rm -r output/
rm "Markov Chain.out"
