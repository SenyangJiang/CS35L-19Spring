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
  char** record = malloc(0);
  int strCount = 0;
  char* currStr = malloc(0);
  int charCount = 0;
  int c = getchar();
  while(1){
    if(c == EOF){
      if(charCount != 0){
	charCount++;
	currStr = realloc(currStr, charCount*sizeof(char));
	currStr[charCount-1] = ' ';
	strCount++;
	record = realloc(record, strCount*sizeof(char*));
	record[strCount-1] = currStr;
      }
      break;
    }
    charCount++;
    currStr = realloc(currStr, charCount*sizeof(char));
    currStr[charCount-1] = c;
    if(c == ' '){
      strCount++;
      record = realloc(record, strCount*sizeof(char*));
      record[strCount-1] = currStr;
      currStr = malloc(0);
      charCount = 0;
    }
    c = getchar();
  }
  int i = 0;
  qsort(record, strCount, sizeof(char*), frobcmp);
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
