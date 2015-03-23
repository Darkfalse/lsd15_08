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
    fprintf(stderr, msg);
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
            errorMsg("Inccorrect Int négation");
            return -1;
        }
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
            errorMsg("Inccorrect Int expression");
            return -1;
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
        if(leftT == AT_ID){
            leftT = getTypeId(node->left, sym);
        }
        rightT = getVarType(node->right);
        if(rightT == AT_ID){
            rightT = getTypeId(node->right, sym);
        }
        if(leftT != TYPE_BOOL || rightT != TYPE_BOOL){
            errorMsg("Inccorrect Bool expression");
            return -1;
        }
        return TYPE_INT;
        break;
    case AT_OPBNOT:
        leftT = getVarType(node->left);
        if(leftT == AT_ID){
            leftT = getTypeId(node->left, sym);
        }
        if(leftT != TYPE_BOOL){
            errorMsg("Inccorrect Bool expression (not)");
            return -1;
        }
        return TYPE_INT;
        break;
    //instruction
    case AT_AFFEXPR:
        leftT = getTypeId(node->left, sym);
        rightT = getVarType(node->right);
        if(rightT == AT_ID){
            rightT = getTypeId(node->right, sym);
        }
        if(leftT == -1 || leftT == -3 || rightT == -1 || rightT == -3 || leftT != rightT){ //peu peut-être être simplifier
            errorMsg("Inccorrect Affect instruction");
            return -1;
        }
        return leftT;
        break;
    case AT_OPIF:
        leftT = getVarType(node->left);
        if(leftT != TYPE_BOOL){
            errorMsg("Inccorrect If condition");
            return -1;
        }
        return TYPE_BOOL;
        break;

    default:     return -1;
    }
}

int getTypeId(ASTTREE node, SYMTABLE sym){
    int type = -1;
    if(node != NULL && sym != NULL){
        type = getSymType(sym, node->sval);
    }

    /*int type = -1;
    ASTTREE nodeTemp = nodeRoot;
    while(nodeTemp != NULL && node != NULL){
        if(node->type == AT_DECLINT && !(strcmp(nodeTemp->sval, node->sval))){
            return TYPE_INT;
        }
        else if(node->type == AT_DECLBOOL && !(strcmp(nodeTemp->sval, node->sval))){
            return TYPE_BOOL;
        }
        else{
            type = getTypeId(node->left);
        }
        nodeTemp = nodeTemp->right;
    }*/
    return type;
}

void validType(ASTTREE node, SYMTABLE sym){
    while(node != NULL && sym != NULL){
        getType(node, sym);
        validType(node->left, sym);
        node = node->right;
    }
}
