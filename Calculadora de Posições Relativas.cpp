#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<math.h>

using namespace std;

//#include"estruturas.h"
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


//#include"gerenciamento.h"
int criar_espaco(char nome[],espaco *e,FILE **arq){
	if((*arq = fopen(nome,"wb"))==NULL)
		return 0;
	e->ponto_qnt = 0;
	e->ponto_prim = NULL;
	e->vetor_qnt = 0;
	e->vetor_prim = NULL;
	e->reta_qnt = 0;
	e->reta_prim = NULL;
	e->plano_qnt = 0;
	e->plano_prim = NULL;
	return 1;
}

void criar_espaco_temp(espaco *e){
	e->ponto_qnt = 0;
	e->ponto_prim = NULL;
	e->vetor_qnt = 0;
	e->vetor_prim = NULL;
	e->reta_qnt = 0;
	e->reta_prim = NULL;
	e->plano_qnt = 0;
	e->plano_prim = NULL;
}

//>>>>>>>>>>>>>>>>>>>>Pontos
void ponto_novo(espaco *e,char nome[],float P[]){
	
	ponto_ponteiro novo = (ponto_ponteiro)malloc(sizeof(ponto_no));
	ponto_ponteiro copia = (ponto_ponteiro)malloc(sizeof(ponto_no));
   
	novo->prox = NULL;

	strcpy(novo->info.nome,nome);
	
    novo->info.ponto[0] = P[0];
    novo->info.ponto[1] = P[1];
    novo->info.ponto[2] = P[2];
    
    if(e->ponto_qnt == 0){
        e->ponto_prim = novo;
    }
    	else{
        	copia = e->ponto_prim;
        	while(copia->prox != NULL){
        		copia = copia->prox;
        	}
        	copia->prox = novo;
    	}
    e->ponto_qnt++;
}

ponto_ponteiro ponto_busca(espaco *e,char x[]){
	ponto_ponteiro copia = (ponto_ponteiro)malloc(sizeof(ponto_no));

	copia = e->ponto_prim;

	if(copia == NULL)
    	return NULL;

	while(strcmp(copia->info.nome,x) != 0 && copia->prox != NULL)
    	copia = copia->prox;

	if(strcmp(copia->info.nome,x) == 0)
    	return copia;
		else
    		return NULL;
}

int ponto_remover(espaco *e,char x[10]){
	ponto_ponteiro antes = (ponto_ponteiro)malloc(sizeof(ponto_no));
	ponto_ponteiro copia = (ponto_ponteiro)malloc(sizeof(ponto_no));

	antes = NULL;
	copia = e->ponto_prim;

	if(e->ponto_qnt == 0)
    	return 0;

	if(e->ponto_qnt == 1 && strcmp(e->ponto_prim->info.nome,x) == 0){
        copia = e->ponto_prim;
        e->ponto_prim = copia->prox;
        free(copia);
        e->ponto_qnt--;
        return 1;
    }

	if(strcmp(copia->info.nome,x) == 0){
		e->ponto_prim=copia->prox;
		free(copia);
		e->ponto_qnt--;
		return 1;
	}

	while(copia->prox != NULL && copia->info.nome != x){
    	antes = copia;
    	copia = copia->prox;
	}

   	if(copia->prox == NULL && copia->info.nome != x)
    	return 0;

	antes->prox = copia->prox;
   	free(copia);
   	e->ponto_qnt--;
   	return 1;
}

void ponto_imprimir(espaco *e){

	if(e->ponto_qnt == 1)
    	cout << "H� " << e->ponto_qnt << " Ponto.\n";
    	else
        	cout << "H� " << e->ponto_qnt << " Pontos.\n";

	if(e->ponto_qnt != 0){
    	ponto_ponteiro copia = (ponto_ponteiro)malloc(sizeof(ponto_no));

    	copia = e->ponto_prim;

    	if(e->ponto_qnt == 1)
        	cout << "O Ponto �:\n\n";
        	else
        		cout << "Os Pontos s�o:\n\n";
    	while(copia != NULL){
    		printf("%s = ",copia->info.nome);
            cout << "(" << copia->info.ponto[0] << "," << copia->info.ponto[1] << "," << copia->info.ponto[2] << ")" << endl;
            copia = copia -> prox;
    	}
	}
}

void ponto_destruir(espaco *e){
	ponto_ponteiro copia = (ponto_ponteiro)malloc(sizeof(ponto_no));
	ponto_ponteiro antes = (ponto_ponteiro)malloc(sizeof(ponto_no));

	copia = e->ponto_prim;
	while(copia != NULL){
    	antes = copia;
    	copia = copia->prox;
    	free(antes);
	}
	e->ponto_prim = NULL;
	e->ponto_qnt = 0;
}
//<<<<<<<<<<<<<<<<<<<<Pontos

//>>>>>>>>>>>>>>>>>>>>Vetores
void vetor_novo(espaco *e,char nome[],float V[]){
	
	vetor_ponteiro novo = (vetor_ponteiro)malloc(sizeof(vetor_no));
	vetor_ponteiro copia = (vetor_ponteiro)malloc(sizeof(vetor_no));
   
	novo->prox = NULL;

	strcpy(novo->info.nome,nome);
	
    novo->info.vetor[0] = V[0];
    novo->info.vetor[1] = V[1];
    novo->info.vetor[2] = V[2];
    
    if(e->vetor_qnt == 0){
        e->vetor_prim = novo;
    }
    	else{
        	copia = e->vetor_prim;
        	while(copia->prox != NULL){
        		copia = copia->prox;
        	}
        	copia->prox = novo;
    	}
    e->vetor_qnt++;
}

int vetor_novo2pon(espaco *e,char p1[],char p2[],char nome[]){
	vetor_ponteiro novo = (vetor_ponteiro)malloc(sizeof(vetor_no));
	vetor_ponteiro copia = (vetor_ponteiro)malloc(sizeof(vetor_no));
	ponto_ponteiro a = (ponto_ponteiro)malloc(sizeof(ponto_no));
	ponto_ponteiro b = (ponto_ponteiro)malloc(sizeof(ponto_no));

	a = ponto_busca(e,p1);
	b = ponto_busca(e,p2);
	
	if(a == NULL || b == NULL)
		return 0;
	
	strcpy(novo->info.nome,nome);
	novo->prox = NULL;
	
    novo->info.vetor[0] = b->info.ponto[0]-a->info.ponto[0];
    novo->info.vetor[1] = b->info.ponto[1]-a->info.ponto[1];
    novo->info.vetor[2] = b->info.ponto[2]-a->info.ponto[2];

    if(e->vetor_qnt == 0){
        e->vetor_prim = novo;
    }
    	else{
		   	copia = e->vetor_prim;
        	while(copia->prox != NULL){
        		copia = copia->prox;
        	}
        	copia->prox = novo;
    	}
    e->vetor_qnt++;
    return 1;
}

vetor_ponteiro vetor_busca(espaco *e, char x[]){
	vetor_ponteiro copia = (vetor_ponteiro)malloc(sizeof(vetor_no));

	copia = e->vetor_prim;

	if(copia == NULL)
    	return NULL;

	while(strcmp(copia->info.nome,x) != 0 && copia->prox != NULL)
    	copia = copia->prox;

	if(strcmp(copia->info.nome,x) == 0)
    	return copia;
		else
    		return NULL;
}

