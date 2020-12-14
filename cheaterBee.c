#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//prototypes
void clearTempWord(char *word);

int main(int argc, char *argv[]){

  //make sure user input is acceptable  
  if (argc != 4 && argc != 5){
      printf("Correct format is: ./spellingBee [mandatory character] [3+ other characters, no space or comma] [dictionary file] [min word length - optional]\n");
      return 1;
    }
    
  //argv[1] - only one required char
  if (strlen(argv[1]) != 1){
    printf("First arg needs to be one character\n");
    return 2;    
  }
  //check that req char is alpha
  else if (isalpha((int) argv[1][0]) == 0){
    printf("First arg needs to be a letter\n");
    return 2;
  }

  //argv[2] - at least 3 chars
  if (strlen(argv[2]) < 3){
    printf("Please give at least 3 additional characters with no spaces between them\n");   
    return 3;
  }
  //check that argv[2] is all alpha chars
  else{
    for (int i = 0; i < strlen(argv[2]); i++){
      if (isalpha((int) argv[2][i]) == 0){
        printf("Please only give letters that should be used. Non-alpha characters should not be used.\n");
        return 3;
      }
    }
  }

  //if 5 argvs then check if final is a number
  if (argc == 5){
    if (isdigit((int) argv[4][0]) == 0){
      printf("Minimum word length must be a number.\n");
      return 4;
    }
  }
  
  //put user input into variables
  char *dictFile = argv[3];
  FILE *inptr = fopen(dictFile, "r");
  
  if (inptr == NULL){
    fprintf(stderr, "Could not open %s\n", dictFile);
    return 5;
  }   

  //set variables
  char *reqChar = argv[1];
  char *otherChars = argv[2];
  char *tempWord = malloc(sizeof(char) * 46); 
  char c = fgetc(inptr);
  int i = 0;
  bool hasReqChar = false;
  int minWordLen = 1;
  
  if (argc == 5){
    minWordLen = atoi(argv[4]);
  }
  
  
  while (c != EOF){
    NEXTWORD:
    i = 0;
    clearTempWord(tempWord);
    hasReqChar = false;
    while (c != '\0' && c != '\n' && c != EOF){
      //check if contains required letter
      if (strchr(reqChar,c) != NULL){
        hasReqChar = true;
      }
      else if (strchr(otherChars,c) == NULL){ 
        //if letter is not acceptable, go to next word
        //move to end of words
        while (c != '\0' && c != '\n' && c != EOF){
          c = fgetc(inptr);   
        }
        
        //if end of file, end program
        if (c == EOF){
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
    if (hasReqChar == true && strlen(tempWord) >= minWordLen){
        printf("%s\n",tempWord);
    }
    c = fgetc(inptr);
  }    
  
  free(tempWord);
  fclose(inptr);
}

void clearTempWord(char *word){
  for (int i = 0; i < 46; i++)
  {
    word[i] = '\0';
  }
}