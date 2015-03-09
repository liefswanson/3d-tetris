libs   = -lGLEW -lglfw -lGL -lX11 -lpthread #-lXrandr -lXi
tLibs  = -lgtest
cflags = -Wall -g
std    = -std=c++11
cc     = clang++
app    = 3d-tetris.app

srcs   = TermColor.cpp Main.cpp ShaderBuilder.cpp VAOBuilder.cpp Renderable.cpp Camera.cpp Tile.cpp Board.cpp RangeMap.cpp Settings.cpp Piece.cpp # Grid.cpp Arm.cpp
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

Camera.test: Camera.o Camera_test.o TermColor.o  
	$(cc) $(std) $(tLibs) $(libs) obj/TermColor.o obj/Camera.o test_obj/Camera_test.o \
		-o test_bin/$@
	test_bin/$@

TermColor.test: TermColor.o TermColor_test.o
	$(cc) $(std) $(tLibs) obj/TermColor.o  test_obj/TermColor_test.o -o test_bin/$@
	test_bin/$@

Board.test: Board.o Board_test.o Tile.o TermColor.o VAOBuilder.o ShaderBuilder.o Renderable.o
	$(cc) $(std) $(tLibs) $(libs) \
		obj/TermColor.o obj/Board.o obj/Tile.o \
		obj/VAOBuilder.o obj/ShaderBuilder.o obj/Renderable.o \
		test_obj/Board_test.o \
		-o test_bin/$@
	test_bin/$@

%.test:
	echo -e "\e[0;93m[ WARN ]\e[0m no tests for \e[0;93m $* \e[0m."

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
