SHELL=/bin/bash
EXEC = list_sort
DEPS = list.h mylist.h
OBJ = link_list.o read_str.o

all: $(EXEC)


$(EXEC): $(OBJ)
	gcc -o $@ $^

link_list.o: link_list.c $(DEPS)
	gcc -c -o $@ $<

read_str.o: read_str.c
	gcc -c -o $@ $<

question.txt:
	for i in {1..100}; do echo $$RANDOM; done > question.txt

answer.txt: question.txt
	cat question.txt | sort -n > answer.txt

output.txt: question.txt $(EXEC)
	cat question.txt | ./$(EXEC) > output.txt

test: answer.txt output.txt
	diff -q answer.txt output.txt

clean:
	rm -f *.o question.txt answer.txt output.txt $(EXEC)
