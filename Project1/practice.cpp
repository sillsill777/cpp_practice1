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
	void resize(const int& size) {
		T* tmp = new T[size];
		if (capacity <= size) {
			for (int i = 0; i < capacity; i++)tmp[i] = data[i];
			for (int i = capacity; i < size; i++)tmp[i] = T{};
		}
		else {
			for (int i = 0; i < size; i++)tmp[i] = data[i];
			length = length < (size - 1) ? length : (size - 1);
		}
		capacity = size;
		delete[] data;
		data = tmp;

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

class Bool;
template<>
class Vector<bool> {
	unsigned int* data;
	int capacity;
	int length;
	int data_loc_int;
	int assigned_int;
	friend Bool;
	
public:
	Vector(int n=1) :capacity(n), length(0), data(new unsigned int[n/32+1]),assigned_int(n/32+1) {
		for (int i = 0; i < assigned_int; i++) data[i] = 0;
		data_loc_int = 0;
	}
	void push_back(bool element) {
		if (data_loc_int >= assigned_int) {
			cout << "New memory allocated current size: " << assigned_int << ", Now allocating : " << 2 * assigned_int << endl;
			unsigned int* tmp = new unsigned int[assigned_int * 2];
			for (int i = 0; i < assigned_int; i++)tmp[i] = data[i];
			for (int i = assigned_int; i < 2 * assigned_int; i++)tmp[i] = 0;
			delete[] data;
			data = tmp;
			assigned_int *= 2;
		}
		if (element) {
			data[data_loc_int] |= (1 << (length % 32));
		}
		length++;
		if (!(length % 32))data_loc_int++;
	}
	void resize(const int& size) {
		int size_int = size / 32 + 1;
		unsigned int* tmp = new unsigned int[size_int];
		for (int i = 0; i < size_int; i++)tmp[i] = data[i];

		if (assigned_int < size_int) {
			for (int i = 0; i < assigned_int; i++)tmp[i] = data[i];
			for (int i = assigned_int; i < size_int; i++)tmp[i] = 0;
		}
		else {
			for (int i = 0; i < size_int-1; i++)tmp[i] = data[i];
			tmp[size_int - 1] = data[size_int - 1] & (0xFFFFFFFF >> (32-size % 32));
			if (length > size) {
				data_loc_int = size_int - 1;
				length = size;
			}
		}
		assigned_int = size_int;
		delete[] data;
		data = tmp;
	}
	int size() {
		return length;
	}
	Bool operator[](const int&);
	~Vector() {
		delete[] data;
	}
};

class Bool {
	int index;
	Vector<bool>* ptr;
public:
	Bool() :index(0),ptr(nullptr) {}
	Bool(int _index, Vector<bool>* _ptr) :index(_index), ptr(_ptr) {}
	bool operator=(const bool& in) {
		if (in) {
			*((ptr->data) + index/32) |= (1 << (index % 32));
		}
		else {
			*((ptr->data) + index/32) &= (~(1 << (index % 32)));
		}
		return in;
	}
	operator bool() {
		return (*((ptr->data) + index / 32) & (1 << (index % 32))) != 0;
	}
};

Bool Vector<bool>::operator[](const int& index) {
	return Bool(index, this);
}

int main() {
	Vector<bool> arr;
	arr.resize(20);
	for (int i = 0; i < 20; i++) {
		if (i % 3)arr[i] = 1;
		else arr[i] = 0;
	}
	for (int i = 0; i < 20; i++)cout << arr[i];
	arr.resize(10);
	cout << endl;
	for (int i = 0; i < 10; i++)cout << arr[i];
	arr.resize(30);
	cout << endl;
	for (int i = 0; i < 30; i++)cout << arr[i];
}