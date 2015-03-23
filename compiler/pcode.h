/* Groupe 8
 * Mertens Xavier
 * Motte Josué
 * 2015
 */

#ifndef _PCODE_H
#define _PCODE_H

#include "ast.h"
#include "sym.h"

extern int fillSymbolTable(ASTTREE tree, SYMTABLE s);
extern int pcodeGenAddress(ASTTREE tree, SYMTABLE s);
extern int pcodeGenValue(ASTTREE tree, SYMTABLE s);
#endif
