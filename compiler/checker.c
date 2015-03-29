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

void errorMsg(const char* msg, int node){
    fprintf(stderr, "KO\n");
    printf("Type error:");
    printf(msg);	//ne fonctionne pas sous ubuntu
    printf("%d",node);
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
            errorMsg("Inccorrect Int négation\n",node->type);
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
            errorMsg("Inccorrect Int expression\n",node->type);
            return 1;
        }
        printf("OP add|sub|mul: %d\n", node->type);
        if(t == AT_OPADD || t == AT_OPSUB || t == AT_OPMUL){
            return TYPE_INT;
        }
        else{
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
            errorMsg("Inccorrect Bool expression\n",node->type);
            return 1;
        }
        printf("OP and|or|equal|greater|smaller|>=|<=: %d\n", node->type);
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
            errorMsg("Inccorrect Int expression (read/write)\n",node->type);
            return 1;
        }
        printf("OP read|write: %d\n", node->type);
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
            errorMsg("Inccorrect Bool expression (not/if)\n",node->type);
            return 1;
        }
        printf("OP if|not: %d\n", node->type);
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
            errorMsg("Inccorrect Affect instruction\n",node->type);
            return 1;
        }
        printf("AT_Affect: %d\n", node->type);
        return leftT;
        break;

    default:     return 1;
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
