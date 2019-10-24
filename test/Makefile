CC        = g++
CCARCH    = -std=c++11
CCOPT     = -O3 -Wall -Wextra -pedantic
INCLUDE   = -I.. -I../../lila
LIB       = -lhdf5

EXECUTABLE = tests
OBJECTS    = tests.o test_estimator.o test_dumper_h5.o test_dumper_h5_lila.o 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CCARCH) $(CCOPT) -o $(EXECUTABLE) $(OBJECTS) $(LIB)

%.o: %.cpp
	$(CC) $(CCARCH) $(CCOPT) $(LAPACKLIB) $(INCLUDE) -c $< -o $@ 
clean:
	rm *.o

rebuild: clean $(EXECUTABLE)
