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
