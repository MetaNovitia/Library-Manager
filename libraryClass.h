#ifndef LIBRARYCLASS_INCLUDED
#define LIBRARYCLASS_INCLUDED

// Library Management Program
// by : Meta Novitia

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class Library
{
private:

    int n;

    struct Book
    {
        string title;
        string author;
        int location;
        string yearPublished;

        Book *next;
        Book *loc;
    };

    Book* head;

public:

    Library();

    void insertBook(string, string, int, string);

    void deleteBook(string);

    void findBook(int);

    void sortBook(int);

    void importData(string);

    void exportData(string, string);

    void displayData();


};

Library::Library()
{
    head = nullptr;
    n=0;
}

void Library::insertBook(string t, string a, int l, string yp)
{

    Book *newBook;
    Book *bookPtr;
    Book *previousBook;

    newBook = new Book;
    newBook->title = t;
    newBook->author = a;
    newBook->location = l;
    newBook->yearPublished = yp;
    newBook->next = nullptr;
    newBook->loc = nullptr;

    if(!head)
    {
        head = newBook;
    }
    else
    {
        bookPtr = head;
        previousBook = nullptr;
        while (bookPtr && bookPtr->location < l)
        {
            previousBook = bookPtr;
            bookPtr = bookPtr->next;
        }
        if(!bookPtr)
        {
            previousBook->next = newBook;
        }
        else if(bookPtr->location==l)
        {
            bool lessThan=true;
            while(bookPtr && lessThan)
            {
                bool check=false;
                if(bookPtr->title!=t)
                {
                    check=true;
                }
                else
                {
                    lessThan=false;
                }
                int sz = bookPtr->title.length();
                for(int i = 0; check && i<sz; i++)
                {
                    if(bookPtr->title[i]<t[i])
                    {
                        previousBook = bookPtr;
                        bookPtr = bookPtr->loc;
                        check=false;
                    }
                    else if(bookPtr->title[i]>t[i])
                    {
                        check=false;
                        lessThan=false;
                    }
                }

            }
            if(bookPtr==head)
            {
                head = newBook;
                newBook->next=bookPtr->next;
                newBook->loc=bookPtr;
                bookPtr->next=nullptr;
            }
            else if(!bookPtr)
            {
                previousBook->loc = newBook;
            }
            else if(previousBook->location!=bookPtr->location)
            {
                previousBook->next=newBook;
                newBook->next=bookPtr->next;
                newBook->loc=bookPtr;
                bookPtr->next=nullptr;
            }
            else
            {
                previousBook->loc = newBook;
                newBook->loc = bookPtr;
            }
        }
        else
        {
            head=newBook;
            newBook->next = bookPtr;
        }

    }

    n++;

}

void  Library::deleteBook(string t)
{
    Book *previousBook;
    Book *bookPtr;
    Book *previousDup;

    if (!head)
    {
        return;
    }
    if(head->title == t)
    {
        if(!head->loc)
        {
            bookPtr = head->next;
        }
        else
        {
            bookPtr = head->loc;
            bookPtr->next = head->next;
        }
        delete head;
        head = bookPtr;
    }
    else
    {
        previousBook = nullptr;
        previousDup = nullptr;
        bookPtr = head;
        bool found;
        bool inLoc;
        while(bookPtr!=nullptr && !found)
        {
            while(bookPtr!=nullptr && !found)
            {
                if(bookPtr->title==t)
                {
                    if(inLoc)
                    {
                        previousDup->loc = bookPtr->loc;
                    }
                    else
                    {
                        if(bookPtr->loc)
                        {
                            previousBook->next = bookPtr->loc;
                            (bookPtr->loc)->next = bookPtr->next;
                        }
                        else
                        {
                            previousBook->next = bookPtr->next;
                        }

                    }

                    delete bookPtr;
                    found = true;
                }
                previousDup=bookPtr;
                bookPtr = bookPtr->loc;
                inLoc = true;

            }
            if(previousBook)
            {
                previousBook = previousBook->next;
            }
            else
            {
                previousBook = head;
            }
            bookPtr = previousBook->next;
            inLoc=false;
        }
    }
}

