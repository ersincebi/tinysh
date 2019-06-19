#!/bin/bash
input=""
BASEDIR="`pwd`"
clear
gcc tinysh.c -o tinysh
while [ "$input" != "exit" ]
do
	echo -n "tinysh > " && read input
	if [ "$input" == "help" ]
	then
		echo 'ls <-l, -a>'
		echo 'cd <dir>'
		echo 'pwd'
		echo 'touch <file>'
		continue
	elif [[ "${input:0:1}" == "c" && "${input:1:1}" == "d" ]]
	then
		read -ra array <<<"$input"
		cd "${array[1]}"
		continue
	elif [[ "$input" != "exit" && "${input:0:1}" != "c" && ["${input:1:1}" != "d" ]]
	then
		echo `${BASEDIR}/tinysh $input`
	fi
done
exit