#!/bin/bash
for(( i = 1; i <= 100; i = i + 1))
do
	./make_data.py > main.in
	(time ./my.cpp.out < main.in > my.out) 2>> checkLog
	./test.cpp.out < main.in > test.out
	diff my.out test.out > /dev/null
	if [ $? -ne 0 ]
		then
			echo Wa >> checkLog
			exit
		else 
			echo Ac $i >> checkLog
	fi
done
