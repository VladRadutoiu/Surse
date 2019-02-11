build:
	gcc -Wall trivia2.c -lncurses -o trivia
run:
	./trivia intrebare
clean: 
	rm -f trivia
