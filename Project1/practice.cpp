#include <iostream>
using namespace std;

template<int N, int M>
struct GCD {
	static const int res = GCD<M, N% M>::res;
};
template<int N>
struct GCD<N, 0> {
	static const int res = N;
};

template<int N, int D=1>
struct Ratio {
private:
	static const int gcd = GCD<N, D>::res;
public:
	static const int num = N / gcd;
	static const int den = D / gcd;
};



template<typename op1, typename op2>
struct _ratio_add {
	using res = Ratio<op1::num* op2::den + op1::den * op2::num, op1::den* op2::den>;
};
int main() {
	using a = Ratio<3, 2>;
	using b = Ratio<3, 3>;
	using c = _ratio_add<a, b>::res;
	cout << c::num << "/" << c::den << endl;
}