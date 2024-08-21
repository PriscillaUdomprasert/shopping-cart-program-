#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <string>

using namespace std; 

struct Product
{
	string product_name;
	double str_price = 0.0;
	int str_discount_percent = 0;
	int str_quantity = 0;
};

void display_menu();
void load_file(vector<Product>& products);
void display_list(vector<Product>& products);
void display_cart(vector<Product>& cart);
void add_item(vector<Product>& products, vector<Product>& cart);
void remove_item(vector<Product>& cart);
double calculate_cart(vector<Product>& cart);

const string filename = "products.txt";

int main()
{
	vector<Product> products;
	vector<Product> cart;

	try
	{
		load_file(products);
	}
	catch (const invalid_argument& e)
	{
		cout << e.what() << "\n\n";

		return 0;
	}

	vector<Product> product; //maybe don't need??

	cout << "Shopping Cart" << endl << endl;
	
	string command = "exit";
	
	do 
	{
		display_menu();

		cout << "Command: ";
		cin >> command;

		cout << endl;

		if (command == "list")
		{
			display_list(products);
		}
		else if (command == "add")
		{
			add_item(products, cart);
		}
		else if (command == "cart")
		{
			display_cart(cart);
		}
		else if (command == "rem")
		{
			remove_item(cart);
		}
		else if (command == "exit")
		{
			break;
		}
		else
		{
			cout << "Invalid command. Please try again." << endl << endl;
			continue;
		}
	} while (command != "exit");


}

void display_menu()
{
	cout << "COMMAND MENU" << endl << "list - show the list of products" << endl <<
		"cart - show the cart" << endl << "add - add an item to the cart" << endl <<
		"rem - remove an item from the cart" << endl << "exit - exit the program" << endl << endl;
}

void load_file(vector<Product>& products)
{
	Product temp;
	string tempproduct_name;
	double tempstr_price = 0.0;
	int tempstr_discount_percent = 0;
	int tempstr_quantity = 0;
	ifstream infile;
	infile.open(filename);

	if (infile)
	{
		stringstream ss;
		string line;

		while (getline(infile, line))
		{
			ss.str(line);
			ss.clear();

			
			getline(ss, tempproduct_name, '\t');
			if (ss >> tempstr_price >> tempstr_discount_percent)
			{
				temp.product_name = tempproduct_name;
				temp.str_price = tempstr_price;
				temp.str_discount_percent = tempstr_discount_percent;
				products.push_back(temp);
			}
		}
		infile.close();
	}
	else
	{
		throw invalid_argument("File: products.txt didn't load successfully.\n\nExiting program...\n\nBye!");
	}
}

void display_list(vector<Product>& products)
{
	cout << "PRODUCTS" << endl;

	cout << left << setw(5) << "#" << setw(45) << "Name" << setw(20) << "Price" << setw(25) << "Discount %" << setw(20) << "Your Price" << endl;

	for (int i = 0; i < products.size(); i++)
	{
		double your_price = products[i].str_price - (products[i].str_discount_percent / 100);

		string index = to_string(i + 1);
 
		cout << left << setw(5) << index << setw(45) << products[i].product_name << setw(20) << products[i].str_price << setw(25) <<
			products[i].str_discount_percent << setw(20) << your_price << endl; //change to your price
	}
	cout << endl;
}

void display_cart(vector<Product>& cart)
{
	double total_cart = calculate_cart(cart);

	cout << fixed << setprecision(2);

	cout << left << setw(5) << "#" << setw(45) << "Name" << setw(20) << "Your Price" << setw(25) << "Quantity" << setw(20) << "Total" << endl;

	for (int i = 0; i < cart.size(); i++)
	{
		string index = to_string(i + 1);

		double first_total = cart[i].str_price * cart[i].str_quantity;

		cout << left << setw(5) << index << setw(45) << cart[i].product_name << setw(20) << cart[i].str_price << setw(25) << cart[i].str_quantity << setw(20) << first_total 
			<< endl ; //possibly yikes
	}
	cout << left << setw(5) << "" << setw(45) << "" << setw(20) << "" << setw(25) << "" << setw(20) << total_cart
		<< endl;

}

void add_item(vector<Product>& products, vector<Product>& cart)
{ //make output file  - cart.txt
	Product temp;

	ofstream outfile;
	outfile.open("cart.txt");

	int number_input;
	int quantity_input;

	cout << "Product number: ";
	cin >> number_input;

	outfile << number_input;

	cout << "Quantity: "; 
	cin >> quantity_input; 

	cout << endl;

	outfile << quantity_input;

	temp = products[number_input - 1]; //gets the actual product

	temp.str_quantity = quantity_input;
	//pushback something

	cart.push_back(temp);

	outfile.close();
}

void remove_item(vector<Product>& cart)
{
	int user_input;

	ofstream outfile;
	outfile.open("cart.txt");

	cout << "Item number: ";
	cin >> user_input;

	if (user_input > 0 && user_input - 1 < cart.size())
	{
		cart.erase(cart.begin() + user_input - 1);
		cout << "Item was removed from cart." << endl << endl;
	}

	//have to update file 

	outfile.close();
}

double calculate_cart(vector<Product>& cart)
{
	double new_value = 0.0;

	for (int i = 0; i < cart.size(); i++)
	{

		double your_price = cart[i].str_price - (double)(cart[i].str_discount_percent / 100);

		double total_price = your_price * cart[i].str_quantity;

		new_value = new_value + total_price;
	}
	return new_value;
}