CXX=g++

CXXFLAGS = -Wall -O0 -g -std=c++11

all:NearestAirport

NearestAirport.o:NearestAirport.cpp Coordinates.hpp GreatCircle.hpp

NearestAirport: NearestAirport.o
	${CXX} -o NearestAirport NearestAirport.o


clean:
	-rm -f NearestAirport NearestAirport.o