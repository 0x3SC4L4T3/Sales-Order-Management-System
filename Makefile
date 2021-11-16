ordering.out: main.o Customer.o SalesOrder.o EODRecord.o
	g++ -o ordering.out main.o Customer.o SalesOrder.o EODRecord.o

main.o: main.cpp Customer.cpp SalesOrder.cpp EODRecord.cpp
	g++ -c main.cpp Customer.cpp SalesOrder.cpp EODRecord.cpp

Customer.o: Customer.cpp
	g++ -c Customer.cpp

SalesOrder.o: SalesOrder.cpp
	g++ -c SalesOrder.cpp
	
EODRecord.o: EODRecord.cpp
	g++ -c EODRecord.cpp

clean:
	rm *.o ordering.out