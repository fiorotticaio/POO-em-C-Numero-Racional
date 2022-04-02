/**********************************************************************
 * Baseado no código disponibilizado em
 *  Application Note: "Object-Oriented Programming in C"
 * https://www.state-machine.com/doc/AN_OOP_in_C.pdf
 *
 * Aqui se implementa o número do tipo "racional"
 *
 * numero.h definiu a interface do "número_t virtual"
 * que é usada aqui
 * ********************************************************************/
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "meu_racional.h"

#define TRUE 1
#define FALSE 0

/*------------------------------------------------------------------*
 *  IMPLEMENTACAO DAS FUNCOES VIRTUAIS DE "Racional"                *
 * Uma função virtual é uma função que é declarada (mas não         *
 * implementada em uma classe base (NO CASO, NUMERO) e redefinida   *
 * pela classe derivada (NO CASO, Racional).                        *
 * Para declarar uma função como sendo virtual, é preciso associá-la*
 * com uma entrada da tabela vtbl da classe base.                   *
 * A redefinição da função na classe derivada sobrepõe a definição  *
 * da função na classe base.                                        *
 *                                                                  *
 * No fundo, a declaração da função virtual na classe base age      *
 * como uma espécie de indicador que especifica uma linha geral de  *
 * ação e estabelece uma interface de acesso.                       *
 *                                                                  *
 * A redefinição da função virtual pela classe derivada especifica  *
 * verdadeiramente IMPLEMENTA as operações realmente executadas     *
 * por cada método da tabela.                                       *
 *                                                                  *
 * Quando acessadas normalmente, funções virtuais se comportam como *
 * qualquer outro tipo de função membro da classe. Entretanto, o que*
 * torna funções virtuais importantes e capazes de suportar         *
 * polimorfismo em tempode execução é o seu modo de comportamento   *
 * quando acessado através de um apontador.                         *
 *                                                                  *
 * Lembre-se que um apontador para a classe base pode ser usado     *
 * para apontar para qualquer classe derivada daquela classe base,  *
 * desde que corretamente convertido ("cast").                      *
 *                                                                  *
 * Quando um apontador base aponta para um objeto derivado que      *
 * contém uma função virtual, o programa irá determina qual versão  *
 * daquela função chamar baseada no tipo do objeto apontado pelo    *
 * apontador.                                                       *
 *                                                                  *
 * Assim, quando objetos diferentes são apontados, versões          *
 * diferentes da função virtual são executadas.                     *
 * -----------------------------------------------------------------*/

/*------------------------------------------------------------------*
 * PROTOTIPOS DA IMPLEMENTACAO DAS FUNCOES VIRTUAIS                 *
 * note o "_" (underline) no final dos nomes das funções            *
 * Trata-se de uma convenção que usamos para nos lembrar que estas  *
 * funções são "static". Isto é: são declaradas e definidas pelo    *
 * compilador de tal forma que são reconhecidas apenas aqui dentro  *
 * deste arquivo  ____.c --> _______.o                              *
 * Estas funções não podem ser chamadas PELO NOME para serem        *
 * executadas por outros trechos de código em outros arquivos .c    *
 * Todavia, podem ser chamadas para serem executadas através de seus*
 * ENDEREÇOS. E são os endereços destas funções que são atribuídos  *
 * às respectivas posições da tabela vtbl que é apontada pelo campo *
 * super. O campo super a que se refere aqui é o PRIMEIRO campo da  *
 *                                                                  *
 * -----------------------------------------------------------------*/
static Numero_pt Rac_copia_(Numero_t const *const me);
static Numero_pt Rac_atribui_(Numero_t const *const me,Numero_t *const outro);
static Numero_pt Rac_soma_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res);
static Numero_pt Rac_subt_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res);
static Numero_pt Rac_mult_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res);
static Numero_pt Rac_divd_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res);
static Numero_pt Rac_ac_soma_(Numero_t *const me, Numero_t const *const outro);
static Numero_pt Rac_ac_subt_(Numero_t *const me, Numero_t const *const outro);
static Numero_pt Rac_ac_mult_(Numero_t *const me, Numero_t const *const outro);
static Numero_pt Rac_ac_divd_(Numero_t *const me, Numero_t const *const outro);
static int Rac_compara_(Numero_t const *const me, Numero_t const *const outro);
static char *Rac_imprime_(Numero_t const *const me);
static void Rac_destroi_(Numero_t *me);

