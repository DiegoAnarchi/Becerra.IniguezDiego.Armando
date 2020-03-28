#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{char cos;
  while((cos = fgetc(stdin)) != EOF)
    {
      if(isalnum(cos))
	{
	printf("%c", cos);
	}
      else
	{
	cos = fgetc(stdin);
	}
    }
  return 1;
}
