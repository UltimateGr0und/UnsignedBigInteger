#pragma once

#include "UnsignedBigInteger.h"

template<std::integral T>
UnsignedBigInteger::UnsignedBigInteger(const T val)
{
	if (val < 0) { throw std::runtime_error("value must be greater than zero"); }
	unsigned const char* val_pt = reinterpret_cast<unsigned const char*>(&val);
	sizeof(T) > this->data_size ? throw std::overflow_error("val must be smaller than data_size") : NULL;
	for (size_t i = 0; i < sizeof(T); i++)
	{
		this->data[i] = val_pt[i];
	}
}

template<std::integral T>
UnsignedBigInteger::UnsignedBigInteger(T val, size_t shift)
{
	unsigned char* val_pt = reinterpret_cast<unsigned char*>(&val);
	sizeof(T) > this->data_size ? throw std::overflow_error("val must be smaller than data_size") : NULL;
	//sizeof(T)+shift > this->data_size ? throw std::overflow_error("buffer overflow") : NULL;
	if (sizeof(T) + shift > this->data_size)
	{
		for (size_t i = this->data_size - shift; i < sizeof(T); i++)
		{
			val_pt[i] != 0 ? throw std::overflow_error("buffer overflow") : NULL;
		}
	}
	for (size_t i = 0; i < sizeof(T); i++)
	{
		this->data[i + shift] = val_pt[i];
	}
}

template<std::integral T>
UnsignedBigInteger& UnsignedBigInteger::operator=(const T& other) {
	this->clear();
	const unsigned char* other_pt = reinterpret_cast<const unsigned char*>(&other);
	sizeof(T) > this->data_size ? throw std::overflow_error("val must be smaller than data_size") : NULL;
	for (size_t i = 0; i < sizeof(T); i++)
	{
		this->data[i] = other_pt[i];
	}
	return *this;
}

template<std::integral T>
UnsignedBigInteger UnsignedBigInteger::operator+ (const T& other) const {
	UnsignedBigInteger value{ other };
	return value + *this;
}

template<std::integral T>
UnsignedBigInteger UnsignedBigInteger::operator- (const T& other) const {
	UnsignedBigInteger value{ other };
	return *this - value;
}

template<std::integral T>
UnsignedBigInteger UnsignedBigInteger::operator*(const T& other) const {
	UnsignedBigInteger val{ other };
	return (*this) * val;
}

template<std::integral T>
UnsignedBigInteger UnsignedBigInteger::operator/(const T& other) const {
	return *this / UnsignedBigInteger(other);
}

template<std::integral T>
UnsignedBigInteger UnsignedBigInteger::operator%(const T& other) const {
	return *this % UnsignedBigInteger(other);
}
