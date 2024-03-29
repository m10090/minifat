#!/bin/bash

build() {
    if [ "$1" == "DEBUG" ]; then
        clang -o main main.c -DDEBUG --debug
        ./main
        return
    fi

    clang -o main main.c 
    ./main
}

build "$1"
