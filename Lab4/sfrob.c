#include <stdio.h>
#include <stdlib.h>

int frobcmp(const void* a,const void* b){
  char const* first = *(char const**) a;
  char const* second = *(char const**) b;
  while(*first != ' ' && *second != ' ' && *first == *second){
    first++;
    second++;
      }
  if(*first == ' ' && *second == ' '){
    return 0;
  }
  else if(*first == ' '){
    return -(*second^42);
  }
  else if(*second == ' '){
    return *first^42;
  }
  else{
    return (*first^42)-(*second^42);
      }
}

int main(){
  char** record = NULL;
  int strCount = 0;
  char* currStr = NULL;
  int charCount = 0;
  char c = getchar();
  if(ferror(stdin)){
    fprintf(stderr, "Error reading from stdin");
    exit(1);
  }
  while(1){
    if(c == EOF){
      if(charCount != 0){
	charCount++;
	currStr = realloc(currStr, charCount*sizeof(char));
	if(!currStr){
	  fprintf(stderr, "Error allocating memory");
	  exit(1);
	}
	currStr[charCount-1] = ' ';
	strCount++;
	record = realloc(record, strCount*sizeof(char*));
	if(!record){
	  fprintf(stderr, "Error allocating memory");
	  exit(1);
	}
	record[strCount-1] = currStr;
      }
      break;
    }
    charCount++;
    currStr = realloc(currStr, charCount*sizeof(char));
    if(!currStr){
      fprintf(stderr, "Error allocating memory");
      exit(1);
    }
    currStr[charCount-1] = c;
    if(c == ' '){
      strCount++;
      record = realloc(record, strCount*sizeof(char*));
      if(!record){
	fprintf(stderr, "Error allocating memory");
	exit(1);
      }
      record[strCount-1] = currStr;
      currStr = NULL;
      charCount = 0;
    }
    c = getchar();
    if(ferror(stdin)){
      fprintf(stderr, "Error reading from stdin");
      exit(1);
    }
  }
  if(record == NULL){
    return 0;
  }
  qsort(record, strCount, sizeof(char*), frobcmp);
  int i = 0;
  for(i = 0; i < strCount; i++){
    char* str = record[i];
    for(;*str != ' '; str++){
      putchar(*str);
    }
    putchar(*str);
  }
  for(i = 0; i < strCount; i++){
    free(record[i]);
  }
  free(record);
  return 0;
}
