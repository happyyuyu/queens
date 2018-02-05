/**Authors: Harry Zhou and Niall Williams
 * n Queens
 * CSC 322 - Programming Languages
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int getBoardSize();
int displayRecurse(int size, int cur, int * a);
int countRecurse(int size, int cur, int * a, int * counter);
int checkHori(int position, int curC, int * a);
int checkDiag(int position, int curC, int * a);
void print(int size, int * a);
void display();
void count();

int main(){
  char input;

  while(1){
    printf("Enter c for count, d for display, or q to quit: ");
    scanf("%s", &input);

    if(input != 'q' && input != 'Q' && input != 'c' &&
       input != 'C' && input != 'd' && input != 'D'){
         printf("I don't understand that. Try again.\n");
       }

    //Quit
    if (input == 'q' || input == 'Q'){
      return 0;
    }

    //Display mode
    else if (input == 'd' || input == 'D'){
      display();
      scanf("%c", &input);
    }

    //Count mode
    else if (input == 'c' || input == 'C'){
      count();
      scanf("%c", &input);
    }
  }
}

/* Check the horizontal spots on the board for the given position curC. Returns true if
there is a valid diagonal spot to place a queen. */
int checkHori(int position, int curC, int * a){
  for (int i = 0; i < curC; i++){
    if (a[i] == position) return 0;
  }
  return 1;
}

/* Check the diagonal spots on the board for the given position curC. Returns true if
there is a valid diagonal spot to place a queen. */
int checkDiag(int position, int curC, int * a){
  for (int i = 0; i < curC; i++){
    if (((a[i] + (curC - i)) == position) || ((a[i] - (curC - i)) == position))
      return 0;
  }

  return 1;
}

/* Recursively solves an nxn chessboard and stores the queens' locations in an array. */
int displayRecurse(int size, int curC, int * a){
  //When we are on the last column
  if (curC == size - 1){
    for(int i = 0; i < size; i++){
      if (checkDiag(i, curC, a) && checkHori(i, curC, a)){
        a[curC] = i;
        return 1; //Solution found, quit out
      }
    }
    return 0;
  }

  //Keep going
  else{
    for(int i = 0; i < size; i++){
      if (checkDiag(i, curC, a) && checkHori(i, curC, a)){
        a[curC] = i;
        if (displayRecurse(size, curC + 1, a)) return 1;
      }
    }
    return 0;
  }
  return 0;
}

/* Recursively counts all unique solutions in an nxn chessboard. */
int countRecurse(int size, int curC, int * a, int * counter){
  //When we are on the last column
  if (curC == size - 1){
    for(int i = 0; i < size; i++){
      if (checkDiag(i, curC, a) && checkHori(i, curC, a)){
        a[curC] = i;
        *counter +=  1; //Solution found, increment counter
        return 1;
      }
    }
    return 0;
  }

  //Keep going
  else{
    for(int i = 0; i < size; i++){
      if (checkDiag(i, curC, a) && checkHori(i, curC, a)){
        a[curC] = i;
        countRecurse(size, curC + 1, a, counter);
      }
    }
    return 0;
  }
  return 0;
}

/* Prints the solved chessboard of the correct size. */
void print(int size, int * a){
  for (int i = 0; i < size*2+1; i++)
    printf("-");
  printf("\n");

  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      int queenPos = a[j];
      if (i == queenPos)
        printf("|Q");
      else
        printf("|_");
    }
    printf("|\n");
  }
}

/* Function that creates the array of appropriate size and calls the display
recursive function. Prints the output of the display recursive function. */
void display(){
  int size = 0;
  struct timeval startTime, endTime;

  printf("Enter size of chessboard, n: ");
  scanf("%d", &size);

  //Ensure the board size is valid
  while (size < 1){
    printf("Please enter a positive number: ");
    scanf("%d", &size);
  }

  gettimeofday(&startTime, NULL); //Begin timer
  int * a = (int *)malloc(size * sizeof(int)); //Create array of the correct size
  int result = displayRecurse(size, 0, a);
  gettimeofday(&endTime, NULL); //End timer

  if (result){
    print(size, a);
    printf("Elapsed time: %f seconds", (float)(endTime.tv_sec - startTime.tv_sec) +
                                      (float)(endTime.tv_usec - startTime.tv_usec)/1000000);
    printf("\n\n");
  }
  else
    printf("No solutions exist!");

  free(a); //Reset the array so the user can try another board size
}

/* Function that creates the array of appropriate size and calls the counting
recursive function. Prints the output of the counting recursive function. */
void count(){
  int countTracker = 0;
  int * counter = &countTracker;
  int size = 0;
  struct timeval startTime, endTime;

  printf("Enter size of chessboard, n: ");
  scanf("%d", &size);

  //Ensure the board size is valid
  while (size < 1){
    printf("Please enter a positive number: ");
    scanf("%d", &size);
  }

  gettimeofday(&startTime, NULL); //Begin timer
  int * a = (int *)malloc(size * sizeof(int)); //Create array of the correct size
  int result = countRecurse(size, 0, a, counter);
  gettimeofday(&endTime, NULL); //End timer

  if (*counter > 0){ //If there are solutions
    printf("Total number of solutions: %d", (int) *counter);
    printf("\nElapsed time: %f seconds", (float)(endTime.tv_sec - startTime.tv_sec) +
                                      (float)(endTime.tv_usec - startTime.tv_usec)/1000000);
    printf("\n\n");
  }
  else
    printf("No solutions exist!");

  free(a);
}
