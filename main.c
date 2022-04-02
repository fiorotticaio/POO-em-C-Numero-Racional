#include <stdio.h>
#include "meu_racional.h"

int main () {

      MeuRacional_pt ptR1 = NULL, ptR2 = NULL, ptR3 = NULL;

      /*Aqui é feito chamadas de algumas funções
      * através dos ponteiros que estão na tabela vtbl (ponteiro "metodo")
      * da superclasse "Numero". Como as funções desta tabela esperam
      * receber "ponteiro para Numero_t", preciso converter o ptX1 para
      * Numero_pt e depois converter o resultado "de volta" para
      * MeuRacional_pt */

      ptR1 = Rac_constroi(ptR1, 10, 3);
      printf ("O primeiro numero é: %s\n", ptR1->Metodo->imprime(ptR1));
      
      ptR2 = ptR1->Metodo->copia(ptR1);
      printf ("Os dois numeros sao %s e %s \n", ptR1->Metodo->imprime (ptR1), ptR2->Metodo->imprime (ptR2));

      ptR3 = Rac_constroi (ptR3, 5, 2);
      ptR3 = ptR2->Metodo->atribui(ptR2, ptR3);
      printf ("R3 recebeu o valor de R2 = %s \n", ptR3->Metodo->imprime (ptR3));

      ptR3 = ptR1->Metodo->soma(ptR1, ptR2, ptR3);
      printf ("R3 recebeu a soma de R1 com R2 = %s \n", ptR3->Metodo->imprime (ptR3));
      
      ptR3 = ptR3->Metodo->subt(ptR1, ptR2, ptR3);
      printf ("R3 recebeu a subtracao de R2 com R1 = %s \n", ptR3->Metodo->imprime (ptR3));

      ptR3 = ptR1->Metodo->mult(ptR1, ptR2, ptR3);
      printf ("R3 recebeu a multiplicacao de R1 com R2 = %s \n", ptR3->Metodo->imprime (ptR3));

      ptR3 = ptR1->Metodo->divd(ptR1, ptR2, ptR3);
      printf ("R3 recebeu a divisão de R1 com R2 = %s \n", ptR3->Metodo->imprime (ptR3));
      
      ptR3 = ptR1->Metodo->ac_soma(ptR3, ptR2);
      printf ("R3 foi somado com R2 = %s \n", ptR3->Metodo->imprime (ptR3));

      ptR3 = ptR3->Metodo->ac_subt(ptR3, ptR2);
      printf ("R3 foi subtraido de R2 = %s \n", ptR3->Metodo->imprime (ptR3));

      ptR3 = ptR3->Metodo->ac_mult(ptR3, ptR2);
      printf ("R3 foi multiplicado por R2 = %s \n", ptR3->Metodo->imprime (ptR3));
      
      ptR3 = ptR3->Metodo->ac_divd(ptR3, ptR2);
      printf ("R3 foi dividido por R2 = %s \n", ptR3->Metodo->imprime (ptR3));

      printf("R1: %s \n", ptR1->Metodo->imprime(ptR1));
      printf("R2: %s \n", ptR2->Metodo->imprime(ptR2));
      printf("R3: %s \n", ptR3->Metodo->imprime(ptR3));

      if (ptR1->Metodo->compara(ptR1,ptR2)==0) printf ("R1 eh igual a R2 = %s\n", ptR1->Metodo->imprime(ptR1));
      if (ptR1->Metodo->compara(ptR1,ptR3)>0) printf ("R1 eh maior que R3 \n");
      if (ptR1->Metodo->compara(ptR3,ptR2)<0) printf ("R3 eh menor que R2 \n");

      ptR1->Metodo->destroi(ptR1);
      ptR2->Metodo->destroi(ptR2);
      ptR3->Metodo->destroi(ptR3);

      return (0);
}