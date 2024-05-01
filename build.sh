#!/bin/zsh

build() {
  # delete the disk
  if [ "$1" = "-l" ]; then
      cd build ; rm Disk.txt ; cd ..
      return
  fi
  if [ "$1" = "-c" ]; then
      cd build ; make clean 
      ./main
      cd ..
      return
  fi
  if [ "$1" = "-d" ]; then
      cmake -B build . -DDEBUG_MODE=ON
      cd build ; make 
      ./main
      cd ..
      return
  fi
  cmake -B build  
  cd build ; make 
  ./main
  cd ..
}

build "$1"
