quicksort:
	gcc -o quicksort quicksort.c simulator.c

heapsort:
	gcc -o heapsort heapsort.c simulator.c

bubble:
	gcc -o bubble bubble.c simulator.c

clean:
	rm -f quicksort
	rm -f heapsort
