# CodeGenerator
Reads a file and generates a cpp file or py file to build copies of that file
<br />

# Description
This project is largely created out of frustration of having to retype the contents of a file 
written in one programming language such as php if I want to automate the generation of that type of code through another language such as cpp. 
This code reads the code you want to copy and generates a cpp or a python file to do that job. Future updates will allow for more file types. 
This should speed up any modifications needed to automate a class if only a few portions of the code need to change. 
<br />
Change
# Usage
The code is run using the command line <br />

<pre>
./CodeGenerator &lt;input filename&gt; -o &lt;output filename&gt;
</pre>

<pre>


<b>-o</b> [FILENAME]        outputFile
                     REQUIRED
                     The output file extension in the output filename is
                     used to determine if a python or cpp builder file 
                     needs to be created to generate the input file 
                     provided. Any other filetypes will generate an error. 
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


