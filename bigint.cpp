#include "bigint.h"

#include <cmath>
#include <string.h>

int max(int a, int b);

bigint::bigint()
{
	this->size = 1;
	this->arr_num = this->to_array(0);
	this->positive = true;
}

bigint::bigint(int n)
{
	this->size = this->get_digits_count(n);
	this->arr_num = this->to_array(n);
	this->positive = n >= 0;
}

bigint::bigint(short *arr_num, int size, bool positive)
{
	this->size = size;
	this->arr_num = arr_num;
	this->positive = positive;
}

bigint::~bigint()
{
}

short *bigint::get_arr_num()
{
	return this->arr_num;
}

short *bigint::to_array(int n)
{
	int size = this->get_digits_count(n);
	short *arr = new short[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = get_digit(n, i + 1);
	}

	return arr;
}

short bigint::get_digit(int n, int pos)
{
	n = std::abs(n);
	return (short)(n / std::pow(10, pos - 1)) % 10;
}

int bigint::get_digits_count(int n)
{
	if (n == 0)
		return 1;

	n = std::abs(n);
	int l = std::log10(n);
	if (l == std::log10(n))
	{
		return l + 1;
	}
	else
	{
		return ((int)std::abs(l)) + 1;
	}
}

bigint bigint::operator*(bigint b)
{
	bool positive = this->is_positive() == b.is_positive();
	int size = this->get_size() + b.get_size() + 1;

	short *arr_res = new short[size];

	short *arr_a = this->get_arr_num();
	short *arr_b = b.get_arr_num();

	for (int i = 0; i < this->get_size(); i++)
	{
		for (int j = 0; j < b.get_size(); j++)
		{
			arr_res[i + j] += arr_a[i] * arr_b[j];
		}
	}

	for (int i = 0; i < size; i++)
	{
		arr_res[i + 1] += arr_res[i] / 10;
		arr_res[i] %= 10;
	}

	while (arr_res[size - 1] == 0)
	{
		size--;
	}

	return bigint(arr_res, size, positive);
}

bigint bigint::operator+(bigint b)
{
	if (this->is_positive() == b.is_positive())
	{
		bool positive = this->is_positive();
		int size = max(this->get_size(), b.get_size()) + 1;
		short *arr_res = new short[size];

		short *arr_a = this->get_arr_num();
		short *arr_b = b.get_arr_num();

		for (int i = 0; i < size - 1; i++)
		{
			if (i < this->get_size() && i < b.get_size())
			{
				arr_res[i] += arr_b[i] + arr_a[i];
			}
			else if (i < this->get_size() && i >= b.get_size())
			{
				arr_res += arr_a[i];
			}
			else if (i >= this->get_size() && i < b.get_size())
			{
				arr_res += arr_b[i];
			}

			arr_res[i + 1] += (short)arr_res[i] >= 10;
			arr_res[i] %= 10;
		}

		while (arr_res[size - 1] == 0)
		{
			size--;
		}

		return bigint(arr_res, size, positive);
	}
	else
	{
		return this->operator-(b);
	}
}

bigint bigint::operator-()
{
	return bigint(this->get_arr_num(), this->get_size(), !this->is_positive());
}

bigint bigint::operator+()
{
	return bigint(this->get_arr_num(), this->get_size(), this->is_positive());
}

bigint bigint::operator-(bigint b)
{
	if (this->is_positive() == b.is_positive())
	{
		return this->operator+(b);
	}
	else
	{
		if (this->operator==(b))
		{
			return bigint(0);
		}

		bool positive = true;

		short *arr_max = this->get_arr_num();
		short *arr_min = b.get_arr_num();

		int max_size = this->get_size();
		int min_size = b.get_size();

		if (this->operator<(b))
		{
			positive = false;

			arr_max = b.get_arr_num();
			arr_min = this->get_arr_num();

			int max_size = b.get_size();
			int min_size = this->get_size();
		}

		int size = max_size + 1;

		short *arr_res = new short[size];

		for (int i = 0; i < size; i++)
		{
			if (i < max_size && i < min_size)
			{
				arr_res[i] += arr_max[i] - arr_min[i];
			} else if(i < max_size && i >= min_size) {
				arr_res[i] += arr_max[i];
			}

			if(arr_res[i] < 0) {
				arr_res[i+1]--;
			}
		}

		while (arr_res[size - 1] == 0)
		{
			size--;
		}

		return bigint(arr_res, size, positive);
	}
}

