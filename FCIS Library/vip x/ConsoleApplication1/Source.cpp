#include <iostream>

using namespace std;

struct stood { int *ptr; };

void main()
{
	stood str;

	int x; cout << "enter x : "; cin >> x; cout << endl;

	str.ptr = new int[x];

	cout << "enter array : "; for (int i = 0; i < x; i++) { cin >> str.ptr[i]; } cout << endl;

	cout << "output array : "; for (int i = 0; i < x - 1; i++) { cout << str.ptr[i] << " "; } cout << str.ptr[x - 1] << endl << endl;

	delete[] str.ptr;
}