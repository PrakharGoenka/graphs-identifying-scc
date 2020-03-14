#!/bin/sh

# copy input to the directory of visualization code
cp input.txt ../visualization/graphviz/
# change directory where python code resides
cd ../visualization/graphviz
# run the python code in a virtual environment
pipenv run python3 visualize.py
