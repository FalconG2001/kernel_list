#include <stddef.h> //get NULL definition
#include <stdbool.h> //get bool definition
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct mylist{
	char *str;
	int str_length;
	struct list_head link;
};

// print each element
void print_list(struct list_head *head) {
    struct list_head *listptr;
    struct mylist *entry;
    
    list_for_each(listptr, head) {
        entry = list_entry(listptr, struct mylist, link);
        printf("%s", entry->str);
    }
}

// compare two string
int str_compare(char *a, char *b, int str_length) {
	for(int i = 0; i < str_length - 1; i++) {
		if(a[i] == b[i]) continue;
		return b[i] - a[i];
	}
}

// add element to list and sorting
void add_sort(struct list_head *head, struct mylist *new) {
	// insert directly if list is empty
	if(list_empty(head)) {
		list_add(&new->link, head);
		return;
	}
	
	// compare each element
	struct list_head *listptr;
	struct mylist *entry;

	list_for_each(listptr, head) {
		entry = list_entry(listptr, struct mylist, link);
		if(new->str_length < entry->str_length) {
			__list_add(&new->link, (&entry->link)->prev, &entry->link);
			return;
		} 
		else if(entry->str_length == new->str_length) {
			if(str_compare(new->str, entry->str, new->str_length) > 0) {
				__list_add(&new->link, (&entry->link)->prev, &entry->link);
				return;
			}
		}
	}
	list_add_tail(&new->link, head);
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
		
		cp[str_length] = c;
		str_length++;
		
		if(c == '\n') {
			// add element to list
			struct mylist *new = malloc(sizeof(struct mylist));
			(*new).str_length = str_length;
			(*new).str = cp;
			add_sort(head, new);
			
			// initialize
			buf_length = 2;
			str_length = 0;
			cp = (char*) malloc(buf_length * sizeof(char));
			continue;
		}
		
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
        entry = list_entry(listptr, struct mylist, link);
        list_del(&entry->link);
        free(entry);
    }
}

int main()
{
	LIST_HEAD(head);
	
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
