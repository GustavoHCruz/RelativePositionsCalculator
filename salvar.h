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
