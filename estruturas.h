//>>>>>>>>>>>>>>>>>>>>Pontos
typedef struct ponto_no * ponto_ponteiro;

typedef struct{
	char nome[10];
	float ponto[3];
}ponto_info;

typedef struct ponto_no{
	ponto_info info;
	ponto_ponteiro prox;
}ponto_no;
//<<<<<<<<<<<<<<<<<<<<Pontos

//>>>>>>>>>>>>>>>>>>>>Vetores
typedef struct vetor_no * vetor_ponteiro;

typedef struct{
	char nome[10];
	float vetor[3];
}vetor_info;

typedef struct vetor_no{
	vetor_info info;
	vetor_ponteiro prox;
}vetor_no;
//<<<<<<<<<<<<<<<<<<<<Vetores

//>>>>>>>>>>>>>>>>>>>>Retas
typedef struct reta_no * reta_ponteiro;

typedef struct{
	char nome[10];
	float ponto[3];
	float vetor[3];
}reta_info;

typedef struct reta_no{
	reta_info info;
	reta_ponteiro prox;
}reta_no;
//<<<<<<<<<<<<<<<<<<<<Retas

//>>>>>>>>>>>>>>>>>>>>Planos
typedef struct plano_no * plano_ponteiro;

typedef struct{
	char nome[10];
	float ponto[3];
	float vetor1[3];
	float vetor2[3];
}plano_info;

typedef struct plano_no{
	plano_info info;
	plano_ponteiro prox;
}plano_no;
//<<<<<<<<<<<<<<<<<<<<Planos

typedef struct{
	int ponto_qnt; //Quantidade de Pontos no Espa�o
	ponto_ponteiro ponto_prim; //Sess�o de Pontos
	int vetor_qnt; //Quantidade de Vetores no Espa�o
	vetor_ponteiro vetor_prim; //Sess�o de Vetores
	int reta_qnt; //Quantidade de Retas no Espa�o
	reta_ponteiro reta_prim; //Sess�o de Retas
	int plano_qnt; //Quantidade de Planos no Espa�o
	plano_ponteiro plano_prim; //Sess�o de Planos
}espaco;
