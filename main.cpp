#include <iostream>
#include "bigint.h"

using namespace std;

bigint fact(bigint n);
bigint standart_factorial(bigint n);

int main(int argc, char **argv)
{
	bigint n;

	if (argc > 1)
	{
		n = atoi(argv[1]);
	}
	else
	{
		cin >> n;
	}

	cout << "Standart" << endl;
	cout << standart_factorial(n) << endl;

	cout << "tails" << endl;
	cout << fact(n) << endl;

	return 0;
}

bigint f(bigint n, bigint a)
{
	if (n == 1 || n == 0)
	{
		return a;
	}
	else
	{
		return f(n - 1, a * n);
	}
}

bigint fact(bigint n)
{
	return f(n, 1);
}

bigint standart_factorial(bigint n)
{
	return n == 0 || n == 1 ? 1 : n * standart_factorial(n - 1);
}