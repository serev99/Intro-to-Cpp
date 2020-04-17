//Assignment 2
//Diyang Zhang
//260796176


#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct ticket {
	unsigned int numbers[6];
	ticket* next;
};


class SuperDraw 
{
public:
	SuperDraw();
	SuperDraw(int numberOfTickets);
	~SuperDraw();
	SuperDraw(const SuperDraw &obj);
	void newTicket(int verbose=0);
	void printAllTicketNumbers();
	int verifySequence(unsigned int myNumbers[6]);
	void deleteSequence(unsigned int myNumebers[6]);
private:
	ticket* ticketListHead;
	ticket* ticketListTail;
};


//Q1: constructor
SuperDraw::SuperDraw()
{
    this->ticketListHead = NULL;
    this->ticketListTail = NULL;
}


//Q2: nerTicket
void SuperDraw::newTicket(int verbose)
{
	int tempArray[6];
	for (int i=0; i<6; i++) {
		tempArray[i] = rand()%49+1;
	}
	//BubbleSort
	for (int i=0; i<6; i++) {
		for (int j=0; j<5-i; j++) {
			if (tempArray[j] > tempArray[j+1]) {
				int t = tempArray[j];
				tempArray[j] = tempArray[j+1];
				tempArray[j+1] = t; 
			}
		}
	}
	//Update ticketList
	ticket* new_tk = (struct ticket*) malloc(sizeof(struct ticket));
	for (int i=0; i<6; i++) {
	    new_tk->numbers[i] = tempArray[i];
	}
	new_tk->next = NULL;
	if (ticketListHead==NULL) {
		ticketListHead = new_tk;
		ticketListTail = new_tk;
	} else if (ticketListHead->next==NULL) {
		ticketListHead->next = new_tk;
		ticketListTail = new_tk;
	} else {
		ticketListTail->next = new_tk;
		ticketListTail = new_tk;
	}
	//print message (or not)
    if (verbose==1) {
		cout << "A new ticket was successfully generated. The numebers are: ";
		for (int i=0; i<6; i++) {
			if (i!=5) {
				cout << tempArray[i] << ", ";	
			} else {
				cout << tempArray[i] << endl;
			}
		}
	}
}


//Q3: constructor(number of tickets)
SuperDraw::SuperDraw(int numberOfTickets)
{
    this->ticketListHead = NULL;
    this->ticketListTail = NULL;
    for (int i=0; i<numberOfTickets; i++) {
    	newTicket(0);
    }
    cout << numberOfTickets << " new ticket were successfully generated." << endl;
    cout << "The numbers are: ";
    ticket* ptr = ticketListHead;
    while (ptr != NULL) {
    	for (int i=0; i<6; i++) {
    		if (i!=5) {
    			cout << ptr->numbers[i] << ", ";
    		} else {
    			cout << ptr->numbers[i] << " ";
    		}
    	}
    	ptr = ptr->next;
    	if (ptr!=NULL) {
    		cout << "and ";
    	} else {
    		cout << endl;
    	}
    }
}


//Q4: printAllTicketNumbers
void SuperDraw::printAllTicketNumbers() {
	int count = 0;
	ticket* ptrA = ticketListHead;
    while (ptrA != NULL) {
    	count++;
    	ptrA = ptrA->next;
    }
    cout << "We found " << count << " generated tickets:" << endl;
    ticket* ptrB = ticketListHead;
    while (ptrB != NULL) {
    	for (int i=0; i<6; i++) {
    		if (i!=5) {
    			cout << ptrB->numbers[i] << ", ";
    		} else {
    			cout << ptrB->numbers[i] << endl;
    		}
    	}
    	ptrB = ptrB->next;
    }
}


