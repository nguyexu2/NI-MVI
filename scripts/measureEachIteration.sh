#!/bin/bash

cd ../source && make clean && make
cd ../scripts
type=eachIteration
mkdir -p $type
data=../data/train/uf200-860/uf200-072.cnf
config=../config/best.conf
FILE=$type/data.csv

../source/main $data $config > $FILE 2>&1