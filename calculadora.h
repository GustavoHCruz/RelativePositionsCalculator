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
