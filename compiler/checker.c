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

void errorMsg(const char* msg, char* nodeT){
    fprintf(stderr, "KO\n");
    printf("Type error: ");
    printf(msg);	//ne fonctionne pas sous ubuntu
    printf(nodeT);
    printf("\n");
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
        else if(leftT == NO_TYPE){
            leftT = getType(node->left, sym);
        }
        if(leftT != TYPE_INT){
            errorMsg("Inccorrect Int négation: ",humanReadableNodeType(node->type));
            return 1;
        }
        printf("OPINV");
        return TYPE_INT;
        break;
    case AT_OPADD:
    case AT_OPSUB:
    case AT_OPMUL:
    case AT_OPBEQUAL:
    case AT_OPBGT:
    case AT_OPBST:
    case AT_OPBGTEQ:
    case AT_OPBSTEQ:
        leftT = getVarType(node->left);
        if(leftT == AT_ID){
            leftT = getTypeId(node->left, sym);
        }
        else if(leftT == NO_TYPE){
            leftT = getType(node->left, sym);
        }
        rightT = getVarType(node->right);
        if(rightT == AT_ID){
            rightT = getTypeId(node->right, sym);
        }
        else if(rightT == NO_TYPE){
            rightT = getType(node->right, sym);
        }
        if(leftT != TYPE_INT || rightT != TYPE_INT){
            errorMsg("Inccorrect Int expression: ",humanReadableNodeType(node->type));
            return 1;
        }
        if(t == AT_OPADD || t == AT_OPSUB || t == AT_OPMUL){
            printf("%s\n", humanReadableNodeType(node->type));
            return TYPE_INT;
        }
        else{
            printf("%s\n", humanReadableNodeType(node->type));
            return TYPE_BOOL;
        }
        break;
    //expressionBool
    case AT_FALSE: 
    case AT_TRUE:
        printf("AT true|false\n");
        return TYPE_BOOL; break;
    case AT_OPBAND:
    case AT_OPBOR:
        leftT = getVarType(node->left);
        if(leftT == AT_ID){
            leftT = getTypeId(node->left, sym);
        }
        else if(leftT == NO_TYPE){
            leftT = getType(node->left, sym);
        }
        rightT = getVarType(node->right);
        if(rightT == AT_ID){
            rightT = getTypeId(node->right, sym);
        }
        else if(rightT == NO_TYPE){
            rightT = getType(node->right, sym);
        }
        if(leftT != TYPE_BOOL || rightT != TYPE_BOOL){
            errorMsg("Inccorrect Bool expression: ",humanReadableNodeType(node->type));
            return 1;
        }
        printf("%s\n", humanReadableNodeType(node->type));
        return TYPE_BOOL;
        break;
    case AT_OPREAD:
    case AT_OPWRITE:
        leftT = getVarType(node->left);
        if(leftT == AT_ID){
            leftT = getTypeId(node->left, sym);
        }
        else if(leftT == NO_TYPE){
            leftT = getType(node->left, sym);
        }
        if(leftT != TYPE_INT){
            errorMsg("Inccorrect Int expression (read/write): ",humanReadableNodeType(node->type));
            return 1;
        }
        printf("%s\n", humanReadableNodeType(node->type));
        return TYPE_INT;
        break;
    case AT_OPIF:
    case AT_OPWHILE:
    case AT_OPBNOT:
        leftT = getVarType(node->left);
        if(leftT == AT_ID){
            leftT = getTypeId(node->left, sym);
        }
        else if(leftT == NO_TYPE){
            leftT = getType(node->left, sym);
        }
        if(leftT != TYPE_BOOL){
            errorMsg("Inccorrect Bool expression (not/if): ",humanReadableNodeType(node->type));
            return 1;
        }
        printf("%s\n", humanReadableNodeType(node->type));
        return TYPE_BOOL;
        break;
    //instruction
    case AT_AFFEXPR:
        leftT = getTypeId(node->left, sym);
        rightT = getVarType(node->right);
        if(rightT == AT_ID){
            rightT = getTypeId(node->right, sym);
        }
        else if(rightT == NO_TYPE){
            rightT = getType(node->right, sym);
        }
        if(leftT == NO_TYPE || leftT != rightT){
            errorMsg("Inccorrect Affect instruction: ",humanReadableNodeType(node->type));
            return 1;
        }
        printf("AT_Affect\n");
        return leftT;
        break;

    default:     return 1;
    }
}

int getTypeId(ASTTREE node, SYMTABLE sym){
    int type = NO_TYPE;
    if(node != NULL && sym != NULL){
        type = getSymType(sym, node->sval);
        //printf("Type of %s: %d\n", node->sval,type);
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
