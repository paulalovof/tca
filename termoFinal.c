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
    printf("- Voce tem apenas 5 chances para descobrir, será que é capaz?\n");
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
    printf(BLUE "\n\t--- VOCE ACERTOU! ---" COLOR_RESET);
    printf("\n\tA palavra era: ");
    printf(GREEN "  %s  \n", palavra);
}

int erro(char palavra[5])
{
    int denovo;
    
    printf(RED "\n\n\n\n\t  --- VOCE PERDEU! ---" COLOR_RESET);
    printf("\n\tA palavra era '%s'\n", palavra);
    printf("\nQuer jogador novamente?\n (1) Sim\n (2) Nao\n -");
    scanf("%d", &denovo);
    __fpurge(stdin);

    return denovo;
}

void zerarPosicao(int verificador[5])
{
    for (int j = 0; j < 5; j++)
    {
        verificador[j] = 6;
    }
}

int gerarNumAleatorio()
{
    int numero;

    srand(time(NULL));
    numero = rand() % 100;
    imprimeInicio();

    return numero;   
}

int main()
{
    char digitada[5], vetorArrumado[5];
    int tamanho, numero, tentativas, igual, contadorLetraCerta = 0, verificadorDePosicao[5] = {6, 6, 6, 6, 6}, denovo;

    do
    {

        //gerando numero aleatorio pra palavra
        numero = gerarNumAleatorio();
        

        for (tentativas = 5; tentativas > 0; tentativas--)
        {

            printf(BLUE "\n\n**Voce tem %d tentativas!**", tentativas);
            printf(COLOR_RESET "\nDigite uma palavra: ");
            gets(digitada);
            __fpurge(stdin);

            tamanho = strlen(digitada);
            
            while (tamanho != 5)
            {
                tamanho = verificaLetras(digitada);
            }

            for (int i = 0; i < 5; i++)
            {
                vetorArrumado[i] = palavra[numero][i];
            }
            
            igual = strncmp(digitada, vetorArrumado, 5);

            if (igual == 0)
            {
                acerto(vetorArrumado);
                return 1;
            }

            else
            { 
                printf("\t");

                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if (vetorArrumado[j] == digitada[j])
                        {
                            verificadorDePosicao[j] = j; 
                        }
                    }

                    for (int j = 0; j < 5; j++)
                    {

                        if (vetorArrumado[i] == digitada[i] && contadorLetraCerta == 0)
                        {
                            printf(GREEN "%c", digitada[i]);
                            printf(" " COLOR_RESET);
                            contadorLetraCerta++; 
                        }

                        if (vetorArrumado[j] == digitada[i] && contadorLetraCerta == 0 && verificadorDePosicao[j] == 6 && i != verificadorDePosicao[i])
                        {
                            printf(YELLOW "%c", digitada[i]);
                            printf(" " COLOR_RESET);
                            contadorLetraCerta++;
                        }
                    }

                    if (contadorLetraCerta == 0)
                    {
                        printf("%c ", digitada[i]);
                    }
                    contadorLetraCerta = 0;

                    zerarPosicao(verificadorDePosicao);
                }
            }
        }

        if (tentativas == 0)
        {
            denovo = erro(vetorArrumado);
        }
    } while (denovo != 2);

    return 0;
}
