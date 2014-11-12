#!/bin/bash

qmake SplitRussianWords.pro
make

# example to run
./bin/SplitRussianWords Почему сложновыговариваемые слова называются сложновыговариваемыми ?
