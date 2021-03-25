#include <iostream>

using namespace std;
template <typename T>
class Vector {
	T* data;
	int length;
	int capacity;
public:
	Vector(int n = 1) :length(0), capacity(n), data(new T[n]) {
		for (int i = 0; i < capacity; i++)data[i] = T{};
	}

	void push_back(T element) {
		if (length >= capacity) {
			T* tmp = new T[2 * capacity];
			for (int i = 0; i < length; i++)tmp[i] = data[i];
			for (int i = length; i < 2 * capacity; i++)tmp[i] = T{};
			delete[] data;
			data = tmp;
			capacity *= 2;
		}
		data[length] = element;
		length++;
	}
	T& operator[](const int& index) {
		//if (index >= capacity)return NULL;
		return data[index];
	}
	T remove(int index) {
		if (index >= capacity)return NULL;
		T ret = data[index];
		for (int i = index + 1; i < length; i++) {
			data[i - 1] = data[i];
		}
		return ret;
	}
	int size() {
		return length;
	}
	int capa() {
		return capacity;
	}
	~Vector() {
		delete[] data;
	}
};
template<>
class Vector<bool> {
	unsigned int* data;
	int capacity;
	int length;
	int data_loc_int;
	int assigned_int;
public:
	Vector(int n=1) :capacity(n), length(0), data(new unsigned int[n/32+1]),assigned_int(n/32+1) {
		for (int i = 0; i < assigned_int; i++) data[i] = 0;
		data_loc_int = 0;
	}
	void push_back(bool element) {
		if (data_loc_int >= assigned_int) {
			unsigned int* tmp = new unsigned int[assigned_int * 2];
			for (int i = 0; i < assigned_int; i++)tmp[i] = data[i];
			for (int i = assigned_int; i < 2 * assigned_int; i++)tmp[i] = 0;
			delete[] data;
			data = tmp;
			assigned_int *= 2;
		}
		if (element) {
			data[data_loc_int] |= (1 >> (length % 32));
		}
		length++;
		if (!(length % 32))data_loc_int++;
	}
	bool& operator[](const int& index) {
		int tmp = data[index / 32] & (1 >> (index % 32));
	}
};


int main() {
	
}