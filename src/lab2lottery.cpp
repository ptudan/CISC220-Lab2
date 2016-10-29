//Lab 2 - Dalton Ashley and Paul Tudan
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "lab2lottery.hpp"
using namespace std;

Owner *makeOwner(){
	/*
		Owner *makeOwner()
	 	-no parameters
	 	-returns an owner pointer with a newly created owner pointing to it
	 	-initiates a number of stores from 1-10
	 	-creates correct num of stores (described in makeStore())
	 	-finds determines total num of tickets sold of all owned stores for totalSold
	*/
	Owner *newOwner;
	newOwner = new Owner;
	newOwner->numStores = rand()%10 +1;
	newOwner->storeList = new Store[newOwner->numStores];
	newOwner->totalWinners[0] = 0;
	newOwner->totalWinners[1] = 0;//asf
	newOwner->totalWinners[2] = 0;
	newOwner->totalSold = 0;
	for(int i = 0; i<newOwner->numStores; i++){
		newOwner->storeList[i] = makeStore();//initializes stores
	}//for
	
	for(int i = 0; i<newOwner->numStores; i++){
		newOwner->totalSold += newOwner->storeList[i].numSold;//counts tix sold
	}//for
	
	return newOwner;
	
}//makeOwner

Store makeStore(){
	/*
		Store makeStore()
		-no parameters
		-returns a Store struct
		-sets id to random int from 1-100
		-sets num of customers to rand int from 1-10
		-creates correct num of customers using makeCustomer()
		-counts tickets sold from customers
	*/
	Store newStore;
	newStore.id = rand()%100 +1;
	newStore.numCustomers = rand()%10 +1;
	newStore.customerList = new Customer[newStore.numCustomers];
	newStore.numSold = 0;
	for(int i = 0; i<newStore.numCustomers; i++){
		newStore.customerList[i] = makeCustomer();//intializes customers
	}//for
	
	for(int i = 0; i<newStore.numCustomers; i++){
		newStore.numSold += newStore.customerList[i].numTickets;//counts tix
	}//for
	return newStore;
}//makeStore

Customer makeCustomer(){
	/*
		Customer makeCustomer()
		-no paramters
		-returns a Customer struct
		-sets id to rand int 1-1000
		-sets numTickets (tickets bought) to rand int 1-20
		-creates correct num of tickets with three unique, random digits 0-9
	*/
	Customer newCustomer;
	newCustomer.id = rand()%1000 +1;
	newCustomer.numTickets = rand()%20 + 1;
	
	newCustomer.lotteryNums= new int *[newCustomer.numTickets];//create ticket array
	
	for(int i = 0; i<newCustomer.numTickets; i++){//creates tickets
		newCustomer.lotteryNums[i] = new int[3];
		int a = rand()%10;
		int b = rand()%10;//temporary variables because typing pointers is a PITA
		int c = rand()%10;
		while((a==b) || (a==c) || (b==c)){
			a = rand()%10;
			b = rand()%10; //assures that each lotto digit isn't repeated
			c = rand()%10;
		}//while
		newCustomer.lotteryNums[i][0] = a;
		newCustomer.lotteryNums[i][1] = b;
		newCustomer.lotteryNums[i][2] = c;
	}//for
	
	return newCustomer;
}//makeCustomer

void getWinners(int arr[]){
	/*
	 	 void getWinners()
	 	 Parameters:
	 	 	 int arr[]: empty int array of length 3 from an owner struct
	 	 -fills arr[] with three unique digits 0-9 to represent winning lotto nums
	*/
	while((arr[0]==arr[1]) || (arr[0]==arr[2]) || (arr[1]==arr[2])){//assures uniqueness
		for(int i = 0; i<3; i++){
			arr[i] = rand()%10;
		}//for
	}//while
}//getWinners

int checkWin(int check[], int win[]){
	/*
	 	 int checkWin()
	 	 Parameters:
	 	 	 int check[]:int array of length 3 from customer struct, ticket to be checked
	 	 	 int win[]: int array of length 3 from main function, winning nums to check against
	 	 -returns the amount of digits matching on tickets check[] and win[]
	*/
	int count = 0;
	for(int i = 0; i<3; i++){
		count += check[i]==win[i];
	}//for
	return count;
}//checkWin

void findWinners(Owner *o, int win[]){
	/*
	 	 void findWinners()
	 	 Parameters:
	 	 	 Owner *o: pointer to an owner struct, which holds all neccessary variables
	 	 	 win[]: int array of length 3 from main function, holds winning numbers
	 	 -iterates through all tickers of all customers at all stores of given owner arguement
	 	 -prints the winning lotto numbers
	 	 -prints the total tickets sold
	 	 -prints the win value of each ticket purchased
	 	 -prints the number of winners of each amount at each store, also tickets purchased there
	 	 -calculates values of totalWinners of each amount (ie 1, 2 or 3 right)
	*/
	cout<<"There were "<<o->totalSold<<" tickets sold in all stores"<<endl;//prints total sold
	cout<<"The winning numbers are: "<<win[0]<<" "<<win[1]<<" "<<win[2]<<endl;//prints win nums
	
	int winCount = 0;
	for(int i = 0; i < o->numStores; i++){//iterates stores
		cout<<"Store ID: "<<o->storeList[i].id<<endl;//prints store id
		int oneCount = 0;
		int twoCount = 0;
		int threeCount = 0;
		for(int j = 0; j < o->storeList[i].numCustomers; j++){//iterates customers
			cout<<"\t Customer ID: "<<o->storeList[i].customerList[j].id<<endl;//prints customer id
			for(int k = 0; k < o->storeList[i].customerList[j].numTickets; k++){//iterates tickets
				int numCorrect = checkWin(o->storeList[i].customerList[j].lotteryNums[k], win);
				if(numCorrect==1){
					o->totalWinners[0]+=1;
					oneCount+=1;
					winCount+=1;
				}//if
				else if(numCorrect==2){
					o->totalWinners[1]+=1;
					twoCount +=1;
					winCount+=1;
				}//else if
				else if(numCorrect==3){
					o->totalWinners[2]+=1;
					threeCount +=1;
					winCount+=1;
				}//else if
				cout<<"\t \t ticket: "<< o->storeList[i].customerList[j].lotteryNums[k][0]<<' ';
				cout<<o->storeList[i].customerList[j].lotteryNums[k][1]<<' ';//prints tickets
				cout<<o->storeList[i].customerList[j].lotteryNums[k][2]<<" matched: "<<numCorrect<<endl;
			}//for
		}//for
		cout<<"1 Correct: "<<oneCount<<" | 2 Correct: "<<twoCount<<" | 3 Correct:"<<' ';
		cout<<threeCount<<" out of: "<<o->storeList[i].numSold<<endl;
		
	}//for
}//findWinners

void cleanUp(Owner* o){
	/*
		void cleanUp()
		Parameters:
			Owner* o: owner struct containing all needed variables
		-deletes all variables created on the heap during construction of given owner arg
			-lotto tickets for each customer
			-owner pointer itself
		-the rest was created on the stack and is thus is not needing deletion
		
	*/
	cout<<"Deleting owner..."<<endl;
	for(int i = 0; i<o->numStores; i++){
		for(int j = 0; j<o->storeList[i].numCustomers; j++){
			for(int k = 0; k<o->storeList[i].customerList[j].numTickets; k++){
				delete o->storeList[i].customerList[j].lotteryNums[k];
			}//for
		}//for
	}//for
	delete o;
}//cleanUp
