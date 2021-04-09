#include <iostream>
#include <initializer_list>
using namespace std;
template<typename T>
class vector {
	T* data;
	int size;
	int res;
public:
	vector(int n):res(n),size(0),data(new T[n]){
		for (int i = 0; i < res; i++)data[i] = T{};
	}
	vector(const initializer_list<T>& li) {
		res = li.size();
		size = res;
		data = new T[res];
		int i = 0;
		for (auto itr = li.begin(); itr != li.end(); i++, itr++) {
			data[i] = *itr;
		}
	}
	T& operator[](const int& idx) const{
		return data[idx];
	}
	void push_back(T element){
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
	int len() const{
		return size;
	}
	~vector() {
		delete[] data;
	}
};
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& list) {
	for (int i = 0; i < list.len(); i++) {
		os << list[i] << " ";
	}
	os << endl;
	return os;
}

template<typename T>
void sort(T& list) {
	for (int i = 0; i < list.len() - 1; i++) {
		for (int j = i + 1; j < list.len(); j++) {
			if (list[i]>list[j]) {
				list.swap(i, j);
			}
		}
	}
}

template<typename T, typename Comp>
void sort(T& list, const Comp& comp) {
	for (int i = 0; i < list.len()-1; i++) {
		for (int j = i+1; j < list.len(); j++) {
			if (!comp(list[i], list[j])) {
				list.swap(i, j);
			}
		}
	}
}
template<typename T>
struct Des {
	bool operator()(const T& t1, const T& t2) const{
		return t1 > t2;
	}
};
int main() {
	vector<int> list = { 3,1,4,2,5,10,11,0,1 };
	cout << list << endl;
	sort(list);
	cout << list << endl;
	sort(list, Des<int>());
	cout << list << endl;
}