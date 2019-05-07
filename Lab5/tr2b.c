#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){
  const char* from = argv[1];
  // if from has duplicate bytes
  // exit with error
  int lenFrom = strlen(from);
  for(int i = 0; i < lenFrom; i++){
    for(int j = i+1; j < lenFrom; j++){
      if(from[i] == from[j]){
	fprintf(stderr, "ERROR: from has duplicate bytes\n");
	exit(1);
      }
    }
  }
  const char* to = argv[2];
  // if from and to are not of the same length
  // exit with error 
  if(lenFrom != strlen(to)){
    fprintf(stderr, "ERROR: from and to are not of the same length\n");
    exit(1);
  }
  
  while(1){
    int c = getchar();
    if(c == EOF){
      break;
    }
    for(int i = 0; i < lenFrom; i++){
      if(from[i] == c){
	c = to[i];
	break;
      }
    }
    putchar(c);
  }

  return 0;
}
