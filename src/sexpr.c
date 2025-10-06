#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "util.h"
#include "env.h"
#include "sexpr.h"

SExpression *add(SExpression *exp){
    if (!isDottedPair(exp)){
        // Keeping error statements inline so that I can reenable them
        // but not screw up tester.c
        fprintf(stderr, "S-Expression passed to add() must be a dotted pair\n");
        return NULL;
    }
    
    if (!isNumber(exp->cons.car) || !isNumber(exp->cons.cdr)){
        fprintf(stderr, "NaN passed to add()\n");
        return NULL;
    }

    Atom *a = &exp->cons.car->atom;
    Atom *b = &exp->cons.cdr->atom;

    AtomType resultType;
    char resultVal[MAX_WORD_LENGTH];
    switch(a->type + b->type){
        case A_INT + A_INT:
            resultType = A_INT;
            sprintf(resultVal, "%d", a->intVal + b->intVal);
            break;
        case A_INT + A_FLT:
            resultType = A_FLT;
            if (a->type == (AtomType)A_INT) sprintf(resultVal, "%f", (float)a->intVal + b->floatVal);
            else sprintf(resultVal, "%f", a->floatVal + (float)b->intVal);
            break;
        case A_FLT + A_FLT:
            resultType = A_FLT;
            sprintf(resultVal, "%f", a->floatVal + b->floatVal);
            break;
        default:
            fprintf(stderr, "Unrecognized AtomTypes in add()\n");
            return NULL;
    }
    return atom(resultType, resultVal);
}

SExpression *and(SExpression *exp, Environment *env){
    if (isAtom(exp)){
        fprintf(stderr, "Atom passed to and()\n");
        return NULL;
    }
    if (isNil(eval(car(exp), env))) return NULL;
    else if (isNil(eval(cdr(exp), env))) return NULL;
    return TRUE;
}

SExpression *atom(AtomType type, char *val){
    SExpression *atom = malloc(sizeof(SExpression));
    atom->type = (SExprType)ATOM;
    atom->atom.type = type;

    // Take a generic c-string as any input and cast it to the correct type
    switch (type){
        case (AtomType)A_STR:
        case (AtomType)A_ID:
            atom->atom.strVal = malloc(sizeof(char*) * strlen((char*)val) + 1);
            strncpy(atom->atom.strVal, (char*)val, strlen((char*)val) + 1);
            break;

        case (AtomType)A_INT:
            atom->atom.intVal = (int)atoi(val);
            break;

        case (AtomType)A_FLT:
            atom->atom.floatVal = (float)atof(val);
            break;

        default:
            fprintf(stderr, "Type: %d is an unhandled AtomType\n", type);
            break;
    }

    return atom;
}

SExpression *car(SExpression *exp){
    if (isNil(exp) || isAtom(exp)) return NULL;
    return exp->cons.car;
}

SExpression *cdr(SExpression *exp){
    if (isNil(exp) || isAtom(exp)) return NULL;
    return exp->cons.cdr;
}

SExpression *cadr(SExpression *exp){
    if (isNil(exp) || isAtom(exp)) return NULL;
    // By calling car and cdr each function handles nil or unexpected atoms
    return car(cdr(exp));
}

SExpression *caddr(SExpression *exp){
    if (isNil(exp) || isAtom(exp)) return NULL;
    // By calling car and cdr each function handles nil or unexpected atoms
    return cadr(cdr(exp));
}

SExpression *cond(SExpression *exp, Environment *env){
    if (exp == NULL) return NULL;
    // If the condition in the car is true, return the expression in the cadr
    if (eval(car(exp), env) != NULL) return eval(cadr(exp), env);
    // else recursively evalute the cdr(cdr)
    return cond(cdr(cdr(exp)), env);
}

SExpression *cons(SExpression* car, SExpression* cdr){
    SExpression *new = malloc(sizeof(SExpression));
    new->type = (SExprType)CONS;
    new->cons.car = car;
    new->cons.cdr = cdr;
    return new;
}

