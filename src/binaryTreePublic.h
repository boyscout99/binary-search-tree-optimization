#ifndef _BINARY_TREE_PUBLIC_INCLUDED
#define _BINARY_TREE_PUBLIC_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "util.h"

#define MAX_LINE 100
#define MAX_NAME 30
#define DATE 10
#define PROG 5

typedef struct node node_t;

int load_file(char *f_name, char *mode, node_t **head_N, node_t **head_ID);
node_t *insert_data(node_t *tmp, long int id_num, char *name, char *date,
                    char *prog, int year);
node_t *insert_node_N(node_t *head_N, node_t *tmp);
node_t *insert_node_ID(node_t *head_ID, node_t *tmp);
void save_tree_N(FILE *fp, node_t *head_N);
void save_tree_ID(FILE *fp, node_t *head_ID);
void save_node(FILE *fp, node_t *head);
node_t *search_name(char *name, node_t *head_N);
node_t *search_ID(long int id, node_t *head_ID);

#endif
