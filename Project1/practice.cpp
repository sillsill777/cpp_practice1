#include <iostream>
#include <initializer_list>
using namespace std;

template<typename T>
class vector {
	T* data;
	int size;
	int res;
public:
	vector(int n):res(n),size(0),data(new T[n]){}
	vector(const initializer_list<T>& li) {
		res = li.size();
		size = res;
		data = new T[res];
		int i = 0;
		for (auto itr = li.begin(); itr != li.end(); i++, itr++) {
			data[i] = *itr;
		}
	}
	T& operator[](const int& idx) {
		return data[idx];
	}
	
	void push_back(T element) {
		if (size >= res) {
			T* tmp = new T[res * 2];
			for (int i = 0; i < size; i++) {
				tmp[i] = data[i];
			}
			res *= 2;
			delete[] data;
			data = tmp;
		}
		data[size] = element;
		size++;
	}
	void swap(int i, int j) {
		T tmp = data[i];
		data[i] = data[j];
		data[j] = tmp;
	}
	int len() {
		return size;
	}
	~vector() {
		delete[] data;
	}
};
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& list) {

}
int main() {

	vector<int> list= {2, 3, 4, 5, 6, 7};
	for (int i = 0; i < list.len(); i++) {
		cout << list[i] << " ";
	}
	list.swap(0, 1);
	for (int i = 0; i < list.len(); i++) {
		cout << list[i] << " ";
	}
}