SExpression *divide(SExpression *exp){
    if (!isDottedPair(exp)){
        fprintf(stderr, "S-Expression passed to divide() must be a dotted pair\n");
        return NULL;
    }
    
    if (!isNumber(exp->cons.car) || !isNumber(exp->cons.cdr)){
        fprintf(stderr, "NaN passed to divide()\n");
        return NULL;
    }

    Atom *a = &exp->cons.car->atom;
    Atom *b = &exp->cons.cdr->atom;

    if (b->type == A_INT && b->intVal == 0) return NULL; // Divide by zero
    if (b->type == A_FLT && b->floatVal == 0.0) return NULL; // Divide by zero

    AtomType resultType;
    char resultVal[MAX_WORD_LENGTH];
    switch(a->type + b->type){
        case A_INT + A_INT:
            resultType = A_INT;
            sprintf(resultVal, "%d", a->intVal / b->intVal);
            break;
        case A_INT + A_FLT:
            resultType = A_FLT;
            if (a->type == (AtomType)A_INT) sprintf(resultVal, "%f", (float)a->intVal / b->floatVal);
            else sprintf(resultVal, "%f", a->floatVal / (float)b->intVal);
            break;
        case A_FLT + A_FLT:
            resultType = A_FLT;
            sprintf(resultVal, "%f", a->floatVal / b->floatVal);
            break;
        default:
            fprintf(stderr, "Unrecognized AtomTypes in divide()\n");
            return NULL;
    }
    return atom(resultType, resultVal);
}

SExpression *eq(SExpression *exp){
    if (isCons(exp)){
        // nil comparisons
        if (exp->cons.car == NULL && exp->cons.cdr == NULL) return TRUE;
        if (exp->cons.car == NULL || exp->cons.cdr == NULL) return NULL;
    }
    if (!isDottedPair(exp)){
        fprintf(stderr, "S-Expression passed to eq() must be a dotted pair\n");
        return NULL;
    }

    Atom *a = &exp->cons.car->atom;
    Atom *b = &exp->cons.cdr->atom;

    if (a->type != b->type) return NULL;

    switch (a->type){
        case A_ID:
        case A_STR:
            if (strcmp(a->strVal, b->strVal) == 0) return TRUE;
            else return NULL;
        case A_INT:
            if (a->intVal == b->intVal) return TRUE;
            else return NULL;
        case A_FLT:
            if (a->floatVal == b->floatVal) return TRUE;
            else return NULL;
        default:
            fprintf(stderr, "An error occurred in eq()\n");
            break;
    }
    return NULL;
}

SExpression *eval(SExpression *exp, Environment *env){
    if (isNil(exp)){
        // if nil return nil
        return NULL;
    }
    if (isCons(exp)){
        if (isNil(exp->cons.car) && isNil(exp->cons.cdr)){
            return NULL;
        }
        if (isNil(exp->cons.cdr)){
            // ex. if passed (3 ()) return (3)
            return eval(exp->cons.car, env);
        }
        if (isIdentifier(exp->cons.car)){
            char identifier[MAX_WORD_LENGTH];
            strncpy(identifier, exp->cons.car->atom.strVal, strlen(exp->cons.car->atom.strVal) + 1);

            // delay evaluation of expression in and(), or(), if(), cond(), quote(), define()
            // and do not allow overload
            if (strcmp(identifier, "and") == 0) return and(cdr(exp), env);
            else if (strcmp(identifier, "or") == 0) return or(cdr(exp), env);
            else if (strcmp(identifier, "if") == 0) return lif(cdr(exp), env);
            else if (strcmp(identifier, "cond") == 0) return cond(cdr(exp), env);
            else if (strcmp(identifier, "quote") == 0) return cdr(exp);
            else if (strcmp(identifier, "define") == 0) return define(env, cdr(exp));

            Variable *id = lookup(env, car(exp)->atom.strVal);
            if(id != NULL && id->type == FUNC){
                // Push a local function-scoped environment
                Environment *local = localEnvironment(env);
                
                // Loop through required and given parameters in function declaration
                SExpression *reqPar = id->param;
                SExpression *givPar = cdr(exp);
                while (reqPar != NULL){
                    set(local, car(reqPar)->atom.strVal, eval(car(givPar), env));
                    reqPar = cdr(reqPar);
                    givPar = cdr(givPar);
                }

                // Now evaluate the definition after the parameters have been passed to
                // the new scope
                return eval(id->exp, local);
            }
            else if (id->exp != NULL && id->type == VAR){
                // Just a variable, return the evaluated value
                if (isNil(cdr(exp))) return id->exp;
                return cons(id->exp, eval(cdr(exp), env));
            }

            // These functions are overloadable
            SExpression *params = eval(exp->cons.cdr, env);
            if (strcmp(identifier, "+") == 0) return add(params);
            else if (strcmp(identifier, "-") == 0) return subtract(params);
            else if (strcmp(identifier, "*") == 0) return multiply(params);
            else if (strcmp(identifier, "/") == 0) return divide(params);
            else if (strcmp(identifier, "%%") == 0) return modulo(params);
            else if (strcmp(identifier, "eq") == 0) return eq(params);
            else if (strcmp(identifier, "neq") == 0) return not(eq(params));
            else if (strcmp(identifier, "lt") == 0) return lt(params);
            else if (strcmp(identifier, "lte") == 0) return lte(params);
            else if (strcmp(identifier, "gt") == 0) return gt(params);
            else if (strcmp(identifier, "gte") == 0) return gte(params);
            else if (strcmp(identifier, "set") == 0) return set(env, params->cons.car->atom.strVal, params->cons.cdr);
            else if (strcmp(identifier, "car") == 0) return car(params);
            else if (strcmp(identifier, "cdr") == 0) return cdr(params);
            else if (strcmp(identifier, "cadr") == 0) return cadr(params);
            else if (strcmp(identifier, "caddr") == 0) return caddr(params);
            else if (strcmp(identifier, "cons") == 0) return cons(car(params), cdr(params));
            else if (strcmp(identifier, "not") == 0) return not(eval(params, env));
            return exp;
        }
        if (isCons(car(exp)) && isIdentifier(car(car(exp)))){
            // If the lambda key word is found
            // Declare a new function with the name lambda and then immediately execute it
            if (strcmp("lambda", car(car(exp))->atom.strVal) == 0){
                define(env, car(exp));
                SExpression *lambda = atom(A_ID, "lambda");
                return eval(cons(lambda, cdr(exp)), env);
            }
        }
        // recursively evaluate the car and cdr
        return cons(eval(exp->cons.car, env), eval(exp->cons.cdr, env));
    }
    else if (isAtom(exp)){
        if (isIdentifier(exp)) {
            if (strcmp(exp->atom.strVal, "true") == 0) return exp;
            return lookup(env, exp->atom.strVal)->exp;
        }
    }
    return exp;
}

