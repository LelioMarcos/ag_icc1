#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define MAX_GERACOES 1000
#define CHANCE_MUTACAO 0.3
#define MAX_NUM_INDIVIDUO 100 // com x > 73, pow(x, 5) explode;

#define FALSE 0
#define TRUE 1

int main()
{   //declaracao e inicializacao
    srand( (unsigned)time( NULL ) );
    long long int equacao;
    int a,b,c,d,e,f, vet_pop_inicial[10], x, melhor[2];
    int maior = 0;
    int melhores[10], m = 0;
    float chances[10], melhor_chance = 0.0;
    long long int eqs[10];
    int mask = 0, pos = 1;

    char found = FALSE;

    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

    //equacao=a*pow(x,5)+b*pow(x,4)+c*pow(x,3)+d*pow(x,2)+e*x+f;

    //gerando populacao aleatoria (supondo n=10;
    for(int i=0; i<10; i++){
        vet_pop_inicial[i] = rand() % MAX_NUM_INDIVIDUO;
    }

    for (int i = 0; i < MAX_GERACOES && !found; i++) {
        m = 0;
        // Avaliar a população
        for(int j=0; j<10; j++) {
            if (vet_pop_inicial[j] < 0) {
                vet_pop_inicial[j] = rand() % MAX_NUM_INDIVIDUO;
            }

            //printf("%d ", vet_pop_inicial[j]);

            x = vet_pop_inicial[j];

            printf("%d ", x);
            equacao = a*pow(x,5)+b*pow(x,4)+c*pow(x,3)+d*pow(x,2)+e*x+f;

            // se a solução é aceitável, sair pela janela
            if (equacao == 0) {
                found = TRUE;
                melhor[0] = x;
                melhor[1] = i + 1;
                break;
            }


            if (equacao > maior) {
                maior = equacao;
            }

            eqs[j] = equacao;
        }
        printf("\n");

        if (found) break;

        for(int j=0; j < 10; j++){
            chances[j] = 1 - (((double)eqs[j]/1.1) / maior);
            if (chances[j] >= melhor_chance) {
                melhor_chance = chances[j];
                melhor[0] = vet_pop_inicial[j];
                melhor[1] = i + 1;
            }
        }
        printf("\n");


        for (int j = 0; j < 5; j++) {
            float choose = (float)rand()/RAND_MAX;

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

        //Cruzamento

        for (int j = 0; j < 5; j+=2) {
            vet_pop_inicial[j] = (melhores[j] & 0xFFFFFF00) ^ (melhores[j + 1] & 0x000000FF);
            vet_pop_inicial[j+1] = (melhores[j] & 0x000000FF) ^ (melhores[j + 1] & 0xFFFFFF00);
        }


        // Mutacao
        for (int j = 0; j < 10; j++) {
            pos = 1;
            mask = 0;
            for (int k = 0; k < 4; k++) {
                float choose = (float)rand()/RAND_MAX;

                if (choose < CHANCE_MUTACAO) {
                    mask += 1 * pos;
                } else {
                    mask += 0 * pos;
                }

                pos *= 2;
            }
            vet_pop_inicial[j] = vet_pop_inicial[j] ^ mask;
        }
    }

    printf("ACHAMOS!!!! %d na geração %d", melhor[0], melhor[1]);

    return 0;
}
