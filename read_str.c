#include <stdio.h>
#include <stdlib.h>

int read_str(FILE *fp, char **str)
{
	int buf_size, str_length;
	// read string from file
	while(1) {
		// initialize
		buf_size = 100;
		str_length = 0;
		*str = (char*) malloc(buf_size * sizeof(char));
		if(*str == NULL) {
			printf("malloc failed\n");
			exit(1);
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
				*str = (char*) realloc(*str, buf_size * sizeof(char));
				if(*str == NULL) {
					printf("realloc failed\n");
					exit(1);
				}
			}
		}
	}
}