/*-----------------------------------------------------------------------*
 * IMPLEMENTAÇÃO DA INTERFACE PÚBLICA das funções virtuais de MeuRacional*
 * ----------------------------------------------------------------------*/
static MeuRacional_pt Copia_(MeuRacional_t const *const me);
static MeuRacional_pt Atribui_(MeuRacional_t const *const me, MeuRacional_t *const outro);
static MeuRacional_pt Soma_(MeuRacional_t const *const me, MeuRacional_t const *const outro, MeuRacional_t *const res);
static MeuRacional_pt Subt_(MeuRacional_t const *const me, MeuRacional_t const *const outro, MeuRacional_t *const res);
static MeuRacional_pt Mult_(MeuRacional_t const *const me, MeuRacional_t const *const outro, MeuRacional_t *const res);
static MeuRacional_pt Divd_(MeuRacional_t const *const me, MeuRacional_t const *const outro, MeuRacional_t *const res);
static MeuRacional_pt Ac_Soma_(MeuRacional_t *const me, MeuRacional_t const *const outro);
static MeuRacional_pt Ac_Subt_(MeuRacional_t *const me, MeuRacional_t const *const outro);
static MeuRacional_pt Ac_Mult_(MeuRacional_t *const me, MeuRacional_t const *const outro);
static MeuRacional_pt Ac_Divd_(MeuRacional_t *const me, MeuRacional_t const *const outro);
static int Compara_(MeuRacional_t const *const me, MeuRacional_t const *const outro);
static char *Imprime_(MeuRacional_t const *const me);
static void Destroi_(MeuRacional_t *me);

/* protótipos das funçoes get e set */
static void Get_(MeuRacional_t const *const me, long int *num, long int *den);
static void Set_(MeuRacional_t *const me, long int num, long int den);

static long int Get_Num_(MeuRacional_t const *const me);
static long int Get_Den_(MeuRacional_t const *const me);
static void Set_Num_(MeuRacional_t *const me, long int num);
static void Set_Den_(MeuRacional_t *const me, long int den);

static long double Modulo_(MeuRacional_t const *const me);

void reduz_racional_euclides(MeuRacional_pt input, MeuRacional_pt output) {
	int sinal;

	if ((input->valores[0] * input->valores[1]) < 0) sinal = -1;
	else sinal = +1;

	long int a, b, rem;

	if (input->valores[0] > input->valores[1]) {
		a = labs(input->valores[0]);
		b = labs(input->valores[1]);
	} else {
		a = labs(input->valores[1]);
		b = labs(input->valores[0]);
	}

	while (b > 0) {
		rem = b;
		b = a % b;
		a = rem;
	}
	
	if (labs(input->valores[0]) == labs(input->valores[1])) {
		output->valores[0] = 1;
		output->valores[1] = 1;
	} else {
		output->valores[0] = labs(input->valores[0]) / a * sinal;
		output->valores[1] = labs(input->valores[1]) / a;
	}
}

/*---------------------------------------------*
 * implementação do construtor                 *
 * --------------------------------------------*/

