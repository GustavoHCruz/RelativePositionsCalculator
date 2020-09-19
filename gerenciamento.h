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
