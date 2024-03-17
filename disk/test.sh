#!/bin/zsh
sudo clang -o test test.c --debug -DDEBUG
./test
