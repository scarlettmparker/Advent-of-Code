#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// no example input today i am too lazy to make one
char input[] = "no example input";

#define START_POS 9531
#define LINE_HEIGHT 130
#define TABLE_SIZE 101
#define DIR_SIZE 4

enum DIRECTION {UP, RIGHT, DOWN, LEFT};

typedef struct Node {
  int value;
  struct Node* next;
} Node;

typedef struct HashSet {
  Node * table[TABLE_SIZE];
  int count;
} HashSet;

unsigned int hash(int value) {
  return abs(value) % TABLE_SIZE;
}

HashSet* create_set() {
  HashSet* set = (HashSet*)malloc(sizeof(HashSet));
  set->count = 0;
  for (int i = 0; i < TABLE_SIZE; i++) {
    set->table[i] = NULL;
  }
  return set;
}

void insert(HashSet* set, int value) {
  unsigned int index = hash(value);
  Node* current = set->table[index];
  
  while (current != NULL) {
    if (current->value == value) return;
    current = current->next;
  }
  
  Node* new_node = (Node*)malloc(sizeof(Node));
  new_node->value = value;
  new_node->next = set->table[index];
  
  set->table[index] = new_node;
  set->count++;
}

int contains(HashSet* set, int value) {
  unsigned int index = hash(value);
  Node* current = set->table[index];
  
  while (current != NULL) {
    if (current->value == value) return 1;
    current = current->next;
  }
  
  return 0;
}

void free_set(HashSet* set) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    Node* current = set->table[i];
    while (current != NULL) {
      Node* temp = current;
      current = current->next;
      free(temp);
    }
  }
  
  free(set);
}

int count(HashSet* set) {
  return set->count;
}

int make_move(int* pos, int* dir, int len, char *input) {
  int next_pos, next_col;
  int col = *pos % LINE_HEIGHT;
    
  switch (*dir) {
    case UP:
      next_pos = *pos - LINE_HEIGHT;
      if (next_pos < 0) return 0;
            
      if (input[next_pos] == '.') {
        *pos = next_pos;
      } else {
        *dir = (*dir + 1) % DIR_SIZE;
      }
      break;
    case RIGHT:
      next_pos = *pos + 1;
      next_col = next_pos % LINE_HEIGHT;
      if (abs(next_col - col) == LINE_HEIGHT - 1) return 0;
            
      if (input[next_pos] == '.') {
        *pos = next_pos;
      } else {
        *dir = (*dir + 1) % DIR_SIZE;
      }
      break;
    case DOWN:
      next_pos = *pos + LINE_HEIGHT;
      if (next_pos > len) return 0;
            
      if (input[next_pos] == '.') {
        *pos = next_pos;
      } else {
        *dir = (*dir + 1) % DIR_SIZE;
      }
      break;
    case LEFT:
      next_pos = *pos - 1;
      next_col = next_pos % LINE_HEIGHT;

      if (abs(next_col - col) == LINE_HEIGHT - 1) return 0;

      if (input[next_pos] == '.') {
        *pos = next_pos;
      } else {
        *dir = (*dir + 1) % DIR_SIZE;
      }
      break;
    default:
      return 0;
    }
  return 1;
}

int loop(int start_pos, char* input, int len) {
  int pos = start_pos;
  int dir = UP;
  int moves = 0;
  const int MAX_MOVES = 10000;
    
  while (moves < MAX_MOVES) {
    if (!make_move(&pos, &dir, len, input)) {
      return 0;
    }
    moves++;
  }
  return 1;
}

int main()
{
  int pos = START_POS;
  int dir = UP;
  int len = strlen(input);
  int obstacles = 0;
  
  HashSet* set = create_set();
  int can_move = 1;
  
  while(can_move) {
    insert(set, pos);
    can_move = make_move(&pos, &dir, len, input);
  }
    
  int visited = count(set);
  for (int i = 0; i < TABLE_SIZE; i++) {
    Node* current = set->table[i];
    pos = START_POS;

    while (current != NULL) {
      char* new_input = strdup(input);
      new_input[current->value] = '#';
        
      if (loop(pos, new_input, len)) {
        obstacles++;
      }
        
      free(new_input);
      current = current->next;
    }
  }

  free_set(set);
  printf("Total visited: %d\n", visited);
  printf("Total obstacles: %d\n", obstacles);
}