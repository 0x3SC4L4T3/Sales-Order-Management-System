#pragma once
/**
 * This is our customer class. This class is used to hold the data for customer name, the customer number and the order quantity.
 * The order quantity is dynamically incremented and set to 0 based on each instruction read from the file.
*/
#include <string>
using std::string;
class Customer {
private :
	string customerName;
	int customerNumber;
	int orderQuantity;

public:
	Customer(string);
	string getCustomerName();
	int getCustomerNumber();
	int getOrderQuantity();
	void incrementQuantity(int);
	void setOrderQuantity(int);
	~Customer();
};