#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char input[] = "1 2 3 4 5 6 7 8\n1 2 3 4 5 6 7 8\n1 2 3 4 5 6 7 8\n1 2 3 4 5 6 7 8"; // example input

#define MAX_LINE_LENGTH 26
#define MAX_NUM_LINES 4

/*
 * PART 1 function: Check if the given line is safe.
 * A line is considered safe if:
 * 1. The absolute difference between consecutive values is between 1 and 3 (inclusive).
 * 2. The values should not switch between increasing and decreasing patterns.
 *
 * @param *arr: The array of integers to check.
 * @param size: The size of the array.
 *
 * @return 1 if the line is safe, 0 if it is not.
 */
int is_safe(int *arr, int size) {
  int increasing = 0, decreasing = 0;
  int prev_val = arr[0];

  for (int j = 1; j < size; j++) {
    int diff = arr[j] - prev_val;

    if (abs(diff) > 3 || abs(diff) < 1) {
      return 0;
    }

    if (diff > 0) increasing++;
    if (diff < 0) decreasing++;

    if (increasing && decreasing) {
      return 0;
    }

    prev_val = arr[j];
  }
  return 1;
}

/**
 * PART 2 function: Check if the list can be made safe by removing one element.
 * It attempts to remove each element from the list and checks if the resulting list is safe.
 *
 * @param *arr: The array of integers to check.
 * @param size: The size of the array.
 *
 * @return 1 if removing one element makes the list safe, otherwise 0.
 */
int safe_removal(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    int new_size = size - 1;
    int *new_arr = (int *)malloc(new_size * sizeof(int));
    if (!new_arr) return 0;

    for (int j = 0, k = 0; j < size; j++) {
      if (j != i) {
        new_arr[k++] = arr[j];
      }
    }

    int safe = is_safe(new_arr, new_size);
    free(new_arr);

    if (safe) {
        return 1;
    }
  }
  return 0;
}


int main()
{
  // data pre-processing 
  int *array[MAX_NUM_LINES] = {0};
  int row_sizes[MAX_NUM_LINES] = {0};
  int num_rows = 0;
  
  char *saveptr1;
  char *line = strtok_r(input, "\n", &saveptr1);
  
  while (line != NULL && num_rows < MAX_NUM_LINES) {
    int count = 0;
    for(char *p = line; *p; p++) {
      if (*p == ' ') count++;
    }
    count = count ? count + 1 : 1;

    array[num_rows] = (int *)malloc(count * sizeof(int));
    if (array[num_rows] == NULL) {
      return 1;
    }

    row_sizes[num_rows] = count;

    char *saveptr2;
    char *token = strtok_r(line, " ", &saveptr2);
    int idx = 0;
    
    while(token != NULL && idx < count) {
      array[num_rows][idx++] = strtol(token, NULL, 10);
      token = strtok_r(NULL, " ", &saveptr2);
    }

    num_rows++;
    line = strtok_r(NULL, "\n", &saveptr1);
  }

  int safe = 0;
  for (int i = 0; i < num_rows; i++) {
    /**
     * PART 1
     */
     
    /*if (is_safe(array[i], row_sizes[i])) {
      safe++;
    }*/
    
    /**
     * PART 2
     */
     
    if (safe_removal(array[i], row_sizes[i])) {
      safe++;
    }
  }
  
  for (int i = 0; i < num_rows; i++) {
    free(array[i]);
  }
  
  printf("Total safe lines: %d\n", safe);
}