void  Library::findBook(int l)
{
    Book *bookPtr;

    cout << "Shelf " << l << ":" << endl;

    if (!head)
    {
        cout << "No books in library";
    }
    else
    {
        bookPtr = head;
        while (bookPtr && bookPtr->location!=l)
        {
            bookPtr = bookPtr->next;
        }
        if(!bookPtr)
        {
            cout << "No books in location";
        }
        else
        {
            while (bookPtr)
            {
                cout << "   >\"" << bookPtr->title << "\" by " << bookPtr->author << ", " << bookPtr->yearPublished << endl;
                bookPtr = bookPtr->loc;
            }
        }
    }

}

void  Library::sortBook(int t)
{
    ofstream outFile;
    outFile.open("sortedLibrary.txt");

    string arr[n][4];
    int i=-1;
    Book *bookPtr;
    Book *dupPtr;

    if(!head)
    {
        return;
    }
    else
    {
        bookPtr = head;
        dupPtr = head;
        while(bookPtr!=nullptr)
        {
            while(dupPtr!=nullptr)
            {
                i++;
                arr[i][0]=dupPtr->title;
                arr[i][1]=dupPtr->author;
                arr[i][3]=dupPtr->location;
                arr[i][2]=dupPtr->yearPublished;

                dupPtr = dupPtr->loc;
            }
            bookPtr = bookPtr->next;
            dupPtr = bookPtr;
        }
    }

    bool switched, check;
    string temp;

    do
    {
        switched = false;
        for(int x=1; x<n ; x++)
        {
            check=true;
            if(arr[x-1][t-1] == arr[x][t-1])
            {
                check = false;
            }
            for(int y=0; check; y++)
            {
                if((arr[x-1][t-1])[y] > (arr[x][t-1])[y])
                {
                    for(int ch = 0; ch<4 ; ch++)
                    {
                        temp = arr[x-1][ch];
                        arr[x-1][ch] = arr[x][ch];
                        arr[x][ch] = temp;

                    }

                    switched = true;

                    check = false;
                }
                else if((arr[x-1][t-1])[y] < (arr[x][t-1])[y])
                {
                    check = false;
                }
            }
        }

    }while(switched);

    for(int x=0; x<n; x++)
    {
        outFile << "   >\"" << arr[x][0] << "\" by " << arr[x][1] << ", " << arr[x][2] << ".  Shelf: " << arr[x][2] << endl;
    }

}

void  Library::importData(string filename)
{
    ifstream inFile;

    inFile.open(filename);

    if(!inFile)
    {
        cout << "File not found";
        return;
    }
    else
    {
        string t, a, ls, yp;
        int l;
        getline(inFile, t);
        getline(inFile, a);
        getline(inFile, ls);
        getline(inFile, yp);
        while (inFile)
        {
            l=stoi(ls);

            insertBook(t,a,l,yp);

            getline(inFile, t);
            getline(inFile, a);
            getline(inFile, ls);
            getline(inFile, yp);
        }


    }
}

void  Library::exportData(string filename, string opt)
{
    ofstream outFile;
    ifstream tryFile;
    tryFile.open(filename);

    if(tryFile && opt=="in")
    {
        string a;
        cout << "File already exists! Overwrite data? (yes/no)";
        cin >> a;
        if(a!="yes")
        {
            return;
        }
    }
    outFile.open(filename);
    Book *bookPtr;
    Book *dupPtr;

    if(!head)
    {
        return;
    }
    else
    {
        bookPtr = head;
        dupPtr = head;
        while(bookPtr!=nullptr)
        {
            while(dupPtr!=nullptr)
            {
                outFile << dupPtr->title << "\n" << dupPtr->author << "\n" << dupPtr->location << "\n" << dupPtr->yearPublished << "\n";
                dupPtr = dupPtr->loc;
            }
            bookPtr = bookPtr->next;
            dupPtr = bookPtr;
        }
    }

}

void Library::displayData()
{
    Book *bookPtr;
    Book *dupPtr;

    if(!head)
    {
        return;
    }
    else
    {
        bookPtr = head;
        dupPtr = head;
        while(bookPtr!=nullptr)
        {
            cout << "Shelf " << dupPtr->location << ":" << endl;
            while(dupPtr!=nullptr)
            {
                cout << "   >\"" << dupPtr->title << "\" by " << dupPtr->author << ", " << dupPtr->yearPublished << endl;
                dupPtr = dupPtr->loc;
            }
            cout << endl;
            bookPtr = bookPtr->next;
            dupPtr = bookPtr;
        }
    }

}

#endif // LIBRARYCLASS_INCLUDED
