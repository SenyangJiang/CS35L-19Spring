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

void freeMem(char** record, int strCount){
  for(int i = 0; i < strCount; i++){
    free(record[i]);
  }
  free(record);
}

int checkAllo(void* p){
  if(!p){
    fprintf(stderr, "Error allocating memory");
    return 1;
  }
  return 0;
}

int checkIO(ssize_t n){
  if(n < 0){
    fprintf(stderr, "Error reading input");
    return 1;
  }
  return 0;
}

int main(int argc, const char* argv[]){
  if(argc == 2 && (strcmp(argv[1],"-f") == 0)){
    ignore_case = 1;
  }
  
  char** record = NULL;
  int strCount = 0;
  char* currStr = NULL;
  ssize_t n;
  
  struct stat fileStat;
  fstat(STDIN_FILENO, &fileStat);
  // if it is a regular file,
  // allocate memory and read the whole file
  if(S_ISREG(fileStat.st_mode)&&fileStat.st_size > 0){
    int bufSize = fileStat.st_size;
    char* buffer = (char*)malloc(bufSize);
    n = read(STDIN_FILENO, buffer, bufSize);
    if(checkIO(n)){
      freeMem(record, strCount);
      exit(1);
    }
    if(buffer[bufSize-1] != ' '){
      bufSize++;
      buffer = (char*)realloc(buffer, bufSize);
      if(checkAllo(buffer)){
        freeMem(record, strCount);
        exit(1);
      }
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
    if(checkAllo(record)){
      freeMem(record, strCount);
      exit(1);
    }
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
      if(checkAllo(currStr)){
        freeMem(record, strCount);
        exit(1);
      }
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
  while(n = read(STDIN_FILENO, &c, 1) > 0){
    charCount++;
    currStr = (char*)realloc(currStr, charCount*sizeof(char));
    if(checkAllo(currStr)){
      freeMem(record, strCount);
      exit(1);
    }
    currStr[charCount-1] = c;
    // if meet space, store the string to record
    // and clear current string
    if(c == ' '){
      strCount++;
      record = (char**)realloc(record, strCount*sizeof(char*));
      if(checkAllo(record)){
        freeMem(record, strCount);
        exit(1);
      }
      record[strCount-1] = currStr;
      currStr = NULL;
      charCount = 0;
    }
  }

  if(checkIO(n)){
    freeMem(record, strCount);
    exit(1);
  }
  
  // save the remaining string into record
  if(charCount != 0){
    if(currStr[charCount-1] != ' '){
      charCount++;
      currStr = (char*)realloc(currStr, charCount*sizeof(char));
      if(checkAllo(currStr)){
        freeMem(record, strCount);
        exit(1);
      }
      currStr[charCount-1] = ' ';
    }
    strCount++;
    record = (char**)realloc(record, strCount*sizeof(char*));
    if(checkAllo(currStr)){
      freeMem(record, strCount);
      exit(1);
    }
    record[strCount-1] = currStr;
  }

  if(record == NULL){
    return 0;
  }
  
  qsort(record, strCount, sizeof(char*), comp);

  // print sorted record
  for(int i = 0; i < strCount; i++){
    char* str = record[i];
    for(;*str != ' '; str++){
      write(STDOUT_FILENO, str, 1);
    }
    write(STDOUT_FILENO, str, 1);
  }
  
  // free memory of strings and record itself
  freeMem(record, strCount);
  return 0;
}
