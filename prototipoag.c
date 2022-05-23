#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define MAX_GERACOES 1

#define FALSE 0
#define TRUE 1

int main()
{   //declaracao e inicializacao
    srand(time(0));
    long long int equacao;
    int a,b,c,d,e,f, vet_pop_inicial[10], x, melhor[2];
    int maior = 0, menor = 0x7FFFFFFF;
    int melhores[10], m = 0;
    double chances[10], maior_chance;
    long long int eqs[10];

    char found = FALSE;

    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

    //equacao=a*pow(x,5)+b*pow(x,4)+c*pow(x,3)+d*pow(x,2)+e*x+f;

    //gerando populacao aleatoria (supondo n=10;
    for(int i=0; i<10; i++){
        vet_pop_inicial[i] = rand() % 20;
        printf("%d\n", vet_pop_inicial[i]);
    }




    for (int i = 0; i < MAX_GERACOES && !found; i++) {
        m = 0;
        // Avaliar a popula��o
        for(int j=0; j<10; j++){
            x = vet_pop_inicial[j];

            equacao=a*pow(x,5)+b*pow(x,4)+c*pow(x,3)+d*pow(x,2)+e*x;

            // se a solu��o � aceit�vel, sair pela janela
            if (equacao == 0) {
                found = TRUE;
                melhor[0] = x;
                melhor[1] = i + 1;
                break;
            }


            if (equacao > maior) {
                maior = equacao;
            }

            if (equacao < menor) {
                menor = equacao;
            }

            eqs[j] = equacao;
        }

        //if (found) break;

        for(int j=0; j < 10; j++){
            chances[j] = 1 - (((double)eqs[j]/1.01) / maior);

            printf("%d -> %llf\n", eqs[j], chances[j]);
        }

        printf("\n\n");

        for (int j = 0; j < 6; j++) {
            int rng = rand() % (maior + 1 - menor) + menor;
            double choose = 1 - ((double)rng / maior);

            for (int k = 0; k < 10; k++) {
                if (choose < chances[k] && chances[k] != 0) {
                    printf("%d -> %f\n", vet_pop_inicial[k], chances[k]);
                    melhores[m++] = vet_pop_inicial[k];
                    chances[k] = 0;
                    break;
                }
            }
        }

        for (int j = 0; j < 10; j++) {
            if (chances[j] != 0) {
                melhores[m++] = chances[j];
            }
        }

        //Cruzamento

        printf("\n");

        for (int j = 0; j < 9; j+=2) {
            vet_pop_inicial[j] = (melhores[j] & 0xFFFF0000) ^ (melhores[j + 1] & 0x0000FFFF);
            vet_pop_inicial[j+1] = (melhores[j] & 0x0000FFFF) ^ (melhores[j + 1] & 0xFFFF0000);

            printf("%d\n", vet_pop_inicial[j]);
            printf("%d\n", vet_pop_inicial[j+1]);
        }
    }

    printf("ACHAMOS!!!! %d na gera��o %d", melhor[0], melhor[1]);

    return 0;
}
