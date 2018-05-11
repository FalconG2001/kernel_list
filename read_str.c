#include <stdio.h>
#include <stdlib.h>

// read string from file
int read_str(FILE *fp, char **str)
{
	// initialize
	int buf_size = 100;
	int str_length = 0;
	char *tmp_buf; // is use to realloc
	*str = (char*) malloc(buf_size * sizeof(char));
	if(*str == NULL) {
		printf("malloc failed\n");
		free(*str);
		return -1; // return -1 if malloc failed
	}
		
	// read character loop
	while(1) {
		// return 0 if read EOF
		if(((*str)[str_length] = fgetc(fp)) == EOF) {
			free(*str);
			return 0;
		}
		
		// replace '\n' with '\0', and then return 1, which means read string successfully
		else if((*str)[str_length] == '\n') {
			(*str)[str_length] = '\0';
			return 1;
		}
		
		str_length++;
		// double the buf_size if str_length is equal to buf_size
		if(buf_size == str_length) {
			buf_size *= 2;
			tmp_buf = (char*) realloc(*str, buf_size * sizeof(char));
			if(*str == NULL) {
				printf("realloc failed\n");
				free(*str);
				return -1; // return -1 if realloc failed
			}
			*str = tmp_buf;
		}
	}
}
