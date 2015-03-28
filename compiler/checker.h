/* Groupe 8
 * Mertens Xavier
 * Motte Josué
 * 2015
 */

#ifndef TYPE_H
#define TYPE_H

#include "ast.h"
#include "sym.h"

extern void errrorMsg(char* msg);
extern int validType(ASTTREE node, SYMTABLE sym);
extern int getType(ASTTREE node, SYMTABLE sym);
extern int getTypeId(ASTTREE node, SYMTABLE sym);

#endif