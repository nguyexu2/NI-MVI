#!/bin/bash
# cd ../source && make clean && make
# cd ../scripts
type=best
mkdir -p $type
config=../config/best.conf
FILE="${type}/it$(basename -- $config)".csv

echo config $FILE

if [[ ! -f $FILE ]]
then
	for folder in ../data/train/* ; do

		if [[ ! -d $folder ]] ; then echo folder $folder doesnt exist ; continue ; fi
		echo $folder
		for data in $folder/*; do
			../source/main $data $config 2>/dev/null >> $FILE
		done
	done
 fi

echo test part

for folder in ../data/* ; do

	if [[ ! -d $folder ]] ; then echo folder $folder doesnt exist ; continue ; fi
	if [[ $(basename -- $folder) == train ]] ; then continue ; fi
	
	FILE_RESULT=best/$(basename -- $folder).csv
	if [[ -f $FILE_RESULT ]] ; then echo file $FILE_RESULT exists ; continue ; fi

	echo writing into $FILE_RESULT

	for data in $folder/*; do
		../source/main $data $config 2>/dev/null >> $FILE_RESULT
	done
done