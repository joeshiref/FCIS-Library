//library & global variables : ----------------------------------------------------------------------------------------

#include <fstream>

#include <iostream>

#include <string>

#include <algorithm>

#include <conio.h>

#include <time.h>

#include <windows.h>

#include <stdexcept>

using namespace std;

#define sizemax 10

int bookNum = 0; //number of books in library

int deleteNum = 0; //number of deleted books

int brwdNum = 0; //number of borrowed books

int saleNum = 0; //number of sales

int borrowNum = 0; //number of borrowers

string seppstr; //separator for data in files

string result; //the return of password

			   //---------------------------------------------------------------------------------------------------------------------


			   //book data : ---------------------------------------------------------------------------------------------------------

struct pub
{
	string name, address; //publisher sub-data
};

struct athr
{
	string name, nationality; //author sub-data
};

struct book
{
	string category; //category section

	string ISBN, title, edition, datePub, rating; //book section

	string status, buyBrr, price, amountstr; int amountint; //status section

	pub publisher; //publisher section "see (pub)"

	athr author[5]; int numAth; //author section "see (athr)"
};

//---------------------------------------------------------------------------------------------------------------------


//mini-book data : ----------------------------------------------------------------------------------------------------

struct minbook
{
	string ISBN; //ID section

	int num; //index section
};

//---------------------------------------------------------------------------------------------------------------------


//sales data : --------------------------------------------------------------------------------------------------------

struct sales
{
	string ISBN, title, price, numstr; int numint; //book section

	string ID, name; //customer section

	string saleMethod, date, trNumstr; long long trNumint; //sales section
};

//---------------------------------------------------------------------------------------------------------------------


//borrow data : -------------------------------------------------------------------------------------------------------

struct brwd
{
	string isbn, Title, Numstr; int Numint; //book section

	string id, Name; //customer section

	string Period, Date, TrNumstr; int TrNumint; //file section
};

//---------------------------------------------------------------------------------------------------------------------


//all functions uses : ------------------------------------------------------------------------------------------------

void read(book arrbook[], book arrdlt[], sales arrsal[], brwd arrbrr[], book arrbrwd[]); //read all data from all files

void balances(); //read all balances of all arrbookays

int lines_count(string fileName); //count number of books in file

void read_library(book arrbook[]); //read books' data after opening program

void read_out(brwd arrbrr[]); //read borrow transactions data after opening program

void read_deleted(book arrdlt[]); //read deleted books' data after opening program

void read_sales(sales arrsal[]); //read sales transactions data after opening program

void separating_line(); //separate each action from following

int customer_or_employee(); //define if user is customer or employee

int password(); //check if password is right no

void customer_list(); //display customer options list

void employee_list(); //display employee options list

void customer(book arrbook[]); //access all customer functions

void employee(book arrbook[], book arrdlt[], sales arrsal[], brwd arrbrr[], book arrbrwd[]); //access all employee functions

void mini_outlook(book out[], int i); //display ISBN & name of one book

void outlook(book arrbook[], int i); //display details of ONE book

void show_all(book arrbook[]); //display details of all books

void buy_borrow_both(book arrbook[]); //display details of books by type

void borrow_book(book arrbook[], brwd arrbrr[], book arrbrwd[]); //borrow a book

void borrow_transaction(book arrbook[], brwd arrbrr[], book arrbrwd[], int i); //input borrower data

void buy_book(book arrbook[], book arrdlt[], sales arrsal[]); //buy a book

void buy_transaction(book arrbook[], book arrdlt[], sales arrsal[], int i); //input transaction data

void search(book arrbook[], int look); //search for a book

void add_choice(book arrbook[], book arrdlt[]); //choose way of addation

void manual_add(book arrbook[]); //add new books

void add_from_delete(book arrbook[], book arrdlt[]); //add book from delete file

void increase_amount(book arrbook[]); //change amount of book in library

void delete_book(book arrbook[], book arrdlt[], string remove); //delete a book

void save_delete(book arrbook[], book arrdlt[], int i); //save data of deleted book

void write(book arrbook[], book arrdlt[], sales arrsal[], brwd arrbrr[], book arrbrwd[]); //write all data into all file

void write_library(book arrbook[]); //save books' data before closing program

string getpassword(const string& prompt = "Enter password: "); //the function which gets the password from the user

void write_out(brwd arrbrr[]); //save borrowers' data before closing program

void write_deleted(book arrdlt[]); //save deleted books' data before closing program

void write_sales(sales arrsal[]); //save sales' data before closing program

void autosave(book arrbook[], book arrdlt[], sales arrsal[], brwd arrbrr[], book arrbrwd[]); //auto save data while program is running

void display_sales_transaction(sales arrsal[]); //displays the sales transaction

int mean_title(book arrbook[], int counter, string srch); //search for the closest title which the user enters

int mean_author(book arrbook[], int counter, string srch); //search for the closest author's name which the user enters

void save_borrowed(book arrbook[], book arrbrwd[], int i); //save borrowed book data

void read_borrowed(book arrbrwd[]); //read data of borrowed books

void write_borrowed(book arrbrwd[]); ////save borrowed books'S data

int clear(); //clear console

			 //---------------------------------------------------------------------------------------------------------------------


			 //functions scope : ---------------------------------------------------------------------------------------------------

int main()
{


	balances();

	book arrbook[10]; //books in library array

	book arrdlt[10]; //deleted books array

	book arrbrwd[10]; //borrowed books array

	sales arrsal[10]; //sales transactions array

	brwd arrbrr[10]; //borrow transactions array

	read(arrbook, arrdlt, arrsal, arrbrr, arrbrwd);

	int opt;

	opt = customer_or_employee();

	if (opt == 1) //customer
	{
		customer(arrbook);
	}

	else if (opt == 2) //employee
	{
		employee(arrbook, arrdlt, arrsal, arrbrr, arrbrwd);
	}

	else //return 0
	{
		cout << "TIME UP" << endl << endl;
	}

	write(arrbook, arrdlt, arrsal, arrbrr, arrbrwd);


	return 0;
}

void read(book arrbook[], book arrdlt[], sales arrsal[], brwd arrbrr[], book arrbrwd[])
{
	read_library(arrbook);

	read_out(arrbrr);

	read_deleted(arrdlt);

	read_sales(arrsal);

	read_borrowed(arrbrwd);
}

void balances()
{
	bookNum = lines_count("Books_In_Library.txt");

	borrowNum = lines_count("Borrowers_Transactions.txt");

	deleteNum = lines_count("Deleted_Books.txt");

	saleNum = lines_count("Sales_Transactions.txt");

	brwdNum = lines_count("Borrowed_Books.txt");
}

int lines_count(string fileName)
{
	int counter = 0;

	string lines;

	ifstream myfile(fileName);

	while (getline(myfile, lines))
	{
		if (lines == "---------------")
		{
			counter++;
		}
	}

	myfile.close();

	return counter;
}

void read_library(book arrbook[])
{
	ifstream myfile("Books_In_Library.txt");

	if (myfile.is_open())
	{
		for (int i = 0; i < bookNum; i++)
		{
			getline(myfile, arrbook[i].category);

			getline(myfile, arrbook[i].ISBN);

			getline(myfile, arrbook[i].title);

			getline(myfile, arrbook[i].edition);

			getline(myfile, arrbook[i].datePub);

			getline(myfile, arrbook[i].rating);

			getline(myfile, arrbook[i].status);

			getline(myfile, arrbook[i].amountstr);

			arrbook[i].amountint = stoi(arrbook[i].amountstr);

			getline(myfile, arrbook[i].buyBrr);

			getline(myfile, arrbook[i].price);

			getline(myfile, arrbook[i].publisher.name);

			getline(myfile, arrbook[i].publisher.address);

			myfile >> arrbook[i].numAth;

			myfile.ignore();

			for (int k = 0; k < arrbook[i].numAth; k++)
			{
				getline(myfile, arrbook[i].author[k].name);

				getline(myfile, arrbook[i].author[k].nationality);
			}

			getline(myfile, seppstr);
		}
	}

	myfile.close();
}

