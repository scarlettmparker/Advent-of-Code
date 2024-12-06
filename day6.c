#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// no example input today i am too lazy to make one
char input[] = "no example input";

#define START_POS 9531
#define LINE_LENGTH 130
#define TABLE_SIZE 101
#define DIR_SIZE 4
#define LOOP_MOVES 7000
#define MAX_POSITIONS 16900
#define BITSET_SIZE (MAX_POSITIONS/64 + 1)

enum DIRECTION {UP, RIGHT, DOWN, LEFT};

typedef unsigned long BITSET[BITSET_SIZE];

void set_bit(BITSET bits, const int pos) {
  bits[pos/64] |= 1UL << (pos % 64);
}

int test_bit(const BITSET bits, const int pos) {
  return (bits[pos/64] & (1UL << (pos % 64))) != 0;
}

int count_bits(const BITSET bits) {
  int count = 0;
  for(int i = 0; i < BITSET_SIZE; i++) {
    unsigned long x = bits[i];
    x = x - ((x >> 1) & 0x5555555555555555UL);
    x = (x & 0x3333333333333333UL) + ((x >> 2) & 0x3333333333333333UL);
    x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0FUL;
    count += (x * 0x0101010101010101UL) >> 56;
  }
  return count;
}

void clear_bitset(BITSET bits) {
  memset(bits, 0, sizeof(BITSET));
}

int make_move(int* pos, int* dir, const int len, const char* input) {
  const int curr_col = *pos % LINE_LENGTH;
  const int moves[4] = {-LINE_LENGTH, 1, LINE_LENGTH, -1};
  const int next_pos = *pos + moves[*dir];
  const int next_col = next_pos % LINE_LENGTH;

  if (*dir == UP && next_pos < 0) return 0;
  if (*dir == DOWN && next_pos >= len) return 0;
  if ((*dir == LEFT || *dir == RIGHT) && abs(next_col - curr_col) != 1) return 0;

  if (input[next_pos] == '.') {
    *pos = next_pos;
  } else {
    *dir = (*dir + 1) % DIR_SIZE;
  }
  return 1;
}

void set_state_bit(BITSET bits, const int pos, const int dir) {
  int state = pos * DIR_SIZE + dir;
  bits[state / 64] |= 1UL << (state % 64);
}

int test_state_bit(const BITSET bits, const int pos, const int dir) {
  int state = pos * DIR_SIZE + dir;
  return (bits[state / 64] & (1UL << (state % 64))) != 0;
}

int loop(const int start_pos, const char* input, const int len) {
  int pos = start_pos;
  int dir = UP;
  
  for(int moves = 0; moves < LOOP_MOVES; moves++) {
    if (!make_move(&pos, &dir, len, input)) return 0;
  }
  return 1;
}

int main() {
  int pos = START_POS;
  int dir = UP;
  const int len = strlen(input);
  int obstacles = 0;
  
  BITSET visited;
  clear_bitset(visited);
  set_bit(visited, pos);
	
  while(make_move(&pos, &dir, len, input)) {
    set_bit(visited, pos);
  }
  
  const int total_visited = count_bits(visited);
  
  for(int i = 0; i < MAX_POSITIONS; i++) {
    if(!test_bit(visited, i)) continue;
    
    char* new_input = strdup(input);
    new_input[i] = '#';
    
    if(loop(START_POS, new_input, len)) {
      obstacles++;
    }
		
    free(new_input);
  }

  printf("Total visited: %d\n", total_visited);
  printf("Total obstacles: %d\n", obstacles);
  return 0;
}