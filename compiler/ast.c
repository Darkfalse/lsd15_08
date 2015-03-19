/* Groupe 8
 * Mertens Xavier
 * Motte Josué
 * 2015
 */

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

ASTTREE createNode(int type,
		   int ival,
		   char* sval,
		   ASTTREE left,
		   ASTTREE right)
{
  ASTTREE node = (ASTTREE) malloc(sizeof(ASTNODE));
  if (node == NULL)
    {
      fprintf(stderr,"KO\n");
      printf("ERROR : malloc failed in createNode(..)\n");
      exit(1);
    }
  else
    {
      node->type = type;
      node->ival = ival;
      node->sval = sval;
      node->left = left;
      node->right = right;

      return node;
    }
}

void freeNode(ASTTREE node)
{
  if (node != NULL)
    {
      if (node->sval != NULL) free(node->sval);
      if (node->left != NULL) freeNode(node->left);
      if (node->right != NULL) freeNode(node->right);

      free(node);
    }
}

void freeTree(ASTTREE tree) // idem above but top root is static
{
  if (tree != NULL)
    {
      if (tree->sval != NULL) free(tree->sval);
      if (tree->left != NULL) freeNode(tree->left);
      if (tree->right != NULL) freeNode(tree->right);
    } 
}


char* humanReadableNodeType(int type)
{
  switch(type) {

  case AT_NB:       return "AT_NB"; break;
  case AT_OPWRITE:  return "AT_OPWRITE"; break;
  case AT_OPADD:    return "AT_OPADD"; break;
  case AT_OPSUB:    return "AT_OPSUB"; break;
  case AT_OPMUL :   return "AT_OPMUL"; break;
  case AT_OPPRINT:  return "AT_OPPRINT"; break;
  case AT_OPREAD:   return "AT_OPREAD"; break;
  case AT_OPAFF:    return "AT_OPAFF"; break;
  case AT_OPMOD:    return "AT_OPMOD"; break;
  case AT_CODEB:    return "AT_CODEB"; break;
  case AT_CODE:     return "AT_CODE"; break;
  case AT_DECLVARS: return "AT_DECLVARS"; break;
  case AT_DECLVOID: return "AT_DECLVOID"; break;
  case AT_DECLINT:  return "AT_DECLINT"; break;
  case AT_DECLBOOL: return "AT_DECLBOOL"; break;
  case AT_OPIF:     return "AT_OPIF"; break;
  case AT_OPWHILE:  return "AT_OPWHILE"; break;
  case AT_OPELSEFI: return "AT_OPELSEFI"; break;
  case AT_FALSE:    return "AT_FALSE"; break;
  case AT_TRUE:     return "AT_TRUE"; break;
  case AT_OPBAND:   return "AT_OPBAND"; break;
  case AT_OPBOR:    return "AT_OPBOR"; break;
  case AT_OPBNOT:   return "AT_OPBNOT"; break;
  case AT_OPBEQUAL: return "AT_OPBEQUAL"; break;
  case AT_OPBGT:    return "AT_OPBGT"; break;
  case AT_OPBST:    return "AT_OPBST"; break;
  case AT_OPBSTEQ:  return "AT_OPBSTEQ"; break;
  case AT_OPBGTEQ:  return "AT_OPBGTEQ"; break;
  case AT_ID:       return "AT_ID"; break;
  case AT_VAR:      return "AT_VAR"; break;
  case AT_AFFEXPR:  return "AT_AFFEXPR"; break;
  case AT_AFFID:    return "AT_AFFID"; break;
  case AT_LINSTR:   return "AT_LINSTR"; break;
  case AT_OPINV:    return "AT_OPINV"; break;
  case AT_ROOT:     return "AT_ROOT"; break;

  default :         return "??";
  }
}

int getVarType(ASTTREE node)
{
  int i = node->type;
  
  switch(i){

  case AT_DECLINT:    return TYPE_INT; break;
  case AT_DECLBOOL:   return TYPE_BOOL; break;
  case AT_NB:         return TYPE_INT; break;
  case AT_TRUE:       return TYPE_BOOL; break;
  case AT_FALSE:      return TYPE_BOOL; break;
  case AT_ID:         return -2; break;

  default:            return -1;
  }
}

void printTree(ASTTREE tree)
{
  if (tree != NULL) 
    {
      printf("; [%p] type=%s, ival=%d, sval=", tree, humanReadableNodeType(tree->type), tree->ival);
      if (tree->sval == NULL) printf("NULL");
      else printf("'%s'", tree->sval);
      printf(", left=%p, right=%p\n", tree->left, tree->right);

      printTree(tree->left);
      printTree(tree->right);
    }
}