int vetor_remover(espaco *e, char x[]){
	vetor_ponteiro antes = (vetor_ponteiro)malloc(sizeof(vetor_no));
	vetor_ponteiro copia = (vetor_ponteiro)malloc(sizeof(vetor_no));

	antes = NULL;
	copia = e->vetor_prim;

	if(e->vetor_qnt == 0)
    	return 0;

	if(e->vetor_qnt == 1 && strcmp(e->vetor_prim->info.nome,x) == 0){
        copia = e->vetor_prim;
        e->vetor_prim = copia->prox;
        free(copia);
        e->vetor_qnt--;
        return 1;
    }

	if(strcmp(copia->info.nome,x) == 0){
		e->vetor_prim=copia->prox;
		free(copia);
		e->vetor_qnt--;
		return 1;
	}

	while(copia->prox != NULL && strcmp(copia->info.nome,x) != 0){
    	antes = copia;
    	copia = copia->prox;
	}

   	if(copia->prox == NULL && strcmp(copia->info.nome,x) != 0)
    	return 0;

	antes->prox = copia->prox;
   	free(copia);
   	e->vetor_qnt--;
   	return 1;
}

void vetor_imprimir(espaco *e){

	if(e->vetor_qnt == 1)
    	cout << "H� " << e->vetor_qnt << " Vetor.\n";
    	else
        	cout << "H� " << e->vetor_qnt << " Vetores.\n";

	if(e->vetor_qnt != 0){
    	vetor_ponteiro copia = (vetor_ponteiro)malloc(sizeof(vetor_no));

    	copia = e->vetor_prim;

    	if(e->vetor_qnt == 1)
        	cout << "O Vetor �:\n\n";
        	else
        		cout << "Os Vetores s�o:\n\n";
    	while(copia != NULL){
    		printf("%s = ",copia->info.nome);
            cout << "(" << copia->info.vetor[0] << "," << copia->info.vetor[1] << "," << copia->info.vetor[2] << ")" << endl;
            copia = copia -> prox;
    	}
	}
}

void vetor_destruir(espaco *e){
	vetor_ponteiro copia = (vetor_ponteiro)malloc(sizeof(vetor_no));
	vetor_ponteiro antes = (vetor_ponteiro)malloc(sizeof(vetor_no));

	copia = e->vetor_prim;
	while(copia != NULL){
    	antes = copia;
    	copia = copia->prox;
    	free(antes);
	}
	e->vetor_prim = NULL;
	e->vetor_qnt = 0;
}
//<<<<<<<<<<<<<<<<<<<<Vetores

//>>>>>>>>>>>>>>>>>>>>Retas
void reta_novo(espaco *e,char nome[],float P[],float V[]){
	
	reta_ponteiro novo = (reta_ponteiro)malloc(sizeof(reta_no));
	reta_ponteiro copia = (reta_ponteiro)malloc(sizeof(reta_no));
   
	novo->prox = NULL;

	strcpy(novo->info.nome,nome);
	
	novo->info.ponto[0] = P[0];
	novo->info.ponto[1] = P[1];
	novo->info.ponto[2] = P[2];

    novo->info.vetor[0] = V[0];
    novo->info.vetor[1] = V[1];
    novo->info.vetor[2] = V[2];
    
    if(e->reta_qnt == 0){
        e->reta_prim = novo;
    }
    	else{
        	copia = e->reta_prim;
        	while(copia->prox != NULL){
        		copia = copia->prox;
        	}
        	copia->prox = novo;
    	}
    e->reta_qnt++;
}

reta_ponteiro reta_busca(espaco *e, char x[]){
	reta_ponteiro copia = (reta_ponteiro)malloc(sizeof(reta_no));

	copia = e->reta_prim;

	if(copia == NULL)
    	return NULL;

	while(strcmp(copia->info.nome,x) != 0 && copia->prox != NULL)
    	copia = copia->prox;

	if(strcmp(copia->info.nome,x) == 0)
    	return copia;
		else
    		return NULL;
}

int reta_remover(espaco *e, char x[]){
	reta_ponteiro antes = (reta_ponteiro)malloc(sizeof(reta_no));
	reta_ponteiro copia = (reta_ponteiro)malloc(sizeof(reta_no));

	antes = NULL;
	copia = e->reta_prim;

	if(e->reta_qnt == 0)
    	return 0;

	if(e->reta_qnt == 1 && strcmp(e->reta_prim->info.nome,x) == 0){
        copia = e->reta_prim;
        e->reta_prim = copia->prox;
        free(copia);
        e->reta_qnt--;
        return 1;
    }

	if(strcmp(copia->info.nome,x) == 0){
		e->reta_prim=copia->prox;
		free(copia);
		e->reta_qnt--;
		return 1;
	}

	while(copia->prox != NULL && strcmp(copia->info.nome,x) != 0){
    	antes = copia;
    	copia = copia->prox;
	}

   	if(copia->prox == NULL && strcmp(copia->info.nome,x) != 0)
    	return 0;

	antes->prox = copia->prox;
   	free(copia);
   	e->reta_qnt--;
   	return 1;
}

void reta_imprimir(espaco *e){

	if(e->reta_qnt == 1)
    	cout << "H� " << e->reta_qnt << " Reta.\n";
    	else
        	cout << "H� " << e->reta_qnt << " Retas.\n";

	if(e->reta_qnt != 0){
    	reta_ponteiro copia = (reta_ponteiro)malloc(sizeof(reta_no));

    	copia = e->reta_prim;

    	if(e->reta_qnt == 1)
        	cout << "A Reta �:\n\n";
        	else
        		cout << "As Retas s�o:\n\n";
    	while(copia != NULL){
    		printf("%s: ",copia->info.nome);
    		cout << "X = (" << copia->info.ponto[0] << "," << copia->info.ponto[1] << "," << copia->info.ponto[2] << ") + ";
			cout << "a(" << copia->info.vetor[0] << "," << copia->info.vetor[1] << ","  << copia->info.vetor[2] << ")\n";
            copia = copia -> prox;
    	}
	}
}

void reta_destruir(espaco *e){
	reta_ponteiro copia = (reta_ponteiro)malloc(sizeof(reta_no));
	reta_ponteiro antes = (reta_ponteiro)malloc(sizeof(reta_no));

	copia = e->reta_prim;
	while(copia != NULL){
    	antes = copia;
    	copia = copia->prox;
    	free(antes);
	}
	e->reta_prim = NULL;
	e->reta_qnt = 0;
}
//<<<<<<<<<<<<<<<<<<<<Retas

//>>>>>>>>>>>>>>>>>>>>Planos
void plano_novo(espaco *e,char nome[],float P[],float V1[],float V2[]){
	
	plano_ponteiro novo = (plano_ponteiro)malloc(sizeof(plano_no));
	plano_ponteiro copia = (plano_ponteiro)malloc(sizeof(plano_no));
   
	novo->prox = NULL;

	strcpy(novo->info.nome,nome);
	
	novo->info.ponto[0] = P[0];
    novo->info.ponto[1] = P[1];
    novo->info.ponto[2] = P[2];
	
	novo->info.vetor1[0] = V1[0];
    novo->info.vetor1[1] = V1[1];
    novo->info.vetor1[2] = V1[2];
	
    novo->info.vetor2[0] = V2[0];
    novo->info.vetor2[1] = V2[1];
    novo->info.vetor2[2] = V2[2];
    
    if(e->plano_qnt == 0){
        e->plano_prim = novo;
    }
    	else{
        	copia = e->plano_prim;
        	while(copia->prox != NULL){
        		copia = copia->prox;
        	}
        	copia->prox = novo;
    	}
    e->plano_qnt++;
}

plano_ponteiro plano_busca(espaco *e, char x[]){
	plano_ponteiro copia = (plano_ponteiro)malloc(sizeof(plano_no));

	copia = e->plano_prim;

	if(copia == NULL)
    	return NULL;

	while(strcmp(copia->info.nome,x) != 0 && copia->prox != NULL)
    	copia = copia->prox;

	if(strcmp(copia->info.nome,x) == 0)
    	return copia;
		else
    		return NULL;
}

