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
	UnsignedBigInteger z{ std::numeric_limits<long long>::max() };
	REQUIRE(x==x);
	REQUIRE_FALSE(x==y);
	REQUIRE_FALSE(x==z);
	REQUIRE(y==y);
	REQUIRE_FALSE(y==x);
	REQUIRE_FALSE(y==z);
	REQUIRE(z==z);
	REQUIRE_FALSE(z==x);
	REQUIRE_FALSE(z==y);

	REQUIRE(x==0);
	REQUIRE_FALSE(x==1);
	REQUIRE_FALSE(x== std::numeric_limits<long long>::max());
	REQUIRE(y==1);
	REQUIRE_FALSE(y==0);
	REQUIRE_FALSE(y== std::numeric_limits<long long>::max());
	REQUIRE(z==std::numeric_limits<long long>::max());
	REQUIRE_FALSE(z==0);
	REQUIRE_FALSE(z==1);

}

TEST_CASE("equal operator") {
	UnsignedBigInteger x{ 0 };
	UnsignedBigInteger y{ 1 };
	UnsignedBigInteger z{ std::numeric_limits<long long>::max() };
	REQUIRE_NOTHROW(x=z);
	REQUIRE(x == z);
	REQUIRE_NOTHROW(x=y);
	REQUIRE(x == y);
	REQUIRE_NOTHROW(z=y);
	REQUIRE(z == y);
}

TEST_CASE("addition operator") {
	UnsignedBigInteger x{ 0 };
	UnsignedBigInteger y{ 1 };
	UnsignedBigInteger z{ std::numeric_limits<long long>::max() };
	REQUIRE(x+y==y);
	REQUIRE(x+2==2);
	REQUIRE(x + std::numeric_limits<long long>::max() == z);
}

TEST_CASE("subtraction operator") {
	UnsignedBigInteger x{ 0 };
	UnsignedBigInteger y{ 1 };
	UnsignedBigInteger z{ std::numeric_limits<long long>::max() };
	REQUIRE_THROWS(x - y);
	REQUIRE_THROWS(x - z);
	REQUIRE(y-x==1);
	REQUIRE(z-y== std::numeric_limits<long long>::max()-1);
	REQUIRE(z-z== 0);
}

TEST_CASE("multiplication operator") {
	UnsignedBigInteger x{ 0 };
	UnsignedBigInteger y{ 1 };
	UnsignedBigInteger z{ std::numeric_limits<long long>::max() };
	UnsignedBigInteger n{ 51233 };
	REQUIRE(x*y==0);
	REQUIRE(y*x==0);
	REQUIRE(z*y==z);
	REQUIRE(n*3==153699);
}

TEST_CASE("division operator") {

	UnsignedBigInteger zero{ 0 };
	UnsignedBigInteger one{ 1 };
	UnsignedBigInteger two{ 2 };
	UnsignedBigInteger five{ 5 };
	UnsignedBigInteger many{ std::numeric_limits<long long>::max() };

	REQUIRE_THROWS(one / zero);
	REQUIRE(zero / one == zero);
	REQUIRE(one / one == one);
	REQUIRE(many / one == many);
	REQUIRE(many / two == std::numeric_limits<long long>::max() / 2);
	REQUIRE(five / two == two);
}

TEST_CASE("modulo operator") {

	UnsignedBigInteger zero{ 0 };
	UnsignedBigInteger one{ 1 };
	UnsignedBigInteger two{ 2 };
	UnsignedBigInteger five{ 5 };
	UnsignedBigInteger many{ std::numeric_limits<unsigned long long>::max() };

	REQUIRE_THROWS(one % zero);
	REQUIRE(many % one==zero);
	REQUIRE(many % two==one);
	REQUIRE(two % many == two);
	REQUIRE(two % two == zero);
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
//	c = 1;
//	//a = 1;
//	//b = UINT64_MAX;
//	//c = a % b;
//	std::cout << c.ToString();
//}