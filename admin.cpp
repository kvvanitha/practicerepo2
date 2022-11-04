#include<iostream>
#include<fstream>
#include<string>
#include"admin.h"
using namespace std;

string Admin::getvalue(char* filename, string user) {

    system("cls");
    int pos;
    string key;
    string val_str;

    ifstream f1(filename);
    string line;
    while (getline(f1, line)) {
        pos = line.find(" ");
        key = line.substr(0, pos);
        val_str = line.substr(pos + 1);
        if (key == user) {

            f1.close();
            return val_str;
        }

    }
    return "-1";

}

void Admin::setvalue(char* filename, char* tempfile, string proid, string updatevalue) {

    int pos;
    string key;
    string val_str;
    int value;

    //open file in read mode
    ifstream f1(filename);
    string line;

    //Temporary file with .tmp extension to copy and modify content
    //from original file
    ofstream fout(tempfile);

    while (getline(f1, line)) {
        pos = line.find(" ");//finding space

        key = line.substr(0, pos);//get username

        val_str = line.substr(pos + 1);//get value


        if (key == proid) {
            val_str = updatevalue;//add value to deposit
        }
        fout << key << ' ' << val_str << endl;//write the same in temporary file

    }


    f1.close();
    fout.close();
    remove(filename);//remove original file
    rename(tempfile, filename); //rename temporary file to original 

}


void Admin::Adminmenu() {
   
        cout << "Welcome\n";
        do{
        int ch;
        cout << "\n\n1.Add New Product\n2.Remove Product\n3.Modify\n4.Discount\n5.Exit\n";
        cin >> ch;
        if (ch == 1) {
            this->AddProduct();
        }
        else if (ch == 2) {
            this->RemoveProduct();
        }
        else if (ch == 3) {
            this->modify();
        }
        else if (ch == 4) {
            this->Discount();
        }
        else if (ch == 5) {
            system("cls");
            return;
        }
        else {
            cout << "Enter correct choice" << endl;
        }
    } while (1);
    
}
void Admin::login() {
    cout << " Enter User name\n";
    string uname;
    cin >> uname;
    cout << " Enter Pasword\n";
    string password;
    cin >> password;


    if (uname == this->AdminuserName && password == this->AdminPassword) {

        cout << " Login Successfully\n";
        Admin ad;
        ad.Adminmenu();
    }
    else {
        cout << " Error!\n";
    }
}

void Admin::AddProduct() {

    cout << "\nPlease Enter The Product ID of The Product ";
    string ProId;
    cin >> ProId;


    ifstream check;
    check.open("proName.txt");
    string key;

    while (check >> key) {
        if (ProId == key) {
            cout << "ProId already exist" << endl;
            return;
        }
    }
    check.close();
    cout << "\n\nPlease Enter The Name of The Product ";
    string ProductName;
    cin >> ProductName;

    ofstream newPro;
    newPro.open("proName.txt", ios::app);

    newPro << ProId << ' ' << ProductName << endl;

    newPro.close();
    
    cout << "\nPlease Enter The Price of The " <<ProductName<<endl;
    string price;
    cin >> price;
    ofstream newPrice;
    newPrice.open("proPrice.txt", ios::app);
    newPrice << ProId << ' ' << price << endl;
    newPrice.close();

    cout << "\nPlease Enter The Quantity of " << ProductName << endl;
    string quant;
    cin >> quant;
    ofstream newQuant;
    newQuant.open("proQuant.txt", ios::app);
    newQuant << ProId << ' ' << quant << endl;
    newQuant.close();


    cout << "Product added successfully " << endl;
    Adminmenu();

}




//***************************************************************
// function to delete record of file
//****************************************************************

void Admin::removepro(char* filename, char* tempfile, string proid) {
    int pos;
    string key;
    string val_str;
    int value;

    //open file in read mode
    ifstream f1(filename);
    string line;

    //Temporary file with .tmp extension to copy and modify content
    //from original file
    ofstream fout(tempfile);

    while (getline(f1, line)) {
        pos = line.find(" ");//finding space

        key = line.substr(0, pos);//get username

        val_str = line.substr(pos + 1);//get value


        if (key == proid) {
            continue;//skip the matching string
        }
        fout << key << ' ' << val_str << endl;//write the same in temporary file

    }


    f1.close();
    fout.close();
    remove(filename);//remove original file
    rename(tempfile, filename); //rename temporary file to original 
}





