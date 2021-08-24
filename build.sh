rm -rf build
mkdir build
cp test.cpp build/test.cpp
cp test.py build/test.py
cd build
cmake ../src
cmake --build .
#./CodeGenerator
#./CodeGenerator test.cpp
#./CodeGenerator test.cpp -t cpp
./CodeGenerator test.cpp -o "builder.cpp"
g++ builder.cpp -obuilder
./builder myFile.cpp
g++ myFile.cpp -o output
./output

./CodeGenerator test.py -o "builder.py"
python builder.py myFile.py
python myFile.py