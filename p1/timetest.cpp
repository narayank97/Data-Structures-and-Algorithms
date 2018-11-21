#include "CPUTimer.h"
#include "LinkedList.h"
#include "StackAr.h"
#include "CursorList.h"
#include "QueueAr.h"
#include "StackLi.h"
#include "vector.h"
#include "SkipList.h"
#include <iostream>
#include <fstream>
vector<CursorNode <int> > cursorSpace(2500001);

using namespace std;

int getChoice();
void displayMenu();
void RunList(char* filename);
void RunCursorList(char* filename);
void RunStackAr();
void RunStackLi();
void RunQueueAr(char* filename);
void RunSkipList(char* filename);

int getChoice() {
    int choice;

    while (1) {
        cout << "\tAdt Menu" << endl;
        cout << "0. Quit \n1. LinkedList \n2. CursorList \n3. StackAr \n4. StackLi \n5. QueueAr \n6. SkipList" << endl;

        cout << "Your choice "; cin >> choice;
        if (-1 < choice && choice < 7) {
            return choice;
        }
        else {
            cout << "\tAdt Menu" << endl <<cout;
            cout << "0. Quit \n1. LinkedList \n2. CursorList \n3. StackAr \n4. QueueAr \n6. SkipList" << endl;

            cout << "Your choice "; cin >> choice;
        }

    }

    return choice;
}

void RunList(char* filename) {
    List<int> list;
    ListItr<int> listitr = list.zeroth();

    char command;
    int value;
    ifstream inf(filename);
    inf.ignore(700,'\n'); // ignores 700 characters or all charcters until '\n'

    while (inf >> command >> value) {
        if (command == 'i') {
            list.insert(value, listitr);
        }
        else {
            list.remove(value);
        }
    }

}

void RunCursorList(char* filename) {

    CursorList<int> cursorlist(cursorSpace);
    CursorListItr<int> cursorlistitr = cursorlist.zeroth();

    char command;
    int value;
    ifstream inf(filename);
    inf.ignore(700, '\n');

    while (inf >> command >> value) {
        if (command == 'i') {
            cursorlist.insert(value, cursorlistitr);
        }
        else {
            cursorlist.remove(value);
        }
    }
}


void RunStackAr(char* filename) {
    StackAr<int> stack(2500000);

    char command;
    int value;
    ifstream inf(filename);
    inf.ignore(700, '\n');

    while (inf >> command >> value) {
        if (command == 'i') {
            stack.push(value);
        }
        else {
            stack.pop();
        }
    }
}

void RunStackLi(char* filename) {
    StackLi<int> StackLi;

    char command;
    int value;
    ifstream inf(filename);
    inf.ignore(700, '\n');

    while (inf >> command >> value) {
        if (command == 'i') {
            StackLi.push(value);
        }
        else {
            StackLi.pop();
        }
    }

}

void RunQueueAr(char* filename) {
    Queue<int> QueueArray(2500000);

    char command;
    int value;
    ifstream inf(filename);
    inf.ignore(700,'\n'); // ignores 700 characters or all charcters until '\n'
    while (inf >> command >> value) {
        if (command == 'i') {
            QueueArray.enqueue(value);
        }
        else {
            QueueArray.dequeue(); // acts as pop
        }
    }
}

void RunSkipList(char* filename) {
    SkipList<int> SkipLi(1, 2500000);

    char command;
    int value;
    ifstream inf(filename);
    inf.ignore(700,'\n'); // ignores 700 characters or all charcters until '\n'
    while (inf >> command >> value) {
        if (command == 'i') {
            SkipLi.insert(value);
        }
        else {
            SkipLi.deleteNode(value); // acts as pop
        }
    }
}

int main() {

    char filename[9];
    cout << "Filename >> ";
    cin >> filename;

    CPUTimer ct;
    int choice;
    do
    {
        choice = getChoice();
        ct.reset();
        switch (choice) {
            case 1: RunList(filename);
                break;
            case 2: RunCursorList(filename);
                break;
            case 3: RunStackAr(filename);
                break;
            case 4: RunStackLi(filename);
                break;
            case 5: RunQueueAr(filename);
                break;
            case 6: RunSkipList(filename);
                break;
            }
            cout << "CPU time: " << ct.cur_CPUTime() << endl;
        } while(choice > 0);

    return 0;
}
