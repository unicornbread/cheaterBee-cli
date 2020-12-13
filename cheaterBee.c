#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//prototypes
void clearTempWord(char *word);

int main(int argc, char *argv[])
{
if (argc != 4 && argc != 5)
  {
    printf("Correct format is: ./spellingBee [mandatory character] [6 other characters] [dictionary file] [min word length - optional]");
    return 1;
  }
  
  if (strlen(argv[1]) != 1)
  {
    printf("First arg needs to be one character");
    return 2;    
  }
  
  if (strlen(argv[2]) != 6)
  {
    printf("Give 6 other characters with no spaces in between");   
    return 3;
  }
  
  char *dictFile = argv[3];
  FILE *inptr = fopen(dictFile, "r");
  
  if (inptr == NULL)
  {
    fprintf(stderr, "Could not open %s\n", dictFile);
  }   

  //set variables
  char *reqChar = argv[1];
  char *otherChars = argv[2];
  char *tempWord = malloc(sizeof(char) * 46); 
  char c = fgetc(inptr);
  int i = 0;
  bool hasReqChar = false;
  int minWordLen = 1;
  
  if (argc == 5)
  {
    minWordLen = atoi(argv[4]);
    printf("\n%i", minWordLen);
  }
  
  
  while (c != EOF)
  {
    NEXTWORD:
    i = 0;
    clearTempWord(tempWord);
    hasReqChar = false;
    while (c != '\0' && c != '\n' && c != EOF)
    {
      //check if contains required letter
      if (strchr(reqChar,c) != NULL)
      {
        hasReqChar = true;
      }
      else if (strchr(otherChars,c) == NULL)
      { 
        //if letter is not acceptable, go to next word
        //move to end of words
        while (c != '\0' && c != '\n' && c != EOF)
        {
          c = fgetc(inptr);   
        }
        
        //if end of file, end program
        if (c == EOF)
        {
          return 1;   
        }
        
        //get first char of next word
        c = fgetc(inptr);
        goto NEXTWORD;
      }
      
      tempWord[i] = c;
      i++;
      c = fgetc(inptr);
    }
    
    //if requirements met, print word
    if (hasReqChar == true && strlen(tempWord) > minWordLen)
    {
        printf("%s\n",tempWord);
    }
    c = fgetc(inptr);
  }    
  
  free(tempWord);
  fclose(inptr);
}

void clearTempWord(char *word)
{
  for (int i = 0; i < 46; i++)
  {
    word[i] = '\0';
  }
}