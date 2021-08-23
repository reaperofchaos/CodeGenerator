# CodeGenerator
Reads a file and generates a cpp file to build copies of that file

# Description
This project is largely created out of frustration of having to retype the contents of a file 
written in one programming language such as php if I want to automate the generation of that type of code through another language such as cpp. 
This code reads the code you want to copy and generates a cpp file to do that job. Future updates will allow for more file types. 
This should speed up any modifications needed to automate a class if only a few portions of the code need to change. 

# Usage
The code is run using the command line
./CodeGenerator <input filename> -t CPP -o <output filename> 
the order of the flags do not matter but both are required
-t  - output type - at this time, the only option is CPP, but python and other formats will be added soon
-o - output file - name of the output file. It could be anything but any resulting code will be written in C++ at this time

# Build Instructions
# CMAKE
The CodeGenerator file can be compiled using cmake
Make a build folder
mkdir build
cd build
cmake ../src
cmake --build .

# Make
I also have a simple Make file included that will store the executable in the build folder and any objects needed to build the file in the objs folder
make cmd
make run



