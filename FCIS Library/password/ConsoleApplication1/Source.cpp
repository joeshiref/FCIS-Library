#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

int counter = 0, test = 0;

void show()
{
	if (test == 1)
	{
		for (int i = 1; i <= counter; i++)
		{
			cout << "*";
		}
	}

	test = 0;
}

void main()
{
	string password;

	while (true)
	{
		string temp; 

		temp = _getch();

		password.append(temp, 0, 1);

		if (temp == "\r") { break; }

		else if (temp == "\b") 
		{ 
			cout << "\b";

			counter--;

			test = 1;

			if (system("CLS"))
			{
				system("clear");
			}
		}

		else 
		{ 
			cout << "*"; 

			counter++;
		}

		show();
	}

	cout << endl;

	cout << "password : " << password << endl;
}

//do not forgot to termonate the charactcer you press baclspace on