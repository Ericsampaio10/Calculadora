#include <stdio.h>
#include "expressao.h"

int main() {
    // Exemplo de uso da função de conversão para notação infixa
    char exprPosFixa[] = "3 4 2 * 1 5 - 2 3 ^ ^ / +";
    printf("Expressão Posfixa: %s\n", exprPosFixa);
    printf("Expressão Infixa: %s\n", getFormaInFixa(exprPosFixa));

    // Exemplo de uso da função de avaliação
    float resultado = getValor(exprPosFixa);
    printf("Resultado: %.6f\n", resultado);

    return 0;
}
