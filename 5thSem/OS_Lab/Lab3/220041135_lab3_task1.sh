#!/bin/bash

echo "Enter a number:"
read n

r=$((n%2))

if [ $r -eq 0 ]; then
    echo "The number $n is even."
else
    echo "The number $n is odd."
fi