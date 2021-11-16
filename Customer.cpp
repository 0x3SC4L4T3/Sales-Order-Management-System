#include "Customer.h"


/* A paramterized constructor for the customer. A line read from file and passed to the constructor that is parsed and stored in each variable of customer */
Customer::Customer(string customer)
{
	this->customerNumber = stoi(customer.substr(1, 4));
	this->customerName = customer.substr(5, customer.size() - 4);
	this->orderQuantity = 0;
}

string Customer::getCustomerName()
{
	return this->customerName;
}

int Customer::getCustomerNumber()
{
	return this->customerNumber;
}

int Customer::getOrderQuantity()
{
	return this->orderQuantity;
}

//This function increments the quantity of customer order quantity by the parameter "quantity"
void Customer::incrementQuantity(int quantity)
{
	this->orderQuantity += quantity;
}

void Customer::setOrderQuantity(int quantity)
{
	this->orderQuantity = quantity;
}


//Destructor for customer.
Customer::~Customer()
{

}