SExpression *gt(SExpression *exp){
    if (!isDottedPair(exp)){
        fprintf(stderr, "S-Expression passed to gt() must be a dotted pair\n");
        return NULL;
    }
    
    if (!isNumber(exp->cons.car) || !isNumber(exp->cons.cdr)){
        fprintf(stderr, "NaN passed to gt()\n");
        return NULL;
    }

    Atom *a = &exp->cons.car->atom;
    Atom *b = &exp->cons.cdr->atom;

    SExpression *resultExp = NULL;
    int result;
    switch(a->type + b->type){
        case A_INT + A_INT:
            result = a->intVal > b->intVal;
            break;
        case A_INT + A_FLT:
            if (a->type == (AtomType)A_INT) result = (float)a->intVal > b->floatVal;
            else result = a->floatVal > (float)b->intVal;
            break;
        case A_FLT + A_FLT:
            result = a->floatVal > b->floatVal;
            break;
        default:
            fprintf(stderr, "Unrecognized AtomTypes in gt()\n");
            return NULL;
    }
    if (result) resultExp = TRUE;
    return resultExp;
}

SExpression *gte(SExpression *exp){
    if (!isDottedPair(exp)){
        fprintf(stderr, "S-Expression passed to gte() must be a dotted pair\n");
        return NULL;
    }
    
    if (!isNumber(exp->cons.car) || !isNumber(exp->cons.cdr)){
        fprintf(stderr, "NaN passed to gte()\n");
        return NULL;
    }

    Atom *a = &exp->cons.car->atom;
    Atom *b = &exp->cons.cdr->atom;

    SExpression *resultExp = NULL;
    int result;
    switch(a->type + b->type){
        case A_INT + A_INT:
            result = a->intVal >= b->intVal;
            break;
        case A_INT + A_FLT:
            if (a->type == (AtomType)A_INT) result = (float)a->intVal >= b->floatVal;
            else result = a->floatVal >= (float)b->intVal;
            break;
        case A_FLT + A_FLT:
            result = a->floatVal >= b->floatVal;
            break;
        default:
            fprintf(stderr, "Unrecognized AtomTypes in gte()\n");
            return NULL;
    }
    if (result) resultExp = TRUE;
    return resultExp;
}

int isAtom(SExpression *exp){ 
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    return (exp->type == (SExprType)ATOM); 
}

int isCons(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    return (exp->type == (SExprType)CONS); 
}

int isDottedPair(SExpression *exp){
    if (isNil(exp)) return UTIL_FALSE;
    if (isAtom(exp)) return UTIL_FALSE;
    if (!isNil(exp->cons.car) && !isNil(exp->cons.cdr)){
        if (isAtom(exp->cons.car) && isAtom(exp->cons.cdr)) return UTIL_TRUE;
    }
    return UTIL_FALSE;
}

