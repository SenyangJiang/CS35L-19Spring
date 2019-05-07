#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int ignore_case = 0;

int frobcmp(char const* a,char const* b){
  while(*a != ' ' && *b != ' '){
    char first = *a^42;
    char second = *b^42;
    if(ignore_case){
      if(first >= 'a' && first <= 'z'){
	first = toupper(first);
      }
      if(second >= 'a' && second <= 'z'){
	second = toupper(second);
      }
    }
    if(first > second){
      return 1;
    }
    else if(first < second){
      return -1;
    }
    else{
      a++;
      b++;
    }
      }
  if(*a == ' ' && *b == ' '){
    return 0;
  }
  else if(*a == ' '){
    return -1;
  }
  else{
    return 1;
  }
}


int comp(const void* a, const void* b){
  return frobcmp(*(char const**) a, *(char const**) b);
}

int main(int argc, const char* argv[]){
  if(argc == 2 && (strcmp(argv[1],"-f") == 0)){
    ignore_case = 1;
  }
  
  char** record = NULL;
  int strCount = 0;
  char* currStr = NULL;
  
  struct stat fileStat;
  fstat(0, &fileStat);
  // if it is a regular file,
  // allocate memory and read the whole file
  if(S_ISREG(fileStat.st_mode)){
    int bufSize = fileStat.st_size;
    char* buffer = (char*)malloc(bufSize);
    read(0, buffer, bufSize);
    if(buffer[bufSize-1] != ' '){
      bufSize++;
      buffer = (char*)realloc(buffer, bufSize);
      buffer[bufSize-1] = ' ';
    }
    // count the number of words according to spaces
    for(int i = 0; i < bufSize; i++){
      if(buffer[i] == ' '){
        strCount++;
      }
    }
    // Allocate enough memory in record
    record = (char**)malloc(strCount*sizeof(char*));

    // copy strings in buffer to record
    int strCopied = 0;
    int begin = 0;
    int end = 0;
    while(strCopied < strCount){
      int i = begin;
      for(; i < bufSize; i++){
        if(buffer[i] == ' '){
          break;
        }
      }
      end = i + 1; // end: position of the first byte after space
      int len = end - begin;
      char* currStr = (char*)malloc(len*sizeof(char));
      for(int k = 0; k < len; k++){
        currStr[k] = buffer[begin+k];
      }
      record[strCopied] = currStr;
      begin = end;
      strCopied++;
    }
  }

  // read byte by byte
  currStr = NULL;
  int c;
  int charCount = 0;
  while(read(0, &c, 1) > 0){
    charCount++;
    currStr = (char*)realloc(currStr, charCount*sizeof(char));
    if(!currStr){
      fprintf(stderr, "Error allocating memory");
      exit(1);
    }
    currStr[charCount-1] = c;
    // if meet space, store the string to record
    // and clear current string
    if(c == ' '){
      strCount++;
      record = (char**)realloc(record, strCount*sizeof(char*));
      if(!record){
        fprintf(stderr, "Error allocating memory");
        exit(1);
      }
      record[strCount-1] = currStr;
      currStr = NULL;
      charCount = 0;
    }
  }

  // save the remaining string into record
  if(charCount != 0){
    charCount++;
    currStr = (char*)realloc(currStr, charCount*sizeof(char));
    if(!currStr){
      fprintf(stderr, "Error allocating memory");
      exit(1);
    }
    currStr[charCount-1] = ' ';
    strCount++;
    record = (char**)realloc(record, strCount*sizeof(char*));
    if(!record){
      fprintf(stderr, "Error allocating memory");
      exit(1);
    }
    record[strCount-1] = currStr;
  }

  if(record == NULL){
    return 0;
  }
  
  qsort(record, strCount, sizeof(char*), comp);

  // print sorted record
  int i = 0;
  for(i = 0; i < strCount; i++){
    char* str = record[i];
    for(;*str != ' '; str++){
      write(1, str, 1);
    }
    write(1, str, 1);
  }
  
  // free memory of strings and record itself
  for(i = 0; i < strCount; i++){
    free(record[i]);
  }
  free(record);
  return 0;
}