int plano_remover(espaco *e, char x[]){
	plano_ponteiro antes = (plano_ponteiro)malloc(sizeof(plano_no));
	plano_ponteiro copia = (plano_ponteiro)malloc(sizeof(plano_no));

	antes = NULL;
	copia = e->plano_prim;

	if(e->plano_qnt == 0)
    	return 0;

	if(e->plano_qnt == 1 && strcmp(e->plano_prim->info.nome,x) == 0){
        copia = e->plano_prim;
        e->plano_prim = copia->prox;
        free(copia);
        e->plano_qnt--;
        return 1;
    }

	if(strcmp(copia->info.nome,x) == 0){
		e->plano_prim=copia->prox;
		free(copia);
		e->plano_qnt--;
		return 1;
	}

	while(copia->prox != NULL && strcmp(copia->info.nome,x) != 0){
    	antes = copia;
    	copia = copia->prox;
	}

   	if(copia->prox == NULL && strcmp(copia->info.nome,x) != 0)
    	return 0;

	antes->prox = copia->prox;
   	free(copia);
   	e->plano_qnt--;
   	return 1;
}

void plano_imprimir(espaco *e){

	if(e->plano_qnt == 1)
    	cout << "H� " << e->plano_qnt << " Plano.\n";
    	else
        	cout << "H� " << e->plano_qnt << " Planos.\n";

	if(e->plano_qnt != 0){
    	plano_ponteiro copia = (plano_ponteiro)malloc(sizeof(plano_no));

    	copia = e->plano_prim;

    	if(e->plano_qnt == 1)
        	cout << "O Plano �:\n\n";
        	else
        		cout << "Os Planos s�o:\n\n";
    	while(copia != NULL){
    		printf("%s: ",copia->info.nome);
    		cout << "X = (" << copia->info.ponto[0] << "," << copia->info.ponto[1] << "," << copia->info.ponto[2] << ") + ";
			cout << "a(" << copia->info.vetor1[0] << "," << copia->info.vetor1[1] << ","  << copia->info.vetor1[2] << ") + ";
			cout << "�(" << copia->info.vetor2[0] << "," << copia->info.vetor2[1] << "," << copia->info.vetor2[2] << ")\n";
            copia = copia -> prox;
    	}
	}
}

void plano_destruir(espaco *e){
	plano_ponteiro copia = (plano_ponteiro)malloc(sizeof(plano_no));
	plano_ponteiro antes = (plano_ponteiro)malloc(sizeof(plano_no));

	copia = e->plano_prim;
	while(copia != NULL){
    	antes = copia;
    	copia = copia->prox;
    	free(antes);
	}
	e->plano_prim = NULL;
	e->plano_qnt = 0;
}
//<<<<<<<<<<<<<<<<<<<<Planos

void imprimir_espaco(espaco *e){
	system("cls");
	printf("===============Pontos===============\n");
	ponto_imprimir(e);
	printf("\n===============Vetores===============\n");
	vetor_imprimir(e);
	printf("\n===============Retas===============\n");
	reta_imprimir(e);
	printf("\n===============Planos===============\n");
	plano_imprimir(e);
}

void destruir_espaco(espaco *e){
	ponto_destruir(e);
	vetor_destruir(e);
	reta_destruir(e);
	plano_destruir(e);
}


//#include"calculadora.h"
//>>>>>>>>>>>>>>>>>>>>Pontos

float ponto_distancia(espaco *e,char x[],char y[]){
	ponto_ponteiro a = (ponto_ponteiro)malloc(sizeof(ponto_no));
	ponto_ponteiro b = (ponto_ponteiro)malloc(sizeof(ponto_no));
	float r;
	
	a = ponto_busca(e,x);
	b = ponto_busca(e,y);
	if(a == NULL || b == NULL)
		return 0;
	else{
		r = pow(b->info.ponto[0]-a->info.ponto[0],2)+pow(b->info.ponto[1]-a->info.ponto[1],2)+pow(b->info.ponto[2]-a->info.ponto[2],2);
		r = sqrt(r);
		return r;
	}
}

//<<<<<<<<<<<<<<<<<<<<Pontos

//>>>>>>>>>>>>>>>>>>>>Vetores
int vetor_linearidade_2vet(float a[],float b[]){
		
	float det1,det2,det3;
	
	det1 = (a[0] * b[1]) - (a[1] * b[0]);
	det2 = (a[0] * b[2]) - (a[2] * b[0]);
	det3 = (a[1] * b[2]) - (a[2] * b[1]);

	if(det1 == 0 && det2 == 0 && det3 == 0){
		return 1;
	}
	else
		return 2;

	return 0;
}

int vetor_linearidade_3vet(float a[],float b[],float c[]){
		
	float det;
	
	det = a[0] * b[1] * c[2] + a[1] * b[2] * c[0] + a[2] * b[0] * c[1];
	det = det - (a[2] * b[1] * c[0] + a[1] * b[0] * c[2] + a[0] * b[2] * c[1]);
	if(det == 0){
		return 1;
	}
	else
		return 2;

	return 0;
}

int vetor_linearidade(espaco *e,int qnt,char vet1[],char vet2[],char vet3[]){
	vetor_ponteiro a = (vetor_ponteiro)malloc(sizeof(vetor_no));
	vetor_ponteiro b = (vetor_ponteiro)malloc(sizeof(vetor_no));
	vetor_ponteiro c = (vetor_ponteiro)malloc(sizeof(vetor_no));
	
	a = vetor_busca(e,vet1);
	b = vetor_busca(e,vet2);
	c = vetor_busca(e,vet3);
	
	if(qnt==2){
		if(a == NULL || b == NULL)
			return 0;
		return vetor_linearidade_2vet(a->info.vetor,b->info.vetor);
	}
	if(qnt==3){
		if(a == NULL || b == NULL || c == NULL)
			return 0;
		return vetor_linearidade_3vet(a->info.vetor,b->info.vetor,c->info.vetor);
	}
	return 0;
}
//<<<<<<<<<<<<<<<<<<<<Vetores

//>>>>>>>>>>>>>>>>>>>>Retas
int reta_relatividade_calc(reta_ponteiro r,reta_ponteiro s){ //1 - Reversos, 2 - Paralelos, 3 - Concorrentes, 4 - Coincidentes
	float vet1[3],vet2[3],P1[3],P2[3];
	float vet3[3];
	
	for(int i=0;i<3;i++){
		P1[i] = r->info.ponto[i];
		P2[i] = s->info.ponto[i];
		vet1[i] = r->info.vetor[i];
		vet2[i] = s->info.vetor[i];
		vet3[i] = vet2[i] - vet1[i];
	}

	int a = vetor_linearidade_3vet(vet1,vet2,vet3);
	int b = vetor_linearidade_2vet(vet1,vet2);
	
	if(a==2)
		return 1;
	else if(a==1){
		if(b==1){
			float x1,x2,x3;
			x1 = (P2[0] - P1[0])/vet2[0];
			x2 = (P2[1] - P1[1])/vet2[1];
			x3 = (P2[2] - P1[2])/vet2[2];
			if(x1 == x2 && x1 == x3 && x2 == x3)
				return 4;
			return 2;
		}
		else if(b==2)
			return 3;
	}
	else 
		return 0;
}

int reta_relatividade(espaco *e,char x[],char y[]){
	reta_ponteiro r = (reta_ponteiro)malloc(sizeof(reta_no));
	reta_ponteiro s = (reta_ponteiro)malloc(sizeof(reta_no));
	
	r = reta_busca(e,x);
	s = reta_busca(e,y);
	
	if(r == NULL || s == NULL)
		return 0;
	else
		return reta_relatividade_calc(r,s);
}

