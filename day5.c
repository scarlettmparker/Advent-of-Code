#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// example input
const char * input = "47|53\n97|13\n97|61\n97|47\n75|29\n97|53\n61|29\n47|13\n75|47\n97|75\n47|61\n75|61\n47|29\n75|13\n53|13\n\n75,47,61,53,29\n97,61,53,29,13";
#define VERTICES_RANGE 100

struct Node{
  int vertex;
  struct Node* next;
};

struct Graph{
  int num_vertices;
  struct Node** adj_pages;
};

/**
 * Creates a graph with a number of verticies.
 * Initializes the adjacency list for each vertex to NULL.
 *
 * @param num_vertices Number of vertices in the graph.
 * @return Pointer to the graph.
 */
struct Graph* create_graph(int num_vertices){
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->num_vertices = num_vertices;
  graph->adj_pages = calloc(num_vertices, sizeof(struct Node*));
  
  for (int i = 0; i < num_vertices; i++){
    graph->adj_pages[i] = NULL;
  }
  
  return graph;
}

/**
 * Adds a directed edge from the source vertex to the destination.
 *
 * @param graph Pointer to the graph.
 * @param src Source vertex.
 * @param dest Destination vertex.
 */
void add_edge(struct Graph* graph, int src, int dest){
  struct Node* new_node = malloc(sizeof(struct Node));
  new_node->vertex = dest;
  new_node->next = graph->adj_pages[src];
  graph->adj_pages[src] = new_node;
}

/**
 * Computes the in-degree for each vertex of the graph.
 * The in-degree of a vertex is the number of edges directed toward it.
 *
 * @param graph Pointer to the graph.
 * @return Array of integeres representing the in-degree of each vertex.
 */
int* compute_in_dg(struct Graph* graph){
  int* in_dg = calloc(graph->num_vertices, sizeof(int));
  for (int i = 0; i < graph->num_vertices; i++){
    struct Node* temp = graph->adj_pages[i];
    while (temp){
      in_dg[temp->vertex]++;
      temp = temp->next;
    }
  }
  return in_dg;
}

/**
 * Performs topological sort on the graph using Kahn's algorithm.
 * It orders vertices so that each directed edge u -> v, u comes before v.
 *
 * @param graph Pointer to the graph.
 * @param page List of page numbers to store the sorted vertices (page numbers).
 * @param page_size Number of verticies in the page number list.
 */
void topological_sort(struct Graph* graph, int* page, int page_size){
  int* in_dg = compute_in_dg(graph);
  int* queue = malloc(graph->num_vertices * sizeof(int));
  int front = 0, back = 0;
  
  for (int i = 0; i < graph->num_vertices; i++){
    if (in_dg[i] == 0){
      queue[back++] = i;
    }
  }
  
  int processed = 0;
  while (front < back){
    int current = queue[front++];
    processed++;
    
    struct Node* temp = graph->adj_pages[current];
    while (temp){
      in_dg[temp->vertex]--;
      if (in_dg[temp->vertex] == 0){
        queue[back++] = temp->vertex;
      }
      temp = temp->next;
    }
  }
  
  free(in_dg);
  free(queue);
}

/**
 * Checks if page order is valid by checking if the order is allowed
 * by the topological constraints of the graph (the rules).
 *
 * @param graph Pointer to the graph.
 * @param page List of page numbers to store the sorted vertices (page numbers).
 * @param page_size Number of verticies in the page number list.
 * @return Middle value of the page number list if valid, otherwise 0.
 */
