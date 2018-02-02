#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int recurse(int size, int cur, int * a);
int checkHori(int position, int curC, int * a);
int checkDiag(int position, int curC, int * a);
void print(int size, int * a);

int checkHori(int position, int curC, int * a){
  for (int i = 0; i < curC; i++){
    if (a[i] == position) return 0;
  }
  return 1;
}


int checkDiag(int position, int curC, int * a){
  for (int i = 0; i < curC; i++){
    if ((a[i] + (curC - i)) == position) return 0;
    if ((a[i] - (curC - i)) == position) return 0;
  }
  return 1;
}

int recurse(int size, int curC, int * a){
  if (curC == size - 1){
    for(int i = 0; i < size; i++){
      if (checkDiag(i, curC, a) && checkHori(i, curC, a)){
        a[curC] = i;
        return 1;
      }
    }
    return 0;
  }
  else{
    for(int i = 0; i < size; i++){
      if (checkDiag(i, curC, a) && checkHori(i, curC, a)){
        a[curC] = i;
        if (recurse(size, curC + 1, a)) return 1;
      }
    }
    return 0;
  }
  return 0;
}

void print(int size, int * a){
  for (int i = 0; i < size*2+1; i++){
    printf("-");
  }
  printf("\n");
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      int queenPos = a[j];
      if (i == queenPos) printf("|Q");
      else printf("|_");
    }
    printf("|\n");
  }
}

int main(){
  int * a = (int *)malloc(10 * sizeof(int));
  /*a[0] = 0;
  a[1] = 2;
  a[2] = 6;*/
  //printf("%d", recurse(4, 0, a));
  recurse(10, 0, a);
  print(10, a);
}
