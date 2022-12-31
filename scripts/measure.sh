#!/bin/bash
# cd ../source && make clean && make
# cd ../scripts


for folder in ../data/train/* ; do

	if [[ ! -d $folder ]] ; then continue ; fi
	echo $folder
	# echo $(ls $folder | wc -l)
	for i in $folder/*; do
		../source/main $i ../config/best.conf 2>/dev/null >> output.csv
	done
done
