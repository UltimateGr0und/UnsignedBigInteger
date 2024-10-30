#include<iostream>
#include<limits.h>
#include<catch.hpp>
#include "UnsignedBigInteger.h"

TEST_CASE("constructors") {
	SECTION("is default constuctor") {
		REQUIRE_NOTHROW(UnsignedBigInteger());
	}
	SECTION("is integral constructor") {
		REQUIRE_NOTHROW(UnsignedBigInteger(1));
		REQUIRE_THROWS(UnsignedBigInteger(-1));
		constexpr int int_max = std::numeric_limits<int>::max();
		REQUIRE_NOTHROW(UnsignedBigInteger(int_max));
		constexpr long long_max = std::numeric_limits<long>::max();
		REQUIRE_NOTHROW(UnsignedBigInteger(long_max));
		constexpr long long long_long_max = std::numeric_limits<long long>::max();
		REQUIRE_NOTHROW(UnsignedBigInteger(long_long_max));
	}
}

TEST_CASE("is equal operator") {
	UnsignedBigInteger x{0};
	UnsignedBigInteger y{1};
	UnsignedBigInteger z{ std::numeric_limits<int>::max() };
	REQUIRE(x==x);
	REQUIRE_FALSE(x==y);
	REQUIRE_FALSE(x==z);
	REQUIRE(y==y);
	REQUIRE_FALSE(y==x);
	REQUIRE_FALSE(y==z);
	REQUIRE(z==z);
	REQUIRE_FALSE(z==x);
	REQUIRE_FALSE(z==y);

}

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