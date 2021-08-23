rm -rf build
mkdir build
cp test.cpp build/test.cpp
cd build
cmake ../src
cmake --build .
touch test.cpp
./CodeGenerator
./CodeGenerator test.cpp
./CodeGenerator test.cpp -t cpp
./CodeGenerator test.cpp -t cpp -o "builder.cpp"
g++ builder.cpp -obuilder
./builder myFile.cpp
g++ myFile.cpp -o output
./output