MeuRacional_pt Rac_constroi(MeuRacional_pt me, long int num, long int den) {
	/* tabela de funções virtuais da classe Numero_t 								*
	 * Esta tabela estática será compartilhada por todos os números *
	 * da classe MeuRacional_t                                      */

	static struct NumeroVtbl const vtbl = {
		&Rac_copia_,
		&Rac_atribui_,
		&Rac_soma_,
		&Rac_subt_,
		&Rac_mult_,
		&Rac_divd_,
		&Rac_ac_soma_,
		&Rac_ac_subt_,
		&Rac_ac_mult_,
		&Rac_ac_divd_,
		&Rac_compara_,
		&Rac_imprime_,
		&Rac_destroi_
	};

	// me = (MeuRacional_pt)Num_constroi((Numero_pt)me);
	me = (MeuRacional_t*) malloc (sizeof(MeuRacional_t));

	/* constroi o Numero_t  */
	/* no início de MeuRacional_t  */

	me->super.metodo = &vtbl;
	/* metodo aponta para vtbl de MeuRacional_t 			*/
	/* as operações do "numero", a partir de agora,   */
	/* são as operações sobre racional                */

	/* Agora, mais uma tabela estática a ser compartilhada pelos     *
	 * "MeuRacional_t": a tabela de interface                        *
	 * note que a estrutura Interface incorpora os métodos Get e Set */
	static struct MeuRacional_interface_st const interface = {
			&Copia_,
			&Atribui_,
			&Soma_,
			&Subt_,
			&Mult_,
			&Divd_,
			&Ac_Soma_,
			&Ac_Subt_,
			&Ac_Mult_,
			&Ac_Divd_,
			&Compara_,
			&Imprime_,
			&Destroi_,
			&Get_,
			&Set_,
			&Get_Num_,
			&Get_Den_,
			&Set_Num_,
			&Set_Den_,
			&Modulo_
	};

	me->Metodo = &interface;
	/* metodo aponta para vtbl de MeuRacional_t 				*/
	/* as operações do "numero", a partir de agora,     */
	/* são as operações sobre Racional	                */

	/* aloca dinamicamente uma area de memoria para um Racional		*/
	/* e atribui o endereço de memória alocada para o ponteiro 		*/
	/* valor que está dentro da estrutura MeuRacional_st         	*/
	me->valores = (long int *)malloc(2 * sizeof(long int));
	if (me->valores == NULL)
	{
		/*erro!!! não conseguiu alocar */
		printf("Erro na alocação de memória em Num_Constroi");
		printf("Nao alocou os valores long int");
		exit(1);
	}

	/* copia os long int passados como parâmetro */
	/* no endereco de memoria recém alocado  */
	me->valores[0] = num;
	me->valores[1] = den;

	return (me);
}





/*---------------------------------------------*
 * implementação do set e get                   *
 * ---------------------------------------------*/

/* O "static" define que a função só é conhecida pelo compilador C
	dentro do arquivo em que a função está (escopo de arquivo) */
/* O "inline" substitui a chamda de todas as linhas da função
	por apenas essa linha */

static inline void Get_(MeuRacional_t const *const me, long int *num, long int *den) {
	*num = (me->valores[0]);
	*den = (me->valores[1]);
}

static inline void Set_(MeuRacional_t *const me, long int num, long int den) {
	me->valores[0] = num;
	me->valores[1] = den;
}

static inline long int Get_Num_(MeuRacional_t const *const me){ return ((me->valores[0])); }
static inline long int Get_Den_(MeuRacional_t const *const me){ return ((me->valores[1])); }

static inline void Set_Num_(MeuRacional_t *const me, long int num) { me->valores[0] = num; }
static inline void Set_Den_(MeuRacional_t *const me, long int den) { me->valores[1] = den; }

static long double Modulo_(MeuRacional_t const *const me){
	return ((long double)Get_Num_(me) / (long double)Get_Den_(me));
}









/*------------------------------------------------------*
 * IMPLEMENTAÇÃO DAS FUNÇÕES VIRTUAIS         				  *
 * -----------------------------------------------------*/



static inline MeuRacional_pt Copia_(MeuRacional_t const *const me){
	return ((MeuRacional_pt) Rac_copia_((Numero_pt)me));
}
static Numero_pt Rac_copia_(Numero_t const *const me) {
	assert(me != NULL);
	Numero_pt outro = NULL;
	outro = (Numero_pt)Rac_constroi((MeuRacional_pt)outro, Get_Num_((MeuRacional_pt)me), Get_Den_((MeuRacional_pt)me));
	return outro;
}

