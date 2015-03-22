/* Groupe 8
 * Mertens Xavier
 * Motte Josué
 * 2015
 */

#ifndef SYM_H
#define SYM_H

struct _stitem {
  char* id;
  int location;
  int type;
  
  struct _stitem* next;
};

typedef struct _stitem STITEM;


typedef STITEM * SYMTABLE;


extern SYMTABLE createSymbolTable();
extern void freeSymbolTable(SYMTABLE s);

extern int addToSymbolTable(SYMTABLE s, char* name, int type);
extern int alreadyIsSymbol(SYMTABLE s, char* name);

extern int computeLocations(SYMTABLE s);
extern int getLocation(SYMTABLE s, char* name);
extern int getMaxMemoryUsage(SYMTABLE s);

extern void printSymbolTable(SYMTABLE s);
#endif
