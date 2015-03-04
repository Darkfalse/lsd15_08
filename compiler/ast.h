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
#define AT_OPFI      17
#define AT_OPELSEFI  18
#define AT_FALSE     19
#define AT_TRUE      20
#define AT_OPBAND    21
#define AT_OPBOR     22
#define AT_OPBNOT    23
#define AT_OPBEQUAL  24
#define AT_OPBGT     25
#define AT_OPBST     26
#define AT_OPBGTEQ   27
#define AT_OPBSTEQ   28
#define AT_ID        29
#define AT_VAR       30
#define AT_AFFEXPR   31
#define AT_AFFID     32
//toujours dernier root
#define AT_ROOT      33

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
