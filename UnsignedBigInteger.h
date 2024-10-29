#pragma once

#include<iostream>
class UnsignedBigInteger
{
public:
	template<std::integral T>
	UnsignedBigInteger(const T val);
	UnsignedBigInteger(const UnsignedBigInteger& other);
	UnsignedBigInteger();

	UnsignedBigInteger& operator= (const UnsignedBigInteger& other);
	template<std::integral T>
	UnsignedBigInteger& operator= (const T& other);

	UnsignedBigInteger operator+ (const UnsignedBigInteger& other) const;
	template<std::integral T>
	UnsignedBigInteger operator+ (const T& other) const;

	UnsignedBigInteger operator- (const UnsignedBigInteger& other) const;
	template<std::integral T>
	UnsignedBigInteger operator- (const T& other) const;

	UnsignedBigInteger operator* (const UnsignedBigInteger& other) const;
	template<std::integral T>
	UnsignedBigInteger operator* (const T& other) const;

	UnsignedBigInteger operator/ (const UnsignedBigInteger& other) const;
	template<std::integral T>
	UnsignedBigInteger operator/ (const T& other) const;

	UnsignedBigInteger operator% (const UnsignedBigInteger& other) const;
	template<std::integral T>
	UnsignedBigInteger operator% (const T& other) const;

	bool operator> (const UnsignedBigInteger& other) const;
	bool operator< (const UnsignedBigInteger& other) const;

	bool operator>= (const UnsignedBigInteger& other) const;
	bool operator<= (const UnsignedBigInteger& other) const;

	bool operator== (const UnsignedBigInteger& other) const;

	std::string ToString() const;

private:

	template<std::integral T>
	UnsignedBigInteger(T val, size_t shift);
	UnsignedBigInteger(const UnsignedBigInteger& val, size_t shift);

	void clear();
	const static size_t data_size = 16;
	unsigned char data[data_size]{};
};

#include "UnsignedBigInteger.inl"

