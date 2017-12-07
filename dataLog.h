#ifndef DATALOG_H_INCLUDED
#define DATALOG_H_INCLUDED

// Library Management Program
// by : Meta Novitia

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class User
{
private:
    string name;
    vector<int> action;
    vector<string> alteration;

public:

    User(string);

    void recordAction(int, string);

    void recordLog();

    void displayLog();


};

User::User(string n)
    {
        name = n;
    }

void User::recordAction(int a, string alter)
    {
        action.push_back(a);
        alteration.push_back(alter);
    }

void User::recordLog()
    {
        ofstream outFile;
        outFile.open("libraryLog.txt");

        outFile << "Last login: " << name << endl;

        for(int i=0; i<action.size(); i++)
        {

            cout << "  ";

            if(action.at(i)==1)
            {
                outFile << "1.  Add a new book : ";
            }
            else if(action.at(i)==2)
            {
                outFile << "2.  Delete a book : ";
            }
            else if(action.at(i)==3)
            {
                outFile << "3.  Find book by location : ";
            }
            else if(action.at(i)==4)
            {
                outFile << "4.  Sort Library : ";
            }
            else if(action.at(i)==5)
            {
                outFile << "5.  Import Data : ";
            }
            else if(action.at(i)==6)
            {
                outFile << "6.  Export Data : ";
            }
            else if(action.at(i)==7)
            {
                outFile << "7.  Display Current Library";
            }
            else if(action.at(i)==8)
            {
                outFile << "8.  Check Log";
            }
            else
            {
                outFile << "9.  Exit";
            }

            outFile << alteration.at(i) << endl;

        }



        outFile.close();
    }

void User::displayLog()
    {
        ifstream inFile;
        inFile.open("libraryLog.txt");

        if(inFile)
        {
            string str;
            getline(inFile, str);

            while(inFile)
            {
                cout << str << endl;
                getline(inFile, str);
            }
        }
        else
        {
            cout << "No existing logs found" << endl;
        }

    }


#endif // DATALOG_H_INCLUDED
