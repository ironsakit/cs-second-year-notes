#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *add_str(char *str1, char *str2)
{
    int len1 = strlen(str1), len2 = strlen(str2);
    int len_hold = (len1 > len2 ? len1: len2) + 2;
    int count_s1 = len1 - 1, count_s2 = len2 - 1;   // salto il '\0' per un carattere strlen(a) mi da 1 quindi il count inizia da 1-1 = 0 (il primo e unico elemento)

    char *hold = (char *)malloc(len_hold);
    int count_res = 0, n1, n2, somma, riporto = 0;
    while (count_s1 >= 0 || count_s2 >= 0)
    {
        n1 = 0, n2 = 0;   // i numeri interi che estraggo da ogni cifra della stringhe in parallelo
        if (count_s1 >= 0) n1 = str1[count_s1--] - '0';
        if (count_s2 >= 0) n2 = str2[count_s2--] - '0';
        somma = n1 + n2 + riporto;

        hold[count_res++] = (char)((somma % 10) + '0');  // prendo solo la 1° cifra della somma tanto l'altra o non c'è o è il riporto che calcolo dopo

        riporto = (somma > 9)? 1 : 0;  // se la somma sfora il 9 allora ho un riporto (max riporto = 1)
    }

    if (riporto == 1) hold[count_res++] = '1';
    hold[count_res] = '\0';

    char *res = (char*)malloc(count_res + 1);

    // lo ricopio al contrario
    for (int i = 0; i < count_res; i++) {
        res[i] = hold[count_res - 1 - i]; // Copia partendo dall'ultimo carattere
    }

    res[count_res] = '\0';  // chiudo la stringa
    free(hold);  // libero la memoria allocata con hold
    return res;
}

int main(void)
{
    char *n1 = strdup("0"), *n2 = strdup("1");  // alloco dinamicamente le due stringhe perchè non potrei fare free su due memorie di sola lettura
    int fib = 100000;

    for (int i = 2; i <= fib; i++)
    {
        char *n3 = add_str(n1, n2);
        free(n1);
        n1 = n2;
        n2 = n3;
        if (i == fib) printf("%d) %s\n\n%zu", i, n3, strlen(n3));
    }

    free(n1);
    free(n2);   // libero solo n2 perchè punta alla stessa memoria di n3
    return 0;
}