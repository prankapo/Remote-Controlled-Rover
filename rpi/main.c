#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#define KRED  "\x1B[91m"
#define RESET "\x1B[0m"

char * copy(char *);
char * copyl(char *, int, int);			//copies characters from index i to index l including the character at index l
int parser(char *);
int interpreter();

struct TOKENS
{
	char *INSTRUCTION, *OPERAND1, *OPERAND2;
};

struct TOKENS RESULT;

int main(int argc, char **argv)
{
	int line_number = 1;
	system("clear");
	while(1)
	{
		fprintf(stdout, "\n%02d. > ", line_number);
		char *ptr;
		ptr = (char *)malloc(64 * sizeof(char));		//max input length is 64 characters. can be changed in future.
		fgets(ptr, 64, stdin);
		char *temp_ptr;
		temp_ptr = copy(ptr);
		free(ptr);
		parser(temp_ptr);
		interpreter();
		++line_number;
	}
	return 0;
}

char * copy(char *src)
{
	char *dest;
	uint8_t null_flag;
	for(int i = 0; i  < 64; ++i)
	{
		if(*(src + i) == NULL)
		{
			null_flag = i;
			break;
		} 
	}
	dest = (char *)malloc(null_flag);
	for(int i = 0; i < null_flag; ++i)
	{
		*(dest + i) = *(src + i);
	}
	return dest;
}

char * copyl(char *src, int min, int max)
{
	char *dest;
	max = max + 1;
	dest = (char *)malloc(max - min + 1);
	for(int i = 0; i < (max - min); ++i)
	{
		*(dest + i) = *(src + min + i);
	}
	return dest;
}

int parser(char *line)
{
	uint8_t instruction_syntax_flag, min, max;
	instruction_syntax_flag = 0;
	min = 0;
	max = 0;
	for(int i = 0; i < strlen(line); ++i)
	{
		if((line[i] >= 'a' && line[i] <= 'z') || 
		(line[i] >= 'A' && line[i] <= 'Z') || 
		(line[i] >= '0' && line[i] <= '9') || 
		(line[i] == '_') || 
		(line[i] == '.') || 
		(line[i] == '+') || 
		(line[i] == '-'))
		{
			max = i;
		}
		else
		{
			if(instruction_syntax_flag == 0)
			{
				RESULT.INSTRUCTION = copyl(line, min, max);
			}
			else if(instruction_syntax_flag == 1)
			{
				RESULT.OPERAND1 = copyl(line, min, max);
			}
			else if(instruction_syntax_flag == 2)
			{
				RESULT.OPERAND2 = copyl(line, min, max);
			}
			else
			{
				fprintf(stdout, KRED"\a\nINSTRUCTION IS TOO LONG!!\n"RESET);
				return 0;
			}
			for(int j = max + 1; j < strlen(line); ++j)
			{
				i = j;
				if((line[i] >= 'a' && line[i] <= 'z') || 
				(line[i] >= 'A' && line[i] <= 'Z') || 
				(line[i] >= '0' && line[i] <= '9') || 
				(line[i] == '_') || 
				(line[i] == '.') || 
				(line[i] == '+') || 
				(line[i] == '-'))
				{
					break;
				}
			}
			min = i;
			max = i;
			++instruction_syntax_flag;
		}
	}
	return 0;
}

int interpreter()
{
	char command[] = "python interface.py ";
	if(RESULT.OPERAND1 != NULL)
	{
		strcat(command, " ");
		strcat(command, RESULT.OPERAND1);
	}
	if(RESULT.OPERAND2 != NULL)
	{
		strcat(command, " ");
		strcat(command, RESULT.OPERAND2);
	}
	
	if(strcmp(RESULT.INSTRUCTION, "movf") == 0)
	{
		system(command);
	}
	else if(strcmp(RESULT.INSTRUCTION, "movb") == 0)
	{
	
	}
	else if(strcmp(RESULT.INSTRUCTION, "strl") == 0)
	{
	
	}
	else if(strcmp(RESULT.INSTRUCTION, "strr") == 0)
	{
	
	}
	else if(strcmp(RESULT.INSTRUCTION, "camc") == 0)
	{
	
	}
	else if(strcmp(RESULT.INSTRUCTION, "camb") == 0)
	{
	
	}
	else if(strcmp(RESULT.INSTRUCTION, "exit") == 0)
	{
		exit(0);
	}
	else
	{
		fprintf(stdout, KRED"\a\n%s", RESULT.INSTRUCTION);
		fprintf(stdout, RESET" is not a supported instruction!!!\n");
	}
	return 0;
}