void read_out(brwd arrbrr[])
{
	ifstream myfile("Borrowers_Transactions.txt");

	if (myfile.is_open())
	{
		for (int i = 0; i < borrowNum; i++)
		{
			getline(myfile, arrbrr[i].isbn);

			getline(myfile, arrbrr[i].Title);

			getline(myfile, arrbrr[i].Numstr);

			arrbrr[i].Numint = stoi(arrbrr[i].Numstr);

			getline(myfile, arrbrr[i].id);

			getline(myfile, arrbrr[i].Name);

			getline(myfile, arrbrr[i].TrNumstr);

			arrbrr[i].TrNumint = stoi(arrbrr[i].TrNumstr);

			getline(myfile, arrbrr[i].Date);

			getline(myfile, arrbrr[i].Period);

			getline(myfile, seppstr);
		}
	}

	myfile.close();
}

void read_deleted(book arrdlt[])
{
	ifstream myfile("Deleted_Books.txt");

	if (myfile.is_open())
	{
		for (int i = 0; i < deleteNum; i++)
		{
			getline(myfile, arrdlt[i].category);

			getline(myfile, arrdlt[i].ISBN);

			getline(myfile, arrdlt[i].title);

			getline(myfile, arrdlt[i].edition);

			getline(myfile, arrdlt[i].datePub);

			getline(myfile, arrdlt[i].rating);

			getline(myfile, arrdlt[i].status);

			getline(myfile, arrdlt[i].amountstr);

			arrdlt[i].amountint = stoi(arrdlt[i].amountstr);

			getline(myfile, arrdlt[i].buyBrr);

			getline(myfile, arrdlt[i].price);

			getline(myfile, arrdlt[i].publisher.name);

			getline(myfile, arrdlt[i].publisher.address);

			myfile >> arrdlt[i].numAth;

			myfile.ignore();

			for (int k = 0; k < arrdlt[i].numAth; k++)
			{
				getline(myfile, arrdlt[i].author[k].name);

				getline(myfile, arrdlt[i].author[k].nationality);
			}

			getline(myfile, seppstr);
		}
	}

	myfile.close();
}

void read_sales(sales arrsal[])
{
	ifstream myfile("Sales_Transactions.txt");

	if (myfile.is_open())
	{
		for (int i = 0; i < saleNum; i++)
		{
			getline(myfile, arrsal[i].ISBN);

			getline(myfile, arrsal[i].title);

			getline(myfile, arrsal[i].price);

			getline(myfile, arrsal[i].numstr);

			arrsal[i].numint = stoi(arrsal[i].numstr);

			getline(myfile, arrsal[i].ID);

			getline(myfile, arrsal[i].name);

			getline(myfile, arrsal[i].trNumstr);

			arrsal[i].trNumint = stoi(arrsal[i].trNumstr);

			getline(myfile, arrsal[i].saleMethod);

			getline(myfile, arrsal[i].date);

			getline(myfile, seppstr);
		}
	}

	myfile.close();
}

void separating_line()
{
	cout << "---------------------------------------" << endl << endl;
}

int customer_or_employee()
{
	cout << "Choose from list:" << endl << endl;

	cout << "1 - Customer" << endl;

	cout << "2 - Employee" << endl << endl;

	for (int i = 1; i <= 3; i++)
	{
		int opt;

		cout << "Your choice: ";

		cin >> opt;

		cout << endl;

		separating_line();

		if (opt == 1)
		{
			return 1;

			break;
		}

		else if (opt == 2)
		{
			getpassword();

			int ans = password();

			return ans;

			break;
		}

		else if (i < 3)
		{
			cout << "Wrong choice try again" << endl << endl;
		}

		else
		{
			return 0;

			break;
		}
	}
}

