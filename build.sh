#!/bin/zsh

build() {
  # delete the disk
  if [ "$1" = "-l" ]; then
      cd build ; rm Disk.txt ; cd ..
      return
  fi
  # make clean
  if [ "$1" = "-c" ]; then
      cd build 
      make clean 
      cd ..
      return
  fi
  # make with debug
  if [ "$1" = "-d" ]; then
      cmake -B build -DCMAKE_BUILD_TYPE=debug . 
      cd build ; make 
      ./main
      cd ..
      return
  fi 
  # Defualt build
  cmake -B build -DCMAKE_BUILD_TYPE=Release .
  cd build ; make 
  ./main
  cd ..
}

build "$1"
