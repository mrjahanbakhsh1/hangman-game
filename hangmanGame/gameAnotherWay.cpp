#include<iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime> // for make randome number and have diffrent every time
#include <cstring>
#include <set> // to store the entered value from cin
using namespace std;

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
        // cout<<"Empty"<<endl;
        return "NULL";
    }

    t = start;
    string man;
	while (t != NULL) {
        // cout << t->data;
        man += t->data;
        t = t->next;
    }
    return man;
    // cout<<"NULL"<<endl;
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
    start=NULL;
    set<char> enteredChars;
    insert_From_Start(" ");

    string body[6] = {"O\n","/", "|", "\\\n", "/ ", "\\\n"};
    
    string guessWord[3] = {"appel", "book", "pencile"};
    int arraySize = sizeof(guessWord)/sizeof(string);

    srand(time(nullptr));
    int randNumber = rand() % arraySize;
    string randWord = guessWord[randNumber];

    int sizeWord = randWord.length();
    int wrongGuess = 0;
    int rightGuess = 0;

    string* myWord = new string[sizeWord];
    for(int i =0; i <sizeWord ; i++) {
        myWord[i] = "_ ";
    }

    cout << "1. You can guess wrong for 6 times" << endl;
    cout << "2. Every time you can enter a special chracter" << endl;

    while(wrongGuess < 6 && rightGuess < sizeWord) {
        cout << "\nYour lives : " << 6 - wrongGuess << endl;
        cout << "Your right Guess : " << rightGuess << endl;
        cout << "Guess this Word : ";
        for(int i =0; i <sizeWord ; i++) {
            cout << myWord[i] << " ";
        }

        cout << " : ";
        char userGuess;
        cin >> userGuess;

        if(enteredChars.count(userGuess) > 0) {
            cout << "YOU ALREADY ENTERD" << endl;
        }else {
            bool found = false;
            enteredChars.insert(userGuess);
            size_t charPos = randWord.find(userGuess);

            if (charPos != string::npos) {
                while (charPos != string::npos) {
                    myWord[charPos] = userGuess;
                    charPos = randWord.find(userGuess, charPos + 1);
                    rightGuess++;
                }
            }else {
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

    if(wrongGuess == 6) {
        cout << " +----+" << endl;
        cout << " |" << endl;
        cout << show();
        cout << " \n======\n";
        cout << "\nYou Lost The Game";
    }

    string userWord;
    for(int i =0; i <sizeWord ; i++) {
        userWord += myWord[i] + " ";
    }

    cout << "\nresulte => The word is : " << randWord << " Your guess was : " << userWord;
    cout << endl << "wrongGuess = "<< wrongGuess;
    getch();
    return 0;
}