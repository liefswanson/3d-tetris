libs   = -lGLEW -lglfw -lGL -lX11 -lpthread #-lXrandr -lXi
t_libs = -gtest
cflags = -Wall -g
std    = -std=c++11
cc     = clang++
app    = 3d-tetris.app

srcs   = termColor.cpp # main.cpp grid.cpp board.cpp piece.cpp tile.cpp renderable.cpp coordMap.cpp VAOBuilder.cpp shaderBuilder.cpp
objs   = $(srcs: .cpp=.o) 

all: $(objs)
	cd obj/
	$(cc) $(std) $(libs) $(lflags) $(objs) -o ../$(app)
	cd ../

run: all
	./$(app)

test: $(srcs: .cpp=.test) 

array2d.test:
	$(cc) $(std) $(t_libs) ./test/array2d_test.cpp -o ./test_bin/array2d.test
	test_bin/array2d.test

%.test: obj/$*.o	 src/$*_test.cpp
	$(cc) $(std) $(t_libs) ./obj/$*.o ./test/$*_test.cpp -o ./test_bin/$*.test
	test_bin/$*.test

clean:
	rm obj/*
	rm test_bin/*
	rm $(app)
