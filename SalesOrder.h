#pragma once
#include <string>
using std::string;
/**
 * This is our salesOrder class that is used to hold the orderDate, orderType, customer number and order quantity of the specific sales order.
 * This is order quantity is for single order for which the object is made while the orderQuantity in customer is different that keeps all the
 * sum of orders for any customer.
*/
class SalesOrder {
private:
	int orderDate;
	char orderType;
	int customerNumber;
	int orderQuantity;
public:
	SalesOrder(string);
	int getCustomerNumber();
	int getOrderQuantity();
	int getOrderDate();
	void setOrderQuantity(int);
	char getOrderType();
	~SalesOrder();
};