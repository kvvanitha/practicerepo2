#pragma once
#include<iostream>
using namespace std;

/// @brief 
class Customer {
private:
	string username;
public:
	Customer();
	Customer(string username);
	string getvalue(char* filename, string user);
	void setvalue(char* filename, char* tempfile, string proid, string updatevalue);
	
	void loginMenu();
	void login();
	void registerCustomer();
	void customerMenu();
	void displayItems();
	void addtocart(string proID,int quant);
	void removefromcart(string proId,int quant);
	void viewcart();
	void placeorder();

};