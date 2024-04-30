#!/bin/zsh

build() {
    if [ "$1" = "DEBUG" ]; then
        clang -g -o main main.c -DDEBUG --debug
        ./main
        return
    fi

    clang -o main main.c 
    ./main
}

build "$1"
