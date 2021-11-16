#include "EODRecord.h"

/* 
  Similar to the salesOrder string and Customer String this EOD string is also a line read from the file and then parsed accordingly. 
*/
EODRecord::EODRecord(string EOD)
{
    this->date = stoi(EOD.substr(1, 8));
}

//Getter that returns the date
int EODRecord::getDate()
{
    return this->date;
}

//Destructor for EODRecord
EODRecord::~EODRecord()
{

}
