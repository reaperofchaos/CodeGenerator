#include <iostream>
#include <vector>
#include <fstream>
#include "PythonFileCreator.h"
#include "CPPFileCreator.h"
/***************************************************************************//**
 * FileCreator
 *
 * Class designed to abstract the process of writing out put files.
 * The output type is parsed and then the output file and lines are passed
 * off to the appropriate class
 *
 *  ******************************************************************************/

class FileCreator
{  
    public:  
        /** 
         * An enum.
         * Stores output file types
         */
        enum OutputTypes { 
          CPP, /**< enum value CPP. */  
          PY, /**< enum value PY. */  
         }    
        enum OutputTypes {CPP, PY};

    private:
        std::string outputFileName; /**< Name of Output File */  
        OutputTypes outputType; /**< Output File enum value */
        std::vector<std::string> lines; /**< A vector of strings holding the lines in the file */

    public: 
       /**
       * Default constructor
       */
        FileCreator(){}
       /**
       * Constructor that takes an output file name, 
       * output file type and lines vector
       * Sets the properties to the values provided
       * @param outputFileName a string argument.
       * @param outputType an OutputTypes enum value.
       * @param lines a vector of strings.
       */
        FileCreator(std::string& outputFileName, OutputTypes& outputType, std::vector<std::string>& lines)
        {
            this->outputFileName = outputFileName;
            this->outputType = outputType;
            this->lines = lines; 
        }
       /**
       * Parses the outputTypes property and creates the appropiate
       * PythonFileCreator or CPPCreator class. Then the class's write
       * function is called
       * @return void
       */
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