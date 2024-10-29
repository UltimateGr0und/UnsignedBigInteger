#include "UnsignedBigInteger.h"


UnsignedBigInteger::UnsignedBigInteger(const UnsignedBigInteger& val, size_t shift)
{
	/*unsigned char* val_pt = reinterpret_cast<unsigned char*>(&val);
	UnsignedBigInteger::data_size > this->data_size ? throw std::overflow_error("val must be smaller than data_size") : NULL;*/
	//sizeof(T)+shift > this->data_size ? throw std::overflow_error("buffer overflow") : NULL;
	if (UnsignedBigInteger::data_size + shift > this->data_size)
	{
		for (size_t i = this->data_size - shift; i < UnsignedBigInteger::data_size; i++)
		{
			val.data[i] != 0 ? throw std::overflow_error("buffer overflow") : NULL;
		}
	}
	for (size_t i = 0; i < UnsignedBigInteger::data_size - shift; i++)
	{
		this->data[i + shift] = val.data[i];
	}
}

UnsignedBigInteger::UnsignedBigInteger(const UnsignedBigInteger& other) {
	for (size_t i = 0; i < UnsignedBigInteger::data_size; i++)
	{
		this->data[i] = other.data[i];
	}
}

UnsignedBigInteger::UnsignedBigInteger() {
	
}

UnsignedBigInteger& UnsignedBigInteger::operator=(const UnsignedBigInteger& other) {
	for (size_t i = 0; i < this->data_size; i++)
	{
		this->data[i] = other.data[i];
	}
	return *this;
}

UnsignedBigInteger UnsignedBigInteger::operator+(const UnsignedBigInteger& other) const {
	UnsignedBigInteger result{};
	unsigned char buffer = 0;
	for (size_t i = 0; i < UnsignedBigInteger::data_size; i++)
	{
		int sum = other.data[i] + this->data[i] + buffer;
		if (sum < 256)
		{
			result.data[i] = sum;
			buffer = 0;
		}
		else {
			buffer = 1;
			result.data[i] = sum - 256;
		}
		if (i == UnsignedBigInteger::data_size - 1 && buffer > 0) {
			throw std::overflow_error("buffer overflow");
		}
	}
	return result;
}

UnsignedBigInteger UnsignedBigInteger::operator-(const UnsignedBigInteger& other) const {
	UnsignedBigInteger result{};
	unsigned char buffer = 0;
	for (size_t i = 0; i < UnsignedBigInteger::data_size; i++)
	{
		int sum = this->data[i] - other.data[i] - buffer;
		if (sum >= 0)
		{
			result.data[i] = sum;
			buffer = 0;
		}
		else {
			buffer = 1;
			result.data[i] = sum + 256;
		}
		if (i == UnsignedBigInteger::data_size - 1 && buffer != 0) {
			throw std::overflow_error("buffer overflow");
		}
	}
	return result;
}

UnsignedBigInteger UnsignedBigInteger::operator*(const UnsignedBigInteger& other) const {
	UnsignedBigInteger result{};
	unsigned char buffer = 0;
	for (size_t i = 0; i < UnsignedBigInteger::data_size; i++)
	{
		for (size_t j = 0; j < UnsignedBigInteger::data_size; j++)
		{
			unsigned short mltp = this->data[j] * other.data[i] + buffer;

			if (mltp < 256) {
				result = result + UnsignedBigInteger(mltp, i + j);
				buffer = 0;
			}
			else {
				result = result + UnsignedBigInteger(mltp % 256, i + j);
				buffer = mltp / 256;
			}
		}
	}
	return result;
}

UnsignedBigInteger UnsignedBigInteger::operator/(const UnsignedBigInteger& other) const {
	UnsignedBigInteger numerator{ *this };
	UnsignedBigInteger denominator{ other };
	UnsignedBigInteger result{};
	size_t den_size = 0;
	size_t num_size = 0;

	for (size_t i = UnsignedBigInteger::data_size - 1; i >= 0; i--)
	{
		if (denominator.data[i] == 0) { continue; }
		den_size = i + 1;
		break;
	}
	if (den_size == 0) { throw std::runtime_error("diveded by zero"); }

	do
	{
		for (size_t i = UnsignedBigInteger::data_size - 1; i >= 0; i--)
		{
			if (numerator.data[i] == 0) { continue; }
			num_size = i + 1;
			break;
		}

		if (num_size == 0 || numerator < denominator) { break; }

		unsigned short num_buff = 0;
		unsigned short den_buff = 0;

		if (numerator.data[num_size - 1] >= denominator.data[den_size - 1]) {
			num_buff = numerator.data[num_size - 1];
			den_buff = denominator.data[den_size - 1];
		}
		else {
			if (num_size > 1)
				num_buff = numerator.data[num_size - 1] * 256 + numerator.data[num_size - 2];
			else
				break;
			den_buff = denominator.data[den_size - 1];
			num_size--;
		}

		unsigned char mltp = num_buff / den_buff;
		size_t shift = num_size >= den_size ? num_size - den_size : 0;
		UnsignedBigInteger raw_diff{ denominator * mltp };
		UnsignedBigInteger diff{ raw_diff, shift };

		while (diff > numerator)
		{
			if (mltp>1)
			{
				mltp--;
				raw_diff = denominator * mltp;
				diff = UnsignedBigInteger{ raw_diff, shift };
			}
			else {
				mltp = 255;
				shift--;
				raw_diff = denominator * mltp;
				diff = UnsignedBigInteger{ raw_diff, shift };
			}
		}
		numerator = numerator - diff;

		result = result + UnsignedBigInteger{ mltp, shift };
	} while (num_size >= den_size);

	return result;
}

