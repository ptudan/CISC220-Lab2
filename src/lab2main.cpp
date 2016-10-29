#include <time.h>
#include <stdlib.h>
#include <iostream>
//#include "storerecordlab2.hpp"
#include "lab2lottery.hpp"
using namespace std;

int main() {
	srand(time(NULL));
	Owner *me= makeOwner();
	int winners[3] = {0,0,0};
	getWinners (winners);
	for (int i = 0; i < 3; i++) {
		cout<<winners[i]<<' ';
	}
	cout<<' '<<endl;
	findWinners(me, winners);
	cout<< "won with 1 number: "<< me->totalWinners[0] << endl;
	cout<< "won with 2 numbers: " << me->totalWinners[1] << endl;
	cout<< "won with 3 numbers: " << me->totalWinners[2] << endl;
	cleanUp(me);
	//cout << x << endl;
	return 0;
} //main
