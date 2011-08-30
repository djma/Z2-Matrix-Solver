OPTIMIZE = 0

crossflip: crossflip2.o
unittests: unittests.o Z2RowReducer.o
	g++ unittests.o Z2RowReducer.o -o unittests
unittests.o: unittests.cpp
	g++ -c unittests.cpp

clean:
	rm *.o
