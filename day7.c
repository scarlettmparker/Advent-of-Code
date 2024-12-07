#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// example input
char input[] = "190: 10 19\n3267: 81 40 27\n83: 17 5\n156: 15 6\n7290: 6 8 6 15\n161011: 16 10 13\n192: 17 8 14\n21037: 9 7 18 13\n292: 11 6 16 20";

#define TESTS 9
#define MAX_EQUATIONS 4

/**
 * Function to calculate the number of digits in a number.
 * Used to quickly concatenate numbers in part 2.
 *
 * @param n Number to calculate the number of digits for.
 */
static inline int num_digits(int n) {
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 10;
}

/**
 * Recursive function to calculate if the equations can reach the test value.
 * It recursively tries to add and multiply the numbers in the equation to reach the test value.
 * If the value is greater than the test value, it returns 0 for early stopping of the branch.
 *
 * @param test Test value to reach.
 * @param nums Array of numbers (the equation).
 * @param len Length of the array.
 * @param current Current value of the equation.
 * @param idx Current index in the array.
 * @param part2 Flag to enable part 2 logic.
 */
int calculate_test(long test, int *nums, int len, long current, int idx, int part2) {
    if (idx == len) return current == test;
    if (idx == 0) return calculate_test(test, nums, len, nums[0], 1, part2);

    if (calculate_test(test, nums, len, current + nums[idx], idx + 1, part2)) 
        return 1;
    if (calculate_test(test, nums, len, current * nums[idx], idx + 1, part2))
        return 1;
        
    if (part2) {
      long power = 1;
      for(int i = 0; i < num_digits(nums[idx]); i++) {
        power *= 10;
      }
      if (calculate_test(test, nums, len, current * power + nums[idx], idx + 1, part2))
          return 1;
    }

    return 0;
}

/**
 * Function to calculate the total of tests given that the equations can reach the test value.
 * 
 * @param left Array of test values.
 * @param left_len Length of the array.
 * @param right Array of equations.
 * @param right_sizes Array of sizes of the equations.
 * @param part2 Flag to enable part 2 logic.
 */
long calculate_total(long *left, int left_len, int right[][MAX_EQUATIONS], int *right_sizes, int part2) {
  long total = 0;
  
  for (int i = 0; i < left_len; i++) {
    if (right_sizes[i] == 1 && left[i] == right[i][0]) {
      total += left[i];
    } else if (calculate_test(left[i], right[i], right_sizes[i], 0, 0, part2)) {
      total += left[i];
    }
  }
  
  return total;
}

int main()
{
    /* DATA PREPROCESSING */
    char *line;
    char *rest = input;
    long tests[TESTS];
    int equations[TESTS][MAX_EQUATIONS];
    int test_count = 0;
    int equation_count[TESTS] = {0};

    while ((line = strtok_r(rest, "\n", &rest))) {
        char *lhs = strtok(line, ":");
        char *rhs = strtok(NULL, ":");

        tests[test_count] = atoll(lhs);

        char *num;
        char *rhs_rest = rhs;
        while ((num = strtok_r(rhs_rest, " ", &rhs_rest))) {
            equations[test_count][equation_count[test_count]++] = atoi(num);
        }

        test_count++;
    }

    /* PART 1 AND PART 2 */
    long p1_total = calculate_total(tests, test_count, equations, equation_count, 0);
    long p2_total = calculate_total(tests, test_count, equations, equation_count, 1);

    printf("Part 1 total: %ld\n", p1_total);
    printf("Part 2 total: %ld\n", p2_total);
    return 0;
}