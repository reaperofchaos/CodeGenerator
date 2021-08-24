/***************************************************************************//**
 * Code Generator
 *
 * Reads a file and generates a cpp or py file to build copies of that file
 *
 *  ******************************************************************************/

#include <iostream>
#include <cstring>
#include <vector>
#include "FileReader.h"
#include "FileCreator.h"

int handleArguments(int argc, char *argv[], std::string &fileName, FileCreator::OutputTypes &outputType, std::string &outputFileName);
bool validateFileType(std::string &fileName);
std::string stringToLower(std::string str);
bool flagExists(std::string flag, std::vector<std::string> arguments);
std::string getFlagArgument(std::string flag, std::vector<std::string> arguments);
void checkForOutputFileName(std::string &outputFileName, FileCreator::OutputTypes &outputType, int &errorCode, std::vector<std::string> &arguments);
bool validateOutputType(std::string &outputFileName, FileCreator::OutputTypes &outputFileType);

/**
* A vector of supported input File Types
*/
std::vector<std::string> SupportedFileTypes = { ".html", ".HTML", ".C", ".c", 
                                                ".cpp", ".CPP",".php", ".PHP",
                                                ".py", ".PY", ".JAVA", ".java",
                                                ".kt", ".KT", ".js", ".JS", 
                                                ".txt", ".TXT", ".h", ".H" };
/**
* A vector of supported output File Types
*/
std::vector<std::string> SupportedOutputTypes = { ".CPP", ".cpp", ".PY", ".py" };

/**
 * Main function that handles provided arguments
 * reads the provided file with the FileReader class
 * and creates a resulting output file using the 
 * FileCreator class
 * @param argc integer for total number of arguments
 * @param argv a character array of arguments
 * @return int
 */
int main(int argc, char *argv[])
{
    std::string fileName; 
    std::string outputFileName;
    FileCreator::OutputTypes outputType;
    //parse arguments
    int errorCode = handleArguments(argc, argv, fileName, outputType, outputFileName);
    // std::cout << "Input File Name: " << fileName << "\n"
    //          << "Output File Name: " << outputFileName << "\n"
    //          << "Output Type: " << outputType << "\n"; 
    // std::cout << "Building File Reader Object \n";
    if(errorCode == 0)
    {
        FileReader f = FileReader(fileName);
        f.read();
        std::vector<std::string> lines = f.getLines();

        FileCreator o = FileCreator(outputFileName, outputType, lines);
        o.write();
    }

    return 0;
}

/**
 * Function that handles user provided arguments
 * Checks to make sure required file name, -o flag 
 * and output file name are set by the user and if not
 * errors are generated. Validates fileName with 
 * validateFileType function and  output fileName
 * using checkForOutputFileName function to make sure
 * they are supported and generates an error if not. 
 * @param argc integer for total number of arguments
 * @param argv a character array of arguments
 * @param fileName string 
 * @param outputTypes ileCreator::OutputTypes Enum Value for output type
 * @param outputFileName string
 * @return int
 */
int handleArguments(int argc, char *argv[], std::string &fileName, FileCreator::OutputTypes &outputType, std::string &outputFileName)
{
    int errorCode = 0; 
    std::vector<std::string> arguments(argv + 1, argv + argc);
    if(argc > 1)
    {
        //first argument is filename
        fileName = argv[1];
        std::cout << "File Name: " << fileName << "\n"; 
        if(validateFileType(fileName))
        {
            std::cout<< "Opening file "  << fileName << "\n"; 
            //handleFile(fileName);
        }
        else
        {
            std::cout << "Error: Invalid File Type (Only ";
            bool first = true; 
            for(std::string f : SupportedFileTypes)
            {
                if(!first){std::cout << ", ";}
                std::cout << f;
                first = false; 
            }
            std::cout << " files are accepted.)";
            errorCode = 1;
        }
        if(argc > 2)
        {
            //checkForOutputType(outputType, errorCode, arguments);
            checkForOutputFileName(outputFileName, outputType, errorCode, arguments);
        }
        else
        {
            std::cout << "Code Generator " << argv[2] << " command requires a -o flag with an expected output type. \n Program will now exit. \n";
            errorCode = 1;
        }
        
    }
    else
    {
        std::cout << "CodeGenerator Command requires <fileName> -o <output file type>\n Program will now exit. \n";
        errorCode = 1;
    }
    return errorCode; 
}