int isFloat(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (exp->type != (SExprType)ATOM) return UTIL_FALSE;
    if (exp->atom.type != (AtomType)A_FLT) return UTIL_FALSE;
    return UTIL_TRUE;
}

int isIdentifier(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (exp->type != (SExprType)ATOM) return UTIL_FALSE;
    if (exp->atom.type != (AtomType)A_ID) return UTIL_FALSE;
    return UTIL_TRUE;
}

int isInt(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (exp->type != (SExprType)ATOM) return UTIL_FALSE;
    if (exp->atom.type != (AtomType)A_INT) return UTIL_FALSE;
    return UTIL_TRUE;
}

int isList(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (isDottedPair(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (exp->type == (SExprType)ATOM) return UTIL_FALSE;
    if (exp->type == (SExprType)CONS && isNil(exp->cons.cdr) == UTIL_TRUE) return UTIL_TRUE;
    return isList(exp->cons.car) || isList(exp->cons.cdr);
}

int isNil(SExpression *exp){
    if (exp == NULL) return UTIL_TRUE;
    return UTIL_FALSE;
}

int isNumber(SExpression *exp){ return isFloat(exp) || isInt(exp); }

int isString(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (exp->type != (SExprType)ATOM) return UTIL_FALSE;
    if (exp->atom.type != (AtomType)A_STR) return UTIL_FALSE;
    return UTIL_TRUE;
}

// Lisp-If
SExpression *lif(SExpression *exp, Environment *env){
    if (eval(car(exp), env) == NULL) return eval(cdr(cdr(exp)), env);
    return eval(cadr(exp), env);
}

SExpression *lt(SExpression *exp){
    if (!isDottedPair(exp)){
        fprintf(stderr, "S-Expression passed to lt() must be a dotted pair\n");
        return NULL;
    }
    
    if (!isNumber(exp->cons.car) || !isNumber(exp->cons.cdr)){
        fprintf(stderr, "NaN passed to lt()\n");
        return NULL;
    }

    Atom *a = &exp->cons.car->atom;
    Atom *b = &exp->cons.cdr->atom;

    SExpression *resultExp = NULL;
    int result;
    switch(a->type + b->type){
        case A_INT + A_INT:
            result = a->intVal < b->intVal;
            break;
        case A_INT + A_FLT:
            if (a->type == (AtomType)A_INT) result = (float)a->intVal < b->floatVal;
            else result = a->floatVal < (float)b->intVal;
            break;
        case A_FLT + A_FLT:
            result = a->floatVal < b->floatVal;
            break;
        default:
            fprintf(stderr, "Unrecognized AtomTypes in lt()\n");
            return NULL;
    }
    if (result) resultExp = TRUE;
    return resultExp;
}

SExpression *lte(SExpression *exp){
    if (!isDottedPair(exp)){
        fprintf(stderr, "S-Expression passed to lte() must be a dotted pair\n");
        return NULL;
    }
    
    if (!isNumber(exp->cons.car) || !isNumber(exp->cons.cdr)){
        fprintf(stderr, "NaN passed to lte()\n");
        return NULL;
    }

    Atom *a = &exp->cons.car->atom;
    Atom *b = &exp->cons.cdr->atom;

    SExpression *resultExp = NULL;
    int result;
    switch(a->type + b->type){
        case A_INT + A_INT:
            result = a->intVal <= b->intVal;
            break;
        case A_INT + A_FLT:
            if (a->type == (AtomType)A_INT) result = (float)a->intVal <= b->floatVal;
            else result = a->floatVal <= (float)b->intVal;
            break;
        case A_FLT + A_FLT:
            result = a->floatVal <= b->floatVal;
            break;
        default:
            fprintf(stderr, "Unrecognized AtomTypes in lte()\n");
            return NULL;
    }
    if (result) resultExp = TRUE;
    return resultExp;
}

SExpression *modulo(SExpression *exp){
    if (!isDottedPair(exp)){
        fprintf(stderr, "S-Expression passed to modulo() must be a dotted pair\n");
        return NULL;
    }
    
    if (!isNumber(exp->cons.car) || !isNumber(exp->cons.cdr)){
        fprintf(stderr, "NaN passed to modulo()\n");
        return NULL;
    }

    Atom *a = &exp->cons.car->atom;
    Atom *b = &exp->cons.cdr->atom;

    if (b->type == A_INT && b->intVal == 0) return NULL; // Divide by zero

    AtomType resultType;
    char resultVal[MAX_WORD_LENGTH];
    switch(a->type + b->type){
        case A_INT + A_INT:
            resultType = A_INT;
            sprintf(resultVal, "%d", a->intVal % b->intVal);
            break;
        case A_INT + A_FLT:
        case A_FLT + A_FLT:
            fprintf(stderr, "Only integer types are supported for the modulo operation\n");
            return NULL;
        default:
            fprintf(stderr, "Unrecognized AtomTypes in modulo()\n");
            return NULL;
    }
    return atom(resultType, resultVal);
}

SExpression *multiply(SExpression *exp){
    if (!isDottedPair(exp)){
        fprintf(stderr, "S-Expression passed to multiply() must be a dotted pair\n");
        return NULL;
    }
    
    if (!isNumber(exp->cons.car) || !isNumber(exp->cons.cdr)){
        fprintf(stderr, "NaN passed to multiply()\n");
        return NULL;
    }

    Atom *a = &exp->cons.car->atom;
    Atom *b = &exp->cons.cdr->atom;

    AtomType resultType;
    char resultVal[MAX_WORD_LENGTH];
    switch(a->type + b->type){
        case A_INT + A_INT:
            resultType = A_INT;
            sprintf(resultVal, "%d", a->intVal * b->intVal);
            break;
        case A_INT + A_FLT:
            resultType = A_FLT;
            if (a->type == (AtomType)A_INT) sprintf(resultVal, "%f", (float)a->intVal * b->floatVal);
            else sprintf(resultVal, "%f", a->floatVal * (float)b->intVal);
            break;
        case A_FLT + A_FLT:
            resultType = A_FLT;
            sprintf(resultVal, "%f", a->floatVal * b->floatVal);
            break;
        default:
            fprintf(stderr, "Unrecognized AtomTypes in multiply()\n");
            return NULL;
    }
    return atom(resultType, resultVal);
}

SExpression *not(SExpression *exp){
    if (isNil(exp)) return TRUE;
    else return NULL;
}

SExpression *or(SExpression *exp, Environment *env){
    if (isAtom(exp)){
        fprintf(stderr, "Atom passed to or()\n");
        return NULL;
    }
    if (isNil(eval(car(exp), env))){
        if (isNil(eval(cdr(exp), env))) return NULL;
    }
    return TRUE;
}

void print(SExpression *exp) {
    if (exp == NULL) {
        printf("()");
        return;
    }

    if (exp->type == (SExprType)ATOM) {
        switch (exp->atom.type){
            case A_STR:
            case A_ID:
                printf("%s", exp->atom.strVal);
                break;

            case A_INT:
                printf("%d", exp->atom.intVal);
                break;

            case A_FLT:
                printf("%f", exp->atom.floatVal);
                break;
        }
    } 
    else if (exp->type == (SExprType)CONS) {
        printf("(");
        while (exp != NULL && exp->type == CONS) {
            print(exp->cons.car);
            exp = exp->cons.cdr;
            if (exp != NULL) printf(" ");
        }
        if (exp != NULL) {
            printf(". ");
            print(exp);
        }
        printf(")");
    }
}

SExpression *subtract(SExpression *exp){
    if (!isDottedPair(exp)){
        fprintf(stderr, "S-Expression passed to subtract() must be a dotted pair\n");
        return NULL;
    }
    
    if (!isNumber(exp->cons.car) || !isNumber(exp->cons.cdr)){
        fprintf(stderr, "NaN passed to subtract()\n");
        return NULL;
    }

    Atom *a = &exp->cons.car->atom;
    Atom *b = &exp->cons.cdr->atom;

    AtomType resultType;
    char resultVal[MAX_WORD_LENGTH];
    switch(a->type + b->type){
        case A_INT + A_INT:
            resultType = A_INT;
            sprintf(resultVal, "%d", a->intVal - b->intVal);
            break;
        case A_INT + A_FLT:
            resultType = A_FLT;
            if (a->type == (AtomType)A_INT) sprintf(resultVal, "%f", (float)a->intVal - b->floatVal);
            else sprintf(resultVal, "%f", a->floatVal - (float)b->intVal);
            break;
        case A_FLT + A_FLT:
            resultType = A_FLT;
            sprintf(resultVal, "%f", a->floatVal - b->floatVal);
            break;
        default:
            fprintf(stderr, "Unrecognized AtomTypes in subtract()\n");
            return NULL;
    }
    return atom(resultType, resultVal);
}

int toBool(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    return UTIL_TRUE;
}
