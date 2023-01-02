#!/bin/bash
# cd ../source && make clean && make
# cd ../scripts
type=population
mkdir -p $type

for config in ../config/$type/*; do
FILE="${type}/it$(basename -- $config)".csv

echo config $FILE

if [[ -f $FILE ]] ; then echo file $FILE exits ; continue ; fi

for folder in ../data/train/* ; do

	if [[ ! -d $folder ]] ; then echo folder $folder doesnt exist ; continue ; fi
	echo $folder
	for data in $folder/*; do
		../source/main $data $config 2>/dev/null >> $FILE
	done
done
done 
