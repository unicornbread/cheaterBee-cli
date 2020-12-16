#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//prototypes
void clearTempWord(char *word);

int main(int argc, char *argv[]){

  //define variables
  char *reqChar = (char*) malloc(sizeof(char)*2);
  char *otherChars = (char*) malloc(sizeof(char) * 26);
  char *dictFile = (char(*)) malloc(sizeof(char)*50);
  int minWordLen = 1;

  //make sure user input is acceptable  
  if (argc != 4 && argc != 5){
      //printf("Correct format is: ./spellingBee [mandatory character] [3+ other characters, no space or comma] [dictionary file] [optional - min word length]\n");
      //return 1;
      printf("You have not entered necessary arguments when running the code. For your convenience, we will collect them now");
      printf("What is the required letter? [only enter one letter]");
      //scanf("%s",&)
  }else{
    //concatenate all error messages to prevent user frustration
    char *errMsg = (char *) malloc(sizeof(char)*150);
    char *tempErrMsg = (char *) malloc(sizeof(char)*100);
    bool userErr = false;

    //argv[1] - only one required char
    if (strlen(argv[1]) != 1){
      strcpy(errMsg,"First arg needs to be a single letter\n"); 
    }
    //check that req char is alpha
    else if (isalpha((int) argv[1][0]) == 0){
      strcpy(errMsg,"First arg needs to be a letter\n");
      userErr = true;
    }

    //argv[2] - at least 3 chars
    if (strlen(argv[2]) < 3){
      if (userErr){
        strcpy(tempErrMsg,"Please give at least 3 additional characters with no spaces between them\n");
        strcat(errMsg,tempErrMsg);   
        memset(tempErrMsg,0,strlen(tempErrMsg) + 1);
      }else{
        strcpy(errMsg,"Please give at least 3 additional characters with no spaces between them\n");   
        userErr = true;
      }
    }
    //no more than 25 chars
    else if (strlen(argv[2]) > 25){
      if (userErr){
        strcpy(tempErrMsg,"Please do not duplicate letters.\n");  
        strcat(errMsg,tempErrMsg);   
        memset(tempErrMsg,0,strlen(tempErrMsg) + 1);
      }else{
        strcpy(errMsg,"Please do not duplicate letters.\n");   
        userErr = true;
      }
    }
    //check that argv[2] is all alpha chars
    else{
      for (int i = 0; i < strlen(argv[2]); i++){
        if (isalpha((int) argv[2][i]) == 0){
          if (userErr){
            strcpy(tempErrMsg,"Second arg must be all letters with no spaces between.\n");
            strcat(errMsg,tempErrMsg);   
            memset(tempErrMsg,0,strlen(tempErrMsg) + 1);
          }else{
            strcpy(errMsg,"Second arg must be all letters with no spaces between.\n");   
            userErr = true;
          }
        }
      }
    }

    //check that dictionary file name is not too long
    if (strlen(argv[3]) > 99){
      if (userErr){
        strcpy(tempErrMsg,"Third arg cannot be larger than 99 characters\n");
        strcat(errMsg,tempErrMsg);   
        memset(tempErrMsg,0,strlen(tempErrMsg) + 1);
      }else{
        strcpy(errMsg,"Third arg cannot be larger than 99 characters\n");   
        userErr = true;
      }
    }

    //if 5 argvs then check if final is a number
    if (argc == 5){
      if (isdigit((int) argv[4][0]) == 0){
        if (userErr){
          strcpy(tempErrMsg,"Final arg must be a positive number.\n");   
          strcat(errMsg,tempErrMsg);  
          memset(tempErrMsg,0,strlen(tempErrMsg) + 1); 
        }else{
          strcpy(errMsg,"Final arg must be a positive numbers.\n");   
          userErr = true;
        }
      }
    }

    //if user errors, return messages
    if (userErr == true){
      printf("%s",errMsg);
      //free(errMsg);
      return 2;
    }
    //else put user input into appropriate variables
    else{
      reqChar = argv[1];
      otherChars = argv[2];
      dictFile = argv[3];
      
      if (argc == 5){
        minWordLen = (int) argv[4];
      }
    }
  }  
  
  //open dictionary
  FILE *inptr = fopen(dictFile, "r");
  
  if (inptr == NULL){
    fprintf(stderr, "Could not open %s\n", dictFile);
    return 3;
  }   

  //define & set remaining variables
  char c = fgetc(inptr);
  char *tempWord = malloc(sizeof(char) * 46); 
  int i = 0;
  bool hasReqChar = false;
  
  if (argc == 5){
    minWordLen = atoi(argv[4]);
  }
  
  
  while (c != EOF){
    NEXTWORD:
    i = 0;
    clearTempWord(tempWord);
    hasReqChar = false;
    while (c != '\0' && c != '\n' && c != ',' && c != EOF){
      //check if contains required letter
      if (strchr(reqChar,c) != NULL){
        hasReqChar = true;
      }
      else if (strchr(otherChars,c) == NULL){ 
        //if letter is not acceptable, go to next word
        //move to end of words
        while (c != '\0' && c != '\n' && c != ',' && c != EOF){
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