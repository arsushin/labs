#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define FILE_NAME_LENGTH 18
#define LINE_LENGTH 40
#define MAXCHAR 1000

char* substring(char* string, int position, int length)
{
	char* pointer;
	int c;

	pointer = malloc(length + 1);

	if (pointer == NULL)
	{
		printf("Unable to allocate memory.\n");
		exit(1);
	}

	for (c = 0; c < length; c++)
	{
		*(pointer + c) = *(string + position - 1);
		string++;
	}

	*(pointer + c) = '\0';

	return pointer;
}

char* my_strcat(char* str1, char* str2) {
	char* pointer;
	int size1 = strlen(str1);
	int size2 = strlen(str2);
	pointer = malloc(size1 + size2);
	*(pointer) = '\0';
	char space[2];
	space[0] = ' ';
	space[1] = '\0';
	strcat_s(pointer, size1 + 1, str1);
	strcat_s(pointer, size1 + 3, space);
	strcat_s(pointer, size1 + size2 + 3, str2);
	return pointer;
}

void addSpaces(char* outp, int currentI, int n) 
{
	for (int s = 0; s <= n; s++)
	{
		if (currentI < LINE_LENGTH) {
			outp[currentI + s] = ' ';
		}
	}

}

void fillWithSpaces(char* line, int lineLength, int spaceCnt) 
{
	char outputLine[LINE_LENGTH + 1] = " ";
	int n = (LINE_LENGTH - lineLength) / spaceCnt;
	int reminder = (LINE_LENGTH - lineLength) % spaceCnt;
	if (reminder == 0)
	{
		int t = 0;
		int k = 0;
		while (t < lineLength)
		{
			if (line[t] != ' ')
			{
				outputLine[k] = line[t];
				k++;
			}
			else
			{
				outputLine[k] = line[t];
				addSpaces(outputLine, k, n + 1);
				k += n + 1;
			}
			t++;
		}
	}
	else
	{
		int t = 0;
		int k = 0;
		while (t < lineLength)
		{
			if (line[t] != ' ')
			{
				outputLine[k] = line[t];
				k++;
			}
			else
			{
				outputLine[k] = line[t];
				if (reminder > 0)
				{
					addSpaces(outputLine, k, n + 2);
					reminder--;
					k += n + 2;
				}
				else
				{
					addSpaces(outputLine, k, n + 1);
					k += n + 1;
				}
			}
			t++;
		}
	}
	printf("%s\n",outputLine);
}

char* printAlignedAndCutBalance(char* str, int sf) {
	int currentLineLength = 0;
	int previousIndex = 0;
	int spaceCount = 0;
	char* buffer = '\0';
	int i = 0;
	while (str[i] != '\0')
	{
		if (i == LINE_LENGTH - 1)
		{
			if (str[strlen(str) - 1] == '\n') {
				currentLineLength = strlen(str) - 1;
			}
			else {
				currentLineLength = strlen(str);
			}

			//printf("line lenght = %d\n", currentLineLength);
			break;
		}
		if (str[i] == ' ')
		{
			spaceCount++;
			previousIndex = i;
		} else if (str[i] == '\n')
		{
			currentLineLength = i;
			break;
		}
		i++;
	}

	if (currentLineLength == LINE_LENGTH)
	{
		char output[LINE_LENGTH];
		for (int t = 0; t < currentLineLength; t++)
		{
			output[t] = str[t];
		}
		printf(output);
	}
	else if (currentLineLength == 0 || currentLineLength == 1)
	{
		//do nothing
	}
	else if (currentLineLength < LINE_LENGTH)
	{
		fillWithSpaces(str, currentLineLength, spaceCount);
	}
	else if (currentLineLength > LINE_LENGTH)
	{
		char* firstPart = substring(str, 0, previousIndex + 1);
		fillWithSpaces(firstPart, previousIndex + 1, spaceCount);
		int end = currentLineLength - previousIndex - sf;
		buffer = substring(str, previousIndex + 2, end);
		//printf("buffer:%s\n", buffer);
	}
	//printf("spaceCount = %d\n", spaceCount);
	return buffer;
}
int main() 
{
	FILE* fp;
	char line[MAXCHAR];
	char * buffer = '\0';
	char * str = '\0';
	//char output[LINE_LENGTH];
	int currentLineLength = 0;
	int lengthWithoutLast = 0;
	char* filename = "d:\\tmp\\task3.txt";
	//char filename[FILE_NAME_LENGTH];
	//fgets(filename, FILE_NAME_LENGTH, stdin);

	errno_t errorCode = fopen_s(&fp,filename, "r");
	if (fp == NULL)
	{
		printf("Could not open file %s", filename);
		return 1;
	}
	while (fgets(line, MAXCHAR, fp) != NULL)
	{
		//printf("%s\n", str);
		if (buffer == '\0') {
			str = line;
		} 
		else
		{
			str = my_strcat(buffer, line);
		}
		buffer = printAlignedAndCutBalance(str, 1);
	}

	while (buffer != '\0')
	{
		buffer = printAlignedAndCutBalance(buffer, 0);
		if (buffer != '\0' && strlen(buffer) < LINE_LENGTH) {
			printf(buffer);
		}
	}
	fclose(fp);
	return 0;
}