#include <iostream>
#include <vector>
#include <fstream>
/***************************************************************************//**
 * CPPFileCreator
 *
 * Class creates a CPP File to build files containing the strings in the lines vector
 *
 *  ******************************************************************************/
class CPPFileCreator{

    private:
        std::string outputFileName; /**< Name of Output File */  

        std::ofstream out; /**< Output File Handle */
        std::vector<std::string> lines; /**< A vector of strings holding the lines in the file */

    public:
        /**
        * Default constructor
        */
        CPPFileCreator(){}

       /**
       * Constructor that takes an output file name, 
       *  and lines vector
       * Sets the properties to the values provided
       * and opens the output file using the out 
       * file handle
       * @param outputFileName a string argument.
       * @param lines a vector of strings.
       */
        CPPFileCreator(std::string outputFileName, std::vector<std::string> lines)
        {
            this->outputFileName = outputFileName;
            this->lines = lines; 
            this->out.open(outputFileName, std::ios::out);
        }

        /**
         * Writes C++ code to the out file handle to
         * build a main function that
         * parses a fileName argument and creates an 
         * output file handle 
         * @return void
         */
        void createHeader()
        {
            this->out << "#include <iostream>\n";
            this->out << "#include <fstream>\n";
            this->out << "\n";
            this->out << "int main(int argc, char *argv[])\n";
            this->out << "{\n";
            this->out << "\t\/\/Default output file is output.cpp\n";
            this->out << "\tstd::string fileName = \"output.cpp\";\n";
            this->out << "\tif(argc > 1)\n";
            this->out << "\t{\n";
            this->out << "\t\t \/\/First argument is the filename\n";
            this->out << "\t\tfileName = argv[1];\n";
            this->out << "\t};\n";
            this->out << "\tstd::ofstream out;\n";
            this->out << "\tout.open(fileName, std::ios::out);\n";
            this->out << "\n";
            this->out << "\t//Write Lines found in Input File \n"; 
        }

        /**
        * Writes C++ code to the out file handle 
        * that closes the written codes output file
        * handle and main function
        * @return void
        */
        void createCloser()
        {
            this->out << "\n";
            this->out << "\tout.close();\n";
            this->out << "\treturn 0;\n";
            this->out << "}";
        }

        /**
        * Writes C++ code to the out file handle 
        * that writes c++ code to write each line
        * in the lines vector
        * @return void
        */
        void write()
        {
            std::cout << "Writing constructor file, " << this->outputFileName << ". \n"; 
            this->createHeader(); 
            for(std::string line : lines)
            {
                this->out << "\tout << \"" <<  line << "\" << \"\\n\";" << "\n"; 
            }
            this->createCloser();
            this->out.close();
            std::cout << this->outputFileName << " has been created. \n"; 
        }
};