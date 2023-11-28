#!/bin/bash

DIROUT="./output"

mkdir -p "${DIROUT}"

for INFILE in *.C *.H; do
    ./convert.py --infile "${INFILE}" --outfile "${DIROUT}/${INFILE}"
done
