#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "sexpr.h"
#include "env.h"

SExpression *copyExp(SExpression *exp){
    if (isNil(exp)){
        //fprintf(stderr, "Error: tried copying nil list\n");
        return NULL;
    }
    else if (isAtom(exp)){
        // this is easy
        char buffer[MAX_WORD_LENGTH];
        switch (exp->atom.type){
            case A_STR:
            case A_ID:
                return atom(exp->atom.type, exp->atom.strVal);
            case A_INT:
                sprintf(buffer, "%d", exp->atom.intVal);
                return atom(A_INT, buffer);
            case A_FLT:
                sprintf(buffer, "%f", exp->atom.floatVal);
                return atom(A_FLT, buffer);
            default:
                fprintf(stderr, "Unexpted AtomType %d in copyExp()\n", exp->atom.type);
                return NULL;
        }
    }
    else if (isCons(exp)){
        // This is easier
        return cons(copyExp(exp->cons.car), copyExp(exp->cons.cdr));
    }
    return NULL;
}

SExpression *define(Environment *env, SExpression *exp){
    // name = car(exp)
    // parameters = car(cdr(exp))
    // code = cdr(cdr(exp))
    
    Variable *func = newVariable(car(exp)->atom.strVal, 1, cdr(cdr(exp)), cadr(exp));
    func->next = (struct Variable*)env->top;
    env->top = func;
    return TRUE;
}

Environment *initEnvironment(){
    Environment *environment = malloc(sizeof(Environment));
    environment->next = NULL;
    environment->top = NULL;
    return environment;
}

Environment *localEnvironment(Environment* previous){
    Environment *new = malloc(sizeof(Environment));
    new->next = (struct Environment*)previous;
    // Should I ever have nested user defined function calls, 
    // the top parameter can be a shortcut to the global environment
    // technically should be called bottom
    new->top = previous->top;
    return new;
}

Variable *lookup(Environment *environment, char *name){
    Variable *iterator = environment->top;
    while (iterator != NULL){
        if (strcmp(iterator->name, name) == 0) return newVariable(name, iterator->type, iterator->exp, iterator->param);
        iterator = (Variable*)iterator->next;
    }
    return newVariable(name, 0, NULL, NULL);
}

Variable *newVariable(char* name, int type, SExpression *exp, SExpression *params){
    Variable *var = malloc(sizeof(Variable));
    
    // Copy the name of the variable into a new char so that it does not get freed elsewhere
    int nameLength = strlen(name) + 1;
    char nameBuffer[nameLength];
    strncpy(nameBuffer, name, nameLength);
    var->name = malloc(sizeof(char) * nameLength);
    strncpy(var->name, nameBuffer, nameLength);
    var->type = type;

    // Now I have to do the same thing for the S-Expression
    if (exp != NULL) var->exp = copyExp(exp);
    else var->exp = NULL;
    if (type == FUNC && params != NULL) var->param = copyExp(params);
    else var->param = NULL;
    return var;
}

SExpression *set(Environment *environment, char* name, SExpression *exp){
    Variable *var = newVariable(name, VAR, exp, NULL);
    var->next = (struct Variable*)environment->top;
    environment->top = var;
    return copyExp(environment->top->exp);
}
