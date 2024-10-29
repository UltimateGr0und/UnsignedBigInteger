#include<iostream>
#include<limits.h>
#include<catch.hpp>
#include "UnsignedBigInteger.h"

TEST_CASE("constructors") {
	SECTION("is_default_constuctor") {
		REQUIRE_NOTHROW(UnsignedBigInteger());
	}
	SECTION("is_integral_constructor") {
		REQUIRE_NOTHROW(UnsignedBigInteger(1));
		REQUIRE_THROWS(UnsignedBigInteger(-1));
		constexpr int int_max = std::numeric_limits<int>::max();
		REQUIRE_NOTHROW(UnsignedBigInteger(int_max));
		constexpr long long_max = std::numeric_limits<long>::max();
		REQUIRE_NOTHROW(UnsignedBigInteger(long_max));
		constexpr long long long_long_max = std::numeric_limits<long>::max();
		REQUIRE_NOTHROW(UnsignedBigInteger(long_long_max));
	}
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