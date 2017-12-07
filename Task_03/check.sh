#!/bin/bash
for(( i = 1; i; i = i + 1))
do
	./make_data.py > main.in
	./my.cpp.out < main.in > my.out
	./test.cpp.out < main.in > test.out
	diff my.out test.out > /dev/null
	if [ $? -ne 0 ]
		then
			echo Wa
			exit
		else 
			echo Ac $i
	fi
done
