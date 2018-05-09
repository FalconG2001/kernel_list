SHELL=/bin/bash
EXEC = list_sort

$(EXEC): link_list.c list.h
	gcc -o $@ $<

question.txt:
	for i in {1..100}; do echo $$RANDOM; done > question.txt

answer.txt: question.txt
	cat question.txt | sort -n > answer.txt

output.txt: question.txt $(EXEC)
	cat question.txt | ./$(EXEC) > output.txt

test: answer.txt output.txt
	diff -q answer.txt output.txt
