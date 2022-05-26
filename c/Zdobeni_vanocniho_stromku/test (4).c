#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define MAX_BRANCHES             3
#define DECORATION_NONE          0
#define DECORATION_CANDLE        1
#define DECORATION_SPARKLER      2


typedef struct TNode
{
  struct TNode   * m_Parent;
  struct TNode   * m_Branches[MAX_BRANCHES];
  int              m_Decoration;
} TNODE;
#endif /* __PROGTEST__ */

int canItBurn(TNODE* n1, TNODE* n2)
{
  if ((n1 == NULL) || (n2 == NULL))
  {
    return 0;
  }
  else if ((n1->m_Decoration == DECORATION_NONE) || (n2->m_Decoration == DECORATION_NONE))
  {
    return 0;
  }
  else if (n1->m_Decoration != n2->m_Decoration)
  {
    return 1;
  }
  return 0;
}

int easyToCatchFire(TNODE* root )
{
  if (root == NULL)
  {
    return 0;
  }
  if (canItBurn(root, root->m_Branches[0]))
  {
    return 1;
  }
  if (canItBurn(root, root->m_Branches[1]))
  {
    return 1;
  }
  if (canItBurn(root, root->m_Branches[2]))
  {
    return 1;
  }

  if (canItBurn(root->m_Branches[0], root->m_Branches[1]))
  {
    return 1;
  }
  if (canItBurn(root->m_Branches[1], root->m_Branches[2]))
  {
    return 1;
  }
  for (int i = 0; i < MAX_BRANCHES; i++)
  {
    if (root->m_Branches[i] != NULL)
    {
      return easyToCatchFire(root->m_Branches[i]);
    }
  }
  return 0;
}

void destroyTree (TNODE* root)
{
  if (root != NULL)
  {
    for (int i = 0; i < MAX_BRANCHES; i++)
    {
      if (root->m_Branches[i] != NULL)
      {
        destroyTree(root->m_Branches[i]);
        root->m_Branches[i] = NULL;
      }
    }
  }
  free(root);
}

int cutBranch( TNODE ** root, const char* path )
{
  if (*root == 0)
  {
    return 0;
  }
  if (strlen(path) == 0)
  {
    destroyTree(*root);
    *root = NULL;
    return 1;
  }
  
  for (size_t i = 0; i < strlen(path); i++)
  {
    char curr = path[i];
    if ((curr != '0') && (curr != '1') && (curr != '2'))
    {
      return 0;
    }
  }
  TNODE *currNode = *root;
  if (currNode == NULL)
  {
    return 0;
  }
  for (size_t i = 0; i < strlen(path); i++)
  {
    if (currNode->m_Branches[path[i] - '0'] == NULL)
    {
      return 0;
    }
    currNode = currNode->m_Branches[path[i] - '0'];
  }
  if (currNode == NULL)
  {
    return 0;
  }
  currNode->m_Parent->m_Branches[path[strlen(path) - 1] - '0'] = NULL;
  destroyTree(currNode);
  return 1;
}

TNODE* addBranch(TNODE *parent)
{
  TNODE* res = (TNODE*)malloc(sizeof(TNODE)); 
  res->m_Branches[0] = NULL;
  res->m_Branches[1] = NULL;
  res->m_Branches[2] = NULL;
  res->m_Decoration = DECORATION_NONE;
  res->m_Parent = parent;
  return res;
}

int setDecoration( TNODE **root, const char *path, int decor )
{
  for (size_t i = 0; i < strlen(path); i++)
  {
    char curr = path[i];
    if ((curr != '0') && (curr != '1') && (curr != '2'))
    {
      return 0;
    }
  }
  if (*root == NULL)
  {
    *root = addBranch(NULL);
  }
  
  TNODE *currNode = *root;
  for (size_t i = 0; i < strlen(path); i++)
  {
    if (currNode->m_Branches[path[i] - '0'] == NULL)
    {
      currNode->m_Branches[path[i] - '0'] = addBranch(currNode);
    }
    currNode = currNode->m_Branches[path[i] - '0'];
  }
  currNode->m_Decoration = decor;
  return 1;
}

void printTree(TNODE *root)
{
  for (int i = 0; i < MAX_BRANCHES; i++)
  {
    if (root->m_Branches[i] != NULL)
    {
      printf(" %d ", root->m_Branches[i]->m_Decoration);
      printTree(root->m_Branches[i]);
    }
  }
  printf(" \n");
}

#ifndef __PROGTEST__
int main ( void )
{
  TNODE * r;
  r = NULL;




  assert ( setDecoration ( &r, "000", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL );



  assert ( setDecoration ( &r, "001", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "002", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "1", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] != NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL
           && r -> m_Branches[1] -> m_Parent == r
           && r -> m_Branches[1] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "01", DECORATION_NONE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] != NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[1] -> m_Parent == r
           && r -> m_Branches[1] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] != NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[1] -> m_Parent == r
           && r -> m_Branches[1] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( easyToCatchFire ( r ) == 0 );
  destroyTree ( r ); 

  r = NULL;
  assert ( setDecoration ( &r, "000", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "002", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "2", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL
           && r -> m_Branches[2] -> m_Parent == r
           && r -> m_Branches[2] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( easyToCatchFire ( r ) == 0 );
  destroyTree ( r ); 

  r = NULL;
  assert ( setDecoration ( &r, "0001", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "000", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( easyToCatchFire ( r ) == 1 );
  destroyTree ( r ); 

  r = NULL;
  assert ( setDecoration ( &r, "012001", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "012002", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( easyToCatchFire ( r ) == 1 );
  assert ( cutBranch ( &r, "0120" ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( easyToCatchFire ( r ) == 0 );
  destroyTree ( r ); 

  r = NULL;
  assert ( setDecoration ( &r, "0123", DECORATION_SPARKLER ) == 0 );
  assert ( r == NULL );
  assert ( cutBranch ( &r, "012" ) == 0 );
  assert ( r == NULL );
  assert ( easyToCatchFire ( r ) == 0 );
  destroyTree ( r ); 

  r = NULL;
  assert ( setDecoration ( &r, "012", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "011", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( easyToCatchFire ( r ) == 1 );
  assert ( cutBranch ( &r, "" ) == 1 );
  assert ( r == NULL );
  assert ( easyToCatchFire ( r ) == 0 );
  assert ( cutBranch ( &r, "" ) == 0 );
  assert ( r == NULL );
  destroyTree ( r ); 

  return 0;
}
#endif /* __PROGTEST__ */
