#include <iostream>

#include "Add.cpp"

using namespace std;

int main()
{
	int a, b, sum;

	cout << "Enter a : ";

	cin >> a;

	cout << "Enter b : ";

	cin >> b;

	sum = added(a, b);

	cout << "Sum is " << sum << endl << endl;

	return 0;
}