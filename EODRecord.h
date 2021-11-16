#pragma once
#include "Customer.h"
#include <vector>
using std::vector;

/* This is our End of Day record class, that is used to hold the end of day date */
class EODRecord {
private:
	int date;
public:
	EODRecord(string);
	int getDate();
	~EODRecord();
};