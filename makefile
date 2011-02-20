OBJS = src/main.o src/addressbookcontroller.o src/dummydatasource.o src/contact.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


address-book: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o address-book

src/main.o : src/main.cpp src/addressbookcontroller.h src/dummydatasource.h src/contact.h \
src/errorinfo.h
	$(CC) $(CFLAGS) src/main.cpp -o src/main.o

src/addressbookcontroller.o: src/addressbookcontroller.cpp src/addressbookcontroller.h \
src/errorinfo.h src/contact.h
	$(CC) $(CFLAGS) src/addressbookcontroller.cpp -o src/addressbookcontroller.o

src/dummydatasource.o: src/dummydatasource.cpp src/dummydatasource.h src/contact.h
	$(CC) $(CFLAGS) src/dummydatasource.cpp -o src/dummydatasource.o

src/contact.o: src/contact.cpp src/contact.h
	$(CC) $(CFLAGS) src/contact.cpp -o src/contact.o

src/addressbookcontroller.h: src/contact.h src/datasource.h src/errorinfo.h

src/dummydatasource.h: src/datasource.h src/contact.h

src/datasource.h: src/contact.h

clean:
	rm src/*.o
