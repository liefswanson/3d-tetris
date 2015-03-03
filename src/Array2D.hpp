#pragma once

#include "../src/TermColor.hpp"
#include <iostream>

template <class A> class Array2D{

public:
	Array2D (int width, int height) {
		_width  = width;
		_height = height;
		
		x = new A*[_width];
		for(int y = 0; y < _width; y++) {
			x[y] = new A[height] {};
		}
	}
	
	~Array2D() {
		for(int y = 0; y < _width; y++) {
			// std::cout << Term::INFO << "deleting column [" << y << ']'  << std::endl;
			delete[] x[y];
		}
		// std::cout << Term::INFO << "deleting upper array"<< std::endl;
		delete[] x;
	}

	int width() {
		return _width;
	}

	int height() {
		return _height;
	}

	//TODO bounding to the inside of the array

	class Proxy {
	public:
		Proxy(A* y) : y(y) {}

		A& operator[](int i) {
			return y[i];
		}
	private:
        A* y;
	};
	
	Proxy operator[](int i) {
		return Proxy(x[i]);
	}
private:
	A** x;

	int _width;
	int _height;
};
