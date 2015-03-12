/* Groupe 8
 * Mertens Xavier
 * Motte Josué
 * 2015
 */

#ifndef TYPE_H
#define TYPE_H

#include "ast.h"

extern void errrorMsg(char* msg);
extern void validType(ASTTREE node);
extern int getType(ASTTREE node);
extern int getTypeId(ASTTREE node);

#endif