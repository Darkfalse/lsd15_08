/* Groupe 8
 * Mertens Xavier
 * Motte Josué
 * 2015
 */

#ifndef AST_H
#define AST_H

// do not change values below, or also edit humanReadableNodeType() in ast.c
#define AT_NB         0
#define AT_OPWRITE    1
#define AT_OPADD      2
#define AT_OPSUB      3
#define AT_OPMUL      4
#define AT_OPPRINT    5
#define AT_OPREAD     6
#define AT_OPAFF      7
#define AT_OPMOD      8
#define AT_CODEB      9
#define AT_CODE      10
#define AT_DECLVARS  11
#define AT_DECLVOID  12
#define AT_DECLINT   13
#define AT_DECLBOOL  14
#define AT_OPIF      15
#define AT_OPWHILE   16
#define AT_OPELSEFI  17
#define AT_FALSE     18
#define AT_TRUE      19
#define AT_OPBAND    20
#define AT_OPBOR     21
#define AT_OPBNOT    22
#define AT_OPBEQUAL  23
#define AT_OPBGT     24
#define AT_OPBST     25
#define AT_OPBGTEQ   26
#define AT_OPBSTEQ   27
#define AT_ID        28
#define AT_VAR       29
#define AT_AFFEXPR   30
#define AT_AFFID     31
#define AT_LINSTR    32
#define AT_OPINV     33
//toujours dernier root
#define AT_ROOT      34

//type
#define TYPE_INT     98
#define TYPE_BOOL    99

struct astnode {
  int type;

  int ival;
  char* sval;

  struct astnode * left;
  struct astnode * right;
};

typedef struct astnode * ASTTREE;
typedef struct astnode   ASTNODE;

extern ASTTREE createNode(int type, int ival, char* sval, ASTTREE left, ASTTREE right);
extern void freeNode(ASTTREE node);
extern void freeTree(ASTTREE tree);

extern void printTree(ASTTREE tree);

#endif
