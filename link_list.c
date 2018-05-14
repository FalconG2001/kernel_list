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
        printf("%s", entry->str);
    }
    return 0;
}

// add entry to list
int add_entry(struct list_head *head, char *str) {
	//create entry
	struct mylist *new = malloc(sizeof(struct mylist));
	if(new == NULL) {
		printf("malloc failed\n");
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
	size_t buf_size;
	ssize_t len;
	int ret;

	while(1){
		// initialize
		str = NULL;
		buf_size = 0;

		len = getline(&str, &buf_size, fp);
		if(len < 0) { // no more input or malloc fail
			free(str);
			break;
		}
		ret = add_entry(&head, str);
		if(ret != 0) { // add_entry fail
			free(str);
			break;
		}
	}
	
	print_list(&head);
	free_list(&head);
	return 0;
}
