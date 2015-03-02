libs   = -lGLEW -lglfw -lGL -lX11 -lpthread #-lXrandr -lXi
tLibs  = -lgtest
cflags = -Wall -g
std    = -std=c++11
cc     = clang++
app    = 3d-tetris.app

srcs   = termColor.cpp # main.cpp grid.cpp board.cpp piece.cpp tile.cpp renderable.cpp coordMap.cpp VAOBuilder.cpp shaderBuilder.cpp
tests  = $(srcs:.cpp=.test)
objs   = $(srcs:.cpp=.o)

all: $(objs)
	cd obj/
	$(cc) $(std) $(libs) $(objs) -o ../$(app)
	cd ../

run: all
	./$(app)

# run all tests and then output the date the test was complete
test: $(tests)
	date

# link gtest object to it's object and run the test
%.test: %.o %_test.o 
	$(cc) $(std) $(tLibs) obj/$*.o test_obj/$*_test.o -o test_bin/$*.test
	test_bin/$*.test

# make arbitrary gtest object
%_test.o:
	$(cc) $(std) $(cflags) -c test/$*_test.cpp -o test_obj/$*_test.o

# make arbitrary non gtest object
%.o:
	$(cc) $(std) $(cflags) -c src/$*.cpp -o obj/$*.o

clean:
	rm $(app)
	rm obj/*

	rm test_bin/*
	rm test_obj/*