/*-----------------------------------------------------------------*/
static inline MeuRacional_pt Atribui_(MeuRacional_t const *const me, MeuRacional_t *const outro){
	return ((MeuRacional_pt) Rac_atribui_((Numero_pt)me, (Numero_pt)outro));
}
static Numero_pt Rac_atribui_(Numero_t const *const me, Numero_t *const outro) {
	Set_Num_((MeuRacional_pt)outro, Get_Num_((MeuRacional_pt)me));
	Set_Den_((MeuRacional_pt)outro, Get_Den_((MeuRacional_pt)me));
	return (Numero_pt)outro;
}

/*-----------------------------------------------------------------*/
static inline MeuRacional_pt Soma_(MeuRacional_t const *const me, MeuRacional_t const *const outro, MeuRacional_t *const res) {
	return ((MeuRacional_pt) Rac_soma_((Numero_pt)me, (Numero_pt)outro, (Numero_pt)res));
}
static Numero_pt Rac_soma_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res) {
	MeuRacional_t * temp;
	temp = Copia_((MeuRacional_pt)me);
	Set_Den_(temp, Get_Den_((MeuRacional_pt)me) * Get_Den_((MeuRacional_pt)outro));
	Set_Num_(temp, Get_Num_((MeuRacional_pt)me) * Get_Den_((MeuRacional_pt)outro) + Get_Num_((MeuRacional_pt)outro) * Get_Den_((MeuRacional_pt)me));

	reduz_racional_euclides(temp, (MeuRacional_pt)res);

	if (Get_Den_((MeuRacional_pt)res) < 0) {
		Set_Den_((MeuRacional_pt)res, -Get_Den_((MeuRacional_pt)res));
		Set_Num_((MeuRacional_pt)res, -Get_Num_((MeuRacional_pt)res));
	}

	Destroi_(temp);

	return (Numero_pt)res;
}

/*-----------------------------------------------------------------*/
static inline MeuRacional_pt Subt_(MeuRacional_t const *const me, MeuRacional_t const *const outro, MeuRacional_t *const res) {
	return ((MeuRacional_pt) Rac_subt_((Numero_pt)me, (Numero_pt)outro, (Numero_pt)res));
}
static Numero_pt Rac_subt_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res) {
	MeuRacional_t * temp;
	temp = Copia_((MeuRacional_pt)me);

	Set_Den_(temp, Get_Den_((MeuRacional_pt)me) * Get_Den_((MeuRacional_pt)outro));
	Set_Num_(temp, Get_Num_((MeuRacional_pt)me) * Get_Den_((MeuRacional_pt)outro) - Get_Num_((MeuRacional_pt)outro) * Get_Den_((MeuRacional_pt)me));
	
	reduz_racional_euclides(temp, (MeuRacional_pt)res);

	if (Get_Den_((MeuRacional_pt)res) < 0) {
		Set_Den_((MeuRacional_pt)res, -Get_Den_((MeuRacional_pt)res));
		Set_Num_((MeuRacional_pt)res, -Get_Num_((MeuRacional_pt)res));
	}

	Destroi_(temp);

	return (Numero_pt)res;
}

/*-----------------------------------------------------------------*/
static inline MeuRacional_pt Mult_(MeuRacional_t const *const me, MeuRacional_t const *const outro, MeuRacional_t *const res) {
	return ((MeuRacional_pt) Rac_mult_((Numero_pt)me, (Numero_pt)outro, (Numero_pt)res));
}
static Numero_pt Rac_mult_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res) {
	MeuRacional_t * temp;
	temp = Copia_((MeuRacional_pt)me);

	Set_Den_(temp,
					 Get_Den_((MeuRacional_pt)me) * Get_Den_((MeuRacional_pt)outro));

	Set_Num_(temp,
					 Get_Num_((MeuRacional_pt)me) * Get_Num_((MeuRacional_pt)outro));

	reduz_racional_euclides(temp, (MeuRacional_pt)res);

	if (Get_Den_((MeuRacional_pt)res) < 0)
	{
		Set_Den_((MeuRacional_pt)res, -Get_Den_((MeuRacional_pt)res));
		Set_Num_((MeuRacional_pt)res, -Get_Num_((MeuRacional_pt)res));
	}

	Destroi_(temp);

	return (Numero_pt)res;
}

