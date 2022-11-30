merge.exe: main.o
	g++ -std=c++11 -o merge.exe main.o

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

debug:
	g++ -std=c++11 -g -o mergeDebug.exe main.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
