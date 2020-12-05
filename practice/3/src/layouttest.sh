#!/bin/bash

echo '#_4' >> test.txt
echo t_Layout >> test.txt
echo x_Anzahl Ebenen >> test.txt
echo y_Laufzeit >> test.txt
echo label_Random >> test.txt
echo label_Sortiert >> test.txt
echo label_Level >> test.txt
echo label_VEB >> test.txt



for((i = 3; i < 31; i++))
do
	./layout $i r >> test.txt
	./layout $i s >> test.txt
	./layout $i l >> test.txt
	./layout $i v >> test.txt
	echo "" >> test.txt
	echo $i
done