/*-----------------------------------------------------------------*/
static inline MeuRacional_pt Divd_(MeuRacional_t const *const me, MeuRacional_t const *const outro, MeuRacional_t *const res) {
	return ((MeuRacional_pt) Rac_divd_((Numero_pt)me, (Numero_pt)outro, (Numero_pt)res));
}
static Numero_pt Rac_divd_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res) {
	MeuRacional_t * temp;
	temp = Copia_((MeuRacional_pt)me);

	Set_Den_(temp, Get_Den_((MeuRacional_pt)me) * Get_Num_((MeuRacional_pt)outro));
	Set_Num_(temp, Get_Num_((MeuRacional_pt)me) * Get_Den_((MeuRacional_pt)outro));

	reduz_racional_euclides(temp, (MeuRacional_pt)res);

	if (Get_Den_((MeuRacional_pt)res) < 0) {
		Set_Den_((MeuRacional_pt)res, -Get_Den_((MeuRacional_pt)res));
		Set_Num_((MeuRacional_pt)res, -Get_Num_((MeuRacional_pt)res));
	}

	Destroi_(temp);

	return (Numero_pt)res;
}

/*-----------------------------------------------------------------*/
static inline MeuRacional_pt Ac_Soma_(MeuRacional_t *const me, MeuRacional_t const *const outro) {
	return ((MeuRacional_pt) Rac_ac_soma_((Numero_pt)me, (Numero_pt)outro));
}
static Numero_pt Rac_ac_soma_(Numero_t *const me, Numero_t const *const outro) {
	MeuRacional_t * temp;
	temp = Copia_((MeuRacional_pt)me);

	Set_Den_(temp, Get_Den_((MeuRacional_pt)me) * Get_Den_((MeuRacional_pt)outro));
	Set_Num_(temp, Get_Num_((MeuRacional_pt)me) * Get_Den_((MeuRacional_pt)outro) + Get_Num_((MeuRacional_pt)outro) * Get_Den_((MeuRacional_pt)me));

	reduz_racional_euclides(temp, (MeuRacional_pt)me);

	if (Get_Den_((MeuRacional_pt)me) < 0) {
		Set_Den_((MeuRacional_pt)me, -Get_Den_((MeuRacional_pt)me));
		Set_Num_((MeuRacional_pt)me, -Get_Num_((MeuRacional_pt)me));
	}

	Destroi_(temp);

	return (Numero_pt)me;
}

/*-----------------------------------------------------------------*/
static inline MeuRacional_pt Ac_Subt_(MeuRacional_t *const me, MeuRacional_t const *const outro) {
	return ((MeuRacional_pt) Rac_ac_subt_((Numero_pt)me, (Numero_pt)outro));
}
static Numero_pt Rac_ac_subt_(Numero_t *const me, Numero_t const *const outro) {
	MeuRacional_t * temp;
	temp = Copia_((MeuRacional_pt)me);

	Set_Den_(temp, Get_Den_((MeuRacional_pt)me) * Get_Den_((MeuRacional_pt)outro));
	Set_Num_(temp, Get_Num_((MeuRacional_pt)me) * Get_Den_((MeuRacional_pt)outro) - Get_Num_((MeuRacional_pt)outro) * Get_Den_((MeuRacional_pt)me));

	reduz_racional_euclides(temp, (MeuRacional_pt)me);

	if (Get_Den_((MeuRacional_pt)me) < 0) {
		Set_Den_((MeuRacional_pt)me, -Get_Den_((MeuRacional_pt)me));
		Set_Num_((MeuRacional_pt)me, -Get_Num_((MeuRacional_pt)me));
	}

	Destroi_(temp);

	return (Numero_pt)me;
}

