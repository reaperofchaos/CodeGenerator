#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
/***************************************************************************//**
 * FileReader
 *
 *  Class designed to read an input text file escape characters and
 *  store each line in a vector
 *
 *  ******************************************************************************/

class FileReader{

    private:
        std::string filename; /**< Name of input file**/  

        std::ifstream in; /**< Input file handle */  
        std::vector<std::string> lines; /**< A vector of strings holding the lines in the file */

    public:
       /**
       * Default constructor
       */
        FileReader(){}
       /**
       *  Constructor that takes a file name
       * Sets the input file handle to the file name provided
       * @param fileName a string argument.
       */
        FileReader(std::string fileName)
                {
                    this->filename = fileName;
                    this->in.open(filename, std::ios::in);
                }
       /**
       *  Getter
       * Gets the input file name
       * @return string
       */
        std::string getFileName(){return this->filename;}
       /**
       *  Getter
       * Gets the lines vector
       * @return vector of strings
       */
        std::vector<std::string>  getLines(){return this->lines;}

       /**
       * Reads the input file, escapes characters and stores results in lines vector
       * @return void
       */
        void read()
        {
            std::cout << "Reading file, " << this->filename << ". \n"; 
            int i = 0; 
            for(std::string line; std::getline(this->in, line); )
            {
                line = ReplaceAll(line, "\"", "\\\""); //replace all new lines in strings with escaped new lines
                line = ReplaceAll(line, "\\n", "\\\\n"); //replace all new lines in strings with escaped new lines
                line = ReplaceAll(line, "\\r", "\\\\r"); //replace all returns in strings with escaped returns
                line = ReplaceAll(line, "\\t", "\\\\t"); //replace all tabs in strings with escaped tabs
                this->lines.push_back(line);
                i++;
            }
        }
        
       /**
       * Utility function to replace all characters
       * Taken from /https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
       * @param str a string with content to find
       * @param from string to find
       * @param to string to replace
       * @return string
       */
        std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) 
        {
            size_t start_pos = 0;
            while((start_pos = str.find(from, start_pos)) != std::string::npos) 
            {
                str.replace(start_pos, from.length(), to);
                start_pos += to.length(); 
            }
            return str;
        }
    
};