#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const* a,char const* b){
  while(*a != ' ' && *b != ' '){
    if((*a^42) > (*b^42)){
      return 1;
    }
    else if((*a^42) < (*b^42)){
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
      // add a trailing space if necessary
      if(charCount != 0){
	charCount++;
	currStr = (char*)realloc(currStr, charCount*sizeof(char));
	// check whether space is allocated
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
      break;
    }
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
    c = getchar();
    if(ferror(stdin)){
      fprintf(stderr, "Error reading from stdin");
      exit(1);
    }
  }
  // if file is empty, return immediately
  if(record == NULL){
    return 0;
  }
  
  qsort(record, strCount, sizeof(char*), comp);

  // print sorted record
  int i = 0;
  for(i = 0; i < strCount; i++){
    char* str = record[i];
    for(;*str != ' '; str++){
      putchar(*str);
    }
    putchar(*str);
  }
  
  // free memory of strings and record itself
  for(i = 0; i < strCount; i++){
    free(record[i]);
  }
  free(record);
  return 0;
}