void Admin :: RemoveProduct()
{
    int no;

    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The product no. of The Product You Want To Delete"<<endl;
    string proId;
    cin >> proId;

    ifstream check;
    string key;
    check.open("proName.txt");
    bool flag = false;

    while (check >> key) {
        if (proId == key) {
            flag = true;
        }
    }
    check.close();
    if (!flag) {
        cout << "ProId does not exist" << endl;
        Adminmenu();
        return;
    }
    char filename[30] = "proName.txt";
    char tempfile[30] = "proName.tmp";
    removepro(filename, tempfile, proId);
    
    char filename2[30] = "proPrice.txt";
    char tempfile2[30] = "proPrice.tmp";
    removepro(filename2, tempfile2, proId);

    char filename3[30] = "proQuant.txt";
    char tempfile3[30] = "proQuant.tmp";
    removepro(filename3, tempfile3, proId);

    cout << "product is removed successfully" << endl;
    
}


//***************************************************************
// function to modify record of file
//****************************************************************

void Admin::modify() {
    system("cls");
    cout << "Enter ProId of the product you want to modify: " << endl;
    string proId;
    cin >> proId;
    ifstream check;
    string key;
    string val_str;
    string productname;
    check.open("proName.txt");
    bool flag = false;

    while (check >> key>>val_str) {
        if (proId == key) {
            productname = val_str;
            flag = true;
        }
    }
    check.close();
    
    if (!flag) {
        cout << "Product not present kindly enter correct ID" << endl;
        Adminmenu();
        return;
    }

    cout << "Enter your choice:" << endl;
    cout << "1. Add Quantity " << endl;
    cout << "2. Decrease Quantity" << endl;
    cout << "3.Change Price" << endl;
    int choice;
    cin >> choice;
    
    char filename[30] = "proQuant.txt";
    char filename1[30] = "proPrice.txt";

    char tempfile[30] = "proQuant.tmp";
    char tempfile1[30] = "proPrice.tmp";


    string quant = getvalue(filename, proId);
    string price = getvalue(filename, proId);
    int quantInt = stoi(quant);

    if (choice == 1) {
        cout << "Enter number of items you want to add: " << endl;
        int value;
        cin >> value;
        value += quantInt;
        string val_str = to_string(value);
        setvalue(filename, tempfile, proId, val_str);
        cout << "Quantity added successfully" << endl;
        cout << "The Updated Quantity for " << productname<<" is " << value << endl;
    }
    else if (choice == 2) {
        cout << "Enter number of items you want to decrease: " << endl;
        int value;
        cin >> value;
        if (value > quantInt) {
            cout << "There are less than " << value << " items in the inventory" << endl;
            return;
        }
        else {
            quantInt-= value;
            string val_str = to_string(quantInt);
            setvalue(filename, tempfile, proId, val_str);
            cout << "Quantity decreased from the inventory " << endl;
            cout << "The Remaining Quantity for " << productname << " is " << quantInt << endl;
        }
    }
    else if (choice == 3) {
        cout << "Enter the updated price " << endl;
        int upPrice;
        cin >> upPrice;
        string val_s = to_string(upPrice);
        setvalue(filename1, tempfile1, proId, val_s);
        cout << "Price of "<<productname<<"  updated successfuly " << endl;
    }
    else {
        cout << "Enter a valid choice " << endl;
    }


}


void Admin::Discount() {
    cout << "Enter the product id of Product you want to add discount to" << endl;
    string proId;
    cin >> proId;
    
    
    ifstream check;
    string key;
    check.open("proName.txt");
    bool flag = false;

    while (check >> key) {
        if (proId == key) {
            flag = true;
        }
    }
    check.close();

    if (!flag) {
        cout << "Product not present kindly enter correct ID" << endl;
        Adminmenu();
        return;
    }

    cout << "Enter Percentage of discount you want to give on product " << endl;
    string discount;
    cin >> discount;

    char filename[30] = "proDiscount.txt";
    char tempfile[30] = "proDiscount.tmp";
    string price = getvalue(filename, proId);

    if (price == "-1") {
        ofstream disc;
        disc.open(filename, ios::app);
        disc << proId << ' ' << discount;
    }
    else {
        setvalue(filename, tempfile, proId, discount);
    }
}

