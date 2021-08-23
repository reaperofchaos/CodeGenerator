#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
	//Default output file is output.cpp
	std::string fileName = "output.cpp";
	if(argc > 1)
	{
		 //First argument is the filename
		fileName = argv[1];
	};
	std::ofstream out;
	out.open(fileName, std::ios::out);

	//Write Lines found in Input File 
	out << "#include <iostream>" << "\n";
	out << "" << "\n";
	out << "int main(int argc, char *argv[])" << "\n";
	out << "{" << "\n";
	out << "    std::cout << \"Hello World!\\n\";" << "\n";
	out << "    return 0;" << "\n";
	out << "}" << "\n";

	out.close();
	return 0;
}