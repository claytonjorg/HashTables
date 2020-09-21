all: hashproj.x

hashproj.x: passserver.o hashproj.o
	g++ -std=c++11 -g -o hashproj.x hashproj.o passserver.o -lcrypt

shashproj.x: passserver.o shashproj.o
	g++ -std=c++11 -g -o shashproj.x shashproj.o passserver.o -lcrypt

passserver.o: passserver.h passserver.cpp hashtable.h hashtable.hpp
	g++ -std=c++11 -g -c passserver.cpp

hashproj.o: passserver.h hashtable.h hashproj.cpp
	g++ -std=c++11 -g -c hashproj.cpp

shashproj.o: passserver.h hashtable.h shashproj.cpp
	g++ -std=c++11 -c shashproj.cpp

clean: 
	rm *.o
	rm *.x
