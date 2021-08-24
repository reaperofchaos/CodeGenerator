#include <iostream>
#include <vector>
#include <fstream>

class PythonFileCreator{

    private:
        std::string outputFileName;

        std::ofstream out; 
        std::vector<std::string> lines;

    public:
        PythonFileCreator(){}

        PythonFileCreator(std::string outputFileName, std::vector<std::string> lines)
        {
            this->outputFileName = outputFileName;
            this->lines = lines; 
            this->out.open(outputFileName, std::ios::out);
        }

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

        void createHeader()
        {
            this->out << "import sys\n";
            this->out << "\n";
            this->out << "def createFile(fileName):\n";
            this->out << "\tf = open(fileName, \"a\")\n";
        }

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