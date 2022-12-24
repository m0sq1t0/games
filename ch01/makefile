%.o: %.c
	g++ -o $@ -Wall $^

text_rpg_battle: text_rpg_battle.o
	g++ -o $@ $^

clean:
	rm -rf text_rpg_battle *.o a.out