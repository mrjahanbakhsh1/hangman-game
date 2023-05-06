// My hangman game with link list
#include<iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime> // for make randome number and have diffrent every time
#include <cstring>
#include <set> // to store the entered value from cin
using namespace std;

// link list
struct node {
    string          data;
    struct node  *next;
}*start;
node *create_node(string myData)
{
    struct  node *n , *s;
    
    n = new(struct node); 
    if (n == NULL) {
        cout<<"not allocated "<<endl;
        return 0;
    }
    else {
        n->data = myData;
        n->next = NULL;  
		   
        return n;
    }
}

void insert_From_Start(string body)
{
    struct node *n, *p;
    string value = body;

    n = create_node(value);
    
    if (start == NULL) {
        start = n;
        start->next = NULL;          
    }else {
        p = start;
        start = n;

        start->next = p;
    }
}

string show() {
    struct node *t;
    if (start == NULL) {
        return "NULL";
    }

    t = start;
    string man;
	while (t != NULL) {
        man += t->data;
        t = t->next;
    }
    return man;
}

void insert_From_Last(string body) {
    struct node *n, *s;
    string value = body;

    n = create_node(value);

	s = start;     
    while (s->next != NULL)
    {         
        s = s->next;        
    }

    n->next = NULL;
    s->next = n;
}

int main() {
    int x;
    start = NULL;
    set<char> enteredChars; // to store the entered value from cin
    insert_From_Start(" ");

    string body[6] = {"O\n","/", "|", "\\\n", "/ ", "\\\n"}; // an array for storing the body items
    
    string guessWord[4] = {"apple", "programming", "book",  "pencil"};
    int arraySize = sizeof(guessWord)/sizeof(string);

    // chose randome word from array
    srand(time(nullptr));
    int randNumber = rand() % arraySize;
    string randWord = guessWord[randNumber];

    int sizeWord = randWord.length(); // get the length of array
    int wrongGuess = 0;
    int rightGuess = 0;

    // give a difult value to an array with flexible size
    string* myWord = new string[sizeWord];
    for(int i =0; i <sizeWord ; i++) {
        myWord[i] = "_ ";
    }

    cout << "1. You can guess wrong for 6 times" << endl;
    cout << "2. Every time you can enter a special chracter" << endl;

    while(wrongGuess < 6 && rightGuess < sizeWord) {
        cout << "\nYour right Guess : " << rightGuess;
        cout << "\nYour lives : " << 6 - wrongGuess << endl;
        cout << "Guess this Word : ";
        for(int i =0; i <sizeWord ; i++) {
            cout << myWord[i] << " ";
        }
        
        cout << " : ";
        char userGuess;
        cin >> userGuess;

        if(enteredChars.count(userGuess) > 0) {
            cout << "*!You cannot enter a same character choose another character!*" << endl;
        }else {
            bool found = false; // for checking a character exist in string or not
            enteredChars.insert(userGuess); // insert the entered character to save it for next time checking

            for(int i = 0; i < sizeWord ; i++) {
                if(randWord[i] == userGuess) {
                    myWord[i] = userGuess;
                    rightGuess++;
                    found = true;
                }
            }

            // show the hangman
            if(found == false) {
                string bodyItem = body[wrongGuess];
                insert_From_Last(bodyItem);
                cout << " +----+" << endl;
                cout << " |" << endl;
                cout << show();
                cout << " \n======\n";
                wrongGuess++;
            }
        }
    }

    string userWord;

    for(int i = 0; i < sizeWord ; i++) {
        userWord += myWord[i];
    }

    if(wrongGuess == 6) {
        cout << "\nYou Lost The Game :(\n";
        cout << show();
    }else if(randWord == userWord) {
        cout << "\nCongratulations, you won :))\n";
    }


    cout << "\nResult => The word is : " << randWord << " and Your guess was : " << userWord;
    cout << endl << "Wrong Guess = "<< wrongGuess;
    getch();
    return 0;
}
// Created by Mohammad reza Jahanbakhsh :)