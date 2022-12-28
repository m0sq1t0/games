VPATH = inc:src
%.o: %.c
	gcc -o $@ -Wall -g -fPIC -Iinc -c $< 
%.o: %.cpp
	g++ -o $@ -Wall -g -fPIC -Iinc -c $<

# Use static library for now 
getchtest: getchtest.o libgcom.a
	gcc -o $@ $< -L. -lgcom  

# shared library 
libgcom.so: getch.o
	gcc -o $@ -shared $<

# static library
libgcom.a: getch.o
	ar -rc libgcom.a getch.o

clean:
	rm -rf *.so *.o getchtest
