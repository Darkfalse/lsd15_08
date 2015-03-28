/* Groupe 8
 * Mertens Xavier
 * Motte Josué
 * 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "checker.h"

extern void printTree(ASTTREE node);

void errorMsg(const char* msg){
    fprintf(stderr, "KO\n");
    fprintf(stderr, "Type error:");
    //fprintf(stderr, msg);	//ne fonctionne pas sous ubuntu
    fprintf(stderr, "\n");
    exit(1);
}

int getType(ASTTREE node, SYMTABLE sym){
    int t = node->type;
    int leftT;
    int rightT;
    switch(t){
    //expressionInt
    case AT_NB:             return TYPE_INT; break;
    case AT_OPINV:
        leftT = getVarType(node->left);
        if(leftT == AT_ID){
            leftT = getTypeId(node->left, sym);
        }
        if(leftT != TYPE_INT){
            errorMsg("Inccorrect Int négation\n");
            return -1;
        }
        printf("OPINV");
        return TYPE_INT;
        break;
    case AT_OPADD:
    case AT_OPSUB:
    case AT_OPMUL:
    case AT_OPMOD:
        leftT = getVarType(node->left);
        if(leftT == AT_ID){
            leftT = getTypeId(node->left, sym);
        }
        rightT = getVarType(node->right);
        if(rightT == AT_ID){
            rightT = getTypeId(node->right, sym);
        }
        if(leftT != TYPE_INT || rightT != TYPE_INT){
            errorMsg("Inccorrect Int expression\n");
            return -1;
        }
        printf("OP add|sub|mul|mod\n");
        return TYPE_INT;
        break;
    //expressionBool
    case AT_FALSE: 
    case AT_TRUE:
        printf("AT true|false\n");
        return TYPE_BOOL; break;
    case AT_OPBAND:
    case AT_OPBOR:
    case AT_OPBEQUAL:
    case AT_OPBGT:
    case AT_OPBST:
    case AT_OPBGTEQ:
    case AT_OPBSTEQ:
        leftT = getVarType(node->left);
        if(leftT == AT_ID){
            leftT = getTypeId(node->left, sym);
        }
        rightT = getVarType(node->right);
        if(rightT == AT_ID){
            rightT = getTypeId(node->right, sym);
        }
        if(leftT != TYPE_BOOL || rightT != TYPE_BOOL){
            errorMsg("Inccorrect Bool expression\n");
            return -1;
        }
        printf("OP and|or|equal|greater|smaller|>=|<=\n");
        return TYPE_BOOL;
        break;
    case AT_OPIF:
    case AT_OPBNOT:
        leftT = getVarType(node->left);
        if(leftT == AT_ID){
            leftT = getTypeId(node->left, sym);
        }
        if(leftT != TYPE_BOOL){
            errorMsg("Inccorrect Bool expression (not/if)\n");
            return -1;
        }
        printf("OP if|not\n");
        return TYPE_BOOL;
        break;
    //instruction
    case AT_AFFEXPR:
        leftT = getTypeId(node->left, sym);
        rightT = getVarType(node->right);
        if(rightT == AT_ID){
            rightT = getTypeId(node->right, sym);
        }
        if(leftT == NO_TYPE || rightT == NO_TYPE || leftT != rightT){ //peu peut-être être simplifier
            errorMsg("Inccorrect Affect instruction\n");
            return -1;
        }
        printf("AT_Affect\n");
        return leftT;
        break;

    default:     return -1;
    }
}

int getTypeId(ASTTREE node, SYMTABLE sym){
    int type = NO_TYPE;
    if(node != NULL && sym != NULL){
        type = getSymType(sym, node->sval);
    }
    return type;
}

int validType(ASTTREE node, SYMTABLE sym){
    while(node != NULL && sym != NULL){
        getType(node, sym);
        validType(node->left, sym);
        node = node->right;
    }
    return 0;
}