float reta_distancia_calc(reta_ponteiro r,reta_ponteiro s){
	float v[3],res[3],a,b;
	int rel;
	
	rel = reta_relatividade_calc(r,s);
	
	if(rel == 3 || rel == 4)
		return 0;
	
	for(int i=0;i<3;i++)
		v[i] = s->info.ponto[i] - r->info.ponto[i];

	res[0] = v[1] * s->info.vetor[2] - (v[2] * s->info.vetor[1]);
	res[1] = v[2] * s->info.vetor[0] - (v[0] * s->info.vetor[2]);
	res[2] = v[0] * s->info.vetor[1] - (v[1] * s->info.vetor[0]);
	a=sqrt(pow(res[0],2)+pow(res[1],2)+pow(res[2],2));
	b=sqrt(pow(s->info.vetor[0],2)+pow(s->info.vetor[1],2)+pow(s->info.vetor[2],2));
	
	return a/b;
}

float reta_distancia(espaco *e,char x[],char y[]){
	reta_ponteiro r = (reta_ponteiro)malloc(sizeof(reta_no));
	reta_ponteiro s = (reta_ponteiro)malloc(sizeof(reta_no));
	
	r = reta_busca(e,x);
	s = reta_busca(e,y);
	
	if(r == NULL || s == NULL)
		return 0;
	
	return reta_distancia_calc(r,s);
}
//<<<<<<<<<<<<<<<<<<<<Retas

//>>>>>>>>>>>>>>>>>>>>Planos
int plano_relatividade_calc(plano_ponteiro x,plano_ponteiro y){ //1 - Paralelos, 2 - Concorrentes
	float n1[3],n2[3];
	
	n1[0] = x->info.vetor1[1] * x->info.vetor2[2] - (x->info.vetor1[2] * x->info.vetor2[1]);
	n1[1] = x->info.vetor1[2] * x->info.vetor2[0] - (x->info.vetor1[0] * x->info.vetor2[2]);
	n1[2] = x->info.vetor1[0] * x->info.vetor2[1] - (x->info.vetor1[1] * x->info.vetor2[0]);
	
	n2[0] = y->info.vetor1[1] * y->info.vetor2[2] - (y->info.vetor1[2] * y->info.vetor2[1]);
	n2[1] = y->info.vetor1[2] * y->info.vetor2[0] - (y->info.vetor1[0] * y->info.vetor2[2]);
	n2[2] = y->info.vetor1[0] * y->info.vetor2[1] - (y->info.vetor1[1] * y->info.vetor2[0]);

	int a = vetor_linearidade_2vet(n1,n2);

	if(a==1)
		return 1;
	else
		return 2;	
}

int plano_relatividade(espaco *e,char x[],char y[]){
	plano_ponteiro plano1 = (plano_ponteiro)malloc(sizeof(plano_no));
	plano_ponteiro plano2 = (plano_ponteiro)malloc(sizeof(plano_no));
	
	plano1 = plano_busca(e,x);
	plano2 = plano_busca(e,y);
	
	if(plano1 == NULL || plano2 == NULL)
		return 0;
	else
		return plano_relatividade_calc(plano1,plano2);
}

float plano_distancia_calc(plano_ponteiro x,plano_ponteiro y){
	float P[3],n[3],res[3],a,b;
	int rel;
	
	rel = plano_relatividade_calc(x,y);
	
	if(rel == 2)
		return 0;

	n[0] = x->info.vetor1[1] * x->info.vetor2[2] - (x->info.vetor1[2] * x->info.vetor2[1]);
	n[1] = x->info.vetor1[2] * x->info.vetor2[0] - (x->info.vetor1[0] * x->info.vetor2[2]);
	n[2] = x->info.vetor1[0] * x->info.vetor2[1] - (x->info.vetor1[1] * x->info.vetor2[0]);

	for(int i=0;i<3;i++)
		P[i] = y->info.ponto[i];

	for(int i=0;i<3;i++){
		res[i] = P[i] * n[i];
	}
	a=sqrt(pow(res[0],2)+pow(res[1],2)+pow(res[2],2));
	b=sqrt(pow(n[0],2)+pow(n[1],2)+pow(n[2],2));

	return a/b;
}

float plano_distancia(espaco *e,char x[],char y[]){
	plano_ponteiro plano1 = (plano_ponteiro)malloc(sizeof(plano_no));
	plano_ponteiro plano2 = (plano_ponteiro)malloc(sizeof(plano_no));
	
	plano1 = plano_busca(e,x);
	plano2 = plano_busca(e,y);
	
	if(plano1 == NULL || plano2 == NULL)
		return 0;
	
	return plano_distancia_calc(plano1,plano2);
}
//<<<<<<<<<<<<<<<<<<<<Planos


//#include"strings.h"
int input(char str[], int size){
	int i=0;
	char c=getchar();

	while(c != '\n'){
		if(size > 0){
			str[i]=c;
			i++;
			size--;
		}
		c=getchar();
	}
	str[i]='\0';
	return i;
}

//#include"salvar.h"
//>>>>>>>>>>>>>>>>>>>>Point
bool ponto_salvar(FILE *arq,espaco *e){
	ponto_ponteiro ponto_temp = (ponto_ponteiro)malloc(sizeof(ponto_no));
	
	int i=0;

	fwrite(&e->ponto_qnt,sizeof(int),1,arq);

	ponto_temp=e->ponto_prim;
	while(i<e->ponto_qnt){
		fwrite(&ponto_temp->info,sizeof(ponto_info),1,arq);
		ponto_temp=ponto_temp->prox;
		i++;
	}
	return true;
}

int ponto_login(FILE **arq,espaco *e){
	int i=0;
	
	ponto_ponteiro aux = (ponto_ponteiro)malloc(sizeof(ponto_no));
	ponto_ponteiro antes = (ponto_ponteiro)malloc(sizeof(ponto_no));

	fread(&e->ponto_qnt,sizeof(int),1,*arq);	
	e->ponto_prim = aux;
	
	while(i<e->ponto_qnt){
		fread(&aux->info,sizeof(ponto_info),1,*arq);
		aux->prox = (ponto_ponteiro)malloc(sizeof(ponto_no));
		antes=aux;
		aux = aux->prox;
		i++;
	}
	antes->prox = NULL;
	return 1;
}
//<<<<<<<<<<<<<<<<<<<<Point

//>>>>>>>>>>>>>>>>>>>>Vector
int vetor_salvar(FILE *arq,espaco *e){
	vetor_ponteiro vetor_temp = (vetor_ponteiro)malloc(sizeof(vetor_no));
	
	int i=0;

	fwrite(&e->vetor_qnt,sizeof(int),1,arq);

	vetor_temp=e->vetor_prim;
	while(i<e->vetor_qnt){
		fwrite(&vetor_temp->info,sizeof(vetor_info),1,arq);
		vetor_temp=vetor_temp->prox;
		i++;
	}
	return 1;
}

int vetor_login(FILE **arq,espaco *e){
	int i=0;
	
	vetor_ponteiro aux = (vetor_ponteiro)malloc(sizeof(vetor_no));
	vetor_ponteiro antes = (vetor_ponteiro)malloc(sizeof(vetor_no));

	fread(&e->vetor_qnt,sizeof(int),1,*arq);	
	e->vetor_prim = aux;
	
	while(i<e->vetor_qnt){
		fread(&aux->info,sizeof(vetor_info),1,*arq);
		aux->prox = (vetor_ponteiro)malloc(sizeof(vetor_no));
		antes=aux;
		aux = aux->prox;
		i++;
	}
	antes->prox = NULL;
	return 1;
}
//<<<<<<<<<<<<<<<<<<<<Vector

