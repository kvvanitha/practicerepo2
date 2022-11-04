#pragma once
#include<iostream>
#include<string>
include<conio.h>
using namespace std;

class Admin
{

private:
    string AdminuserName = "Admin@123";
    string AdminPassword = "1234567";
public:
    //this function is used to display the admin menu
    void Adminmenu();

    //this function is used for the admin login
    void login();
    string getvalue(char* filename, string user);
    void setvalue(char* filename, char* tempfile, string user, string updatevalue);
    
    void AddProduct();

    void removepro(char* filename, char* tempfile, string proid);
    void RemoveProduct();
    void Discount();
    void modify();

};