//Q5: verifySequence()
// !!! IMPORTANT: Please use UNSIGNED INT sequence when check this question,
//                as you provide UNSIGNED INT sequence NUMBERS[6] in your STRUCT: TICKET
int SuperDraw::verifySequence(unsigned int myNumbers[6]) {
	//sort
	for (int i=0; i<6; i++) {
		for (int j=0; j<5-i; j++) {
			if (myNumbers[j] > myNumbers[j+1]) {
				int t = myNumbers[j];
				myNumbers[j] = myNumbers[j+1];
				myNumbers[j+1] = t; 
			}
		}
	}
	//check
	int count = 0;
	ticket* ptr = ticketListHead;
    while (ptr != NULL) {
    	count++;
    	int temp = 0;
    	for (int i=0; i<6; i++) {
    		if (ptr->numbers[i]==myNumbers[i]) {
    			temp++;
    		}
    	}
    	if (temp==6) {
    		cout << "The provided sequence of numbers was already generated" << endl;
    		return count;
    	}
    	ptr = ptr->next;
    }
    cout << "The provided sequence of numbers was never generated before" << endl;
    return 0;
}


//Q6: deleteSequence
// !!! IMPORTANT: Please use UNSIGNED INT sequence when check this question,
//                as you provide UNSIGNED INT sequence NUMBERS[6] in your STRUCT: TICKET
void SuperDraw::deleteSequence(unsigned int myNumebers[6]) {
	int index = verifySequence(myNumebers);
	if (index==0) {
		cout << "The provided sequence of numbers was never generated before";
		return;
	}

	int count = 0;
	ticket* ptr = ticketListHead;
    //CASE: only 1 ticket && need to remove
    if (ptr==ticketListTail && index==1) {
    	ptr = NULL;
    	ticketListTail = NULL;
    	free(ptr);
    	cout << "The provided sequence of numbers was successfully deleted" << endl;
    	return;
    }
    //CASE: more than 1 ticket && remove first
    if (index==1) {
    	ticketListHead = ptr->next;
    	free(ptr);
    	cout << "The provided sequence of numbers was successfully deleted" << endl;
    	return;
    }
    //CASE: OHTERWISE (2 conditions)
    ticket* prev = NULL;
    while (ptr != NULL && count!=index-1) {
    	count++;
    	if (count==index-1) {
    		prev = ptr;
    	}
    	ptr = ptr->next;
    }
    prev->next = ptr->next;
    free(ptr);
    cout << "The provided sequence of numbers was successfully deleted" << endl;
    return;
}


//Q7: DESTRUCTOR
SuperDraw::~SuperDraw() {
	ticket* ptr = ticketListHead;
	while (ptr != NULL) {
		struct ticket* nextTicket = ptr->next;
		delete[] ptr;
		ptr = nextTicket;
	}
}


//Q8: COPY CONSTRUCTOR
SuperDraw::SuperDraw(const SuperDraw &obj) {
    ticket* curr = obj.ticketListHead;
    ticket* prev = NULL;
    ticketListHead = new ticket;
    while(curr != NULL) {
        ticket* new_tk = new ticket;
        for(int i=0; i<6; i++) {
            new_tk->numbers[i] = curr->numbers[i];
        }
        if(curr==obj.ticketListHead) {
            ticketListHead = new_tk;
        } 
        if(curr == obj.ticketListTail) {
            ticketListTail = new_tk;
        }
        if(prev != NULL) {
            prev->next = new_tk;
        }
        prev = new_tk;
        curr = curr->next;
    }
}

int main()
{
    srand(time(NULL));
    
    //Q2   
    //SuperDraw sd;
    //sd.newTicket(1);
    
    //Q3
    //SuperDraw sd(2);
    
    //Q4
    //SuperDraw sd;
    //sd.newTicket();
    //sd.newTicket();
    //sd.newTicket();
    //sd.newTicket();
    //sd.printAllTicketNumbers();
    
    //Q5
    //SuperDraw sd;
    //sd.newTicket();
    //sd.newTicket();
    //sd.newTicket();
    //sd.newTicket();
    //sd.printAllTicketNumbers();
    //unsigned int myNumbers[6] = {7,18,19,21,22,23};
    //sd.verifySequence(myNumbers);
    
    //Q6
    //SuperDraw sd;
    //sd.newTicket();
    //sd.newTicket();
    //sd.newTicket();
    //sd.newTicket();
    //sd.printAllTicketNumbers();
    //unsigned int myNumbers[6] = {7,18,19,21,22,23};
    //sd.deleteSequence(myNumbers);
    //sd.printAllTicketNumbers();
    
    //Q8
    SuperDraw sd;
    sd.newTicket();
    sd.newTicket();
    sd.newTicket();
    SuperDraw sd2(sd);
    sd2.printAllTicketNumbers();
}