string getpassword(const string& prompt)
{
	DWORD mode, count;
	HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleMode(ih, &mode))
		throw runtime_error(
			"getpassword: You must be connected to a console to use this program.\n"
			);
	SetConsoleMode(ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

	WriteConsoleA(oh, prompt.c_str(), prompt.length(), &count, NULL);
	char c;
	while (ReadConsoleA(ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
	{
		if (c == '\b')
		{
			if (result.length())
			{
				WriteConsoleA(oh, "\b \b", 3, &count, NULL);
				result.erase(result.end() - 1);
			}
		}
		else
		{
			WriteConsoleA(oh, "*", 1, &count, NULL);
			result.push_back(c);
		}
	}

	cout << endl << endl;

	SetConsoleMode(ih, mode);

	return result;
}

int password()
{
	for (int i = 0; i < 3; i++)
	{

		if (result == "3D2Y")
		{
			separating_line();
			return 2;
			break;
		}
		else if (i < 3)
		{
			separating_line();
			cout << "Wrong password try again" << endl << endl;
			result.clear();
			getpassword();
		}
		else
		{
			return 0;
		}
	}
}

void customer_list()
{
	cout << "Choose from list:" << endl << endl;

	cout << "1 - list all books in library" << endl;

	cout << "2 - list all books to buy or borrow" << endl;

	cout << "3 - search for a book" << endl;

	cout << "4 - exit program" << endl << endl;
}

void employee_list()
{
	cout << "Choose from list:" << endl << endl;

	cout << "1 - list all books in library" << endl;

	cout << "2 - list all books to buy or borrow" << endl;

	cout << "3 - borrow book" << endl;

	cout << "4 - buy book" << endl;

	cout << "5 - search for a book" << endl;

	cout << "6 - add book" << endl;

	cout << "7 - delete book" << endl;

	cout << "8 - Show Sales Transaction" << endl;

	cout << "9 - exit program" << endl << endl;
}

void customer(book arrbook[])
{

	while (true)
	{


		customer_list();

		separating_line();

		int cus;

		cout << "Your choice: ";

		cin >> cus;

		cout << endl;

		if (cus == 1)
		{
			show_all(arrbook);
		}

		else if (cus == 2)
		{
			buy_borrow_both(arrbook);
		}

		else if (cus == 3)
		{
			search(arrbook, cus);
		}

		else if (cus == 4)
		{
			cout << "THANK YOU" << endl << endl;

			break;
		}

		else
		{
			cout << "wrong choice try again" << endl << endl;
		}

		int h;
		cout << "To countine press (1)" << endl;
		cout << "To exit press (2)" << endl << endl;
		h = clear();
		cout << endl;

		if (h == 1)
		{
			if (system("CLS"))
			{
				system("clear");
			}
		}

		else if (h == 2)
		{
			break;
		}
	}
}

void employee(book arrbook[], book arrdlt[], sales arrsal[], brwd arrbrr[], book arrbrwd[])
{


	while (true)
	{
		employee_list();

		separating_line();

		int emp;

		cout << "Your choice: ";

		cin >> emp;

		cout << endl;

		string TYPE = "TYPE";

		if (emp == 1)
		{
			show_all(arrbook);
		}

		else if (emp == 2)
		{
			buy_borrow_both(arrbook);
		}

		else if (emp == 3)
		{
			borrow_book(arrbook, arrbrr, arrbrwd);
		}

		else if (emp == 4)
		{
			buy_book(arrbook, arrdlt, arrsal);
		}

		else if (emp == 5)
		{
			search(arrbook, emp);
		}

		else if (emp == 6)
		{
			add_choice(arrbook, arrdlt);
		}

		else if (emp == 7)
		{
			delete_book(arrbook, arrdlt, TYPE);
		}
		else if (emp == 8)
		{
			display_sales_transaction(arrsal);
		}

		else if (emp == 9)
		{
			cout << "THANK YOU" << endl << endl;

			break;
		}

		else
		{
			cout << "wrong choice try again" << endl << endl;
		}

		autosave(arrbook, arrdlt, arrsal, arrbrr, arrbrwd);

		int h;
		cout << "To countine press (1)" << endl;
		cout << "To exit press (2)" << endl << endl;
		h = clear();
		cout << endl;

		if (h == 1)
		{
			if (system("CLS"))
			{
				system("clear");
			}
		}

		else if (h == 2)
		{
			break;
		}
	}
}

void mini_outlook(book out[], int i)
{
	cout << out[i].ISBN << " : --> " << out[i].title << endl << endl;
}

void outlook(book out[], int i)
{
	cout << "Book no." << i + 1 << " in library:" << endl << endl;

	cout << "Category: " << out[i].category << endl << endl;

	cout << "Book details:" << endl << endl;

	cout << "--> ISBN: " << out[i].ISBN << endl;

	cout << "--> Title: " << out[i].title << endl;

	cout << "--> Edition: " << out[i].edition << endl;

	cout << "--> Date published: " << out[i].datePub << endl;

	cout << "--> Rating: " << out[i].rating << endl << endl;

	cout << "Status:" << endl << endl;

	cout << "--> Status: " << out[i].status << endl;

	cout << "--> Amount in library: " << out[i].amountint << endl;

	cout << "--> Buy / Borrow: " << out[i].buyBrr << endl;

	cout << "--> Price: " << out[i].price << endl << endl;

	cout << "Publisher details:" << endl << endl;

	cout << "--> Name: " << out[i].publisher.name << endl;

	cout << "--> Address: " << out[i].publisher.address << endl << endl;

	cout << "Author(s) details:" << endl << endl;

	for (int k = 0; k < out[i].numAth; k++)
	{
		cout << "--> Name: " << out[i].author[k].name << endl;

		cout << "--> Nationality: " << out[i].author[k].nationality << endl << endl;
	}
}

void show_all(book arrbook[])
{
	for (int h = 0; h < bookNum; h++)
	{
		outlook(arrbook, h);
	}
}

void buy_borrow_both(book arrbook[])
{
	cout << "List options:" << endl << endl;

	cout << "Press (1) buy & borrow" << endl;

	cout << "Press (2) borrow only" << endl;

	cout << "press (3) buy only" << endl << endl;

	int choice;

	cout << "Your choice: ";

	cin >> choice;

	cout << endl;

	cin.ignore();

	int counter = 0;

	string list_1;

	if (choice == 1)
	{
		list_1 = "both";
	}

	else if (choice == 2)
	{
		list_1 = "borrow";
	}

	else if (choice == 3)
	{
		list_1 = "buy";
	}

	else
	{
		cout << "Wrong choice, press (2) to try again" << endl << endl;

		counter++;
	}

	for (int i = 0; i < bookNum; i++)
	{
		if (arrbook[i].buyBrr == list_1)
		{
			outlook(arrbook, i);

			counter++;
		}
	}
	if (counter == 0)
	{
		cout << "No books found" << endl << endl;
	}
}

void borrow_book(book arrbook[], brwd arrbrr[], book arrbrwd[])
{
	int length = 0;

	minbook ach[sizemax];

	for (int i = 0; i < bookNum; i++)
	{
		if (arrbook[i].buyBrr == "borrow" || arrbook[i].buyBrr == "both")
		{
			ach[length].num = i;

			ach[length].ISBN = arrbook[i].ISBN;

			length++;
		}
	}

	if (length != 0)
	{
		cout << "Found " << length << " books:" << endl << endl;

		for (int i = 0; i < length; i++)
		{
			mini_outlook(arrbook, ach[i].num);
		}

		int counter = 0;

		string ID;

		cout << "Enter ISBN of book: ";

		cin >> ID;

		cout << endl;

		for (int i = 0; i < bookNum; i++)
		{
			if (arrbook[i].ISBN == ID)
			{
				if (arrbook[i].buyBrr == "borrow" || arrbook[i].buyBrr == "both")
				{
					borrow_transaction(arrbook, arrbrr, arrbrwd, i);
				}

				else
				{
					cout << "This book is not for borrow" << endl << endl;
				}

				counter++;

				break;
			}
		}

		if (counter == 0)
		{
			cout << "No book found, press (3) to try again" << endl << endl;
		}
	}

	else
	{
		cout << "No books for borrow" << endl << endl;
	}
}

void borrow_transaction(book arrbook[], brwd arrbrr[], book arrbrwd[], int i)
{
	int brk = 1;

	char date[9];

	int iSecret;

	string temp = "";

	while (true)
	{
		cout << "Book details:" << endl << endl;

		arrbrr[borrowNum].isbn = arrbook[i].ISBN;

		cout << "--> ISBN: " << arrbrr[borrowNum].isbn << endl;

		arrbrr[borrowNum].Title = arrbook[i].title;

		cout << "--> Title: " << arrbrr[borrowNum].Title << endl;

		for (int l = 1; l <= 3; l++)
		{
			cout << "--> No. to borrow: ";

			cin >> arrbrr[borrowNum].Numstr;

			arrbrr[borrowNum].Numint = stoi(arrbrr[borrowNum].Numstr);

			cout << endl;

			if (arrbrr[borrowNum].Numint <= arrbook[i].amountint)
			{
				arrbook[i].amountint = arrbook[i].amountint - arrbrr[borrowNum].Numint;

				break;
			}

			else if (l < 3)
			{
				cout << "The amount you entered is more than what is in library" << endl << endl;
			}

			else
			{
				cout << "TIME UP" << endl << endl;

				brk = 0;
			}
		}

		if (brk == 0)
		{
			break;
		}

		if (arrbook[i].amountint == 0)
		{
			arrbook[i].status = "Unavailable";
		}

		cin.ignore();

		cout << "Borrower details: " << endl << endl;

		cout << "--> ID: ";

		getline(cin, arrbrr[borrowNum].id);

		cout << "--> Name: ";

		getline(cin, arrbrr[borrowNum].Name);

		cout << endl << "File details:" << endl << endl;

		srand((unsigned int)time(NULL));

		iSecret = (rand() % 90000) + 10000;

		temp = to_string(iSecret);

		temp = arrbrr[borrowNum].isbn + temp;

		arrbrr[borrowNum].TrNumint = stoi(temp);

		arrbrr[borrowNum].TrNumint = 1234;

		cout << "--> Transaction no.: " << arrbrr[borrowNum].TrNumint << endl;

		cout << "--> Date borrowed: ";

		_strdate_s(date);

		arrbrr[borrowNum].Date = date;

		cout << arrbrr[borrowNum].Date << endl;

		cout << "--> Period: ";

		getline(cin, arrbrr[borrowNum].Period);

		cout << endl;



		arrbrwd[brwdNum].amountint = arrbrr[borrowNum].Numint;

		save_borrowed(arrbook, arrbrwd, i);

		borrowNum++;

		break;
	}
}

void buy_book(book arrbook[], book arrdlt[], sales arrsal[])
{
	int length = 0;

	minbook ach[sizemax];

	for (int i = 0; i < bookNum; i++)
	{
		if (arrbook[i].buyBrr == "buy" || arrbook[i].buyBrr == "both")
		{
			ach[length].num = i;

			ach[length].ISBN = arrbook[i].ISBN;

			length++;
		}
	}

	if (length > 0)
	{
		cout << "Found " << length << " books:" << endl << endl;

		for (int i = 0; i < length; i++)
		{
			mini_outlook(arrbook, ach[i].num);
		}

		int counter = 0;

		string ID;

		cout << "Enter ISBN of book: ";

		cin >> ID;

		cout << endl;

		for (int u = 0; u < bookNum; u++)
		{
			if (arrbook[u].ISBN == ID)
			{
				if (arrbook[u].buyBrr == "buy" || arrbook[u].buyBrr == "both")
				{
					buy_transaction(arrbook, arrdlt, arrsal, u);
				}

				else
				{
					cout << "This book is not for sale" << endl << endl;
				}

				counter++;

				break;
			}
		}

		if (counter == 0)
		{
			cout << "No book found, press (4) to try again" << endl << endl;
		}
	}

	else
	{
		cout << "No books for sale" << endl << endl;
	}
}

void buy_transaction(book arrbook[], book arrdlt[], sales arrsal[], int i)
{
	int brk = 1;

	char date[9];

	int iSecret;

	string temp = "";

	while (true)
	{
		cout << "Book details:" << endl << endl;

		arrsal[saleNum].ISBN = arrbook[i].ISBN;

		cout << "--> ISBN: " << arrsal[saleNum].ISBN << endl;

		arrsal[saleNum].title = arrbook[i].title;

		cout << "--> Title: " << arrsal[saleNum].title << endl;

		arrsal[saleNum].price = arrbook[i].price;

		cout << "--> Price: " << arrsal[saleNum].price << endl;

		for (int e = 1; e <= 3; e++)
		{
			cout << "--> No. to sell: ";

			cin >> arrsal[saleNum].numstr;

			arrsal[saleNum].numint = stoi(arrsal[saleNum].numstr);

			cout << endl;

			if (arrsal[saleNum].numint <= arrbook[i].amountint)
			{
				arrbook[i].amountint = arrbook[i].amountint - arrsal[saleNum].numint;

				break;
			}

			else if (e < 3)
			{
				cout << "The amount you entered is more than what is in library" << endl << endl;
			}

			else
			{
				cout << "TIME UP" << endl << endl;

				brk = 0;
			}
		}

		if (brk == 0)
		{
			break;
		}

		if (arrbook[i].amountint == 0)
		{
			delete_book(arrbook, arrdlt, arrbook[i].ISBN);
		}

		cin.ignore();

		cout << "Customer details: " << endl << endl;

		cout << "--> ID: ";

		getline(cin, arrsal[saleNum].ID);

		cout << "--> Name: ";

		getline(cin, arrsal[saleNum].name);

		cout << endl << "Invoice details:" << endl << endl;

		srand((unsigned int)time(NULL));

		iSecret = (rand() % 90000) + 10000;

		temp = to_string(iSecret);

		temp = arrsal[saleNum].ISBN + temp;

		arrsal[saleNum].trNumint = stoi(temp);

		//arrsal[saleNum].trNumint = 1234;

		cout << "--> Transaction no.: " << arrsal[saleNum].trNumint << endl;

		cout << "--> Payment method: ";

		getline(cin, arrsal[saleNum].saleMethod);

		transform(arrsal[saleNum].saleMethod.begin(), arrsal[saleNum].saleMethod.end(), arrsal[saleNum].saleMethod.begin(), ::tolower);

		cout << "--> Date sold: ";

		_strdate_s(date);

		arrsal[saleNum].date = date;

		cout << arrsal[saleNum].date << endl;

		cout << endl;

		saleNum++;

		if (arrbook[i].amountint == 0)
		{
			cout << "NOTE : BOOK DELETED" << endl << endl;
		}

		break;
	}
}

void search(book arrbook[], int look)
{
	cout << "Search options:" << endl << endl;

	cout << "Press (1) ISBN" << endl;

	cout << "Press (2) Title" << endl;

	cout << "press (3) Author name" << endl;

	cout << "Press (4) Category" << endl << endl;

	int choice;

	cout << "Your choice: ";

	cin >> choice;

	cout << endl;

	cin.ignore();

	string srch;

	int counter = 0;

	if (choice == 1)
	{
		cout << "Enter ISBN of book: ";

		getline(cin, srch);

		cout << endl;

		for (int i = 0; i < bookNum; i++)
		{
			if (srch == arrbook[i].ISBN)
			{
				outlook(arrbook, i);

				counter++;
			}
		}
	}

	else if (choice == 2)
	{
		cout << "Enter title of book: ";

		getline(cin, srch);

		cout << endl;

		for (int i = 0; i < bookNum; i++)
		{
			if (srch == arrbook[i].title)
			{
				outlook(arrbook, i);

				counter++;
			}

		}
		if (counter == 0)
			counter = mean_title(arrbook, counter, srch);
	}

	else if (choice == 3)
	{
		string author_books[sizemax];
		int queue_choice;
		cout << "Enter author name: ";

		getline(cin, srch);

		cout << endl;

		for (int i = 0; i < bookNum; i++)
		{
			for (int j = 0; j < 5; j++)
			{

				if (srch == arrbook[i].author[j].name)
				{
					counter++;
					//outlook(arrbook, i);
					cout << counter << "- " << arrbook[i].title << endl;
					author_books[counter] = arrbook[i].title;
				}

			}
		}
		if (counter != 0)
		{
			cout << "Your choice" << endl;
			cin >> queue_choice;
			for (int i = 0; i < bookNum; i++)
			{
				if (author_books[queue_choice] == arrbook[i].title)
				{
					outlook(arrbook, i);
				}
			}
		}


		if (counter == 0)
			counter = mean_author(arrbook, counter, srch);
	}

	else if (choice == 4)
	{
		cout << "Enter category of book: ";

		getline(cin, srch);

		cout << endl;

		for (int i = 0; i < bookNum; i++)
		{
			if (srch == arrbook[i].category)
			{
				outlook(arrbook, i);

				counter++;
			}
		}
	}

	else
	{
		cout << "Wrong choice, press (" << look << ") to try again" << endl << endl;

		counter++;
	}

	if (counter == 0)
	{
		cout << "No books found, press (" << look << ") to try again" << endl << endl;
	}
}

void add_choice(book arrbook[], book arrdlt[])
{
	cout << "Choose from:" << endl << endl;

	cout << "1 - add manually" << endl;

	cout << "2 - re-add deleted book" << endl;

	cout << "3 - increase amount of a book" << endl << endl;

	for (int w = 1; w <= 3; w++)
	{
		int arc;

		cout << "Your choice: ";

		cin >> arc;

		cout << endl;

		if (arc == 1)
		{
			manual_add(arrbook);

			break;
		}

		else if (arc == 2)
		{
			add_from_delete(arrbook, arrdlt);

			break;
		}

		else if (arc == 3)
		{
			increase_amount(arrbook);

			break;
		}

		else if (w < 3)
		{
			cout << "Wrong choice try again" << endl << endl;
		}

		else
		{
			cout << "TIME UP" << endl << endl;
		}
	}
}

void manual_add(book arrbook[])
{
	int newBook;

	cout << "How many books you want to add: ";

	cin >> newBook;

	cout << endl;

	int index = bookNum + newBook;

	cin.ignore();

	for (int i = bookNum; i < index; i++)
	{
		cout << "Book no." << i + 1 << " in library:" << endl << endl;

		cout << "Category: ";

		getline(cin, arrbook[i].category);

		cout << endl << "Book details:" << endl << endl;

		cout << "--> ISBN: ";

		getline(cin, arrbook[i].ISBN);

		cout << "--> Title: ";

		getline(cin, arrbook[i].title);

		cout << "--> Edition: ";

		getline(cin, arrbook[i].edition);

		cout << "--> Date published: ";

		getline(cin, arrbook[i].datePub);

		cout << "--> Rating: ";

		getline(cin, arrbook[i].rating);

		cout << endl << "Status:" << endl << endl;

		cout << "--> Status: Available" << endl;

		arrbook[i].status = "Available";

		cout << "--> Amount in library: ";

		cin >> arrbook[i].amountstr;

		arrbook[i].amountint = stoi(arrbook[i].amountstr);

		cin.ignore();

		cout << "--> Buy / Borrow: ";

		getline(cin, arrbook[i].buyBrr);

		transform(arrbook[i].buyBrr.begin(), arrbook[i].buyBrr.end(), arrbook[i].buyBrr.begin(), ::tolower);

		if (arrbook[i].buyBrr == "buy" || arrbook[i].buyBrr == "both")
		{
			cout << "--> Price: ";

			getline(cin, arrbook[i].price);
		}

		else
		{
			cout << "--> Price: N/A" << endl;

			arrbook[i].price = "N/A";
		}

		cout << endl << "Publisher details:" << endl << endl;

		cout << "--> Name: ";

		getline(cin, arrbook[i].publisher.name);

		cout << "--> Address: ";

		getline(cin, arrbook[i].publisher.address);

		cout << endl << "Author(s) details:" << endl << endl;

		cout << "Enter number of author(s) of book: ";

		cin >> arrbook[i].numAth;

		cout << endl;

		cin.ignore();

		for (int k = 0; k < arrbook[i].numAth; k++)
		{
			cout << "--> Name: ";

			getline(cin, arrbook[i].author[k].name);

			cout << "--> Nationality: ";

			getline(cin, arrbook[i].author[k].nationality);

			cout << endl;
		}
	}

	bookNum = index;
}

void add_from_delete(book arrbook[], book arrdlt[])
{
	if (deleteNum > 0)
	{
		int counter = 0;

		string ice;

		cout << "Enter ISBN: ";

		cin >> ice;

		cout << endl;

		for (int i = 0; i < deleteNum; i++)
		{
			if (ice == arrdlt[i].ISBN)
			{
				counter = 1;

				outlook(arrdlt, i);

				arrbook[bookNum].category = arrdlt[i].category;

				arrbook[bookNum].ISBN = arrdlt[i].ISBN;

				arrbook[bookNum].title = arrdlt[i].title;

				arrbook[bookNum].edition = arrdlt[i].edition;

				arrbook[bookNum].datePub = arrdlt[i].datePub;

				arrbook[bookNum].rating = arrdlt[i].rating;

				arrbook[bookNum].status = "Available";

				cout << "Enter new amount: ";

				cin >> arrbook[bookNum].amountint;

				cout << endl;

				arrbook[bookNum].buyBrr = arrdlt[i].buyBrr;

				arrbook[bookNum].price = arrdlt[i].price;

				arrbook[bookNum].publisher.name = arrdlt[i].publisher.name;

				arrbook[bookNum].publisher.address = arrdlt[i].publisher.address;

				arrbook[bookNum].numAth = arrdlt[i].numAth;

				for (int k = 0; k < arrdlt[i].numAth; k++)
				{
					arrbook[bookNum].author[k].name = arrdlt[i].author[k].name;

					arrbook[bookNum].author[k].nationality = arrdlt[i].author[k].nationality;
				}

				bookNum++;

				deleteNum--;

				cout << "BOOK ADDED" << endl << endl;

				break;
			}
		}

		if (counter == 0)
		{
			cout << "No books found with this ISBN" << endl << endl;
		}
	}

	else if (deleteNum <= 0)
	{
		cout << "No books to add from" << endl << endl;
	}
}

void increase_amount(book arrbook[])
{
	if (bookNum > 0)
	{
		int counter = 0;

		string ID;

		cout << "Enter ISBN: ";

		cin >> ID;

		cout << endl;

		for (int i = 0; i < bookNum; i++)
		{
			if (arrbook[i].ISBN == ID)
			{
				counter = 1;

				cout << "Book no." << i + 1 << " in library:" << endl << endl;

				cout << "Title: " << arrbook[i].title << endl << endl;

				cout << "Current amount: " << arrbook[i].amountint << endl << endl;

				int amount;

				cout << "Enter amount to be added: ";

				cin >> amount;

				cout << endl;

				arrbook[i].amountint = arrbook[i].amountint + amount;

				cout << "AMOUNT ADDED" << endl << endl;

				break;
			}
		}

		if (counter == 0)
		{
			cout << "No book with that ISBN" << endl << endl;
		}
	}

	else
	{
		cout << "There is no books in library" << endl << endl;
	}
}

void delete_book(book arrbook[], book arrdlt[], string remove)
{
	int counter = 0;

	string ID;

	//if (remove == "TYPE")
	//{
		cout << "Enter ISBN of book: ";

		cin >> ID;

		cout << endl;
	//}

	//else
	//{
		//ID = remove;
	//}

	for (int i = 0; i < bookNum; i++)
	{
		if (arrbook[i].ISBN == ID)
		{
			counter++;

			save_delete(arrbook, arrdlt, i);

			if (i != (bookNum - 1))
			{
				arrbook[i].category = arrbook[bookNum - 1].category;

				arrbook[i].ISBN = arrbook[bookNum - 1].ISBN;

				arrbook[i].title = arrbook[bookNum - 1].title;

				arrbook[i].edition = arrbook[bookNum - 1].edition;

				arrbook[i].datePub = arrbook[bookNum - 1].datePub;

				arrbook[i].rating = arrbook[bookNum - 1].rating;

				arrbook[i].status = arrbook[bookNum - 1].status;

				arrbook[i].amountint = arrbook[bookNum - 1].amountint;

				arrbook[i].buyBrr = arrbook[bookNum - 1].buyBrr;

				arrbook[i].price = arrbook[bookNum - 1].price;

				arrbook[i].publisher.name = arrbook[bookNum - 1].publisher.name;

				arrbook[i].publisher.address = arrbook[bookNum - 1].publisher.address;

				arrbook[i].numAth = arrbook[bookNum - 1].numAth;

				for (int k = 0; k < arrbook[bookNum - 1].numAth; k++)
				{
					arrbook[i].author[k].name = arrbook[bookNum - 1].author[k].name;

					arrbook[i].author[k].nationality = arrbook[bookNum - 1].author[k].nationality;
				}
			}

			bookNum--;

			if (remove == "TYPE")
			{
				cout << "BOOK DELETED" << endl << endl;
			}

			break;
		}
	}

	if (counter == 0)
	{
		cout << "No book with this ISBN in library" << endl << endl;

		//cout << "Press (8) to try again" << endl << endl;
	}
}

void save_delete(book arrbook[], book arrdlt[], int i)
{
	arrdlt[deleteNum].category = arrbook[i].category;

	arrdlt[deleteNum].ISBN = arrbook[i].ISBN;

	arrdlt[deleteNum].title = arrbook[i].title;

	arrdlt[deleteNum].edition = arrbook[i].edition;

	arrdlt[deleteNum].datePub = arrbook[i].datePub;

	arrdlt[deleteNum].rating = arrbook[i].rating;

	arrdlt[deleteNum].status = "Unavailable";

	arrdlt[deleteNum].amountint = 0;

	arrdlt[deleteNum].buyBrr = arrbook[i].buyBrr;

	arrdlt[deleteNum].price = arrbook[i].price;

	arrdlt[deleteNum].publisher.name = arrbook[i].publisher.name;

	arrdlt[deleteNum].publisher.address = arrbook[i].publisher.address;

	arrdlt[deleteNum].numAth = arrbook[i].numAth;

	for (int k = 0; k < arrbook[i].numAth; k++)
	{
		arrdlt[deleteNum].author[k].name = arrbook[i].author[k].name;

		arrdlt[deleteNum].author[k].nationality = arrbook[i].author[k].nationality;
	}

	deleteNum++;
}

void write(book arrbook[], book arrdlt[], sales arrsal[], brwd arrbrr[], book arrbrwd[])
{
	write_library(arrbook);

	write_out(arrbrr);

	write_deleted(arrdlt);

	write_sales(arrsal);

	write_borrowed(arrbrwd);
}

void write_library(book arrbook[])
{
	ofstream outfile;

	outfile.open("Books_In_Library.txt");

	for (int i = 0; i < bookNum; i++)
	{
		outfile << arrbook[i].category << endl;

		outfile << arrbook[i].ISBN << endl;

		outfile << arrbook[i].title << endl;

		outfile << arrbook[i].edition << endl;

		outfile << arrbook[i].datePub << endl;

		outfile << arrbook[i].rating << endl;

		outfile << arrbook[i].status << endl;

		outfile << arrbook[i].amountint << endl;

		outfile << arrbook[i].buyBrr << endl;

		outfile << arrbook[i].price << endl;

		outfile << arrbook[i].publisher.name << endl;

		outfile << arrbook[i].publisher.address << endl;

		outfile << arrbook[i].numAth << endl;

		for (int k = 0; k < arrbook[i].numAth; k++)
		{
			outfile << arrbook[i].author[k].name << endl;

			outfile << arrbook[i].author[k].nationality << endl;
		}

		outfile << "---------------" << endl;
	}

	outfile.close();
}

void write_out(brwd arrbrr[])
{
	ofstream outfile;

	outfile.open("Borrowers_Transactions.txt");

	for (int i = 0; i < borrowNum; i++)
	{
		outfile << arrbrr[i].isbn << endl;

		outfile << arrbrr[i].Title << endl;

		outfile << arrbrr[i].Numint << endl;

		outfile << arrbrr[i].id << endl;

		outfile << arrbrr[i].Name << endl;

		outfile << arrbrr[i].TrNumint << endl;

		outfile << arrbrr[i].Date << endl;

		outfile << arrbrr[i].Period << endl;

		outfile << "---------------" << endl;
	}

	outfile.close();
}

void write_deleted(book arrdlt[])
{
	ofstream outfile;

	outfile.open("Deleted_Books.txt");

	for (int i = 0; i < deleteNum; i++)
	{
		outfile << arrdlt[i].category << endl;

		outfile << arrdlt[i].ISBN << endl;

		outfile << arrdlt[i].title << endl;

		outfile << arrdlt[i].edition << endl;

		outfile << arrdlt[i].datePub << endl;

		outfile << arrdlt[i].rating << endl;

		outfile << arrdlt[i].status << endl;

		outfile << arrdlt[i].amountint << endl;

		outfile << arrdlt[i].buyBrr << endl;

		outfile << arrdlt[i].price << endl;

		outfile << arrdlt[i].publisher.name << endl;

		outfile << arrdlt[i].publisher.address << endl;

		outfile << arrdlt[i].numAth << endl;

		for (int k = 0; k < arrdlt[i].numAth; k++)
		{
			outfile << arrdlt[i].author[k].name << endl;

			outfile << arrdlt[i].author[k].nationality << endl;
		}

		outfile << "---------------" << endl;
	}

	outfile.close();
}

void write_sales(sales arrsal[])
{
	ofstream outfile;

	outfile.open("Sales_Transactions.txt");

	for (int i = 0; i < saleNum; i++)
	{
		outfile << arrsal[i].ISBN << endl;

		outfile << arrsal[i].title << endl;

		outfile << arrsal[i].price << endl;

		outfile << arrsal[i].numint << endl;

		outfile << arrsal[i].ID << endl;

		outfile << arrsal[i].name << endl;

		outfile << arrsal[i].trNumint << endl;

		outfile << arrsal[i].saleMethod << endl;

		outfile << arrsal[i].date << endl;

		outfile << "---------------" << endl;
	}

	outfile.close();
}

void autosave(book arrbook[], book arrdlt[], sales arrsal[], brwd arrbrr[], book arrbrwd[])
{
	write(arrbook, arrdlt, arrsal, arrbrr, arrbrwd);

	read(arrbook, arrdlt, arrsal, arrbrr, arrbrwd);
}

void display_sales_transaction(sales arrsal[])
{
	int choice;
	int cash_counter = 0, cheque_counter = 0, credit_counter = 0;

	sales display_sal_trans[sizemax];

	cout << "1- Show All Transactions Happened With Cash" << endl;
	cout << "2- Show All Transactions Happened With Cheque" << endl;
	cout << "3- Show All Transactions Happened With Credit Card" << endl;
	cout << "4- Show All Transactions" << endl << endl;

	cout << "You Choice :";
	cin >> choice;
	cout << endl;
	cin.ignore();

	if (choice == 1)
	{
		for (int i = 0, j = 0; i < saleNum; i++)
		{
			if (arrsal[i].saleMethod == "cash")
			{
				display_sal_trans[j].ISBN = arrsal[i].ISBN;
				display_sal_trans[j].title = arrsal[i].title;
				display_sal_trans[j].price = arrsal[i].price;
				display_sal_trans[j].numstr = arrsal[i].numstr;
				display_sal_trans[j].ID = arrsal[i].ID;
				display_sal_trans[j].name = arrsal[i].name;
				display_sal_trans[j].trNumstr = arrsal[i].trNumstr;
				display_sal_trans[j].saleMethod = arrsal[i].saleMethod;
				display_sal_trans[j].date = arrsal[i].date;
				cash_counter++;
				j++;
			}
		}
		if (cash_counter > 0)
		{
			for (int i = 0; i < cash_counter; i++)
			{
				if (i < cash_counter && i != (cash_counter - 1))
				{
					cout << "Transaction Number :" << i + 1 << endl << endl;
					cout << "ISBN Of Book :" << display_sal_trans[i].ISBN << endl;
					cout << "Book Title :" << display_sal_trans[i].title << endl;
					cout << "Book Price :" << display_sal_trans[i].price << endl;
					cout << "The Amount The Customer Took :" << display_sal_trans[i].numstr << endl;
					cout << "The Customer ID :" << display_sal_trans[i].ID << endl;
					cout << "Customer Name :" << display_sal_trans[i].name << endl;
					cout << "Number Of Transaction :" << display_sal_trans[i].trNumstr << endl;
					cout << "Sale Method :" << display_sal_trans[i].saleMethod << endl;
					cout << "Date Of Transaction :" << display_sal_trans[i].date << endl << endl;
					separating_line();
				}
				else if (i == (cash_counter - 1))
				{
					cout << "Transaction Number :" << i + 1 << endl << endl;
					cout << "ISBN Of Book :" << display_sal_trans[i].ISBN << endl;
					cout << "Book Title :" << display_sal_trans[i].title << endl;
					cout << "Book Price :" << display_sal_trans[i].price << endl;
					cout << "The Amount The Customer Took :" << display_sal_trans[i].numstr << endl;
					cout << "The Customer ID :" << display_sal_trans[i].ID << endl;
					cout << "Customer Name :" << display_sal_trans[i].name << endl;
					cout << "Number Of Transaction :" << display_sal_trans[i].trNumstr << endl;
					cout << "Sale Method :" << display_sal_trans[i].saleMethod << endl;
					cout << "Date Of Transaction :" << display_sal_trans[i].date << endl << endl;
				}
			}
		}
		else
		{
			cout << "There are no books sold with cash" << endl << endl;
		}
	}
	if (choice == 2)
	{
		for (int i = 0, j = 0; i < saleNum; i++)
		{
			if (arrsal[i].saleMethod == "cheque")
			{
				display_sal_trans[j].ISBN = arrsal[i].ISBN;
				display_sal_trans[j].title = arrsal[i].title;
				display_sal_trans[j].price = arrsal[i].price;
				display_sal_trans[j].numstr = arrsal[i].numstr;
				display_sal_trans[j].ID = arrsal[i].ID;
				display_sal_trans[j].name = arrsal[i].name;
				display_sal_trans[j].trNumstr = arrsal[i].trNumstr;
				display_sal_trans[j].saleMethod = arrsal[i].saleMethod;
				display_sal_trans[j].date = arrsal[i].date;
				cheque_counter++;
				j++;
			}
		}
		if (cheque_counter > 0)
		{
			for (int i = 0; i < cheque_counter; i++)
			{
				if (i < cheque_counter && i != (cheque_counter - 1))
				{
					cout << "Transaction Number :" << i + 1 << endl << endl;
					cout << "ISBN Of Book :" << display_sal_trans[i].ISBN << endl;
					cout << "Book Title :" << display_sal_trans[i].title << endl;
					cout << "Book Price :" << display_sal_trans[i].price << endl;
					cout << "The Amount The Customer Took :" << display_sal_trans[i].numstr << endl;
					cout << "The Customer ID :" << display_sal_trans[i].ID << endl;
					cout << "Customer Name :" << display_sal_trans[i].name << endl;
					cout << "Number Of Transaction :" << display_sal_trans[i].trNumstr << endl;
					cout << "Sale Method :" << display_sal_trans[i].saleMethod << endl;
					cout << "Date Of Transaction :" << display_sal_trans[i].date << endl << endl;
					separating_line();
				}
				else if (i == (cheque_counter - 1))
				{
					cout << "Transaction Number :" << i + 1 << endl << endl;
					cout << "ISBN Of Book :" << display_sal_trans[i].ISBN << endl;
					cout << "Book Title :" << display_sal_trans[i].title << endl;
					cout << "Book Price :" << display_sal_trans[i].price << endl;
					cout << "The Amount The Customer Took :" << display_sal_trans[i].numstr << endl;
					cout << "The Customer ID :" << display_sal_trans[i].ID << endl;
					cout << "Customer Name :" << display_sal_trans[i].name << endl;
					cout << "Number Of Transaction :" << display_sal_trans[i].trNumstr << endl;
					cout << "Sale Method :" << display_sal_trans[i].saleMethod << endl;
					cout << "Date Of Transaction :" << display_sal_trans[i].date << endl << endl;
				}
			}
		}
		else
		{
			cout << "There are no books sold with cheques" << endl << endl;
		}
	}
	if (choice == 3)
	{
		for (int i = 0, j = 0; i < saleNum; i++)
		{
			if (arrsal[i].saleMethod == "credit card")
			{
				display_sal_trans[j].ISBN = arrsal[i].ISBN;
				display_sal_trans[j].title = arrsal[i].title;
				display_sal_trans[j].price = arrsal[i].price;
				display_sal_trans[j].numstr = arrsal[i].numstr;
				display_sal_trans[j].ID = arrsal[i].ID;
				display_sal_trans[j].name = arrsal[i].name;
				display_sal_trans[j].trNumstr = arrsal[i].trNumstr;
				display_sal_trans[j].saleMethod = arrsal[i].saleMethod;
				display_sal_trans[j].date = arrsal[i].date;
				credit_counter++;
				j++;
			}
		}
		if (credit_counter > 0)
		{
			for (int i = 0; i < credit_counter; i++)
			{
				if (i < credit_counter && i != (credit_counter - 1))
				{
					cout << "Transaction Number :" << i + 1 << endl << endl;
					cout << "ISBN Of Book :" << display_sal_trans[i].ISBN << endl;
					cout << "Book Title :" << display_sal_trans[i].title << endl;
					cout << "Book Price :" << display_sal_trans[i].price << endl;
					cout << "The Amount The Customer Took :" << display_sal_trans[i].numstr << endl;
					cout << "The Customer ID :" << display_sal_trans[i].ID << endl;
					cout << "Customer Name :" << display_sal_trans[i].name << endl;
					cout << "Number Of Transaction :" << display_sal_trans[i].trNumstr << endl;
					cout << "Sale Method :" << display_sal_trans[i].saleMethod << endl;
					cout << "Date Of Transaction :" << display_sal_trans[i].date << endl << endl;
					separating_line();
				}
				else if (i == (credit_counter - 1))
				{
					cout << "Transaction Number :" << i + 1 << endl << endl;
					cout << "ISBN Of Book :" << display_sal_trans[i].ISBN << endl;
					cout << "Book Title :" << display_sal_trans[i].title << endl;
					cout << "Book Price :" << display_sal_trans[i].price << endl;
					cout << "The Amount The Customer Took :" << display_sal_trans[i].numstr << endl;
					cout << "The Customer ID :" << display_sal_trans[i].ID << endl;
					cout << "Customer Name :" << display_sal_trans[i].name << endl;
					cout << "Number Of Transaction :" << display_sal_trans[i].trNumstr << endl;
					cout << "Sale Method :" << display_sal_trans[i].saleMethod << endl;
					cout << "Date Of Transaction :" << display_sal_trans[i].date << endl << endl;
				}
			}
		}
		else
		{
			cout << "There are no books sold with credit card" << endl << endl;
		}
	}
	if (choice == 4)
	{
		if (saleNum > 0)
		{
			for (int i = 0; i < saleNum; i++)
			{
				if (i < saleNum && i != (saleNum - 1))
				{
					cout << "Transaction Number :" << i + 1 << endl << endl;
					cout << "ISBN Of Book :" << arrsal[i].ISBN << endl;
					cout << "Book Title :" << arrsal[i].title << endl;
					cout << "Book Price :" << arrsal[i].price << endl;
					cout << "The Amount The Customer Took :" << arrsal[i].numstr << endl;
					cout << "The Customer ID :" << arrsal[i].ID << endl;
					cout << "Customer Name :" << arrsal[i].name << endl;
					cout << "Number Of Transaction :" << arrsal[i].trNumstr << endl;
					cout << "Sale Method :" << arrsal[i].saleMethod << endl;
					cout << "Date Of Transaction :" << arrsal[i].date << endl << endl;
					separating_line();
				}
				else if (i == (saleNum - 1))
				{
					cout << "Transaction Number :" << i + 1 << endl << endl;
					cout << "ISBN Of Book :" << arrsal[i].ISBN << endl;
					cout << "Book Title :" << arrsal[i].title << endl;
					cout << "Book Price :" << arrsal[i].price << endl;
					cout << "The Amount The Customer Took :" << arrsal[i].numstr << endl;
					cout << "The Customer ID :" << arrsal[i].ID << endl;
					cout << "Customer Name :" << arrsal[i].name << endl;
					cout << "Number Of Transaction :" << arrsal[i].trNumstr << endl;
					cout << "Sale Method :" << arrsal[i].saleMethod << endl;
					cout << "Date Of Transaction :" << arrsal[i].date << endl << endl;
				}
			}
		}
		else
		{
			cout << "There Are No Sold Books" << endl << endl;
		}
	}
}

int mean_title(book arrbook[], int counter, string srch)
{
	string third;
	int mean_choice;
	third = srch.substr(0, 3);
	string choice[sizemax];
	for (int i = 0; i < bookNum; i++)
	{
		transform(arrbook[i].title.begin(), arrbook[i].title.end(), arrbook[i].title.begin(), ::tolower);
		transform(srch.begin(), srch.end(), srch.begin(), ::tolower);
		transform(third.begin(), third.end(), third.begin(), ::tolower);
		if (arrbook[i].title.find(srch) != string::npos)
		{
			counter++;
			if (counter == 1)
			{
				cout << "Did you mean :" << endl << endl;
			}
			cout << counter << "- " << arrbook[i].title << endl;
			choice[counter] = arrbook[i].title;
		}
		else if (arrbook[i].title.find(third) != string::npos)
		{
			counter++;
			if (counter == 1)
			{
				cout << "Did you mean :" << endl << endl;
			}
			cout << counter << "- " << arrbook[i].title << endl;
			choice[counter] = arrbook[i].title;
		}
	}
	if (counter != 0)
	{
		cout << endl;
		cout << "Your choice :";
		cin >> mean_choice;
		for (int i = 0; i < bookNum; i++)
		{
			if (choice[mean_choice] == arrbook[i].title)
			{
				outlook(arrbook, i);
			}
		}
	}
	return counter;
}

int mean_author(book arrbook[], int counter, string srch)
{
	string third;
	int mean_choice, queue = 0, queue_choice;
	third = srch.substr(0, 3);
	string choice[sizemax];
	string author_books[sizemax];
	for (int i = 0; i < bookNum; i++)
	{
		for (int j = 0; j < 5; j++)
		{

			transform(arrbook[i].author[j].name.begin(), arrbook[i].author[j].name.end(), arrbook[i].author[j].name.begin(), ::tolower);
			transform(srch.begin(), srch.end(), srch.begin(), ::tolower);
			transform(third.begin(), third.end(), third.begin(), ::tolower);
			if (arrbook[i].author[j].name.find(srch) != string::npos)
			{
				counter++;
				if (counter == 1)
				{
					cout << "Did you mean :" << endl << endl;
				}
				cout << counter << "- " << arrbook[i].author[j].name << endl;
				choice[counter] = arrbook[i].author[j].name;
			}
			else if (arrbook[i].author[j].name.find(third) != string::npos)
			{
				counter++;
				if (counter == 1)
				{
					cout << "Did you mean :" << endl << endl;
				}
				cout << counter << "- " << arrbook[i].author[j].name << endl;
				choice[counter] = arrbook[i].author[j].name;
			}
		}

		if (counter != 0)
		{
			cout << endl;
			cout << "Your choice :";
			cin >> mean_choice;
			for (int i = 0; i < bookNum; i++)
			{
				for (int j = 0; j < 5; j++)
				{

					if (choice[mean_choice] == arrbook[i].author[j].name)
					{
						queue++;
						cout << queue << "- " << arrbook[i].title << endl;
						author_books[queue] = arrbook[i].title;
					}
				}
			}
			cout << endl;
			cout << "Your choice :";
			cin >> queue_choice;
			for (int i = 0; i < bookNum; i++)
			{
				if (author_books[queue_choice] == arrbook[i].title)
				{
					outlook(arrbook, i);
				}
			}
		}
		return counter;
	}
}

void save_borrowed(book arrbook[], book arrbrwd[], int i)
{
	arrbrwd[brwdNum].category = arrbook[i].category;

	arrbrwd[brwdNum].ISBN = arrbook[i].ISBN;

	arrbrwd[brwdNum].title = arrbook[i].title;

	arrbrwd[brwdNum].edition = arrbook[i].edition;

	arrbrwd[brwdNum].datePub = arrbook[i].datePub;

	arrbrwd[brwdNum].rating = arrbook[i].rating;

	arrbrwd[brwdNum].status = "Borrowed";

	arrbrwd[brwdNum].buyBrr = arrbook[i].buyBrr;

	arrbrwd[brwdNum].price = arrbook[i].price;

	arrbrwd[brwdNum].publisher.name = arrbook[i].publisher.name;

	arrbrwd[brwdNum].publisher.address = arrbook[i].publisher.address;

	arrbrwd[brwdNum].numAth = arrbook[i].numAth;

	for (int k = 0; k < arrbook[i].numAth; k++)
	{
		arrbrwd[brwdNum].author[k].name = arrbook[i].author[k].name;

		arrbrwd[brwdNum].author[k].nationality = arrbook[i].author[k].nationality;
	}



	brwdNum++;
}

void read_borrowed(book arrbrwd[])
{
	ifstream myfile("Borrowed_Books.txt");

	if (myfile.is_open())
	{
		for (int i = 0; i < brwdNum; i++)
		{
			getline(myfile, arrbrwd[i].category);

			getline(myfile, arrbrwd[i].ISBN);

			getline(myfile, arrbrwd[i].title);

			getline(myfile, arrbrwd[i].edition);

			getline(myfile, arrbrwd[i].datePub);

			getline(myfile, arrbrwd[i].rating);

			getline(myfile, arrbrwd[i].status);

			getline(myfile, arrbrwd[i].amountstr);

			arrbrwd[i].amountint = stoi(arrbrwd[i].amountstr);

			getline(myfile, arrbrwd[i].buyBrr);

			getline(myfile, arrbrwd[i].price);

			getline(myfile, arrbrwd[i].publisher.name);

			getline(myfile, arrbrwd[i].publisher.address);

			myfile >> arrbrwd[i].numAth;

			myfile.ignore();

			for (int k = 0; k < arrbrwd[i].numAth; k++)
			{
				getline(myfile, arrbrwd[i].author[k].name);

				getline(myfile, arrbrwd[i].author[k].nationality);
			}

			getline(myfile, seppstr);
		}
	}

	myfile.close();
}

void write_borrowed(book arrbrwd[])
{
	ofstream outfile;

	outfile.open("Borrowed_Books.txt");

	for (int i = 0; i < brwdNum; i++)
	{
		outfile << arrbrwd[i].category << endl;

		outfile << arrbrwd[i].ISBN << endl;

		outfile << arrbrwd[i].title << endl;

		outfile << arrbrwd[i].edition << endl;

		outfile << arrbrwd[i].datePub << endl;

		outfile << arrbrwd[i].rating << endl;

		outfile << arrbrwd[i].status << endl;

		outfile << arrbrwd[i].amountint << endl;

		outfile << arrbrwd[i].buyBrr << endl;

		outfile << arrbrwd[i].price << endl;

		outfile << arrbrwd[i].publisher.name << endl;

		outfile << arrbrwd[i].publisher.address << endl;

		outfile << arrbrwd[i].numAth << endl;

		for (int k = 0; k < arrbrwd[i].numAth; k++)
		{
			outfile << arrbrwd[i].author[k].name << endl;

			outfile << arrbrwd[i].author[k].nationality << endl;
		}

		outfile << "---------------" << endl;
	}

	outfile.close();
}

int clear()
{
	int h;

	while (true)
	{
		cout << "Your choice: ";
		cin >> h;

		if (h == 1)
		{
			return 1;
		}

		else if (h == 2)
		{
			return 2;
		}

		else
		{
			cout << "wrong choice try again" << endl << endl;
		}
	}
}


//---------------------------------------------------------------------------------------------------------------------