//>>>>>>>>>>>>>>>>>>>>Line
int reta_salvar(FILE *arq,espaco *e){
	reta_ponteiro reta_temp = (reta_ponteiro)malloc(sizeof(reta_no));
	
	int i=0;

	fwrite(&e->reta_qnt,sizeof(int),1,arq);

	reta_temp=e->reta_prim;
	while(i<e->reta_qnt){
		fwrite(&reta_temp->info,sizeof(reta_info),1,arq);
		reta_temp=reta_temp->prox;
		i++;
	}
	return 1;
}

int reta_login(FILE **arq,espaco *e){
	int i=0;
	
	reta_ponteiro aux = (reta_ponteiro)malloc(sizeof(reta_no));
	reta_ponteiro antes = (reta_ponteiro)malloc(sizeof(reta_no));

	fread(&e->reta_qnt,sizeof(int),1,*arq);	
	e->reta_prim = aux;
	
	while(i<e->reta_qnt){
		fread(&aux->info,sizeof(reta_info),1,*arq);
		aux->prox = (reta_ponteiro)malloc(sizeof(reta_no));
		antes=aux;
		aux = aux->prox;
		i++;
	}
	antes->prox = NULL;
	return 1;
}
//<<<<<<<<<<<<<<<<<<<<Line

//>>>>>>>>>>>>>>>>>>>>Plane
int plano_salvar(FILE *arq,espaco *e){
	plano_ponteiro plano_temp = (plano_ponteiro)malloc(sizeof(plano_no));
	
	int i=0;

	fwrite(&e->plano_qnt,sizeof(int),1,arq);

	plano_temp=e->plano_prim;
	while(i<e->plano_qnt){
		fwrite(&plano_temp->info,sizeof(plano_info),1,arq);
		plano_temp=plano_temp->prox;
		i++;
	}
	return 1;
}

int plano_login(FILE **arq,espaco *e){
	int i=0;
	
	plano_ponteiro aux = (plano_ponteiro)malloc(sizeof(plano_no));
	plano_ponteiro antes = (plano_ponteiro)malloc(sizeof(plano_no));

	fread(&e->plano_qnt,sizeof(int),1,*arq);	
	e->plano_prim = aux;
	
	while(i<e->plano_qnt){
		fread(&aux->info,sizeof(plano_info),1,*arq);
		aux->prox = (plano_ponteiro)malloc(sizeof(plano_no));
		antes=aux;
		aux = aux->prox;
		i++;
	}
	antes->prox = NULL;
	return 1;
}
//<<<<<<<<<<<<<<<<<<<<Plane

int salvar(FILE *arq,espaco *e){

	rewind(arq);

	if(!ponto_salvar(arq,e))
		return 0;
	if(!vetor_salvar(arq,e))
		return 0;
	if(!reta_salvar(arq,e))
		return 0;
	if(!plano_salvar(arq,e))
		return 0;
	
	return 1;
}

int login(FILE **arq,char nome[],espaco *e){
	if((*arq = fopen(nome,"rb+"))==NULL)
		return 0;

	ponto_login(*&arq,e);
	vetor_login(*&arq,e);
	reta_login(*&arq,e);
	plano_login(*&arq,e);
}

void logout(FILE *arq,espaco *e){
	fclose(arq);
}