/*-----------------------------------------------------------------*/
static inline MeuRacional_pt Ac_Mult_(MeuRacional_t *const me, MeuRacional_t const *const outro) {
	return ((MeuRacional_pt) Rac_ac_mult_((Numero_pt)me, (Numero_pt)outro));
}
static Numero_pt Rac_ac_mult_(Numero_t *const me, Numero_t const *const outro) {
	MeuRacional_t * temp;
	temp = Copia_((MeuRacional_pt)me);

	Set_Den_(temp, Get_Den_((MeuRacional_pt)me) * Get_Den_((MeuRacional_pt)outro));
	Set_Num_(temp, Get_Num_((MeuRacional_pt)me) * Get_Num_((MeuRacional_pt)outro));

	reduz_racional_euclides(temp, (MeuRacional_pt)me);

	if (Get_Den_((MeuRacional_pt)me) < 0) {
		Set_Den_((MeuRacional_pt)me, -Get_Den_((MeuRacional_pt)me));
		Set_Num_((MeuRacional_pt)me, -Get_Num_((MeuRacional_pt)me));
	}

	Destroi_(temp);

	return (Numero_pt)me;
}

/*-----------------------------------------------------------------*/
static inline MeuRacional_pt Ac_Divd_(MeuRacional_t *const me, MeuRacional_t const *const outro) {
	return ((MeuRacional_pt) Rac_ac_divd_((Numero_pt)me, (Numero_pt)outro));
}
static Numero_pt Rac_ac_divd_(Numero_t *const me, Numero_t const *const outro) {
	MeuRacional_t * temp;
	temp = Copia_((MeuRacional_pt)me);

	Set_Den_(temp, Get_Den_((MeuRacional_pt)me) * Get_Num_((MeuRacional_pt)outro));
	Set_Num_(temp, Get_Num_((MeuRacional_pt)me) * Get_Den_((MeuRacional_pt)outro));

	reduz_racional_euclides(temp, (MeuRacional_pt)me);

	if (Get_Den_((MeuRacional_pt)me) < 0) {
		Set_Den_((MeuRacional_pt)me, -Get_Den_((MeuRacional_pt)me));
		Set_Num_((MeuRacional_pt)me, -Get_Num_((MeuRacional_pt)me));
	}

	Destroi_(temp);

	return (Numero_pt)me;
}

/*-----------------------------------------------------------------*/
static inline int Compara_(MeuRacional_t const *const me, MeuRacional_t const *const outro){
	return (Rac_compara_((Numero_pt)me, (Numero_pt)outro));
}
static int Rac_compara_(Numero_t const *const me, Numero_t const *const outro) {
	
	double result1 = ((MeuRacional_pt)me)->valores[0] / ((MeuRacional_pt)me)->valores[1];
	double result2 = ((MeuRacional_pt)outro)->valores[0] / ((MeuRacional_pt)outro)->valores[1];

	if (result1 == result2) {
		return 0;

	} else if (result1 > result2) {
		return 1;

	} else if (result1 < result2) {
		return -1;
	}
	
}

/*-----------------------------------------------------------------*/
static char * Imprime_(MeuRacional_t const *const me) {
	return (Rac_imprime_((Numero_pt)me));
}
static char * Rac_imprime_(Numero_t const *const me) {
	static char buffer[100];
	reduz_racional_euclides((MeuRacional_pt)me, (MeuRacional_pt)me);
	if (!Get_Num_((MeuRacional_pt)me)) sprintf(buffer, "0");
	else if (Get_Num_((MeuRacional_pt)me) == 1 && Get_Den_((MeuRacional_pt)me) == 1) sprintf(buffer, "1");
	else sprintf(buffer, "%ld / %ld", Get_Num_((MeuRacional_pt)me), Get_Den_((MeuRacional_pt)me));
	return buffer;
}

/*-------------------------------*
 * implementação do destrutor    *
/*-------------------------------*/
static inline void Destroi_(MeuRacional_t *me) {
	Rac_destroi_((Numero_t *)me);
}
static void Rac_destroi_(Numero_t *me) {
	// destruindo numerador e denominador
	if (((MeuRacional_pt)me)->valores!=NULL) free(((MeuRacional_pt)me)->valores);

	/*... e só agora destroi-se o número virtual da classe base */
	if (me!=NULL) free(me);
}

