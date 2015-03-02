libs   = -lGLEW -lglfw -lGL -lX11 -lpthread #-lXrandr -lXi
cflags = -Wall -g
lflags =
std    = -std=c++11
cc     = clang++
app    = 3d-tetris.app

srcs    =  
objs    = $(srcs:   .cpp=.o) 


all: $(objs)
	$(cc) $(std) $(libs) $(lflags) $(objs) -o $(app)

test %: $*.o $*_test.cpp
	$(cc) $(std) $(libs) $(lflags) ./obj/$*.o ./test/$*_test.cpp -o ./test_bin/$*.test
	./test_bin/$*.test
