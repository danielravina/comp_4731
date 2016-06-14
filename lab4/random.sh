#! /bin/bash
while [ ture ]; do
  n=$RANDOM
  let "n = 1 + $n % 5"
  echo "$1$n"
  sleep $n
done
