#include <iostream>
#include <vector>
#include <fstream>

class CPPFileCreator{

    private:
        std::string outputFileName;

        std::ofstream out; 
        std::vector<std::string> lines;

    public:
        CPPFileCreator(){}

        CPPFileCreator(std::string outputFileName, std::vector<std::string> lines)
        {
            this->outputFileName = outputFileName;
            this->lines = lines; 
            this->out.open(outputFileName, std::ios::out);
        }

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

        void createCloser()
        {
            this->out << "\n";
            this->out << "\tout.close();\n";
            this->out << "\treturn 0;\n";
            this->out << "}";
        }

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