// Library Management Program
// by: Meta Novitia

#include <iostream>
#include <fstream>
#include <string>

#include "libraryClass.h"
#include "dataLog.h"


using namespace std;

//function prototypes

int directory();

string getTitle();

string getAuthorLastName();

string getLocation();

string getYearPublished();

string getSortType();

string getFilename();

int main()
{

    string name, alter;
    int n;

    //records data of who recently logged in

    cout << "Name: ";
    getline(cin, name);
    User u(name);

    //create library class

    Library lib;

    lib.importData("libraryData.txt");

    do
    {
        //show directory

        n = directory();

        //performs action according to choice

        alter = "";

        cout << endl;

        if(n==1)
        {
            alter = getTitle();
            lib.insertBook(alter, getAuthorLastName(), stoi(getLocation()), getYearPublished());
        }

        if(n==2)
        {
            alter = getTitle();
            lib.deleteBook(alter);
        }

        if(n==3)
        {
            alter = getLocation();
            lib.findBook(stoi(alter));
        }

        if(n==4)
        {
            alter = getSortType();

            lib.sortBook(stoi(alter));
        }

        if(n==5)
        {
            alter = getFilename();
            lib.importData(alter);
        }

        if(n==6)
        {
            alter = getFilename();
            lib.exportData(alter, "in");
        }

        if(n==7)
        {
            alter = "";
            lib.displayData();
        }

        if(n==8)
        {
            alter = "";
            u.displayLog();
        }

    u.recordAction(n, alter);

    }while(n != 9);          //if user chooses 9 (exit), then stop loop

    lib.exportData("libraryData.txt", "out");

    u.recordLog();           //record user's log into a file as program ends

    return 0;
}

int directory()
{
    int n;

    cout << "\n1.  Add a new book\n2.  Delete a book\n3.  Find book by location\n4.  Sort Library\n5.  Import Data";
    cout << "\n6.  Export Data\n7.  Display Current Library\n8.  Check Log\n9.  Exit" << endl;
    cout << "Please enter a number: ";
    cin >> n;

    //validate

    while( n<1 || n>9 )
    {
        cout << "Please enter a valid number: ";
        cin >> n;
    }

    return n;
}

string getTitle()
{
    cin.ignore();

    string title;

    cout << "Please enter book title: ";
    getline(cin, title);

    return title;
}

string getAuthorLastName()
{
    string author;

    cout << "Please enter book author's last name: ";
    cin >> author;

    return author;
}

string getLocation()
{
    string location;

    cout << "Please enter location: ";
    cin >> location;

    return location;
}

string getYearPublished()
{
    string yearPublished;

    cout << "Please enter year published: ";
    cin >> yearPublished;
    while(yearPublished.length()!=4)
    {
        cout << "Please enter 4 digits for year: ";
        cin >> yearPublished;
    }

    return yearPublished;
}

string getSortType()
{
    string n;

    cout << "Sort by:\n1. Title\n2. Author\n3. Year Published" << endl;
    cout << "Please enter a number: ";
    cin >> n;

    //validate

    while(n!="1" && n!="2" && n!="3")
    {
        cout << "Please enter a valid number: " << endl;
        cin >> n;
    }

    return n;
}

string getFilename()
{
    string filename;

    cout << "Please enter filename: ";
    cin >> filename;

    return filename;
}
