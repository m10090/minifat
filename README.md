# MiniFAT

## Description

MiniFAT is a lightweight simulation of a FAT (File Allocation Table) file system, implemented in C. This project aims to demonstrate the fundamental concepts and operations involved in managing a file system, with a focus on simplicity and clarity.

## Features

- **Basic File System Operations:** MiniFAT supports essential file system operations such as file creation, deletion, reading, and writing.
- **Directory Structure Management:** The project illustrates the management of directory structures for organizing files.
- **File Allocation Techniques:** MiniFAT showcases file allocation techniques, demonstrating how files are stored and accessed within the file system.
- **Command-Line Interface:** Users can interact with MiniFAT through a simple command-line interface, providing a hands-on experience of working with the file system.

## Purpose

The purpose of MiniFAT is to provide a clear and concise example of how a basic file system operates. It serves as a learning tool for understanding the underlying principles of file systems, disk allocation, and directory management. 

## Get Started

To run MiniFAT, you need macOS or Linux as it works with clang.
you can run with windows not sure about spacing 

```bash
git clone github.com/m10090/minifat minifat
cd minifat
chmod +x build.sh
./build.sh [-d #if you want to run in debug mode]
```

## Basic Commands

- `import <filename>`: Import files from your PC. Note: You can import files from outside your project files, but it may result in improper naming.
- `export <filename>`: Export from your MiniFAT to your PC.
- `mvd <dirname> <path/newDirname>`: Move a directory.
- `copy <filename> <path/newFilename>`: Copy a file.
- `md <dirname>`: Make directory(s).
- `cd <dirname>`: Change directory and go back if `dirname = ..`.
- `dir`: Show the current directory content.
- `type`: Cat a file.
- `rd <dirname>`: Remove directory(s).
- `del <filename>`: Delete file(s).
- `rename <filename> <newFilename>`: Rename a file.
