/*
            ***Trabalho 1 de ICC - Algoritmo Genético***
    **Alunos Lélio Marcos Rangel Cunha, Rafael Comitre Garcia Conrado**
O problema a ser resolvido é a equação de quinto grau ax^5+bx^4+cx^3+dx^2+ex+f
*/



#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define MAX_GERACOES 1000  //o escopo do algoritmo será de 1000 geracoes.
#define CHANCE_MUTACAO 0.3   //definimos arbitrariamente a chance de mutacao como 0.3
#define MAX_NUM_INDIVIDUO 200 // Aqui definimos um "limite" para individuos. com x > 73, pow(x, 5) explode e nao chegamos em solucoes boas.

#define FALSE 0
#define TRUE 1




int main()
{   //declaracao e inicializacao
    srand( (unsigned)time( NULL ) );
    long long int equacao;
    int a,b,c,d,e,f, vet_pop_inicial[10], x, melhor[2];
    long long int maior = 0;
    int melhores[10], m = 0;
    float chances[10], melhor_chance = 0.0;
    long long int eqs[10];
    int mask = 0, pos = 1;

    char found = FALSE;

    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);  //recebemos os coeficientes da equacao



    // ***gerando populacao aleatoria (considerando o  nº de individuos=10)***
    for(int i=0; i<10; i++){
        vet_pop_inicial[i] = (rand() % MAX_NUM_INDIVIDUO) - MAX_NUM_INDIVIDUO/2;  //aqui, geramos o individuo e armazenamos no vetor vet_pop_inicial
    }                                                                               //

    for (int i = 0; i < MAX_GERACOES && !found; i++) {      //enquanto nao atingir a ultima geracao e nenhuma solucao boa for encontrada, continuar
        m = 0;
        maior = 0;

        // Avaliar a população
        for(int j=0; j<10; j++) {
            while (vet_pop_inicial[j] >= 73 || vet_pop_inicial[j] <= -73) {
                vet_pop_inicial[j] = (rand() % MAX_NUM_INDIVIDUO) - MAX_NUM_INDIVIDUO/2;
            }

            x = vet_pop_inicial[j];

            printf("%d\t", x);
            equacao = a*pow(x,5)+b*pow(x,4)+c*pow(x,3)+d*pow(x,2)+e*x+f;

            if (equacao < 0) equacao *= -1;   //consideramos sempre o modulo da solucao (distancia ate 0)

            // se a solução eh otima (=0), fim
            if (equacao == 0) {
                found = TRUE;
                melhor[0] = x;
                melhor[1] = i + 1;
                break;
            }

            if (equacao > maior) {  //aqui, vamos armazenar qual foi a maior solucao (mais distante de 0)
                maior = equacao;          // e sera util posteriormente
            }

            eqs[j] = equacao;  //eqs eh o vetor que armazena as solucoes
        }

        if (found) break; //se o algoritmo acha a solucao 0, fim da procura

        printf("\n");


        for(int j=0; j < 10; j++){
            chances[j] = 1 - (((float)eqs[j]/1.1) / maior); //definindo qual a chance de um cruzamento ocorrer. Eh inversamente proporcional ao tamanho
            if (chances[j] >= melhor_chance) {              // da solucao.
                melhor_chance = chances[j];                   //aqui, classificamos com relacao ao tamanho da chance e armazenamos em um vetor
                melhor[0] = vet_pop_inicial[j]; // aqui, armazenamos o individuo para determinar qual eh o "melhor" dessa geracao
                melhor[1] = i + 1;               //guardamos qual eh o numero da geracao
            }
        }

        for (int j = 0; j < 5; j++) {
            float choose = (float)rand()/RAND_MAX;              //neste bloco, trabalhamos

            for (int k = 0; k < 10; k++) {
                if (choose < chances[k] && chances[k] != 0) {
                    melhores[m++] = vet_pop_inicial[k];
                    chances[k] = 0;
                    break;
                }
            }
        }

        for (int j = 0; j < 6; j++) {
            if (chances[j] != 0) {
                melhores[m++] = chances[j];
            }
        }

        //  ***Cruzamento***
        for (int j = 0; j < 5; j+=2) {
            vet_pop_inicial[j] = (melhores[j] & 0x000000F) ^ (melhores[j + 1] & 0xFFFFFFF0);   //cruzamos o primeiro byte de um com o resto do bytes de outro
            vet_pop_inicial[j+1] = (melhores[j] & 0xFFFFFFF0) ^ (melhores[j + 1] & 0x000000F);  //e vice versa
        }          //OBSERVACAO: tratamos como 2 filhos por casal.


        // ***Mutacao***
        for (int j = 0; j < 10; j++) {
            pos = 1;
            mask = 0;
            for (int k = 0; k < 4; k++) {
                float choose = (float)rand()/RAND_MAX;  //choose eh a 'moeda' que lançaremos para descobrir se o bit do indivíduo vai sofrer mutacao

                if (choose < CHANCE_MUTACAO) {   //se a moeda for inferior a chance de mutacao
                    mask += 1 * pos;
                } else {
                    mask += 0 * pos;              //se a moeda for superior a chance de mutacao, ocorre
                }

                pos *= 2;
            }
            vet_pop_inicial[j] = vet_pop_inicial[j] ^ mask;      //aplicamos a mascara resultante em cada individuo da pop, que sofrem ou nao mutacao,
        }                                                                       //dependendo do resultado da 'moeda'
    }

    printf("\n\nA solucao foi encontrada:\nX=%d na geracao %d", melhor[0], melhor[1]);

    return 0;
}
