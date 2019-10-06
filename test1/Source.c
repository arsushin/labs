#include <stdio.h> 
#define MAX 15 
int main()
{
	char buf[MAX];
	int i=0;
	int characters=0;
	int simbols=0;
	int numbers = 0;
	int strGroupCount=0;
	int simbolsGroupCount = 0;

	fgets(buf, MAX, stdin);
	for (i = 0; i < MAX-1; i++)
	{ 
		printf("%d ",buf[i]);
		printf("isalpha= %d", isalpha(buf[i]));
		printf("isdigit= %d\n", isdigit(buf[i]));
		if (i == 0)
		{
			if (isalpha(buf[i])==0 && isdigit(buf[i]) == 0 )
			{
				simbols++;
				continue;
			}
			else if (isalpha(buf[i]) == 0 && isdigit(buf[i]) != 0)
			{
				numbers++;
				continue;
			}
			else
			{
				characters++;
				continue;
			}
		}

		if (isalpha(buf[i]) == 0)
		{
			if (isdigit(buf[i]) == 0)
			{
				if (characters > 0 || (numbers > 0 && simbols == 0))
				{
					strGroupCount++;
				}
				simbols++;
				characters = 0;
				numbers = 0;
			}
			else if (isdigit(buf[i]) != 0)
			{
				if (characters > 0)
				{
					strGroupCount++;
				}
				else if (simbols > 0)
				{
					simbolsGroupCount++;
				}
				printf("numbers++\n");
				numbers++;
				simbols = 0;
				characters = 0;
				continue;
			}
		}
		else
		{ 
			if (simbols > 0 || (numbers > 0 && characters == 0))
			{
				simbolsGroupCount++;
			}
			characters++;
			simbols = 0;
			numbers = 0;
		}
		if (i == MAX-2)
		{
			if (isalpha(buf[i] == 0) && isdigit(buf[i]) == 0)
			{
				simbolsGroupCount++;
			}
			else if (isalpha(buf[i]) != 0)
			{
				strGroupCount++;
			}
		}
	}
	if (strGroupCount > simbolsGroupCount)
	{
		printf("The statement is true. There are more letter groups = %d than character groups = %d ", strGroupCount, simbolsGroupCount);
	}
	else
	{
		printf("The statement is not true. There are fewer letter groups = %d than character groups = %d", strGroupCount, simbolsGroupCount);
	}

	return 0;
}