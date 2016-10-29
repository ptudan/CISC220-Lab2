/*
 * lab2lottery.hpp
 *
 *  Created on: Sep 21, 2016
 *      Author: Paul
 */

#ifndef LAB2LOTTERY_HPP_
#define LAB2LOTTERY_HPP_

struct Customer{
	/*
		struct Customer
			int id: 1-1000, identification
			int numTickets: number of tickets purchased, 1-20
			int **lotteryNums: array of length numTickets that will hold int arr[3] lotto tix 
	*/
	int id;
	int numTickets;
	int **lotteryNums;
};//Customer

struct Store{
	/*
		struct Store
			int id: 1-100, identification
			int numCustomers: number of customers, 1-10
			Customer *customerList: Customer array of length numCustomers
			int numSold: hold total number of tickets purchased by all customers in customerList
			int numWinners: arr of length 3 holding number of winners of each val 1, 2 or 3 at store
	*/
	int id;
	int numCustomers;
	Customer *customerList;
	int numSold;
	int numWinnders[3];
};//Store

struct Owner{
	/*
		struct Owner
			Store *storeList: Store struct array of length numStores 
			int totalSold: holds total number of tickets sold across all customers at all stores
			int totalWinners: holds int array of length 3 of winners of each val 1, 2 or 3 at all stores
	*/
	Store *storeList;
	int numStores;
	int totalSold;
	int totalWinners[3];
};//Owner

Owner *makeOwner();
Store makeStore();
Customer makeCustomer();
void getWinners(int winners[]);
void findWinners(Owner *owner, int *ls);
int checkWin(int *nums, int *winners);
void cleanUp(Owner *owner);




#endif /* LAB2LOTTERY_HPP_ */
