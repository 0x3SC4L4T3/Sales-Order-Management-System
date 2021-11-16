#include "SalesOrder.h"

/* 
   A line for salesOrder read from the file and passed as a string name "salesOrder", This salesOrder string is parsed and the values
   are stored in the data members of salesOrder Object.	
*/ 
SalesOrder::SalesOrder(string salesOrder)
{
	this->orderDate = stoi(salesOrder.substr(1, 9));
	this->orderType = salesOrder.at(9);
	this->customerNumber = stoi(salesOrder.substr(10, 4));
	this->orderQuantity = stoi(salesOrder.substr(14, 3));
}

int SalesOrder::getCustomerNumber()
{
	return this->customerNumber;
}

int SalesOrder::getOrderQuantity()
{
	return this->orderQuantity;
}

int SalesOrder::getOrderDate()
{
	return this->orderDate;
}

void SalesOrder::setOrderQuantity(int quantity)
{
	this->orderQuantity = quantity;
}

char SalesOrder::getOrderType()
{
	return this->orderType;
}

//Destructor for SalesOrder
SalesOrder::~SalesOrder()
{

}