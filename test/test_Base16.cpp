#include "Base16.h"

using namespace std;

int main() {
	{
		string teststr{ "²âÊÔBase16Êı¾İ" };
		vector<unsigned char> data(teststr.data(), teststr.data() + teststr.size() + 1);

		auto Base16str = Base16Encode(data);
		cout << "srcdata: " << teststr << endl;
		cout << "Base16 encode: " << Base16str << endl;
		
		cout << "Base16 decode: ";
		auto resdata = Base16Decode(Base16str);
		for (auto c : resdata) {
			cout << c;
		}
	}
}