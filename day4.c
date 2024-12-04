#include <stdio.h>
#include <string.h>

// example input (not real)
const char input[] = "QWERTYXMASZXMASVBNMASWXYZMASXMASYXMASMASZXMASABCXMASXMASXMASZMASQWERTYXMASZXMASVBNMASWXYZMASXMASYXMASMASZXMASABCXMASXMASXMASZMAS";

#define LINE_LENGTH 20

int main()
{
  clock_t begin = clock();
  int len = strlen(input);
  int total_p1 = 0;
  int total_p2 = 0;
    
  for (int i = 0; i < len; i++) {
    /**
     * PART 1
     */
    if (i % LINE_LENGTH + 3 < LINE_LENGTH && input[i] == 'X' && input[i + 1] == 'M' && input[i + 2] == 'A' && input[i + 3] == 'S')
        total_p1++; // hr
    if (i % LINE_LENGTH - 3 >= 0 && input[i] == 'X' && input[i - 1] == 'M' && input[i - 2] == 'A' && input[i - 3] == 'S')
        total_p1++; //hl
    if (i + 3 * LINE_LENGTH < len && input[i] == 'X' && input[i + LINE_LENGTH] == 'M' && input[i + 2 * LINE_LENGTH] == 'A' && input[i + 3 * LINE_LENGTH] == 'S')
        total_p1++; //vd
    if (i - 3 * LINE_LENGTH >= 0 && input[i] == 'X' && input[i - LINE_LENGTH] == 'M' && input[i - 2 * LINE_LENGTH] == 'A' && input[i - 3 * LINE_LENGTH] == 'S')
        total_p1++; //vu
    if (i % LINE_LENGTH + 3 < LINE_LENGTH && i + 3 * LINE_LENGTH + 3 < len && input[i] == 'X' && input[i + LINE_LENGTH + 1] == 'M' && input[i + 2 * LINE_LENGTH + 2] == 'A' && input[i + 3 * LINE_LENGTH + 3] == 'S')
        total_p1++; //dr
    if (i % LINE_LENGTH - 3 >= 0 && i - 3 * LINE_LENGTH - 3 >= 0 && input[i] == 'X' && input[i - LINE_LENGTH - 1] == 'M' && input[i - 2 * LINE_LENGTH - 2] == 'A' && input[i - 3 * LINE_LENGTH - 3] == 'S')
        total_p1++; //ul
    if (i % LINE_LENGTH - 3 >= 0 && i + 3 * LINE_LENGTH - 3 < len && input[i] == 'X' && input[i + LINE_LENGTH - 1] == 'M' && input[i + 2 * LINE_LENGTH - 2] == 'A' && input[i + 3 * LINE_LENGTH - 3] == 'S')
        total_p1++; //dl
    if (i % LINE_LENGTH + 3 < LINE_LENGTH && i - 3 * LINE_LENGTH + 3 >= 0 && input[i] == 'X' && input[i - LINE_LENGTH + 1] == 'M' && input[i - 2 * LINE_LENGTH + 2] == 'A' && input[i - 3 * LINE_LENGTH + 3] == 'S')
        total_p1++; //ur
    
    /**
     * PART 2
     */
     
    if (i + 2 * LINE_LENGTH + 2 < len && i % LINE_LENGTH + 2 < LINE_LENGTH) {
      if (input[i] == 'M' && input[i + LINE_LENGTH + 1] == 'A' && input[i + 2 * LINE_LENGTH + 2] == 'S') {
        if (input[i + 2] == 'M' && input[i + LINE_LENGTH + 1] == 'A' && input[i + 2 * LINE_LENGTH] == 'S') {
          total_p2++;
        } else if (input[i + 2] == 'S' && input[i + LINE_LENGTH + 1] == 'A' && input[i + 2 * LINE_LENGTH] == 'M') {
          total_p2++;
        }
      } else if (input[i] == 'S' && input[i + LINE_LENGTH + 1] == 'A' && input[i + 2 * LINE_LENGTH + 2] == 'M') {
        if (input[i + 2] == 'M' && input[i + LINE_LENGTH + 1] == 'A' && input[i + 2 * LINE_LENGTH] == 'S') {
          total_p2++;
        } else if (input[i + 2] == 'S' && input[i + LINE_LENGTH + 1] == 'A' && input[i + 2 * LINE_LENGTH] == 'M') {
          total_p2++;
        }
      }
    }
  }
  
  printf("Part 1 Total: %d\n", total_p1);
  printf("Part 2 Total: %d\n", total_p2);
}