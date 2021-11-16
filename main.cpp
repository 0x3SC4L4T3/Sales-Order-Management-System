#include <iostream>
#include <fstream>
#include "Customer.h"
#include "EODRecord.h"
#include "SalesOrder.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

/**
* Reason for using vectors : 
* The reason of using vectors is that we really don't need write our own insert, remove, search functions for array. All are already provided in vector.
* The second most important reason is that it is dynamic. So, whatever number of data is in file. It can be read in vector without any hesitation.
*/


//Invoice number that is being incremented automatically when an invoice is generated on express order or end of day sale.
static int invoice = 1000;

//This function performs the express Order shipping. A customers vector is passed by reference and salesOrder is passed.
void expressShip(vector<Customer>& customers, SalesOrder S) {
	for (int i = 0; i < customers.size(); i++) {
		if (customers.at(i).getCustomerNumber() == S.getCustomerNumber()) {
			cout << "OP: customer " << setfill('0') << setw(4) << customers.at(i).getCustomerNumber() << ": shipped quantity " << customers.at(i).getOrderQuantity() << endl;
			cout << "SC: customer " << setfill('0') << setw(4) << customers.at(i).getCustomerNumber() << ": invoice " << invoice++ << ": date " << S.getOrderDate() << ": quantity " << customers.at(i).getOrderQuantity() << endl;
			customers.at(i).setOrderQuantity(0);
		}
	}
}

// Whenever a new salesOrder is read from file, this function is being called. This function increase the orderquantity of that specific customer
// whose customer number present in the already read salesOrder. 
void updateQuantity(vector<Customer> &customerRecord, SalesOrder s) {
	for (int i = 0; i < customerRecord.size(); i++) {
		if (customerRecord.at(i).getCustomerNumber() == s.getCustomerNumber()) {
			if (s.getOrderType() == 'N') {
				customerRecord.at(i).incrementQuantity(s.getOrderQuantity());
				cout << "OP: customer " << setfill('0') << setw(4) << s.getCustomerNumber() << ": normal order: quantity " << s.getOrderQuantity() << endl;
			}
			else {
				customerRecord.at(i).incrementQuantity(s.getOrderQuantity());
				cout << "OP: customer " << setfill('0') << setw(4) << s.getCustomerNumber() << ": EXPRESS order: quantity " << s.getOrderQuantity() << endl;
				expressShip(customerRecord, s);
			}
			return;
		}
	}
}

// this function actually checks if the order in salesOrderRec vector can be shipped or not. The order can only be shipped if the date matches
// with the end of day record date and the quanity is not equal to 0. If it is 0 that means the order has already been shipped previosly by express order.
vector<int> canShip(vector<SalesOrder> salesOrderRec, EODRecord E) {
	vector<int> customerNumbers;
	for (int i = 0; i < salesOrderRec.size(); i++) {
		if (salesOrderRec.at(i).getOrderDate() == E.getDate() && salesOrderRec.at(i).getOrderQuantity() != 0) {
			customerNumbers.push_back(salesOrderRec.at(i).getCustomerNumber());
			salesOrderRec.at(i).setOrderQuantity(0);
		}
	}
	return customerNumbers;
}

//This function removes duplicates from the vector.
void removeDuplicates(vector<int>& v)
{
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	v.erase(end, v.end());
}


// This function first find the all the customer numbers whose order dates of orders matches with eod date. A vector with duplicate values are returned.
// Duplicate values means a customer might have several orders. So we remove those duplicates. Once removed, we ship all the customers order that are
// present in the customerNumbers vector.
void ship(vector<Customer>& customers, vector<SalesOrder> salesOrderRec, EODRecord eod ) {
	cout << "OP: end of day " << eod.getDate() << endl;
	vector<int> customerNumbers = canShip(salesOrderRec, eod);
	removeDuplicates(customerNumbers);
	if (customerNumbers.size() == 0) {
		return;
	}
	else {
		for (int i = 0; i < customers.size(); i++) {
			for (int j = 0; j < customerNumbers.size(); j++) {
				if (customers.at(i).getCustomerNumber() == customerNumbers.at(j) && customers.at(i).getOrderQuantity() != 0 ) {
					cout << "OP: customer " << setfill('0') << setw(4) << customers.at(i).getCustomerNumber() << ": shipped quantity " << customers.at(i).getOrderQuantity() << endl;
					cout << "SC: customer " << setfill('0') << setw(4) << customers.at(i).getCustomerNumber() << ": invoice " << invoice++ << ": date " << eod.getDate() << ": quantity " << customers.at(i).getOrderQuantity() << endl;
					customers.at(i).setOrderQuantity(0);
				}
			}
		}
	}

}



//This function reads file and all the vectors are passed by reference so that the changes in vectors will actually affect the real vectors in main.
void readFile(const char* filename, vector<Customer> &customerRecord, vector <SalesOrder> &salesOrderRecord, vector<EODRecord> &EODs) {
	ifstream infile;
	string line;
	infile.open(filename);
	if (infile.is_open()) {
		while (!infile.eof()) {
			getline(infile,line);
			if (line.at(0) == 'C') { //It's a customer record
				Customer C(line);
				customerRecord.push_back(C);
				cout << "OP: Customer " << setfill('0') << setw(4) << C.getCustomerNumber() << " added\n";
			}
			else if (line.at(0) == 'S') { //It's a salesOrder Record 
				SalesOrder S(line);
				salesOrderRecord.push_back(S);
				updateQuantity(customerRecord, S);
			}
			else if (line.at(0) == 'E') { //It's a eod record
				EODRecord E(line);
				EODs.push_back(E);
				ship(customerRecord, salesOrderRecord, E);
				
			}
		}
	}
	else {
		cout << "Unable to open file\n";
	}
}

int main(int args, char *argv[]) {

	vector<Customer> customerRecord;
	vector<SalesOrder> salesOrderRecord;
	vector<EODRecord> EODs;
	readFile(argv[1], customerRecord, salesOrderRecord, EODs);

	return 0;
}
