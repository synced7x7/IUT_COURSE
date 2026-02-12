#!/bin/bash

echo "Enter a number"
read n

if [ $n -le 1 ]; then
    echo "$n is not a prime number"
    exit
fi

i=2
flag=0

while [ $i -le $((n / 2)) ]
do
    r=$((n % i))
    if [ $r -eq 0 ]; then 
        flag=1
        break
    fi
     i=$((i + 1))
done

if [ $flag -eq 1 ]; then 
    echo "$n is not a prime number"
else 
    echo "$n is a prime number"
fi


