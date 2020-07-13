#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <iostream>

class bigint
{
private:
	short *arr_num;
	int size;
	bool positive;

	short *to_array(int n);
	int get_digits_count(int n);
	short get_digit(int n, int pos);

protected:
	short *get_arr_num();
	int get_size();

public:
	bigint();
	bigint(int n);
	bigint(short *arr_num, int size, bool positive);

	~bigint();

	bigint operator-();
	bigint operator+();

	bigint operator*(bigint b);
	bigint operator+(bigint b);
	bigint operator-(bigint b);
	bool operator==(bigint b);
	bool operator>(bigint b);
	bool operator<(bigint b);
	bool operator>=(bigint b);
	bool operator<=(bigint b);

	bigint operator*(int b);
	bigint operator+(int b);
	bigint operator-(int b);
	bool operator==(int b);
	bool operator>(int b);
	bool operator<(int b);
	bool operator>=(int b);
	bool operator<=(int b);

	bool is_positive();
	char *to_string();

	friend std::ostream &operator<<(std::ostream &out, const bigint &i);
	friend std::istream &operator>>(std::istream &in, bigint &i);
};

#endif