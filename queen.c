// Authors: Harry Zhou and Niall Williams

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int recurse(int size, int cur, int * a);
int recurse2(int size, int cur, int * a, int * counter);
int checkHori(int position, int curC, int * a);
int checkDiag(int position, int curC, int * a);
void print(int size, int * a);
void display();
void count(int * counter);

int main(){
  int countTracker = 0;
  int * counter = &countTracker;
  char input;


  printf("Enter c for count, d for display, or q to quit: ");
  scanf("%c", &input);

  while (input != 'q'){
    if (input == 'd'){
      display();
      scanf("%c", &input);
    }
    else if (input == 'c'){
      count(counter);
      scanf("%c", &input);
    }
    else{
      printf("Sorry, I don't understand that. Please try again: ");
      scanf("%c", &input);
    }
  }
  exit(0);


  // struct timeval startTime, endTime;
  // gettimeofday(&startTime, NULL);
  // recurse2(13, 0, a, counter);
  // printf("%d", count);
  // gettimeofday(&endTime, NULL);
  // printf("\n");
  // printf("Elapsed time: %f seconds", (float)(endTime.tv_sec - startTime.tv_sec) + (float)(endTime.tv_usec - startTime.tv_usec)/1000000);
}

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

int recurse2(int size, int curC, int * a, int * counter){
  if (curC == size - 1){
    for(int i = 0; i < size; i++){
      if (checkDiag(i, curC, a) && checkHori(i, curC, a)){
        a[curC] = i;
        *counter +=  1;
        return 1;
      }
    }
    return 0;
  }
  else{
    for(int i = 0; i < size; i++){
      if (checkDiag(i, curC, a) && checkHori(i, curC, a)){
        a[curC] = i;
        recurse2(size, curC + 1, a, counter);
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

void display(){
  int size;

  printf("Enter size of chessboard, n: ");
  scanf("%d", &size);
  int * a = (int *)malloc(size * sizeof(int));
  int result = recurse(size, 0, a);
  if (result){
    print(size, a);
  }
  else{
    printf("No solutions exist!");
  }
  free(a);
}

void count(int * counter){
  int size;

  printf("Enter size of chessboard, n: ");
  scanf("%d", &size);
  int * a = (int *)malloc(size * sizeof(int));
  int result = recurse2(size, 0, a, counter);
  if (result){
    print("Total number of solutions: %d", *counter);
  }
  else{
    printf("No solutions exist!");
  }
  *counter = 0;
  free(a);
}