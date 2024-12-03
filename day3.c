#include <stdio.h>
#include <string.h>
#include <ctype.h>

char * input = ")potato():']mul(12,936)"; // example input

int main()
{
  int len = strlen(input);
  int enabled = 1;
  int total = 0;
  int i = 0;

  while (i < len){
    /**
     * PART 2
     */
    if (input[i] == 'd' && input[i+1] == 'o' && input[i+2] == 'n' && input[i+3] == '\''
    && input[i+4] == 't' && input[i+5] == '(' && input[i+6] == ')'){
      enabled = 0;
      i += 7;
      while (i < len && !(input[i] == 'd' && input[i+1] == 'o' && input[i+2] == '(' && input[i+3] == ')')){
        i++;
      }
      continue;
    }
    else if (input[i] == 'd' && input[i+1] == 'o' && input[i+2] == '(' && input[i+3] == ')'){
      enabled = 1;
      i += 4;
    }
        
    /**
     * PART 1
     */
    if (input[i] == 'm' && input[i+1] == 'u' && input[i+2] == 'l' && input[i+3] == '('){
      i += 4;
      int left = 0, right = 0;

      while (i < len && isdigit(input[i])){
        left = left * 10 + (input[i++] - '0');
      }

      if (input[i] == ','){
        i++;
        while (i < len && isdigit(input[i])){
          right = right * 10 + (input[i++] - '0');
        }
        if (input[i] == ')' && enabled){
          total += (left * right);
        }
        i++;
      }
    }
    else{
      i++;
    }
  }
  printf("Total: %d\n", total);
}