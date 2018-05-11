#include <stddef.h> //get NULL definition
#include <stdbool.h> //get bool definition
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "read_str.h"

struct mylist{
	char *str;
	int str_length;
	struct list_head list;
};

// print each element
int print_list(struct list_head *head) {
    struct mylist *entry;
    list_for_each_entry(entry, head, list) {
        printf("%s\n", entry->str);
    }
    return 0;
}

// add entry to list
int add_entry(struct list_head *head, char *str) {
	//create entry
	struct mylist *new = malloc(sizeof(struct mylist));
	if(new == NULL) {
		printf("malloc failed\n");
		free(str);
		return -1; // return -1 if malloc failed
	}
	new->str_length = strlen(str);
	new->str = str;
	
	// add new entry directly if list is empty
	if(list_empty(head)) {
		list_add(&new->list, head);
		return 0;
	}
	
	// compare each element
	struct mylist *entry;
	list_for_each_entry(entry, head, list) {
		// add new entry before current entry if length of current entry is larger than length of new entry
		if(new->str_length < entry->str_length) {
			list_add_tail(&new->list, &entry->list);
			return 0;
		} 
		// do string compare if two strings have same length
		else if(entry->str_length == new->str_length) {
			if(strcmp(new->str, entry->str) <= 0) {
				list_add_tail(&new->list, &entry->list);
				return 0;
			}
		}
	}
	// add new entry to the last since it is the latgest number
	list_add_tail(&new->list, head);
	return 0;
}

int free_list(struct list_head *head)
{
    struct mylist *entry, *tmp_entry;
    list_for_each_entry_safe(entry, tmp_entry, head, list) {
        list_del(&entry->list);
        free(entry->str);
        free(entry);
    }
    return 0;
}

int main()
{
	LIST_HEAD(head); // create head and initialize
	
	// read string from file and add to list
	FILE *fp = stdin;
	char *str = NULL;
	int err_flag = 0;
	while((err_flag = read_str(fp, &str)) == 1) {
		// break if malloc failed
		if(err_flag = add_entry(&head, str)) {
			break;
		}
		err_flag = 0; // No error
	}
	
	//not print if malloc or realloc failed
	if(err_flag == 0) {
		print_list(&head);
	}
	free_list(&head);
	return 0;
}
