/* Groupe 8
 * Mertens Xavier
 * Motte Josué
 * 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "checker.h"
#include "ast.h"

extern void printTree(ASTTREE node);

void error(const char* msg, ...){
    fprintf(stderr, "KO\n");
    fprintf(stderr, "Type error:");
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(1);
}

int getType(ASTTREE node){
    int t = node->type;
    char* leftT;
    char* rightT;
    switch(t){
    case AT_DECLINT:        return TYPE_INT; break;
    case AT_DECLBOOL:       return TYPE_BOOL; break;
    //expressionInt
    case AT_NB:             return TYPE_INT; break;
    case AT_OPADD:
    case AT_OPSUB:
    case AT_OPMUL:
    case AT_OPMOD:
        leftT = getVarType(node->left);
        rightT = getVarType(node->right);
        if(leftT != "i" || rightT != "i"){
            error("Inccorect Int expression");
        }
        return TYPE_INT;
        break;
    //expressionBool
    case AT_FALSE: 
    case AT_TRUE:           return TYPE_BOOL; break;
    case AT_OPBAND:
    case AT_OPBOR:
    case AT_OPBEQUAL:
    case AT_OPBGT:
    case AT_OPBST:
    case AT_OPBGTEQ:
    case AT_OPBSTEQ:
        leftT = getVarType(node->left);
        rightT = getVarType(node->right);
        if(leftT != "b" || rightT != "b"){
            error("Inccorect Bool expression");
        }
        return TYPE_INT;
        break;
    case AT_OPBNOT:
        leftT = getVarType(node->left);
        if(leftT != "b"){
            error("Inccorect Bool expression");
        }
        return TYPE_INT;
        break;
    //instruction
    case AT_AFFEXPR:
        leftT = getVarType(node->left);
        rightT = getVarType(node->right);
        if(leftT != rightT){
            error("Inccorect Affect instruction");
        }
        return leftT;
        break;
    case AT_OPIF:
        leftT = getVarType(node->left);
        if(leftT != "b"){
            error("Inccorect If condittion");
        }
        return TYPE_BOOL;
        break;

    default:     error("Impossible to get type!!");
    }
}

void validType(ASTTREE node){
    while(node){
        getType(node);
        validType(node->left);
        node = node->right;
    }
}
