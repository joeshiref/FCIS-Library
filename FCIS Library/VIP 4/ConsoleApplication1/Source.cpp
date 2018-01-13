#include <iostream> // library that contains basic input output functions
#include <string> // library for c++ strings

using namespace std;

int main()
{
	//Username and Password to validate credentials
	const string USERNAME = "user";
	const string PASSWORD = "123456";
	//strings in which user will enter username and password 
	string username, password;

	// Prompting user to input username
	cout << "Enter Username : ";
	cin >> username;

	//Checking if username length is less than 4 characters then display an error message
	if (username.length() < 4)
	{
		cout << "Username length must be atleast 4 characters long.";
	}
	else  //if username length is greater than 3
	{
		//promprting user for password
		cout << "Enter Password : ";
		cin >> password;
		//Checking if password length is less than 6 characters then display an error message
		if (password.length() < 6)
		{
			cout << "Password length must be atleast 6 characters long.";
		}
		else //if password length is greater than 5
		{
			//Checking if user's entered credentials are equal to actual USERNAME and PASSWORD 
			if (username == USERNAME && password == PASSWORD)
			{
				cout << "User credentials are correct!!!" << endl;
			}
			else
			{
				cout << "Invalid login details" << endl;
			}
		}
	}

	return 0;
}