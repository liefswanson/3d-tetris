libs   = -lGLEW -lglfw -lGL -lX11 -lpthread #-lXrandr -lXi
tLibs  = -lgtest
cflags = -Wall -g
std    = -std=c++11
cc     = clang++
app    = 3d-tetris.app

srcs   = TermColor.cpp Main.cpp ShaderBuilder.cpp VAOBuilder.cpp Renderable.cpp Camera.cpp Tile.cpp # grid.cpp board.cpp piece.cpp tile.cpp
tests  = $(srcs:.cpp=.test) Array2D.test
objs   = $(srcs:.cpp=.o)

all: $(objs)
	cd obj/; $(cc) $(std) $(libs) $(objs) -o ../bin/$(app); cd ../

run: all
	bin/$(app)

# run all tests and then output the date the test was complete
test: $(tests)
	date

Array2D.test: Array2D_test.o TermColor.o
	$(cc) $(std) $(tLibs) obj/TermColor.o test_obj/Array2D_test.o -o test_bin/$@
	test_bin/$@

# link gtest object to it's object(s) to test and run that test
%.test: %.o %_test.o 
	$(cc) $(std) $(tLibs) obj/$*.o test_obj/$*_test.o -o test_bin/$@
	test_bin/$@

# make arbitrary gtest object
%_test.o:
	$(cc) $(std) $(cflags) -c test/$*_test.cpp -o test_obj/$@

# make arbitrary non-gtest object
%.o:
	$(cc) $(std) $(cflags) -c src/$*.cpp -o obj/$@

clean:
	rm -f bin/*
	rm -f obj/*

	rm -f test_bin/*
	rm -f test_obj/*
