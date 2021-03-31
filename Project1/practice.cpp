#include <iostream>
#include <string>
using namespace std;

size_t str_size(const string& str) {
	return str.size();
}
size_t str_size(const char* str) {
	return strlen(str);
}
template<typename String, typename... args>
size_t str_size(const String& str, args... arg) {
	return str_size(str) + str_size(arg...);
}

void add_str(string* str) {
	return;
}
template<typename String, typename... args>
void add_str(string* source, const String& str, args... arg) {
	source->append(string(str));
	add_str(source, arg...);
}
template<typename String, typename... args>
string Strcat(const String& str, args... arg) {
	size_t tot_size = str_size(str, arg...);
	string ret;
	ret.reserve(tot_size);

	ret.append(string(str));
	add_str(&ret, arg...);
	return ret;
}




int main() {
	string tmp = "willy";
	string str = Strcat(string("hello")," ","world", " ",tmp, string("!"));
	cout << str << endl;
}