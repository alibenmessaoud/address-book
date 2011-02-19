address-book: src/main.o src/addressbook.o src/dummydatasource.o
	g++ src/main.o src/addressbook.o src/dummydatasource.o -o address-book

main.o: src/main.cpp
	g++ -c -Wall main.cpp

addressbook.o: src/addressbook.cpp
	g++ -c -Wall addressbook.cpp

dummydatasource.o: src/dummydatasource.cpp
	g++ -c -Wall dummydatasource.cpp
