VPATH = inc:src
%.o: %.c
	gcc -o $@ -Wall -g -fPIC -Iinc -c $< 
%.o: %.cpp
	g++ -o $@ -Wall -g -fPIC -Iinc -c $<

getchtest: getchtest.o libgcom.so
	gcc -o $@ -L. -lgcom $<  

libgcom.so: getch.o
	gcc -o $@ -shared $<

clean:
	rm -rf *.so *.o getchtest
