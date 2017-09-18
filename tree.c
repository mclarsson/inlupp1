#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"

typedef struct node node_t;

struct tree {
  node_t *top;
};

struct node {
  K key;
  T element;
  node_t *left;
  node_t *right;
};

/// Whether or not two keys matches.
///
/// \param k1 First key
/// \param k2 Second key
/// \returns If they match
bool key_matches(K k1, K k2)
{
  return strcmp(k1, k2) == 0;
}

/// Creates a new tree
///
/// \returns: empty tree
tree_t *tree_new()
{
  return calloc(1, sizeof(tree_t));
}

/// Frees node and subtrees
///
/// \param node Node to start remove at
void free_branches(node_t *node)
{
  if (node->left != NULL)
    {
      free_branches(node->left);
    }

  if (node->right != NULL)
    {
      free_branches(node->right);
    }

  free(node);
}

/// Remove a tree along with all T elements.
/// Note, if T is a pointer, elements will not
/// be removed. 
///
/// \returns: empty tree
void tree_delete(tree_t *tree)
{
  if (tree->top != NULL)
    {
      free_branches(tree->top);
    }

  free(tree);
}

/// Count all nodes in tree
///
/// \param node Node to continue counting at.
/// \returns Number of nodes in tree.
int count_nodes(node_t *node)
{
  if (node->left == NULL && node->right == NULL)
    {
      // end of branch
      return 1;
    }
  else
    {
      int left  = node->left  == NULL ? 0 : count_nodes(node->left);
      int right = node->right == NULL ? 0 : count_nodes(node->right);
      return 1 + left + right;
    }
}

/// Get the size of the tree 
///
/// \returns: the number of nodes in the tree
int tree_size(tree_t *tree)
{
  return tree->top == NULL ? 0 : count_nodes(tree->top);
}

/// Return the biggest of two numbers
///
/// \param a First number
/// \param b Second number
/// \returns Biggest number
int max(int a, int b)
{
  return a > b ? a : b;
}

/// Count max node depth
///
/// \param node current node
int count_depth(node_t *node)
{
  if (node->left == NULL && node->right == NULL)
    {
      return 1;
    }
  else
    {
      int left  = node->left  == NULL ? 1 : 1 + count_depth(node->left);
      int right = node->right == NULL ? 1 : 1 + count_depth(node->right);
      return max(left, right);
    }
}

/// Get the depth of the tree 
///
/// \returns: the depth of the deepest subtree
int tree_depth(tree_t *tree)
{
  return tree->top == NULL ? 0 : count_depth(tree->top);
}

/// Help function for node insertion, whether or not k1 is alphabetically before k2
///
/// \param k1 First key
/// \param k2 Second key
bool move_right(K k1, K k2)
{
  // strcmp return negative when k1 comes before k2
  return strcmp(k1, k2) < 0;
}

/// Finds correct parent for node.
///
/// \param parent node to start the search at.
/// \param insert node to insert.
bool insert_node(node_t *parent, node_t *insert)
{
  if (key_matches(parent->key, insert->key))
    {
      return false;
    }
  else if (move_right(parent->key, insert->key))
    {
      if (parent->right == NULL)
	{
	  parent->right = insert;
	  return true;
	}
      else
	{
	  return insert_node(parent->right, insert);
	}
    }
  else
    {
      if (parent->left == NULL)
	{
	  parent->left = insert;
	  return true;
	}
      else
	{
	  return insert_node(parent->left, insert);
	}
    }
}

/// Insert element into the tree. Returns false if the key is already used.
///
/// \param tree pointer to the tree
/// \param key the key of element to be appended
/// \param elem the element 
/// \returns: true if successful, else false
bool tree_insert(tree_t *tree, K key, T elem)
{ 
  node_t *new = calloc(1, sizeof(node_t));
  new->key = key;
  new->element = elem;
  
  if (tree->top == NULL)
    {
      tree->top = new;
      return true;
    }
  else
    {
      return insert_node(tree->top, new);
    }
}

/// Helper for tree_has_key TODO
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: true if key is a key in tree
bool look_for_key(node_t *node, K key)
{
  bool l = node->left == NULL ? false : look_for_key(node->left, key);
  bool r = node->right == NULL ? false : look_for_key(node->right, key);
  return key_matches(node->key, key) || l || r;
}

/// Checks whether a key is used in a tree
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: true if key is a key in tree
bool tree_has_key(tree_t *tree, K key)
{
  return tree->top == NULL ? false : look_for_key(tree->top, key);
}

/// Helper function for tree_get
///
/// \param node Node to search at.
/// \param key Key to find.
/// \returns Matching node.
T find_element(node_t *node, K key)
{
  if (key_matches(node->key, key))
    {
      return node->element;
    }
  else if (move_right(node->key, key))
    {
      return find_element(node->right, key);
    }
  else
    {
      return find_element(node->left, key);
    }
}

/// Returns the element for a given key in tree.
/// (The implementation may assume that the key exists.)
/// 
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: true if key is a key in tree
T tree_get(tree_t *tree, K key)
{
  return find_element(tree->top, key);
}
