#include <iostream>

#include <string>

using namespace std;

int main()
{
	int row, col;

	cout << "Enter length of:" << endl << endl;

	cout << "1 - rows: ";

	cin >> row;

	cout << endl;

	cout << "2 - columns: ";

	cin >> col;

	cout << endl;

	int **arr = new int*[row];

	for (int i = 0; i < row; i++)
	{
		arr[i] = new int[col];
	}

	cout << "Enter 2D array:" << endl << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> arr[i][j];
		}
	}

	cout << endl;

	string ans;

	cout << "Would you like to change a row or a column ?" << endl << endl;

	cin >> ans;

	cout << endl;

	int num;

	cout << "Enter number of " << ans << " : ";

	cin >> num;

	cout << endl;

	num--;

	if (ans == "row")
	{
		for (int k = 0; k < col; k++)
		{
			arr[num][k] = 0;
		}
	}

	else if (ans == "column")
	{
		for (int k = 0; k < row; k++)
		{
			arr[k][num] = 0;
		}
	}

	cout << "New array:" << endl << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col - 1; j++)
		{
			cout << arr[i][j] << " ";
		}

		cout << arr[i][col - 1] << endl;
	}

	cout << endl;

	for (int j = 0; j < row; j++)
	{
		delete[] arr[j];
	}

	delete []arr;

	return 0;
}

---------------------------------------------------------------------

#include <iostream>

#include <string>

using namespace std;

int main()
{
	int n;

	string s;

	cin >> s;

	n = stoi(s);

	//n = stod(s); for double

	cout << n << endl;

	return 0;
}

-----------------------------------------------------------------------

#include <fstream>
#include <iostream>
using namespace std;
 
int main ()
{
    
   char data[100];

   // open a file in write mode.
   ofstream outfile;
   outfile.open("afile.dat");

   cout << "Writing to the file" << endl;
   cout << "Enter your name: "; 
   cin.getline(data, 100);

   // write inputted data into the file.
   outfile << data << endl;

   cout << "Enter your age: "; 
   cin >> data;
   cin.ignore();
   
   // again write inputted data into the file.
   outfile << data << endl;

   // close the opened file.
   outfile.close();

   // open a file in read mode.
   ifstream infile; 
   infile.open("afile.dat"); 
 
   cout << "Reading from the file" << endl; 
   infile >> data; 

   // write the data at the screen.
   cout << data << endl;
   
   // again read the data from the file and display it.
   infile >> data; 
   cout << data << endl; 

   // close the opened file.
   infile.close();

   return 0;
}