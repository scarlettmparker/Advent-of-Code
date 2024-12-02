#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char * input = "12345123451234512345"; // example input

#define TABLE_SIZE 2

typedef struct {
  int key;
  int value;
  int in_use;
} HashMapEntry;

typedef struct {
  HashMapEntry* table[TABLE_SIZE];
} HashMap;

unsigned int hash(int key) {
  return key % TABLE_SIZE;
}

/**
 * Function to create a hash map.
 * This function initializes a hash map with pre-defined
 * TABLE_SIZE and sets all entries to null.
 * 
 * @return A pointer to the hash map.
 */
HashMap* create_map() {
  HashMap* map = (HashMap*)malloc(sizeof(HashMap));
  for (int i = 0; i < TABLE_SIZE; i++) {
    map->table[i] = NULL;
  }
  return map;
}

/**
 * Function to insert a K-V pair into the hash map.
 * 
 * This function calculates the index for the given key
 * and inserts the K-V pair at the position in the table.
 * If a collision occurs, linear probing is used.
 * 
 * @param map A pointer to the hash map.
 * @param key Key to be inserted.
 * @param value Value associated with the key.
 */
void insert(HashMap* map, int key, int value) {
  unsigned int index = hash(key);
  
  while (map->table[index] != NULL && map->table[index]->in_use) {
    index= (index + 1) % TABLE_SIZE;
  }
  
  if (map->table[index] == NULL) {
    map->table[index] = (HashMapEntry*)malloc(sizeof(HashMapEntry));
  }
  
  map->table[index]->key = key;
  map->table[index]->value = value;
  map->table[index]->in_use = 1;
}

/**
 * Function to search for a value by key in a hash map.
 * 
 * This calculates the index for the given key
 * and checks if the key exists in the table.
 * If found, the associated value is returned, otherwise -1.
 * 
 * @param map A pointer to the hash map.
 * @param key Key to search for.
 * 
 * @return Value associated with the key, or -1.
 */
int search(HashMap* map, int key) {
  unsigned int index = hash(key);
  
  while (map->table[index] != NULL) {
    if (map->table[index]->in_use && map->table[index]->key == key) {
      return map->table[index]->value;
    }
    index = (index + 1) % TABLE_SIZE;
  }
  
  return -1;
}

/**
 * Function to free the memory allocated for a hash map.
 * This function frees each entry in the table
 * and then frees the hash map itself.
 * 
 * @param map A pointer to the hash map to be freed.
 */
void free_map(HashMap* map) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (map->table[i] != NULL) {
      free(map->table[i]);
    }
  }
  free(map);
}

/**
 * Function to insert or update a key in the hash map,
 * incrementing its value if the key already exists.
 * 
 * It calcalates the index for the key and checks
 * if the key already exists in the table.
 * If found, the value is incremented, if not,
 * a new entry is created with a value of 1.
 * 
 * @param map A pointer to the hash map.
 * @param key Key to be inserted or updated.
 */
void insert_update(HashMap* map, int key) {
  unsigned int index = hash(key);
  
  while (map->table[index] != NULL && map->table[index]->in_use) {
    if (map->table[index]->key == key) {
      map->table[index]->value++;
      return;
    }
    index = (index + 1) % TABLE_SIZE;
  }
  
  if (map->table[index] == NULL) {
    map->table[index] = (HashMapEntry*)malloc(sizeof(HashMapEntry));
  }
  
  map->table[index]->key = key;
  map->table[index]->value = 1;
  map->table[index]->in_use = 1;
}

/**
 * Function to print all K/V pairs in a hash map.
 * 
 * It iterates through the table and prints the
 * keys and values ofa ll entries that are in use.
 * 
 * @param map A pointer to the hash map to be printed.
 */
void print_map(HashMap* map) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (map->table[i] != NULL && map->table[i]->in_use) {
      printf("Key: %d, Count: %d\n", map->table[i]->key, map->table[i]->value);
    }
  }
}

/**
 * Comparison function for sorting integers.
 * Compares two integers for use in sorting functions.
 * 
 * @param a A pointer to the first integer.
 * @param b A pointer to the second integer.
 * 
 * @return A negative number if a < b, zero if 
 * a == b, or a positive integer if a > b.
 */
int comp(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

/**
 * Function to remove duplicates from a sorted array.
 * Removes duplicate elements from a sorted array
 * and returns the new length of the array.
 * 
 * @param arr A pointer to the array to remove duplicates from.
 * @param n Current size of the array.
 * 
 * @return New size of the array after duplicates are removed.
 */
int remove_duplicates(int * arr, int n) {
  if (n == 0) return 0;
  
  int j = 0;
  for (int i = 1; i < n - 1; i++) {
    if (arr[i] != arr[j]) arr[++j] = arr[i];
  }
  
  return j + 1;
}

int main()
{
  int left[TABLE_SIZE] = {0};
  int right[TABLE_SIZE] = {0};   
  int len = strlen(input);
  int left_c = 0, right_c = 0;
    
  // preprocess data to get left and right arrays
  for (int i = 0; i < len; i += 5) {
    int value = 0;
    for (int j = 0; j < 5 && (i + j) < len; ++j) {
      value = value * 10 + (input[i  + j] - '0');
    }
    if ((i / 5) % 2 == 0 ) {
      left[left_c++] = value;
    } else {
      right[right_c++] = value;
    }
  }
  
  /* 
   * PART 1 CODE
   */
  qsort(left, TABLE_SIZE, sizeof(int), comp);
  qsort(right, TABLE_SIZE, sizeof(int), comp);  
  
  int p1_total = 0;
  for (int i = 0; i < TABLE_SIZE; i++) {
    p1_total += abs(left[i] - right[i]);
  }
  
  /*
   * PART 2 CODE
   */
  HashMap* map = create_map();
  
  int p2_total = 0;
  for (int i = 0; i < TABLE_SIZE; i++) {
    insert_update(map, right[i]);
  }

  for (int i = 0; i < TABLE_SIZE; i++) {
    int left_val = left[i];
    int right = search(map, left_val);
    if (right != -1)  p2_total += left_val * right;
  }
  
  free_map(map);
  printf("Part 1 total: %d\n", p1_total);
  printf("Part 2 total: %d\n", p2_total);
}