/**
 * Function that checks if a fileName has an extension
 * in the SupportedFileTypes vector and returns true if
 * sp and false if not. 
 * @param fileName string 
 * @return bool
 */
bool validateFileType(std::string &fileName)
{
    std::string fileNameLC = stringToLower(fileName);
    for(std::string f : SupportedFileTypes)
    {
        if(fileNameLC.find(f, fileNameLC.size()-4) != std::string::npos)
        {
            return true;
        }
    }
    return false; 
}

/**
 * Function that checks if an output fileName has an 
 * extension in the SupportedOutputTypes vector and 
 * returns true if sp and false if not. Also sets the
 * outputTypes to the appropriate FileCreator::OutputTypes
 * enum value 
 * @param fileName string 
 * @param outputTypes ileCreator::OutputTypes Enum Value for output type
 * @return bool
 */
bool validateOutputType(std::string &outputFileName, FileCreator::OutputTypes &outputFileType)
{
    std::string outputFileNameLC = stringToLower(outputFileName);
    for(std::string f : SupportedOutputTypes)
    {
        if(outputFileNameLC.find(f, outputFileNameLC.size()-4) != std::string::npos)
        {  
            if(f == ".py")
            {
                outputFileType = FileCreator::PY;
            }
            else if(f == ".cpp")
            {
                outputFileType = FileCreator::CPP;
            }
            return true;
        }
    }
    return false; 
}

/**
 * Function that converts a string to lower case
 * Taken from //http://cplusplus.com/forum/beginner/218745/
 * extension in the SupportedOutputTypes vector and 
 * returns true if sp and false if not. Also sets the
 * outputTypes to the appropriate FileCreator::OutputTypes
 * enum value 
 * @param str string 
 * @return string
 */
std::string stringToLower(std::string str)
{
    for (size_t i=0; i<str.size(); ++i) 
    {
        if (isalpha(str[i])) 
        {
            str[i] = tolower(str[i]);
        }
    }
    return str; 
}

/**
 * Function that checks if a flag exists in a
 * set of vector of provided arguments. Returns 
 * true if so and false if not. 
 * @param flag string 
 * @param arguments vector of strings 
 * @return bool
 */
bool flagExists(std::string flag, std::vector<std::string> arguments)
{
    for(std::string f : arguments)
    {
        if(f == flag)
        {
            return true; 
        }
    }
    return false;
}

/**
 * Function that checks if a flag exists in a
 * vector of provided arguments and returns
 * the argument immediately after it. Returns 
 * "-1" if not found.  
 * @param flag string 
 * @param arguments vector of strings 
 * @return string
 */
std::string getFlagArgument(std::string flag, std::vector<std::string> arguments)
{
    std::string arg; 
    int i = 0;
    for(std::string f : arguments)
    {
        if(f == flag)
        {
            return arguments[i+1];
        }
        i++;
    }
    return "-1";
}

/**
 * Function that checks if -o flag exists
 * and if an output fileName is provided 
 * using the getFlagArgument. Then it 
 * valideates the outputFileType using the
 * validateOutputType function. If an error 
 * is found the error code is set to 1. 
 * @param outputFileName string
 * @param outputFileType ileCreator::OutputTypes Enum Value for output type
 * @param errorCode int 
 * @param arguments vector of strings 
 * @return void
 */
void checkForOutputFileName(std::string &outputFileName, FileCreator::OutputTypes &outputFileType, int &errorCode, std::vector<std::string> &arguments)
{
    if(flagExists("-o", arguments))
    {
        outputFileName = getFlagArgument("-o", arguments);
        //check if parameter provided
        if(outputFileName != "-1")
        {
            if(!validateOutputType(outputFileName, outputFileType))
            {
                std::cout << "Error: Invalid Output Type (Only ";
                bool first = true; 
                for(std::string f : SupportedOutputTypes)
                {
                    if(!first){std::cout << ", ";}
                    std::cout << f;
                    first = false; 
                }
                std::cout << " outputs can be generated.)";
                errorCode = 1; 
            }
        }
        else
        {
            std::cout << "The -o parameter requires an output filename. Program will now exit. \n";
            errorCode = 1; 
        }
    }
    else
    {
        std::cout << "The -o parameter with an output file name is required. Program will now exit. \n";
        errorCode = 1; 
    }
}