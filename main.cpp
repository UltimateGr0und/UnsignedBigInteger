#include<iostream>
#include<catch.hpp>
#include "UnsignedBigInteger.h"

int main(int argc, char* argv[]) {
	int result = Catch::Session().run(argc, argv);
	return result;
}

//int main()
//{
//	std::cout << UINT64_MAX<<'\n';
//	UnsignedBigInteger a{ UINT64_MAX};
//	UnsignedBigInteger b{ UINT64_MAX/256 };
//	UnsignedBigInteger c{a*b};
//	c = c / b;
//	std::cout << c.ToString()<<'\n';
//	a = 1;
//	b = UINT64_MAX;
//	c = a % b;
//	std::cout << c.ToString();
//}