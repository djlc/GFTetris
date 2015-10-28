#pragma once

#include <iostream>
#include <fstream>

using namespace std;

template <class T> class Array {

private:

	T* buf;
	const int width, height;

public:

	Array() : width(0), height(0) {
		buf = 0;
	}

	Array(const Array& obj) : width(obj.width), height(obj.height) {
		buf = new T[width*height];
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				buf[y * width + x] = obj.buf[y * width + x];
			}
		}

	}

	Array(int x, int y) : width(x), height(y) {
		buf = 0;
		buf = new T[width*height];
	}

	~Array() {
		if (buf != 0) delete[] buf;
		buf = 0;
	}

	T& operator()(int x, int y) const {
		return buf[y * width + x];
	}

	void fill(T t) {
		for (int i = 0; i < width*height; i++) {
			buf[i] = t;
		}
	}

	void write() {
		for (int i = 0; i < width*height; i++) {
			cout << buf[i];
			if (i % width == 0 && i != 0) cout << endl;
		}
	}

	void load(const T* data) {
		memcpy(buf, data, width * height);
	}

	void save(const char* filename) {
		ofstream ofs(filename);
		for (int i = 0; i < width*height; i++) {
			ofs << buf[i];
		}
	}

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}

};