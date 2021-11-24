#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

char * copy(char *, char *);

struct TOKENS
{
	char *INSTRUCTION, *OPERAND1, *OPERAND2;
};

int main(int argc, char **argv)
{
	char *ptr;
	ptr = (char *)malloc(64 * sizeof(char));		//max input length is 64 characters. can be changed in future.
	fscanf(stdin, "%s", ptr);
	
	char *temp_ptr;
	temp_ptr = copy(ptr, temp_ptr);
	free(ptr);
	fprintf(stdout, "> %s", temp_ptr);
	return 0;
}

char * copy(char *ptr, char *temp_ptr)
{
	uint8_t null_flag;
	for(int i = 0; i  < 64; ++i)
	{
		if(*(ptr + i) == NULL)
		{
			null_flag = i;
			break;
		} 
	}
	printf("NULL FLAG = %d\n", null_flag);
	temp_ptr = (char *)malloc(null_flag * sizeof(char));
	for(int i = 0; i < null_flag; ++i)
	{
		*(temp_ptr + i) = *(ptr + i);
		printf(".%c\n", *(temp_ptr + i));
	}
	return temp_ptr;
}