# ./run.sh <filename>

g++ -O0 -w -g3 -Wall -c -fmessage-length=0 -o object.o $1 
g++ -o run.out object.o -lglu32 -lopengl32 -lfreeglut
rm object.o
./run.out
rm run.out