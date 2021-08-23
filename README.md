# CodeGenerator
Reads a file and generates a cpp file to build copies of that file
<br />

# Description
This project is largely created out of frustration of having to retype the contents of a file 
written in one programming language such as php if I want to automate the generation of that type of code through another language such as cpp. 
This code reads the code you want to copy and generates a cpp file to do that job. Future updates will allow for more file types. 
This should speed up any modifications needed to automate a class if only a few portions of the code need to change. 
<br />

# Usage
The code is run using the command line <br />

<pre>
./CodeGenerator &lt;input filename&gt; -t CPP -o &lt;output filename&gt;
</pre>
the order of the flags do not matter but both are required <br />

<pre>
<b>-t</b> [OUTPUT TYPE] Output Type
                     REQUIRED
                     Specify the type of code generated to build
                     <em>CPP</em>   - C++ <br />
                  

<b>-o</b> [FILENAME]        outputFile
                     REQUIRED
                     The output file extension could be anything 
                     but any resulting code will be written in C++ 
                     at this time
</pre>

# Build Instructions
## CMAKE
The CodeGenerator file can be compiled using cmake <br />
1. Make a build folder
<pre>
mkdir build
cd build
</pre>
2. Run CMAKE
<pre>
cmake ../src
cmake --build .
</pre>
  
## Make
I also have a simple Make file included that will store the executable in the build folder and any objects needed to build the file in the objs folder
<pre>
make cmd 
make run
</pre>


