#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lista.h"
#define GREEN "\e[0;32m" //cores em ANSI utilizadas
#define YELLOW "\e[0;33m"
#define COLOR_RESET "\e[0m"
#define BLUE "\e[0;36m"
#define RED "\e[0;31m"

void imprimeInicio()
{
    char var;

    printf(YELLOW "\n\t\t --- T E R M O ---\n" COLOR_RESET);
    printf("- Tente descobrir uma palavra aleatória de 5 letras\n");
    printf("- Letras verdes faz parte da palvra e estão na posição correta\n");
    printf("- Letras amarelas fazem parte da palavra porém estão na posição errada\n");
    printf("- VocÃª tem apenas 5 chances para descobrir, será que é capaz?\n");
    printf(BLUE "\t(aperte enter para continuar)\n" COLOR_RESET);
    scanf("%c", &var);

    system("clear");
    printf(YELLOW "\n\t --- T E R M O ---\n" COLOR_RESET);
}

int verificaLetras(char string[5])
{
    int tam;

    printf(BLUE "\nSua palavra precisa conter 5 letras!\n" COLOR_RESET);
    printf("\nDigite novamente: ");
    gets(string);
    __fpurge(stdin);
    tam = strlen(string);

    return tam;
}

void acerto(char palavra[5])
{
    printf(BLUE "\n\t--- VOCÃŠ ACERTOU! ---" COLOR_RESET);
    printf("\n\tA palavra era: ");
    printf(GREEN "  %s  \n", palavra);
}

void erro(char palavra[5])
{
    printf(RED "\n\n\n\n\t  --- VOCÃŠ PERDEU! ---" COLOR_RESET);
    printf("\n\tA palavra era '%s'\n", palavra);
    printf("\nQuer jogador novamente?\n (1) Sim\n (2) NÃ£o\n -");
}

int main()
{
    char digitada[5], aux[5];
    int tamanho, numero, tentativas, igual, a = 0, bl[5] = {6, 6, 6, 6, 6}, denovo;

    do
    {

        //gerando numero aleatorio pra palavra
        srand(time(NULL));
        numero = rand() % 100;
        imprimeInicio();

        for (tentativas = 5; tentativas > 0; tentativas--)
        {

            printf(BLUE "\n\n**Voce tem %d tentativas!**", tentativas);
            printf(COLOR_RESET "\nDigite uma palavra: ");
            gets(digitada);
            __fpurge(stdin);

            tamanho = strlen(digitada);
            //apenas palavras de 5 letras, nao perde a vez se digitar com mais letras
            while (tamanho != 5)
            {
                tamanho = verificaLetras(digitada);
            }

            for (int i = 0; i < 5; i++)
            {
                aux[i] = palavra[numero][i];
            }
            //compara strings
            igual = strncmp(digitada, aux, 5);

            if (igual == 0)
            {
                acerto(aux);
                return 1;
            }

            else
            { //"ordenando" e comparando uma letra do aux com todas do digitada
                printf("\t");

                for (int i = 0; i < 5; i++)
                {

                    for (int k = 0; k < 5; k++)
                    { //ve quantas letras verdes tem na digitada
                        if (aux[k] == digitada[k])
                        {
                            bl[k] = k; //variavel bl recebe a posicao da letra verde
                        }
                    }

                    for (int j = 0; j < 5; j++)
                    {

                        if (aux[i] == digitada[i] && a == 0)
                        { //printa verde
                            printf(GREEN "%c", digitada[i]);
                            printf(" " COLOR_RESET);
                            a++; //contador pra entrar apenas em uma opção por letra (ou é verde ou é amarelo ou nao é nada, nao pode ser os dois)
                        }

                        if (aux[j] == digitada[i] && a == 0 && bl[j] == 6 && i != bl[i])
                        { //printa amarelo se nao tiver nenhuma verde na posicao certa
                            printf(YELLOW "%c", digitada[i]);
                            printf(" " COLOR_RESET);
                            a++;
                        }
                    }

                    if (a == 0)
                    {
                        printf("%c ", digitada[i]); //printa branca se nao tiver entrado nem no verde nem no amarelo
                    }
                    a = 0;

                    for (int j = 0; j < 5; j++)
                    { //for para zerar a variavel bl para verificar a proxima palavra no proximo laço
                        bl[j] = 6;
                    }
                }
            }
        }

        if (tentativas == 0)
        {
            erro(aux);
            scanf("%d", &denovo);
            __fpurge(stdin);
        }
    } while (denovo != 2);

    return 0;
}
