::: run.bat <filename>

g++ -O0 -w -g3 -Wall -c -fmessage-length=0 -o object.o %1 
g++ -o run.exe object.o -lglu32 -lopengl32 -lfreeglut
del object.o
run.exe
del run.exe