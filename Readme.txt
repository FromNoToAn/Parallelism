FL - flag to change program to 'float' or 'double' version.
if FL == 1:
	then change to 'double'
else (without FL, FL == another value, but FL == 0 mostly correct):
	then change to 'float'


let x - value for FL, then in current branch:

|cmake instructions|
mkdir result
cd result
cmake ../CMakeLists.txt -D FL=x
cmake --build ../result
Debug\CMake_Parallelism_Dz_1.exe

|make instructions|
make FL=x
./result

| RESULT |
float: 0.291951
double: 4.89582e-11

