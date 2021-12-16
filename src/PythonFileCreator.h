#include <iostream>
#include <vector>
#include <fstream>
/***************************************************************************//**
 * PythonFileCreator
 *
 * Class creates a PY File to build files containing the strings in the lines vector
 *
 *  ******************************************************************************/
class PythonFileCreator{

    private:
        std::string outputFileName; /**< Name of Output File */  

        std::ofstream out; /**< Output File Handle */
        std::vector<std::string> lines; /**< A vector of strings holding the lines in the file */

    public:
        /**
        * Default constructor
        */
        PythonFileCreator(){}

        /**
        * Constructor that takes an output file name, 
        *  and lines vector
        * Sets the properties to the values provided
        * and opens the output file using the out 
        * file handle
        * @param outputFileName a string argument.
        * @param lines a vector of strings.
        */
        PythonFileCreator(std::string outputFileName, std::vector<std::string> lines)
        {
            this->outputFileName = outputFileName;
            this->lines = lines; 
            this->out.open(outputFileName, std::ios::out);
        }

        /**
         * Writes Python code to the out file handle to
         * start building a create file function that
         * creates an output file handle 
         * @return void
         */
        void createHeader()
        {
            this->out << "import sys\n";
            this->out << "\n";
            this->out << "def createFile(fileName):\n";
            this->out << "\tf = open(fileName, \"a\")\n";
        }

        /**
        * Writes Python code to the out file handle 
        * that closes the written codes output file
        * handle and creates a main function that
        * parses a file name argument and provides
        * code to run the main function
        * 
        * @return void
        */
        void createCloser()
        {
            this->out << "\tf.close()\n";
            this->out << "\n";
            this->out << "def main():\n";
            this->out << "\tlist_args = sys.argv\n";
            this->out << "\tfileName = list_args[1]\n";
            this->out << "\tcreateFile(fileName)\n";
            this->out << "\n";
            this->out << "if __name__ == \"__main__\":\n";
            this->out << "\tmain()\n";
        }
        
        /**
        * Writes Python code to the out file handle 
        * that writes Python code to write each line
        * in the lines vector
        * @return void
        */
        void write()
        {
            std::cout << "Writing constructor file, " << this->outputFileName << ". \n"; 
            this->createHeader(); 
            for(std::string line : lines)
            {
                this->out << "\tf.write(\"" <<  line << "\\n\")" << "\n"; 
            }
            this->createCloser();
            this->out.close();
            std::cout << this->outputFileName << " has been created. \n"; 
        }
};