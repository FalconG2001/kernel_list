#include <stddef.h> //get NULL definition
#include <stdbool.h> //get bool definition
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct mylist{
	char *str;
	int str_length;
	struct list_head list;
};

// print each element
void print_list(struct list_head *head) {
    struct list_head *listptr;
    struct mylist *entry;
    
    list_for_each_entry(entry, head, list) {
        printf("%s\n", entry->str);
    }
}


// add entry to list
void add_entry(struct list_head *head, struct mylist *new) {
	// add new entry directly if list is empty
	if(list_empty(head)) {
		list_add(&new->list, head);
		return;
	}
	
	// compare each element
	struct list_head *listptr;
	struct mylist *entry;

	list_for_each(listptr, head) {
		entry = list_entry(listptr, struct mylist, list);
		// add new entry before current entry if length of current entry is larger than length of new entry
		if(new->str_length < entry->str_length) {
			list_add_tail(&new->list, &entry->list);
			return;
		} 
		// do string compare if two strings have same length
		else if(entry->str_length == new->str_length) {
			if(strcmp(new->str, entry->str) <= 0) {
				list_add_tail(&new->list, &entry->list);
				return;
			}
		}
	}
	// add new entry to the last since it is the latgest number
	list_add_tail(&new->list, head);
}

// read file content
void read_file(struct list_head *head, FILE *fp) {
	int buf_length = 2, str_length = 0;
	char c, *cp = (char*) malloc(buf_length * sizeof(char));
	
	while(c = fgetc(fp)) {
		if(c == EOF) {
			free(cp);
			break;
		}
		
		
		if(c == '\n') {
			cp[str_length] = '\0';
			// add element to list
			struct mylist *new = malloc(sizeof(struct mylist));
			new->str_length = str_length;
			new->str = cp;
			add_entry(head, new);
			
			// initialize
			buf_length = 2;
			str_length = 0;
			cp = (char*) malloc(buf_length * sizeof(char));
			continue;
		}
		
		cp[str_length] = c;
		str_length++;
		
		// double the buf size if length of string is bigger than buf
		if(buf_length == str_length){
			buf_length *= 2;
			cp = (char*) realloc(cp, buf_length * sizeof(char));
		}
	}
}

void free_list(struct list_head *head)
{
	struct list_head *listptr;
    struct mylist *entry;
    
    list_for_each(listptr, head) {
        entry = list_entry(listptr, struct mylist, list);
        list_del(&entry->list);
        free(entry->str);
        free(entry);
    }
}

int main()
{
	LIST_HEAD(head); //create head and initialize
	
	FILE *fp = stdin;
	/*
	if(fp = fopen("question.txt", "r")) {
		printf("file is opened\n");
		read_file(&head, fp);
	}
	*/
	read_file(&head, fp);
	
	print_list(&head);
	free_list(&head);
	return 0;
}
