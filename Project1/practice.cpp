#include <iostream>
using namespace std;

template<int N>
struct INT {
	static const int data = N;
};
using one = INT<1>;
using two = INT<2>;
using three = INT<3>;

template<typename N, typename M>
struct add {
	using result = INT<N::data + M::data>;
};

template<typename N, typename M>
struct division {
	using result = INT<N::data / M::data>;
};

template<typename N, typename M>
struct divide {
	static const bool result = (N::data % M::data == 0) || divide<N, typename add<M, one>::result>::result;
};

template<typename N>
struct divide<N, typename division<N, two>::result> {
	static const bool result = (N::data % (N::data / 2)) == 0;
};

template<typename N>
struct is_prime {
	static const bool result = !(divide<N, two>::result);
};

template<>
struct is_prime<two> {
	static const bool result = true;
};
template<>
struct is_prime<three> {
	static const bool result = true;
};

int main() {
	is_prime<INT<61>>::result;

}