bool bigint::operator>(bigint b)
{
	if (this->operator==(b))
	{
		return false;
	}

	return !this->operator<(b);
}

bool bigint::operator<(bigint b)
{
	if (this->operator==(b))
	{
		return false;
	}

	if (this->is_positive() && !b.is_positive())
	{

		return true;
	}

	if (!this->is_positive() && b.is_positive())
	{

		return false;
	}

	if (this->get_size() > b.get_size())
	{
		if (this->is_positive())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	if (this->get_size() < b.get_size())
	{
		if (this->is_positive())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	short *arr_a = this->get_arr_num();
	short *arr_b = b.get_arr_num();

	for (int i = 0; i < this->get_size(); i++)
	{
		if (arr_a[i] > arr_b[i])
		{
			if (this->is_positive())
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	return false;
}

bool bigint::operator>(int b)
{
	return this->operator>(bigint(b));
}

bool bigint::operator<(int b)
{
	return this->operator<(bigint(b));
}

bool bigint::operator>=(bigint b)
{
	if (this->operator==(b))
	{
		return true;
	}

	if (this->operator>(b))
	{
		return true;
	}

	return false;
}

bool bigint::operator<=(bigint b)
{
	if (this->operator==(b))
	{
		return true;
	}
	if (this->operator<(b))
	{
		return true;
	}

	return false;
}

bool bigint::operator>=(int b)
{
	return this->operator>=(bigint(b));
}

bool bigint::operator<=(int b)
{
	return this->operator<=(bigint(b));
}

bool bigint::operator==(bigint b)
{
	if (this->is_positive() != b.is_positive())
		return false;

	if (this->get_size() != b.get_size())
		return false;

	short *arr_a = this->get_arr_num();
	short *arr_b = b.get_arr_num();

	for (int i = 0; i < this->get_size(); i++)
	{
		if (arr_b[i] != arr_a[i])
			return false;
	}

	return true;
}

bool bigint::operator==(int b)
{
	return this->operator==(bigint(b));
}

bigint bigint::operator+(int b)
{
	return this->operator+(bigint(b));
}

bigint bigint::operator-(int b)
{
	return this->operator-(bigint(b));
}

bigint bigint::operator*(int b)
{
	return this->operator*(bigint(b));
}

int bigint::get_size()
{
	return this->size;
}

bool bigint::is_positive()
{
	return this->positive;
}

char *bigint::to_string()
{
	char *str = new char[this->size + (int)!this->positive];
	int start_index = !positive;

	if (!positive)
	{
		str[0] = '-';
	}

	for (int j = size - 1; j >= 0; j--, start_index++)
	{
		str[start_index] = (char)(arr_num[j] + 48);
	}

	return str;
}

std::ostream &operator<<(std::ostream &out, const bigint &c)
{
	out << bigint(c).to_string();
	return out;
}

std::istream &operator>>(std::istream &in, bigint &c)
{
	char *num;
	in >> num;

	int length = strlen(num);
	int end = 0;

	c.positive = true;

	if (length > 1)
	{
		if (num[0] == '-')
		{
			c.positive = false;
			end++;
		}
	}

	int size = length - end;

	c.size = size;

	short *arr = new short[size];

	for (int i = length - 1, j = 0; i >= end; i--, j++)
	{
		short digit = ((short)num[i]) - 48;

		if (digit > 10 || digit < 0)
		{
			in.setstate(std::ios_base::failbit);
			return in;
		}

		arr[j] = digit;
	}

	c.arr_num = arr;

	return in;
}

int max(int a, int b)
{
	return a > b ? a : b;
}