UnsignedBigInteger UnsignedBigInteger::operator%(const UnsignedBigInteger& other) const {
	UnsignedBigInteger numerator{ *this };
	UnsignedBigInteger denominator{ other };
	size_t den_size{ 0 };
	size_t num_size{ 0 };

	for (size_t i = UnsignedBigInteger::data_size - 1; i >= 0; i--)
	{
		if (denominator.data[i] == 0) { continue; }
		den_size = i + 1;
		break;
	}
	if (den_size == 0) { throw std::runtime_error("diveded by zero"); }

	do
	{
		num_size = 0;

		unsigned char temp = numerator.data[0];

		for (size_t i = UnsignedBigInteger::data_size - 1; i > 0; i--)
		{
			if (numerator.data[i] == 0) { continue; }
			num_size = i + 1;
			break;
		}

		if (num_size == 0 || numerator < denominator) { break; }

		unsigned short num_buff = 0;
		unsigned short den_buff = 0;

		if (numerator.data[num_size - 1] >= denominator.data[den_size - 1]) {
			num_buff = numerator.data[num_size - 1];
			den_buff = denominator.data[den_size - 1];
		}
		else {
			if (num_size > 1)
				num_buff = numerator.data[num_size - 1] * 256 + numerator.data[num_size - 2];
			else
				break;
			den_buff = denominator.data[den_size - 1];
			num_size--;
		}

		unsigned char mltp = num_buff / den_buff;
		size_t shift = num_size >= den_size ? num_size - den_size : 0;
		UnsignedBigInteger raw_diff{ denominator * mltp };
		UnsignedBigInteger diff{ raw_diff, shift };

		while (diff > numerator)
		{
			if (mltp > 1)
			{
				mltp--;
				raw_diff = denominator * mltp;
				diff = UnsignedBigInteger{ raw_diff, shift };
			}
			else {
				mltp = 255;
				shift--;
				raw_diff = denominator * mltp;
				diff = UnsignedBigInteger{ raw_diff, shift };
			}
		}
		numerator = numerator - diff;

	} while (num_size >= den_size);

	return numerator;
}

bool UnsignedBigInteger::operator==(const UnsignedBigInteger& other) const {
	for (size_t i = UnsignedBigInteger::data_size - 1; i > 0; i--)
	{
		if (this->data[i] != other.data[i]) {
			return false;
		}
	}return true;
}

bool UnsignedBigInteger::operator<(const UnsignedBigInteger& other) const {
	for (size_t i = UnsignedBigInteger::data_size - 1; i > 0; i--)
	{
		if (this->data[i] < other.data[i]) {
			return true;
		}
		else if (this->data[i] > other.data[i]) {
			return false;
		}
	}
	return false;
}

bool UnsignedBigInteger::operator>(const UnsignedBigInteger& other) const {
	for (size_t i = UnsignedBigInteger::data_size - 1; i > 0; i--)
	{
		if (this->data[i] > other.data[i]) {
			return true;
		}
		else if (this->data[i] < other.data[i]) {
			return false;
		}
	}
	return false;
}

bool UnsignedBigInteger::operator>=(const UnsignedBigInteger& other) const {
	return *this > other || *this == other;
}

bool UnsignedBigInteger::operator<=(const UnsignedBigInteger& other) const {
	return *this < other || *this == other;
}

void UnsignedBigInteger::clear() {
	for (auto c : this->data)
	{
		c = 0;
	}
}

std::string UnsignedBigInteger::ToString() const {
	using std::string;
	string res{};
	UnsignedBigInteger value{ *this };
	UnsignedBigInteger mltp{ 10 };
	UnsignedBigInteger modulo= value % mltp;
	while (modulo != value)
	{
		res = "0123456789"[(modulo / (mltp / 10)).data[0]]+res;
		mltp = mltp * 10;
		modulo = value % mltp;
	}
	res = "0123456789"[(modulo / (mltp / 10)).data[0]] + res;
	
	return res;
}