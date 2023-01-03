%.o: %.cpp
	g++ -g -O0 -o $@ -Wall -I../common/inc -c $^

lifegame: lifegame.o
	g++ -o $@ $^ -L../common -lgcom

clean:
	rm -rf lifegame *.o a.out
