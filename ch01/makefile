%.o: %.cpp
	g++ -o $@ -Wall -I../common/inc -c $^

text_rpg_battle: text_rpg_battle.o
	g++ -o $@ -L../common -lgcom $^

clean:
	rm -rf text_rpg_battle *.o a.out
