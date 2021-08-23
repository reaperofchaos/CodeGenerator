#include <iostream>
#include <cstring>
#include <vector>
#include "FileReader.h"
#include "FileCreator.h"

int handleArguments(int argc, char *argv[], std::string &fileName, std::string &outputType, std::string &outputFileName);
bool validateFileType(std::string &fileName);
bool validateOutputType(std::string &outputType);
std::string stringToLower(std::string str);
bool flagExists(std::string flag, std::vector<std::string> arguments);
std::string getFlagArgument(std::string flag, std::vector<std::string> arguments);
void checkForOutputFileName(std::string &outputFileName, int &errorCode, std::vector<std::string> &arguments);
void checkForOutputType(std::string &outputType, int &errorCode,  std::vector<std::string> &arguments);

//Supported File extensions
std::vector<std::string> SupportedFileTypes = { ".html", ".HTML", ".C", ".c", 
                                                ".cpp", ".CPP",".php", ".PHP",
                                                ".py", ".PY", ".JAVA", ".java",
                                                ".kt", ".KT", ".js", ".JS", 
                                                ".txt", ".TXT", ".h", ".H" };
std::vector<std::string> SupportedOutputTypes = { "cpp", "CPP" };

int main(int argc, char *argv[])
{
    std::string fileName; 
    std::string outputType;
    std::string outputFileName;
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

int handleArguments(int argc, char *argv[], std::string &fileName, std::string &outputType, std::string &outputFileName)
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
            checkForOutputType(outputType, errorCode, arguments);
            checkForOutputFileName(outputFileName, errorCode, arguments);
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

bool validateOutputType(std::string &outputType)
{
    std::string outputTypeLC = stringToLower(outputType);
    for(std::string f : SupportedOutputTypes)
    {
        if(f == outputType)
        {
            return true;
        }
    }
    return false; 
}

//http://cplusplus.com/forum/beginner/218745/
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

void checkForOutputType(std::string &outputType, int &errorCode, std::vector<std::string> &arguments)
{
    //check for -t flag
    if(flagExists("-t", arguments))
    {
        outputType = getFlagArgument("-t", arguments);
        //check if parameter provided
        if(outputType != "-1")
        {
            //check if valid
            if(!validateOutputType(outputType))
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
            }
        }
        else
        {
            std::cout << "The -t parameter requires an output type such as cpp. Program will now exit. \n";
            errorCode = 1; 
        }
    }
    else
    {
        std::cout << "The -t parameter with an output file type is required. Program will now exit. \n";
        errorCode = 1; 
    }
}

void checkForOutputFileName(std::string &outputFileName, int &errorCode, std::vector<std::string> &arguments)
{
    if(flagExists("-o", arguments))
    {
        outputFileName = getFlagArgument("-o", arguments);
        //check if parameter provided
        if(outputFileName == "-1")
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