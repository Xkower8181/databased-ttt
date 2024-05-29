all: TTTOOP

TTTOOP: Projekt_OOP.o
	 g++ -o TTTOOP Projekt_OOP.o

Projekt_OOP.o: 
	 g++ -c Projekt_OOP.cpp
     
clean:
	 rm Projekt_OOP.o TTTOOP
