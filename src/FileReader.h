#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class FileReader{

    private:
        std::string filename;

        std::ifstream in; 
        std::vector<std::string> lines;

    public:
        FileReader(){}

        FileReader(std::string fileName)
                {
                    this->filename = fileName;
                    this->in.open(filename, std::ios::in);
                }

        std::vector<std::string>  getLines(){return this->lines;}
        std::string getFileName(){return this->filename;}

        void read()
        {
            std::cout << "Reading file, " << this->filename << ". \n"; 
            int i = 0; 
            for(std::string line; std::getline(this->in, line); )
            {
                //std::cout << i << ".\t" << line << "\n";
                //escape all quotes
                //std::replace( line.begin(), line.end(), '"', '\''); //replace all quotes with apostrophes
                line = ReplaceAll(line, "\"", "\\\""); //replace all new lines in strings with escaped new lines
                line = ReplaceAll(line, "\\n", "\\\\n"); //replace all new lines in strings with escaped new lines
                line = ReplaceAll(line, "\\r", "\\\\r"); //replace all returns in strings with escaped returns
                line = ReplaceAll(line, "\\t", "\\\\t"); //replace all tabs in strings with escaped tabs

                //std::cout << "Quotes removed \n"; 
                //std::cout << i << ".\t" << line << "\n";

                this->lines.push_back(line);
                i++;
            }
        }

        //https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
        //Utility function to replace all characters
        std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
            size_t start_pos = 0;
            while((start_pos = str.find(from, start_pos)) != std::string::npos) {
                str.replace(start_pos, from.length(), to);
                start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
            }
            return str;
        }
    
};