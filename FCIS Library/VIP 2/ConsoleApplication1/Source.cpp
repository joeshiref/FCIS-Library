#include <iostream>

using namespace std;

void convert(int x, int arr[])
{
	int *ptr = new int[x];

	for (int i = 0; i < x - 1; i++)
	{
		ptr[i] = arr[i];
	}

	delete[] arr;

	arr = new int[x];

	for (int i = 0; i < x - 1; i++)
	{
		arr[i] = ptr[i];
	}

	delete[] ptr;
}

void main()
{
	int x; cout << "enter x : "; cin >> x; cout << endl;

	int *arr = new int[x];

	for (int i = 0; i < x; i++)
	{
		cout << "arr[" << i << "] : "; cin >> arr[i];
	}

	cout << endl;

	x++;

	convert(x, arr);

	cout << "arr[" << x - 1 << "] : "; cin >> arr[x - 1]; cout << endl;

	delete[] arr;
}