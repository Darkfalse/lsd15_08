/* Groupe 8
 * Mertens Xavier
 * Motte Josué
 * 2015
 */

#ifndef TYPE_H
#define TYPE_H

#include "sym.h"
#include "ast.h"

extern void validType(ASTTREE node);
extern int getType(ASTTREE node);
extern int getTypeId(ASTTREE node);

#endif