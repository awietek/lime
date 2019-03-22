CC        = g++
CCARCH    = -std=c++11
CCOPT     = -O3 -Wall -Wextra -pedantic
INCLUDE   = -I..

EXECUTABLE = tests
OBJECTS    = tests.o test_estimator.o

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CCARCH) $(CCOPT) -o $(EXECUTABLE) $(OBJECTS) $(LAPACKLIB)   

%.o: %.cpp
	$(CC) $(CCARCH) $(CCOPT) $(LAPACKLIB) $(INCLUDE) -c $< -o $@ 
clean:
	rm *.o

rebuild: clean $(EXECUTABLE)
