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

ASTTREE nodeRoot = NULL;

int getType(ASTTREE node){
    int t = node->type;
    int leftT;
    int rightT;
    switch(t){
    case AT_DECLINT:
        if(getTypeId(node->left) != TYPE_INT){
            errorMsg("Id inccorrectly declared (int)");
        }
        return TYPE_INT;
        break;
    case AT_DECLBOOL:
        if(getTypeId(node->left) != TYPE_BOOL){
        	errorMsg("Id inccorrectly declared (bool)");
        }
        return TYPE_BOOL;
        break;
    //expressionInt
    case AT_NB:             return TYPE_INT; break;
    case AT_OPINV:
        leftT = getVarType(node->left);
        if(leftT == -2){
            leftT = getTypeId(node->left);
        }
        if(leftT != TYPE_INT){
            errorMsg("Inccorrect Int négation");
        }
        return TYPE_INT;
        break;
    case AT_OPADD:
    case AT_OPSUB:
    case AT_OPMUL:
    case AT_OPMOD:
        leftT = getVarType(node->left);
        if(leftT == -2){
            leftT = getTypeId(node->left);
        }
        rightT = getVarType(node->right);
        if(rightT == -2){
            rightT = getTypeId(node->right);
        }
        if(leftT != TYPE_INT || rightT != TYPE_INT){
            errorMsg("Inccorrect Int expression");
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
        if(leftT == -2){
            leftT = getTypeId(node->left);
        }
        rightT = getVarType(node->right);
        if(rightT == -2){
            rightT = getTypeId(node->right);
        }
        if(leftT != TYPE_BOOL || rightT != TYPE_BOOL){
            errorMsg("Inccorrect Bool expression");
        }
        return TYPE_INT;
        break;
    case AT_OPBNOT:
        leftT = getVarType(node->left);
        if(leftT == -2){
            leftT = getTypeId(node->left);
        }
        if(leftT != TYPE_BOOL){
            errorMsg("Inccorrect Bool expression (not)");
        }
        return TYPE_INT;
        break;
    //instruction
    case AT_AFFEXPR:
        leftT = getVarType(node->left);
        rightT = getVarType(node->right);
        if(leftT != rightT){
            errorMsg("Inccorrect Affect instruction");
        }
        return leftT;
        break;
    case AT_OPIF:
        leftT = getVarType(node->left);
        if(leftT != TYPE_BOOL){
            errorMsg("Inccorrect If condition");
        }
        return TYPE_BOOL;
        break;

    default:     return -1;
    }
}

int getTypeId(ASTTREE node){
    int type = -1;
    ASTTREE nodeTemp = nodeRoot;
    while(nodeTemp){
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
    }
    return type;
}

void validType(ASTTREE node){
    if(nodeRoot != NULL){
        nodeRoot = node;
    }
    while(node){
        getType(node);
        validType(node->left);
        node = node->right;
    }
}
