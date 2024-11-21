#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "expressao.h"

// Função auxiliar para verificar se um caractere é operador
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ||
            c == 'r' || c == 's' || c == 'c' || c == 't' || c == 'l');
}

// Função auxiliar para verificar se um caractere é número
int isNumber(char c) {
    return (isdigit(c) || c == '.');
}

// Função que realiza a conversão de pós-fixa para infixa
char* getFormaInFixa(char *Str) {
    static char result[512];
    char stack[512][512];  // Pilha para armazenar subexpressões
    int top = -1;  // Índice do topo da pilha

    int i = 0, j = 0;
    while (Str[i] != '\0') {
        // Ignorar espaços em branco
        if (Str[i] == ' ') {
            i++;
            continue;
        }

        // Se o caractere for número ou variável, empilha
        if (isNumber(Str[i])) {
            j = 0;
            while (isNumber(Str[i])) {
                result[j++] = Str[i++];
            }
            result[j] = '\0';
            strcpy(stack[++top], result);  // Empilha o número ou variável
        }

        // Se for operador, desempilha e forma a expressão infixa
        else if (isOperator(Str[i])) {
            char operand2[512], operand1[512];
            strcpy(operand2, stack[top--]);  // Desempilha o segundo operando
            strcpy(operand1, stack[top--]);  // Desempilha o primeiro operando

            // Forma a subexpressão infixa com parênteses
            sprintf(result, "(%s %c %s)", operand1, Str[i], operand2);
            strcpy(stack[++top], result);  // Empilha a subexpressão
        }

        i++;
    }

    return stack[top];  // Retorna a expressão infixa
}

// Função que avalia uma expressão pós-fixada
float getValor(char *Str) {
    float stack[512];  // Pilha para armazenar os operandos
    int top = -1;  // Índice do topo da pilha
    int i = 0;
    float op1, op2;

    while (Str[i] != '\0') {
        // Ignorar espaços
        if (Str[i] == ' ') {
            i++;
            continue;
        }

        // Se for número, empilha
        if (isNumber(Str[i])) {
            char num[512];
            int j = 0;
            while (isNumber(Str[i])) {
                num[j++] = Str[i++];
            }
            num[j] = '\0';
            stack[++top] = atof(num);  // Converte string para número e empilha
        }

        // Se for operador, desempilha e faz o cálculo
        else if (isOperator(Str[i])) {
            op2 = stack[top--];  // Desempilha o segundo operando
            op1 = stack[top--];  // Desempilha o primeiro operando

            switch (Str[i]) {
                case '+': stack[++top] = op1 + op2; break;
                case '-': stack[++top] = op1 - op2; break;
                case '*': stack[++top] = op1 * op2; break;
                case '/': stack[++top] = op1 / op2; break;
                case '^': stack[++top] = pow(op1, op2); break;
                case 'r': stack[++top] = sqrt(op1); break; // Raiz quadrada
                case 's': stack[++top] = sin(op1); break;  // Seno
                case 'c': stack[++top] = cos(op1); break;  // Cosseno
                case 't': stack[++top] = tan(op1); break;  // Tangente
                case 'l': stack[++top] = log10(op1); break; // Logaritmo de base 10
            }
        }

        i++;
    }

    return stack[top];  // Retorna o resultado final
}