int page_valid(struct Graph* graph, int* page, int page_size){
  int* position = malloc(graph->num_vertices * sizeof(int));
    
  for (int i = 0; i < graph->num_vertices; i++){
    position[i] = -1;
  }
    
  for (int i = 0; i < page_size; i++){
    position[page[i]] = i;
  }
   
      
  int middle_index = page_size / 2;
  int middle_value = page[middle_index];
  
  for (int i = 0; i < graph->num_vertices; i++){
    struct Node* temp = graph->adj_pages[i];
    while (temp){
      int a = i, b = temp->vertex;
      if (position[a] != -1 && position[b] != -1 && position[a] > position[b]){
        /**
         * PART 1
         */ 
         
        free(position);
        return 0;
        
        /**
         * PART 2
         */
         
        /*
        topological_sort(graph, page, page_size);
        free(position);
        return middle_value;
        */
        
      }
      temp = temp->next;
    }
  }
  
  /**
   * PART 1
   */

  return middle_value;
  
  /**
   * PART 2
   */
   
  return 0;
}

/**
 * Searches each page number list and adds its middle value to the total
 * (valid_c) given that the order is allowed by the topological constraints
 * of the graph (the rules).
 *
 * @param graph Pointer to the graph.
 * @param pages 2D array of page numbers.
 * @param num_pages Number of lists of page numbers.
 * @param page_sizes Array of sizes for each list of page numbers.
 * @return Added total of all middle values from valid lists of page numbers.
 */
int count_valid(struct Graph* graph, int** pages, int num_pages, int* page_sizes){
  int valid_c = 0;
  
  for (int i = 0; i < num_pages; i++){
    valid_c += page_valid(graph, pages[i], page_sizes[i]);
  }
  
  return valid_c;
}

int main()
{
  /**
   * DATA PREPROCESSING
   */

  char *input_copy = strdup(input);
  char *split_pos = strstr(input_copy, "\n\n");
  
  int **rules = NULL;
  int **pages = NULL;
    
  if (!split_pos){
    free(input_copy);
    return 1;
  }
    
  *split_pos = '\0';
    
  char *rules_sec = input_copy;
  char *pages_sec = split_pos + 2;
  char *line = strtok(rules_sec, "\n");
    
  int rules_c = 0;
    
  // iterate through rules and add to array
  while (line){
    int a, b;
    if (sscanf(line, "%d|%d", &a, &b) == 2){
      rules = realloc(rules, (rules_c + 1) * sizeof(int *));
      rules[rules_c] = malloc(2 * sizeof(int));
      rules[rules_c][0] = a;
      rules[rules_c][1] = b;
      rules_c++;
    }
    line = strtok(NULL, "\n");
  }
    
  int *page_lengths = NULL;
  int page_c = 0;
  line = strtok(pages_sec, "\n");
    
  while (line){
    char *inner_ctx;
    char *number = strtok_r(line, ",", &inner_ctx);
  
    int page_idx = 0;
    pages = realloc(pages, (page_c + 1) * sizeof(int *));
    pages[page_c] = NULL;
  
    while (number){
      int value = atoi(number);
      pages[page_c] = realloc(pages[page_c], (page_idx + 1) * sizeof(int));
      pages[page_c][page_idx] = value;
      page_idx++;
      number = strtok_r(NULL, ",", &inner_ctx);
    }
  
    // store the length of the current page
    page_lengths = realloc(page_lengths, (page_c + 1) * sizeof(int));
    page_lengths[page_c] = page_idx;
  
    page_c++;
    line = strtok(NULL, "\n");
  }

  free(input_copy);

  /**
   * ACTUAL LOGIC STUFF
   */
  int total_p1 = 0;
  int total_p2 = 0;
    
  struct Graph* graph = create_graph(VERTICES_RANGE);
  for (int i = 0; i < rules_c; i++){
    add_edge(graph, rules[i][0], rules[i][1]);
  }
    
  int valid_c = count_valid(graph, pages, page_c, page_lengths);
  printf("Total: %d\n", valid_c);
    
  // freeing memory
  for (int i = 0; i < rules_c; i++){
    free(rules[i]);
  }
  free(rules);

  for (int i = 0; i < page_c; i++){
    free(pages[i]);
  } 
  free(pages);
}