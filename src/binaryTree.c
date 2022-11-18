#include "binaryTreePrivate.h"
/*
- load name
  reads the file *name* and stores its content in a
  proper data structure.
*/
int load_file(char *f_name, char *mode, node_t **head_N, node_t **head_ID)
{
  FILE *fp;
  fp = util_fopen(f_name, mode);
  long int id_num;
  int year;
  char last_n[MAX_NAME+1], first_n[MAX_NAME+1], date[DATE+1], prog[PROG+1];
  char buffer[MAX_LINE+1], name[2*MAX_NAME+3];
  node_t *tmp;

  //read the content of the file
  while(fscanf(fp, "%ld%s%s%s%s%d",
              &id_num, last_n, first_n, date, prog, &year) != EOF)
  {
    sprintf (name, "%s %s", last_n, first_n);
    tmp = (node_t *) util_malloc(sizeof(node_t));
    tmp = insert_data(tmp, id_num, name, date, prog, year);
    //insert the node into the binary tree
    *head_N = insert_node_N(*head_N, tmp);
    *head_ID = insert_node_ID(*head_ID, tmp);
  }

  fclose(fp);
  return 1;
}
/*
insert_node() insert the given elements into a node in an organized way
*/
node_t *insert_data(node_t *tmp, long int id_num, char *name, char *date,
                    char *prog, int year)
{
  tmp->code = id_num;
  tmp->name = util_strdup(name);
  tmp->date = util_strdup(date);
  tmp->course = util_strdup(prog);
  tmp->year = year;
  tmp->left_N = NULL;
  tmp->right_N = NULL;
  tmp->left_ID = NULL;
  tmp->right_ID = NULL;

  return tmp;
}

/*
Insert the node in alphabetical order
*/
node_t *insert_node_N(node_t *head_N, node_t *tmp)
{
  if(head_N == NULL)
  {
    head_N = tmp;
    return head_N;
  }
  //node already present in the binary tree
  if(strcmp(head_N->name, tmp->name) == 0)
    return head_N;
  //tmp->name is before in alhabetical order
  if(strcmp(head_N->name, tmp->name) > 0)
  {
    head_N->left_N = insert_node_N(head_N->left_N, tmp);
  }
  //tmp->name is after in alphabetical order
  if(strcmp(head_N->name, tmp->name) < 0)
  {
    head_N->right_N = insert_node_N(head_N->right_N, tmp);
  }

  return head_N;
}
/*
Insert the node in numerical order
*/
node_t *insert_node_ID(node_t *head_ID, node_t *tmp)
{
  if(head_ID == NULL)
  {
    head_ID = tmp;
    return head_ID;
  }
  //node already present in the binary tree
  if(head_ID->code - tmp->code == 0)
    return head_ID;
  //tmp->name is before in numerical order
  if(head_ID->code - tmp->code > 0)
  {
    head_ID->left_ID = insert_node_ID(head_ID->left_ID, tmp);
  }
  //tmp->name is after in numerical order
  if(head_ID->code - tmp->code  < 0)
  {
    head_ID->right_ID = insert_node_ID(head_ID->right_ID, tmp);
  }

  return head_ID;
}
/*
save_tree_N() saves the binary tree in a file following _N pointers
*/
void save_tree_N (FILE *fp, node_t *head_N)
{
  if(head_N == NULL)
    return;

  save_node(fp, head_N);
  save_tree_N(fp, head_N->left_N);
  save_tree_N(fp, head_N->right_N);

  return;
}
/*
save_tree_ID() saves the binary tree in a file following _ID pointers
*/
void save_tree_ID (FILE *fp, node_t *head_ID)
{
  if(head_ID == NULL)
    return;

  save_node(fp, head_ID);
  save_tree_ID(fp, head_ID->left_ID);
  save_tree_ID(fp, head_ID->right_ID);

  return;
}
/*
- save name
  stores into the file *name* all students information (with the same
  format of the input file).
*/
void save_node(FILE *fp, node_t *head)
{
  fprintf(fp, "%ld %s %s %s %d\n",
          head->code, head->name,
          head->date, head->course,
          head->year);
  return;
}
/*
- searchS last first
  searches in the data structure all data fields related to the
  student with last and first name equal to *last* and *first*,
  respectively.
*/
node_t *search_name(char *name, node_t *head_N)
{
  while(head_N != NULL)
  {
    if(strcmp(name, head_N->name) == 0)
    {
      fprintf(stdout, "%ld %s %s %s %d\n",
              head_N->code, head_N->name,
              head_N->date, head_N->course,
              head_N->year);
      return head_N;
    }

    if(strcmp(name, head_N->name) < 0)
      head_N = head_N->left_N;

    if(strcmp(name, head_N->name) > 0)
      head_N = head_N->right_N;
  }

  if(head_N == NULL)
    return NULL;
    
  return head_N;
}
/*
- searchN integer
  searches in the data structure all data related to the student
  with register number equal to the *integer* value.
*/
node_t *search_ID(long int id, node_t *head_ID)
{
  while(head_ID != NULL)
  {
    if((id - head_ID->code) == 0)
    {
      fprintf(stdout, "%ld %s %s %s %d\n",
              head_ID->code, head_ID->name,
              head_ID->date, head_ID->course,
              head_ID->year);
      return head_ID;
    }

    if((id - head_ID->code) < 0)
      head_ID = head_ID->left_ID;
    if((id - head_ID->code) > 0)
      head_ID = head_ID->right_ID;
  }

  if(head_ID == NULL)
    return NULL;

  return head_ID;
}
