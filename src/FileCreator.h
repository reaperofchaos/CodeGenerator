#include <iostream>
#include <vector>
#include <fstream>
#include "PythonFileCreator.h"
#include "CPPFileCreator.h"

class FileCreator
{  
    public:         
        enum OutputTypes {CPP, PY};

    private:
        std::string outputFileName;
        OutputTypes outputType; 
        std::vector<std::string> lines;

    public: 
        FileCreator(){}
        FileCreator(std::string& outputFileName, OutputTypes& outputType, std::vector<std::string>& lines)
        {
            this->outputFileName = outputFileName;
            this->outputType = outputType;
            this->lines = lines; 
        }

        void write()
        {
            switch(this->outputType)
            {
                case PY:
                {
                    PythonFileCreator pyFile = PythonFileCreator(this->outputFileName, this->lines);
                    pyFile.write();
                    break;
                }
                case CPP:
                {
                    CPPFileCreator cppFile = CPPFileCreator(this->outputFileName, this->lines);
                    cppFile.write();
                    break;
                }
            }
        }
};