//#include"menus.h"
void gotoxy(int x,int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int menu_binario(int x){
	int a,b,linha,linha_anterior,opcao,limite_inf,limite_sup;

	linha=x;
	linha_anterior=x;
	b=x;
	limite_inf=x;
	limite_sup=x+1;

	printf("   Yes\n   No\n");
	do{
    	gotoxy(0,linha);
    	printf("-->");
    	gotoxy(6,linha);
    	printf("<--");
    	gotoxy(0,5);
    	if(kbhit){
			a=getch();
		}
    	if(a == 80 && b < limite_sup){ //seta pra baixo
			linha_anterior=linha;
			linha++;
			b++;
		}
    	if(a == 72 && b > limite_inf){ //seta pra cima
			linha_anterior=linha;
			linha--;
			b--;
		}
    	if(linha!=linha_anterior){ //apagar
			gotoxy(0,linha_anterior);
			printf("   ");
			gotoxy(6,linha_anterior);
	        printf("   ");
			linha_anterior=linha;
		}
		if(a == 13){
				opcao = b + 1 - x;
		}
    }while(opcao == 0);
    
    return opcao;
}

int menu_pontos(int x){
	int a,b,linha,linha_anterior,opcao,limite_inf,limite_sup;
	
	if(x == 0){
		limite_inf = 1;
		limite_sup = 2;
	}
	else if(x == 1){
		limite_inf = 1;
		limite_sup = 5;
	}
	else{
		limite_inf = 1;
		limite_sup = 6;
	}

	opcao=0;
    linha=1;linha_anterior=1;b=1;
    system("cls");
    printf("==================PONTOS==================\n   Voltar\n   Adicionar um Ponto ao Espa�o\n   Mostrar a lista de Pontos\n   Remover Ponto\n   Apagar a lista de Pontos\n   Dist�ncia entre dois pontos\n");
    do{
        gotoxy(0,linha);
        printf("-->");
    	gotoxy(31,linha);
    	printf("<--");
    	gotoxy(0,7);
        if(kbhit){
			a=getch();
		}
        if(a == 80 && b < limite_sup){ //seta pra baixo
			linha_anterior=linha;
			linha++;
			b++;
		}
        if(a == 72 && b > limite_inf){ //seta pra cima
			linha_anterior=linha;
			linha--;
			b--;
		}
        if(linha!=linha_anterior){ //apagar
			gotoxy(0,linha_anterior);
			printf("   ");
			gotoxy(31,linha_anterior);
	        printf("   ");
			linha_anterior=linha;
		}
		if(a == 13){
			opcao = b;
		}
    }while(opcao == 0);
    
    return opcao-1;
}

int menu_vetores(int x){
	int a,b,linha,linha_anterior,opcao,limite_inf,limite_sup;
	
	if(x == 0){
		limite_inf = 1;
		limite_sup = 2;
	}
	else if(x == 1){
		limite_inf = 1;
		limite_sup = 5;
	}
	else{
		limite_inf = 1;
		limite_sup = 6;
	}

	opcao=0;
    linha=1;linha_anterior=1;b=1;
    system("cls");
    printf("==================Vetores==================\n   Voltar\n   Adicionar um Vetor ao Espa�o\n   Mostrar a lista de Vetores\n   Remover Vetor\n   Apagar a lista de Vetores\n   Linearidade entre Vetores\n");
    do{
        gotoxy(0,linha);
        printf("-->");
    	gotoxy(31,linha);
    	printf("<--");
    	gotoxy(0,7);
        if(kbhit){
			a=getch();
		}
        if(a == 80 && b < limite_sup){ //seta pra baixo
			linha_anterior=linha;
			linha++;
			b++;
		}
        if(a == 72 && b > limite_inf){ //seta pra cima
			linha_anterior=linha;
			linha--;
			b--;
		}
        if(linha!=linha_anterior){ //apagar
			gotoxy(0,linha_anterior);
			printf("   ");
			gotoxy(31,linha_anterior);
	        printf("   ");
			linha_anterior=linha;
		}
		if(a == 13){
			opcao = b;
		}
    }while(opcao == 0);
    
    return opcao-1;
}

int menu_retas(int x){
	int a,b,linha,linha_anterior,opcao,limite_inf,limite_sup;
	
	if(x == 0){
		limite_inf = 1;
		limite_sup = 2;
	}
	else if(x == 1){
		limite_inf = 1;
		limite_sup = 5;
	}
	else{
		limite_inf = 1;
		limite_sup = 7;
	}

	opcao=0;
    linha=1;linha_anterior=1;b=1;
    system("cls");
    printf("==================Retas==================\n   Voltar\n   Adicionar uma Reta ao Espa�o\n   Mostrar a lista de Retas\n   Remover Reta\n   Apagar a lista de Retas\n   Dist�ncia entre duas Retas\n   Posi��o relativa entre duas Retas\n");
    do{
        gotoxy(0,linha);
        printf("-->");
    	gotoxy(36,linha);
    	printf("<--");
    	gotoxy(0,9);
        if(kbhit){
			a=getch();
		}
        if(a == 80 && b < limite_sup){ //seta pra baixo
			linha_anterior=linha;
			linha++;
			b++;
		}
        if(a == 72 && b > limite_inf){ //seta pra cima
			linha_anterior=linha;
			linha--;
			b--;
		}
        if(linha!=linha_anterior){ //apagar
			gotoxy(0,linha_anterior);
			printf("   ");
			gotoxy(36,linha_anterior);
	        printf("   ");
			linha_anterior=linha;
		}
		if(a == 13){
			opcao = b;
		}
    }while(opcao == 0);
    
    return opcao-1;
}

int menu_planos(int x){
	int a,b,linha,linha_anterior,opcao,limite_inf,limite_sup;
	
	if(x == 0){
		limite_inf = 1;
		limite_sup = 2;
	}
	else if(x == 1){
		limite_inf = 1;
		limite_sup = 5;
	}
	else{
		limite_inf = 1;
		limite_sup = 7;
	}

	opcao=0;
    linha=1;linha_anterior=1;b=1;
    system("cls");
    printf("==================Planos==================\n   Voltar\n   Adicionar um Plano ao Espa�o\n   Mostrar a lista de Planos\n   Remover Plano\n   Apagar a lista de Planos\n   Dist�ncia entre dois Planos\n   Posi��o relativa entre dois Planos\n");
    do{
        gotoxy(0,linha);
        printf("-->");
    	gotoxy(37,linha);
    	printf("<--");
    	gotoxy(0,9);
        if(kbhit){
			a=getch();
		}
        if(a == 80 && b < limite_sup){ //seta pra baixo
			linha_anterior=linha;
			linha++;
			b++;
		}
        if(a == 72 && b > limite_inf){ //seta pra cima
			linha_anterior=linha;
			linha--;
			b--;
		}
        if(linha!=linha_anterior){ //apagar
			gotoxy(0,linha_anterior);
			printf("   ");
			gotoxy(37,linha_anterior);
	        printf("   ");
			linha_anterior=linha;
		}
		if(a == 13){
			opcao = b;
		}
    }while(opcao == 0);
    
    return opcao-1;
}

int menu_geral(int ponto,int vetor,int reta,int plano){
	int a,b,linha,linha_anterior,opcao,resposta,limite_sup,limite_inf,qnt_menu,qnt_opcao;
	
	qnt_menu = 4;
	qnt_opcao = 3;
	limite_inf = 1;
	limite_sup = qnt_opcao + qnt_menu + limite_inf;
	
    do{
		opcao=0;
    	linha=1;linha_anterior=1;b=1;
    	system("cls");
    	printf("==================MENU DE OP��ES==================\n   Opera��es com Pontos\n   Opera��es com Vetores\n   Opera��es com Retas\n   Opera��es com Planos\n   Imprimir tudo\n   Apagar tudo\n   Salvar\n   Sair\n");
    	do{
    	    gotoxy(0,linha);
    	    printf("-->");
    		gotoxy(24,linha);
    		printf("<--");
    		gotoxy(0,limite_sup+1);
    	    if(kbhit){
				a=getch();
			}
    	    if(a == 80 && b < limite_sup){ //seta pra baixo
				linha_anterior=linha;
				linha++;
				b++;
			}
    	    if(a == 72 && b > limite_inf){ //seta pra cima
				linha_anterior=linha;
				linha--;
				b--;
			}
    	    if(linha!=linha_anterior){ //apagar
				gotoxy(0,linha_anterior);
				printf("   ");
				gotoxy(24,linha_anterior);
	            printf("   ");
				linha_anterior=linha;
			}
			if(a == 13){
				opcao = b;
			}
    	}while(opcao == 0);

		if(opcao == 1){
			resposta = menu_pontos(ponto);

			if(resposta != 0){
				opcao = resposta - 1 + 10;
				break;
			}
		}
		if(opcao == 2){
			resposta = menu_vetores(vetor);
			
			if(resposta != 0){
				opcao = resposta - 1 + 20;
				break;
			}
		}
		if(opcao == 3){
			resposta = menu_retas(reta);
			
			if(resposta != 0){
				opcao = resposta - 1 + 30;
				break;
			}
		}
		if(opcao == 4){
			resposta = menu_planos(plano);
			
			if(resposta != 0){
				opcao = resposta - 1 + 40;
				break;
			}
		}

		if(opcao > qnt_menu){
			opcao = opcao - qnt_menu;
			break;
		}

	}while(opcao < qnt_menu+1);

	return opcao;
}

int menu(char menu[],int x,int tam,int pos){
	int a,b,linha,linha_anterior,opcao,limite_inf,limite_sup;

	linha=x;
	linha_anterior=x;
	b=x;
	limite_inf=x;
	limite_sup=x+tam-1;

	int final = x+tam;

	gotoxy(0,linha);
	printf("%s",menu);
	do{
    	gotoxy(0,linha);
    	printf("-->");
    	gotoxy(pos,linha);
    	printf("<--");
    	gotoxy(0,final);
    	if(kbhit){
			a=getch();
		}
    	if(a == 80 && b < limite_sup){ //seta pra baixo
			linha_anterior=linha;
			linha++;
			b++;
		}
    	if(a == 72 && b > limite_inf){ //seta pra cima
			linha_anterior=linha;
			linha--;
			b--;
		}
    	if(linha!=linha_anterior){ //apagar
			gotoxy(0,linha_anterior);
			printf("   ");
			gotoxy(pos,linha_anterior);
			printf("   ");
			linha_anterior=linha;
		}
		if(a == 13){
				opcao = b + 1 - x;
		}
    }while(opcao == 0);
    
    return opcao;
}


//Main
main(){
	setlocale(LC_ALL,"portuguese");
	FILE *arq;
	char x[10],y[10],nomearq[30];
	float ret;
	int escolha,res,confir,confirext=0,mud,r,ant_mud=0;

	espaco e;
	
	printf("Boas vindas � Calculadora de Posi��es Relativas\n\nDeseja carregar algum espa�o salvo anteriormente?\n");
	
	r = menu_binario(3);
	do{
		if(r == 1){
			do{
				fflush(stdin);
				cout << "\nEntre com o nome do arquivo a ser carregado:";
				input(nomearq,30);
				strcat(nomearq,".cpr");
				setbuf(stdin,NULL);
				res = login(&arq,nomearq,&e);
				if(res==1){
					cout << "Arquivo carregado com sucesso.\n";
					confir=1;
					confirext=1;
				}
					else{
						cout << "Arquivo n�o encontrado.\n\n";
						confir=0;
						system("pause");
						system("cls");
						cout << "Deseja tentar novamente?\n";
						r = menu_binario(1);
						if(r == 2){
							cout << "O programa ser� encerrado.";
							exit(1);
						}
						else if(r == 1){
							system("pause");
							system("cls");
						}
						else{
							cout << "Comando n�o reconhecido.\n";
							system("pause");
							system("cls");
						}
					}
			}while(confir==0);
		}
			else if(r == 2){
				cout << endl;
				system("pause");
				system("cls");
				cout << "Criar um arquivo novo?\n";
				r = menu_binario(1);
				if(r == 1){
					cout << "Entre com o nome do arquivo a ser criado:";
					fflush(stdin);
					input(nomearq,30);
					cout << endl;
					strcat(nomearq,".cpr");
					setbuf(stdin,NULL);
					res = criar_espaco(nomearq,&e,&arq);
					if(res==0){
						cout << "Erro interno.\n";
						system("pause");
						exit(1);
					}
						else
							cout << "Arquivo criado com sucesso.\n";
							confirext=1;
				}
					else{
						system("pause");
						system("cls");
						cout << "Continuar sem salvar?\n";
						r = menu_binario(1);
						if(r == 1){
							ant_mud = 1;
							confirext=1;
							criar_espaco_temp(&e);
						}
						else
							exit(0);
					}
			}
		if(confirext != 1){
			cout << "Entrada inv�lida, tente novamente.\nResposta:";
			cin >> r;
			setbuf(stdin,NULL);
		}
	}while(confirext != 1);

	system("pause");

//============================================================================================================================================MENU
	do{
		escolha = menu_geral(e.ponto_qnt,e.vetor_qnt,e.reta_qnt,e.plano_qnt);

		system("cls");

		if(escolha == 1){ //Imprimir Espa�o
			imprimir_espaco(&e);
		}
		else if(escolha == 2){ //Destruir Espa�o
        	cout << "Voc� tem certeza que quer continuar, isso apagar� tudo.\n";
        	r = menu_binario(1);
        	if(r == 1){
        		destruir_espaco(&e);
        		cout << "Dados apagados com sucesso.\n";
        		mud = 1;
        	}
         	else
            	cout << "Opera��o abortada.\n";
    	}
		else if(escolha == 3){ //Salvar
			if(ant_mud == 1)
				cout << "N�o � poss�vel salvar um arquivo tempor�rio.\n";
			else{
	    		res = salvar(arq,&e);
	    		if(res == 1){
	    			cout << "Arquivo salvo com sucesso.\n";
	    			mud = 0;
	    		}
	    		else
	    			cout << "Erro interno.\n";
	    	}
		}
		else if(escolha == 4){ //Sair
    		cout << "Voc� escolheu sair.\n";
    		
    		if(ant_mud == 0){
    			if(mud == 1){
					cout << "\nExistem altera��es n�o salvas, deseja salvar?\n";
					r = menu_binario(3);
					if(r == 1){
						res = salvar(arq,&e);
						if(res == 1)
							cout << "Arquivo salvo com sucesso.\n";
						else
						cout << "Erro interno.\n";
					}
				}
				logout(arq,&e);
			}
    	}
    	
	else if(escolha == 10){ //Adicionar Ponto
			char nome_ponto[10];
			float P[3];
			
			fflush(stdin);
			cout << "D� um Nome ao Ponto:";
			input(nome_ponto,10);
			fflush(stdin);

    		cout << "\nEntre com as coordenadas do Ponto\n";
    		cout << "Entre com o Valor de X:";
    		cin >> P[0];
    		cout << "Entre com o Valor de Y:";
    		cin >> P[1];
    		cout << "Entre com o Valor de Z:";
    		cin >> P[2];
    		cout << "\n";
    		
    		ponto_novo(&e,nome_ponto,P);

    		mud = 1;
		}
		else if(escolha == 11){ //Imprimir Pontos
				ponto_imprimir(&e);
		}
		else if(escolha == 12){ //Remover Ponto
		    fflush(stdin);
    		cout << "Ponto a ser Exclu�do:";
        	input(x,10);
        	fflush(stdin);
        	cout << endl;
        	res = ponto_remover(&e,x);
        	if(res == 1){
        		cout << "Ponto Removido com sucesso.\n";
        		mud=1;
        	}
        	else
            	cout << "N�o foi poss�vel localizar o Ponto.\n";
		}
		else if(escolha == 13){ //Destruir Pontos
			cout << "Voc� tem certeza que quer continuar, isso apagar� toda a lista de Pontos.\n";
        	r = menu_binario(1);
        	if(r == 1){
        		ponto_destruir(&e);
        		cout << "Pontos apagados com sucesso.\n";
        		mud = 1;
        	}
         	else
            	cout << "Opera��o abortada.\n";
		}
		else if(escolha == 14){ //Calcular Dist�ncia entre dois Pontos
        	fflush(stdin);
            cout << "Nome do Primeiro Ponto:";
            input(x,10);
            fflush(stdin);
            cout << "Nome do Segundo Ponto:";
            input(y,10);
            fflush(stdin);
            cout << endl;
            ret = ponto_distancia(&e,x,y);
            if(ret == 0){
            	cout << "N�o foi poss�vel calcular.\n";
			}
			else{
				printf("A dist�ncia entre os dois pontos �: %.2f\n",ret);
			}
		}
		else if(escolha == 20){ //Adicionar Vetor
			char nome_vetor[10];
			float V[3];
			r=0;
			
			fflush(stdin);
			cout << "D� um Nome ao Vetor:";
			input(nome_vetor,10);
			
			system("cls");
			
			if(e.ponto_qnt > 1){
				cout << "Criar vetor a partir de dois pontos?\n";
				r = menu_binario(1);
			}
			if(r == 1){
				char a[10],b[10];
				fflush(stdin);
				cout << "Entre com o nome do primeiro ponto:";
				input(a,10);
				fflush(stdin);
				cout << "Entre com o nome do segundo ponto:";
				input(b,10);
				fflush(stdin);
				r = vetor_novo2pon(&e,a,b,nome_vetor);
				if(r == 0)
					cout << "N�o foi poss�vel achar os pontos, inser��o abortada\n";
			}
			else{
				fflush(stdin);
    			cout << "\nEntre com as coordenadas do Vetor\n";
    			cout << "Entre com o Valor de X:";
    			cin >> V[0];
    			cout << "Entre com o Valor de Y:";
    			cin >> V[1];
    			cout << "Entre com o Valor de Z:";
    			cin >> V[2];
    			cout << "\n";
    		
    			vetor_novo(&e,nome_vetor,V);

	    		mud = 1;
    		}
		}
		else if(escolha == 21){ //Imprimir Vetores
			vetor_imprimir(&e);
		}
		else if(escolha == 22){ //Remover Vetor
			fflush(stdin);
    		cout << "Vetor a ser Exclu�do:";
        	input(x,10);
        	fflush(stdin);
        	cout << endl;
        	res = vetor_remover(&e,x);
        	if(res == 1){
        		cout << "Vetor Removido com sucesso.\n";
        		mud=1;
        	}
        	else
            	cout << "N�o foi poss�vel localizar o Vetor.\n";
		}
		else if(escolha == 23){ //Destruir Vetores
			cout << "Voc� tem certeza que quer continuar, isso apagar� toda a lista de Vetores.\n";
        	r = menu_binario(1);
        	if(r == 1){
        		vetor_destruir(&e);
        		cout << "Vetores apagados com sucesso.\n";
        		mud = 1;
        	}
         	else
            	cout << "Opera��o abortada.\n";
		}
		else if(escolha == 24){ //Verificar Linearidade
			char vet1[10],vet2[10],vet3[10];
			int qnt;
			cout << "Quantidade de Vetores a serem analisados:";
			cin >> qnt;

			if(qnt == 1){
				r = 1;
			}
			else if(qnt == 2){
				fflush(stdin);
	            cout << "Nome do Primeiro Vetor:";
            	input(vet1,10);
            	fflush(stdin);
            	cout << "Nome do Segundo Vetor:";
            	input(vet2,10);
            	fflush(stdin);
            	cout << endl;
            	r = vetor_linearidade(&e,qnt,vet1,vet2,"");
            }
            else if(qnt == 3){
            	fflush(stdin);
            	cout << "Nome do Primeiro Vetor:";
            	input(vet1,10);
            	fflush(stdin);
            	cout << "Nome do Segundo Vetor:";
            	input(vet2,10);
            	fflush(stdin);
            	cout << "Nome do Terceiro Vetor:";
            	input(vet3,10);
            	fflush(stdin);
            	cout << endl;
            	r = vetor_linearidade(&e,qnt,vet1,vet2,vet3);
			}
			else
				r = 1;

            if(r == 0){
            	cout << "N�o foi poss�vel calcular.\n";
			}
			else if(r == 1){
				cout << "Linearmente Dependente.\n";
			}
			else
				cout << "Linearmente Independente.\n";
		}

		else if(escolha == 30){ //Adicionar Reta
			char nome_reta[10];
			float P[3],V[3];
			r=0;
			
			fflush(stdin);
			cout << "D� um Nome a Reta:";
			input(nome_reta,10);
			fflush(stdin);

			cout << "\nEntre com as coordenadas do Ponto.\n";
			cout << "Entre com o Valor de X:";
			cin >> P[0];
			cout << "Entre com o Valor de Y:";
    		cin >> P[1];
    		cout << "Entre com o Valor de Z:";
    		cin >> P[2];
    		cout << "\n";

    		cout << "\nEntre com as coordenadas do Vetor\n";
    		cout << "Entre com o Valor de X:";
    		cin >> V[0];
    		cout << "Entre com o Valor de Y:";
    		cin >> V[1];
    		cout << "Entre com o Valor de Z:";
    		cin >> V[2];
    		cout << "\n";
    		
    		reta_novo(&e,nome_reta,P,V);

	    	mud = 1;
    	}
		else if(escolha == 31){ //Imprimir Retas
			reta_imprimir(&e);
		}
		else if(escolha == 32){ //Remover Reta
		    fflush(stdin);
    		cout << "Reta a ser Exclu�da:";
        	input(x,10);
        	fflush(stdin);
        	cout << endl;
        	res = reta_remover(&e,x);
        	if(res == 1){
        		cout << "Reta Removida com sucesso.\n";
        		mud=1;
        	}
        	else
            	cout << "N�o foi poss�vel localizar a Reta.\n";
		}
		else if(escolha == 33){ //Destruir Retas
			cout << "Voc� tem certeza que quer continuar, isso apagar� toda a lista de Retas.\n";
        	r = menu_binario(1);
        	if(r == 1){
        		reta_destruir(&e);
        		cout << "Retas apagadas com sucesso.\n";
        		mud = 1;
        	}
         	else
            	cout << "Opera��o abortada.\n";
		}
		else if(escolha == 34){ //Dist�ncia entre Retas
			fflush(stdin);
			cout << "Nome da Primeira Reta:";
			input(x,10);
			fflush(stdin);
			cout << "\nNome da Segunda Reta:";
			input(y,10);
			fflush(stdin);
			
			ret = reta_distancia(&e,x,y);

			printf("\nA dist�ncia entre as duas retas �: %.2f\n",ret);
		}
		else if(escolha == 35){ //Verificar Posi��o Relativa
			fflush(stdin);
			cout << "Nome da Primeira Reta:";
			input(x,10);
			fflush(stdin);
			cout << "\nNome da Segunda Reta:";
			input(y,10);
			fflush(stdin);
			
			r = reta_relatividade(&e,x,y);
			
			if(r == 1){
				cout << "\nRetas Reversas\n";
			}
			else if(r == 2){
				cout << "\nRetas Paralelas\n";
			}
			else if(r == 3){
				cout << "\nRetas Concorrentes\n";
			}
			else if(r == 4){
				cout << "\nRetas Coincidentes\n";
			}
			else
				cout << "\nN�o foi poss�vel calcular.\n";
		}
		
		else if(escolha == 40){ //Adicionar Plano
			char nome_plano[10];
			float P[3],V1[3],V2[3];
			r=0;
			
			fflush(stdin);
			cout << "D� um Nome ao Plano:";
			input(nome_plano,10);
			fflush(stdin);

			cout << "\nEntre com as coordenadas do Ponto.\n";
			cout << "Entre com o Valor de X:";
			cin >> P[0];
			cout << "Entre com o Valor de Y:";
    		cin >> P[1];
    		cout << "Entre com o Valor de Z:";
    		cin >> P[2];
    		cout << "\n";

			cout << "\nEntre com as coordenadas do primeiro Vetor\n";
    		cout << "Entre com o Valor de X:";
    		cin >> V1[0];
    		cout << "Entre com o Valor de Y:";
    		cin >> V1[1];
    		cout << "Entre com o Valor de Z:";
    		cin >> V1[2];
    		cout << "\n";

    		cout << "\nEntre com as coordenadas do segundo Vetor\n";
    		cout << "Entre com o Valor de X:";
    		cin >> V2[0];
    		cout << "Entre com o Valor de Y:";
    		cin >> V2[1];
    		cout << "Entre com o Valor de Z:";
    		cin >> V2[2];
    		cout << "\n";
    		
    		if(vetor_linearidade_2vet(V1,V2) == 1)
    			cout << "Para obter um plano, � necess�rio dois Vetores LI, cria��o abortada\n";
			else{		
    			plano_novo(&e,nome_plano,P,V1,V2);

	    		mud = 1;
	    	}
    	}
		else if(escolha == 41){ //Imprimir Planos
			plano_imprimir(&e);
		}
		else if(escolha == 42){ //Remover Plano
    		fflush(stdin);
			cout << "Plano a ser Exclu�do:";
        	input(x,10);
        	fflush(stdin);
        	cout << endl;
        	res = plano_remover(&e,x);
        	if(res == 1){
        		cout << "Plano Removido com sucesso.\n";
        		mud=1;
        	}
        	else
            	cout << "N�o foi poss�vel localizar o Plano.\n";
		}
		else if(escolha == 43){ //Destruir Planos
			cout << "Voc� tem certeza que quer continuar, isso apagar� toda a lista de Planos.\n";
        	r = menu_binario(1);
        	if(r == 1){
        		plano_destruir(&e);
        		cout << "Planos apagados com sucesso.\n";
        		mud = 1;
        	}
         	else
            	cout << "Opera��o abortada.\n";
		}
		else if(escolha == 44){ //Dist�ncia entre Planos
			fflush(stdin);
			cout << "Nome do Primeiro Plano:";
			input(x,10);
			fflush(stdin);
			cout << "\nNome do Segundo Plano:";
			input(y,10);
			fflush(stdin);
			
			ret = plano_distancia(&e,x,y);

			printf("\nA dist�ncia entre os dois planos �: %.2f\n",ret);
		}
		else if(escolha == 45){ //Verificar Posi��o Relativa
			fflush(stdin);
			cout << "Nome do Primeiro Plano:";
			input(x,10);
			fflush(stdin);
			cout << "\nNome do Segundo Plano:";
			input(y,10);
			fflush(stdin);
			
			r = plano_relatividade(&e,x,y);
			
			if(r == 1)
				cout << "\nPlanos Paralelos\n";
			else if(r == 2)
				cout << "\nPlanos Concorrentes\n";
			else
				cout << "\nN�o foi poss�vel calcular.\n";
		}
		
		else
      		if(escolha != 3)
         		cout << "Erro.\n";
		
		cout << endl;
		system("pause");
		
	}while(escolha != 4);
}
