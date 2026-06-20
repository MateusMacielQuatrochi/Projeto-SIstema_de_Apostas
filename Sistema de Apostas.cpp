#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <time.h>


//Definição de constantes
#define TFNA 10
#define TFNS 5
#define TFNM 50
#define TFB 20

//area das structs
struct TpConcurso
{	//PK = NumCurso 
	int NumCurso, NumSort[TFNS];
	char data[12], status;
};


struct TpApostadores
{	//PK = CPF
	char CPF[13], Nome[TFNM], status;
	int DDD, NumTel;
};

struct TpAposta
{	//PK = NumCurso && CPF
	int NumCurso, qtd_aposta, NumApost[TFNA];
	char CPF[13], status;
};

//prototipo das funcoes

//menus
char Menu_principal();
char Menu_cadastro();
char Menu_busca();
char Menu_exclusao();
char Menu_alteracao();
char Menu_relatorio();
void InsereTeste();
void Moldura(int CI, int LI, int CF, int LF);
int contar_acertos(int numsApost[TFNA], int qtd_aposta, int numsSort[TFNS], int Pos[5]);
void Sotnum(int Num[5]);





// Regra de nomeacao de funcoes basicas
// Cadastro - Cad + Nome(Concurso, Apostadores, Aposta)
	//funcoes
	void CadApostador();
	void  CadAposta();
	void CADCOncurso();
// Busca - Bus + Nome(Concurso, Apostadores, Aposta)
	//funcoes
	void BusAposta();
	int BusAposta_exaust(FILE *PtrAposta, char auxCPF[10], int auxnum);
	void BuscarApostadores();
	int BuscarCPF(FILE *PtrApostador, char auxCPF[10]);
	int VeriNum(FILE *PtrConcurso , int AuxBus);
	int BusNumSorteio(FILE *PtrConcurso, int num);
	int BusNumAposta(FILE *PtrAposta, int num);
	void BusConcurso();
	void RecebeASConcurso (	FILE *PtrApostador, FILE *PtrConcurso,char aux[TFNM], int &aux_con);
// Exclusao fisica - Ex + Nome(Concurso, Apostadores, Aposta)
	//funcoes
	void ExAposta_logico();
	void ExAposta_fisico();
	void Exc_Fisi_Apostador(void);
	void ExclusaoLogica_Apostador();
	void ExConc(TpConcurso Concurso[TFB], int &TLC, TpAposta C[TFB*TFB], int TLAP);
// Alteracao - Alt + Nome(Concurso, Apostadores, Aposta)
	//funcoes
	void AltAposta();
	void AlterarDadosApostador();
	void AltNum(TpConcurso Concurso[TFB], int TLC);
	
//relatorios
 	void RelEspec();
 	void MaisMenoSorteio();
 	void MaisMenoAposta();
 	void ExibeApostadores();
 	void ExibeApostadoresPremiados();
	void relatorioConcurso(TpConcurso Concurso[TFB], int TLC);
	void Rel_aposta();
	void Rel_terno();
 	

int main ()
{
	TpConcurso  Concurso[TFB];
	TpApostadores Apostadores[TFB];
	TpAposta Aposta[TFB*TFB];
	int TLC = 0, TLAS = 0, TLAP = 0, i=0;
	char opcao, opcao_2;
	
	srand(time(NULL));
	opcao = Menu_principal();
	while (opcao !=27)
		{	
			switch (opcao)
			{
				case 'F': if (i == 0)
						  {
						   	InsereTeste();
						   	system("cls");
								printf("Dados salvos!");
								Sleep(1000);
							i=1;
						  }
							
						  else
						  	{
						  		system("cls");
								printf("Dados ja salvos...");
								Sleep(1000);
						  	}
						  break;
				case 'A': opcao_2 = Menu_cadastro();
						  while(opcao_2 != 27)
						  	{
						  		switch(opcao_2)
						  			{
						  				case 'A': 
						  				 	 	 CADCOncurso();
						  						 break;
						  				case 'B':
						  						 CadApostador();
												 break;
										case 'C':
												 CadAposta();
												 break;
						  			}
						  		opcao_2 = Menu_cadastro();
						  	}
						 break;
						 
				case 'B': opcao_2 = Menu_busca();
						  while(opcao_2 != 27)
						  	{
						  		switch(opcao_2)
						  			{
						  				case 'A': BusConcurso();
						  						 break;
						  				case 'B':
						  						 BuscarApostadores();
												 break;
										case 'C':
												 BusAposta();
												 break;
						  			}
						  		opcao_2 = Menu_busca();
						  	}
						 break;
						 
				case 'C': opcao_2 = Menu_exclusao();
						  while(opcao_2 != 27)
						  	{
						  		switch(opcao_2)
						  			{
						  				case 'A':
						  						 ExConc(Concurso, TLC, Aposta, TLAP);
						  						 break;
						  				case 'B':
						  						 ExclusaoLogica_Apostador();
												 break;
										case 'C':
												 ExAposta_logico();
												 break;
						  			}
						  		opcao_2 = Menu_exclusao();
						  	}
						 break;
						 
				case 'D': opcao_2 = Menu_alteracao();
						  while(opcao_2 != 27)
						  	{
						  		switch(opcao_2)
						  			{
						  				case 'A':
						  						 AltNum(Concurso, TLC);
						  						 break;
						  				case 'B':
						  						 AlterarDadosApostador();
												 break;
										case 'C':
												 AltAposta();
												 break;
						  			}
						  		opcao_2 = Menu_alteracao();
						  	}
						 break;
						 
				case 'E': opcao_2 = Menu_relatorio();
						  while(opcao_2 != 27)
						  	{
						  		switch(opcao_2)
						  			{
						  				case 'A': relatorioConcurso(Concurso, TLC);
						  						 break;
						  				case 'B':  ExibeApostadores();
												 break;
										case 'C': Rel_aposta(); 
												 break;
										case 'D': ExibeApostadoresPremiados();
												 break;
										case 'E': RelEspec();
												 break;
										case 'F': MaisMenoSorteio();
												 break;
										case 'G': MaisMenoAposta();
												 break;
										case 'H': Rel_terno();
												  break;
						  			}
						  		opcao_2 = Menu_relatorio();
						  	}
						 break;
					
			}
			opcao = Menu_principal();
		}

	
	
	return 0;
}

//Corpo das funcoes

//Teste Moldura -------------------------------------------------
void Moldura(int x, int y, int largura, int altura)
{
    int i;

    // Canto superior esquerdo
    gotoxy(x, y); printf("%c", 201); 

    // Linha superior
    for (i = 1; i < largura - 1; i++)
        printf("%c", 205); 

    // Canto superior direito
    printf("%c", 187); 

    // Linhas laterais
    for (i = 1; i < altura - 1; i++) {
        gotoxy(x, y + i); printf("%c", 186); 
        gotoxy(x + largura - 1, y + i); printf("%c", 186); 
    }

    // Canto inferior esquerdo
    gotoxy(x, y + altura - 1); printf("%c", 200); 

    // Linha inferior
    for (i = 1; i < largura - 1; i++)
        printf("%c", 205); 

    // Canto inferior direito
    printf("%c", 188); 
}
//-------------------------------------------------------------------------

//inicio dos menus
char Menu_principal()
{
	system("cls");
	
	//Moldura-----------------------------------------------
	int largura = 30, altura = 18;
	int x = 45;
	int y = 3;
	//------------------------------------------------------
	
	Moldura(x, y, largura, altura);
	gotoxy(x + 3, y + 1);
	textcolor(LIGHTGREEN);
	printf(" ### MENU PRINCIPAL ###");

	gotoxy(x + 2, y + 3); textcolor(WHITE); printf("Trabalho Criado Por:");
	gotoxy(x + 2, y + 4); printf(" - Arthur Orosco");
	gotoxy(x + 2, y + 5); printf(" - Mateus Maciel");

	gotoxy(x + 2, y + 8);  printf("[A] Cadastros");
	gotoxy(x + 2, y + 9);  printf("[B] Buscas");
	gotoxy(x + 2, y +10);  printf("[C] Exclusao dos dados");
	gotoxy(x + 2, y +11);  printf("[D] Alteracao dos dados");
	gotoxy(x + 2, y +12);  printf("[E] Relatorios");
	gotoxy(x + 2, y +13);  printf("[F] Insere dados para teste");

	gotoxy(x + 2, y +15); textcolor(LIGHTRED); printf("[ESC] Sair");
	textcolor(WHITE);
	return toupper(getche());
}

char Menu_cadastro()
{
	system("cls");
	
	//Moldura-----------------------------------------------
	int largura = 30, altura = 18;
	int x = 45;
	int y = 3;
	//------------------------------------------------------

	Moldura(x, y, largura, altura);
	gotoxy(x + 3, y + 1);
	textcolor(LIGHTGREEN);
	printf(" ### MENU CADASTRO ###");

	textcolor(WHITE);
	gotoxy(x + 2, y + 3); printf("[A] Concurso");
	gotoxy(x + 2, y + 4); printf("[B] Apostadores");
	gotoxy(x + 2, y + 5); printf("[C] Apostas");

	gotoxy(x + 2, y + 7); textcolor(LIGHTRED); printf("[ESC] Sair");
	textcolor(WHITE);
	return toupper(getche());
}

char Menu_busca()
{
	system("cls");
	
	//Moldura-----------------------------------------------
	int largura = 30, altura = 18;
	int x = 45;
	int y = 3;
	//------------------------------------------------------

	Moldura(x, y, largura, altura);
	gotoxy(x + 3, y + 1);
	textcolor(LIGHTGREEN);
	printf(" ### MENU BUSCA ###");

	textcolor(WHITE);
	gotoxy(x + 2, y + 3); printf("[A] Concurso");
	gotoxy(x + 2, y + 4); printf("[B] Apostadores");
	gotoxy(x + 2, y + 5); printf("[C] Apostas");

	gotoxy(x + 2, y + 7); textcolor(LIGHTRED); printf("[ESC] Sair");
	textcolor(WHITE);
	return toupper(getche());
}

char Menu_exclusao()
{
	system("cls");
	
	//Moldura-----------------------------------------------
	int largura = 30, altura = 18;
	int x = 45;
	int y = 3;
	//------------------------------------------------------

	Moldura(x, y, largura, altura);
	gotoxy(x + 3, y + 1);
	textcolor(LIGHTGREEN);
	printf(" ### MENU EXCLUSAO ###");

	textcolor(WHITE);
	gotoxy(x + 2, y + 3); printf("[A] Concurso");
	gotoxy(x + 2, y + 4); printf("[B] Apostadores");
	gotoxy(x + 2, y + 5); printf("[C] Apostas");

	gotoxy(x + 2, y + 7); textcolor(LIGHTRED); printf("[ESC] Sair");
	textcolor(WHITE);
	return toupper(getche());
}

char Menu_alteracao()
{
	system("cls");
	
	//Moldura-----------------------------------------------
	int largura = 30, altura = 18;
	int x = 45;
	int y = 3;
	//------------------------------------------------------

	Moldura(x, y, largura, altura);
	gotoxy(x + 3, y + 1);
	textcolor(LIGHTGREEN);
	printf(" ### MENU ALTERACAO ###");

	textcolor(WHITE);
	gotoxy(x + 2, y + 3); printf("[A] Concurso");
	gotoxy(x + 2, y + 4); printf("[B] Apostadores");
	gotoxy(x + 2, y + 5); printf("[C] Apostas");

	gotoxy(x + 2, y + 7); textcolor(LIGHTRED); printf("[ESC] Sair");
	textcolor(WHITE);
	return toupper(getche());
}

char Menu_relatorio()
{
	system("cls");
	
	//Moldura-----------------------------------------------
	int largura = 55, altura = 18;
	int x = 35;
	int y = 3;
	//------------------------------------------------------

	Moldura(x, y, largura, altura);
	gotoxy(x + 15, y + 1);
	textcolor(LIGHTGREEN);
	printf(" ### MENU RELATORIO ###");

	textcolor(WHITE);
	gotoxy(x + 2, y + 3);  printf("[A] Exibicao Concurso");
	gotoxy(x + 2, y + 4);  printf("[B] Exibe Apostadores");
	gotoxy(x + 2, y + 5);  printf("[C] Exibe Apostas");
	gotoxy(x + 2, y + 6);  printf("[D] Resumo de Apostadores premiados");
	gotoxy(x + 2, y + 7);  printf("[E] Acertadores de quantidade especifica");
	gotoxy(x + 2, y + 8);  printf("[F] Numeros que mais e menos aparecem no sorteio");
	gotoxy(x + 2, y + 9);  printf("[G] Numeros que mais e menos aparecem nas apostas");
	gotoxy(x + 2, y +10);  printf("[H] Terno, Quadra e Quina");

	gotoxy(x + 2, y +12); textcolor(LIGHTRED); printf("[ESC] Sair");
	textcolor(WHITE);
	return toupper(getche());
}

// fim dos menus
void CadAposta()
{
	TpAposta AP;
	int i, aux_con, aux_qtd, valida, aux_max_ap, j, repetido;
	char aux[TFNM];
	FILE *PtrAposta = fopen("Apostas.dat", "ab+");
	FILE *PtrApostador = fopen("Apostadores.dat", "rb");
	FILE *PtrConcurso = fopen("Concursos.dat", "rb");
	system("cls");
	printf(" ### Cadastro de Apostas ###");
	RecebeASConcurso(PtrApostador, PtrConcurso, aux, aux_con);

	while(strcmp(aux, "\0") != 0 && aux_con != 0 && BusAposta_exaust(PtrAposta, aux, aux_con) >= 0 )
	{
		printf("\nEsse registro ja existe dentro das Apostas, cadastrar outro por favor")	;
		RecebeASConcurso (PtrApostador, PtrConcurso, aux, aux_con);
	}
	
	
	
	printf("\nDigite a quantidade de numeros a serem apostados(max 10):");
	scanf("%d", &aux_qtd);
	
	while(aux_qtd>10)
		{
			printf("\nquantidade invalida!");
			printf("\nDigite a quantidade de numeros a serem apostados(max 10):");
			scanf("%d", &aux_qtd);	
		}
	
	while (strcmp(aux, "\0") != 0 && aux_con != 0 && aux_qtd != 0)
		{
			strcpy(AP.CPF, aux);
			AP.NumCurso = aux_con;
			AP.qtd_aposta = aux_qtd;
			for (i = 0; i < aux_qtd; i++)
			{
				repetido = 0;
				printf("\nDigite o %do numero apostado: ",i+1);
				scanf("%d",&aux_max_ap);
				
				// Verifica se o número já foi gerado antes
	            for (j = 0; j < i; j++) {
	                if (AP.NumApost[j] == aux_max_ap) {
	                    repetido = 1;
	                }
	            }
				
				while((aux_max_ap > 60 || aux_max_ap<=0) || (repetido == 1))
				{
					repetido = 0;
					printf("\nNumero invalido, fora do intervalo de 1 a 60 ou repetido");
					printf("\nDigite o %do numero apostado: ",i+1);
					scanf("%d",&aux_max_ap);
					
					// Verifica se o número já foi gerado antes
		            for (j = 0; j < i; j++) {
		                if (AP.NumApost[j] == aux_max_ap) {
		                    repetido = 1;
		                }
		            }
				}
				
				AP.NumApost[i] = aux_max_ap;
			}
			AP.status = 'A';
			fwrite(&AP, sizeof(TpAposta),1, PtrAposta);
			printf("\nRegistro Cadastrado!");
			Sleep(1000);
			
			printf("\n\nNovo Registro");
			RecebeASConcurso (PtrApostador, PtrConcurso, aux, aux_con);
			while(strcmp(aux, "\0") != 0 && aux_con != 0 && BusAposta_exaust(PtrAposta, aux, aux_con) >= 0 )
			{
				printf("\nEsse registro ja existe dentro das Apostas, cadastrar outro por favor")	;
				printf("\nDigite o CPF do Apostador: ");
				fflush(stdin);
				gets(aux);
				RecebeASConcurso (PtrApostador, PtrConcurso, aux, aux_con);
			}
			
			
			printf("\nDigite a quantidade de numeros a serem apostados:");
			scanf("%d", &aux_qtd);
			
			while(aux_qtd>10)
			{
				printf("\nquantidade invalida!");
				printf("\nDigite a quantidade de numeros a serem apostados(max 10):");
				scanf("%d", &aux_qtd);	
			}
		}
		fclose(PtrApostador);
		fclose(PtrConcurso);
		fclose(PtrAposta);
	
}
int BusAposta_exaust(FILE *PtrAposta, char auxCPF[10], int auxnum)
{
	TpAposta Ap;
	int achou_apostador=0;
	fseek(PtrAposta,0,SEEK_SET);
	
	fread(&Ap,sizeof(TpAposta),1,PtrAposta);
	
	while(!feof(PtrAposta) && (!(strcmp(Ap.CPF,auxCPF)==0 && Ap.NumCurso == auxnum && Ap.status == 'A'))){
		fread(&Ap,sizeof(TpAposta),1,PtrAposta);
	}
	
	if(!feof(PtrAposta)){
		return ftell(PtrAposta) - sizeof(TpAposta);
	}
	else{
		return -1;
	}

}

int BusNumSorteio(FILE *PtrConcurso, int num)
{
	int i=0, j, pos;
	TpConcurso C;

	rewind(PtrConcurso);
	fread(&C, sizeof(TpConcurso), 1, PtrConcurso);
	while (!feof(PtrConcurso) && pos == TFNS)
		{
			pos =0;
			for(j =0;j < TFNS && C.NumSort[j] != num; j++)
				pos++;
			fread(&C, sizeof(TpConcurso), 1, PtrConcurso);	
		}
		
	if (pos != TFNS)
		return ftell(PtrConcurso) - sizeof(TpConcurso)*2;
	else
		return i;
}

int BusNumAposta(FILE * PtrAposta, int num)
{
	int i=0, j, pos, apostas=TFNA;
	TpAposta AP;
	
	rewind(PtrAposta);
	fread(&AP, sizeof(TpAposta), 1, PtrAposta);
	while (!feof(PtrAposta) && pos == AP.qtd_aposta)
		{
			pos =0;
			for(j =0;j < AP.qtd_aposta && AP.NumApost[j] != num; j++)
				pos++;
			fread(&AP, sizeof(TpAposta), 1, PtrAposta);	
		}
		
	if (pos != AP.qtd_aposta)
		return ftell(PtrAposta) - sizeof(TpAposta)*2;
	else
		return i;
}

void BusAposta()
{
	int auxi, achou=0, i;
	char aux[TFNM];
	TpAposta AP;
	FILE *PtrAposta = fopen("Apostas.dat", "rb");
	FILE *PtrApostador = fopen("Apostadores.dat", "rb");
	FILE *PtrConcurso = fopen("Concursos.dat", "rb");
	
	system("cls");
	
	if (PtrAposta == NULL)
	{
		printf("\nNenhuma Aposta registrada");
		Sleep(2000);
	}
	else
	{
		printf("### BUSCA de APOSTA ###");
     	RecebeASConcurso (PtrApostador, PtrConcurso, aux, auxi);
	
		//Devo colocar um IF aqui para caso Concurso seja 0? Para parar a exec aqui?
		
		while(auxi != 0 && strcmp(aux, "\0") != 0)
		{
			achou = BusAposta_exaust(PtrAposta, aux, auxi);
			if (achou != -1)
			{
				fseek(PtrAposta, achou, SEEK_SET);
				fread(&AP, sizeof(TpAposta), 1, PtrAposta);				
				
				printf("\nRegistro existe! Esta na posicao: %d", (achou+1+sizeof(TpAposta))/sizeof(TpAposta));
				printf("\nCPF: %s", AP.CPF);
				printf("\nNumero do Concurso: %d", AP.NumCurso);
				printf("\nNumeros apostados: ");
				for (i = 0; i<AP.qtd_aposta-1; i++)
					printf(" %d,", AP.NumApost[i]);
				printf(" %d\n", AP.NumApost[i]);
				
				Sleep(3000);
			}
			else
			{
				printf("Registro nao existe!");
				Sleep(3000);
			}
				
			RecebeASConcurso (PtrApostador, PtrConcurso, aux, auxi);		
		}
	}
	fclose(PtrApostador);
	fclose(PtrConcurso);
	fclose(PtrAposta);
}

void AltAposta()
{
	int i, auxi, achou=0, aux_max_ap, j, repetido;
	char aux[TFNM], opcao;
	TpAposta AP;
	FILE *PtrAposta= fopen("Apostas.dat","rb+");
	FILE *PtrApostador = fopen("Apostadores.dat", "rb");
	FILE *PtrConcurso = fopen("Concursos.dat", "rb");
	system("cls");
	
	if (PtrAposta == NULL)
	{
		printf("\nNenhuma Aposta registrada");
		Sleep(2000);
	}
	else
	{
		printf("### Alteracao de APOSTA ###");
		RecebeASConcurso (PtrApostador, PtrConcurso, aux, auxi);
		
		while(auxi != 0 && strcmp(aux, "\0") != 0)
		{
			achou = BusAposta_exaust(PtrAposta, aux, auxi);
			if (achou != -1)
			{
				fseek(PtrAposta, achou, SEEK_SET);
				fread(&AP, sizeof(TpAposta), 1, PtrAposta);				
				
				printf("\n\nCPF: %s", AP.CPF);
				printf("\nNumero do Concurso: %d", AP.NumCurso);
				printf("\n\n[A]Qtde de Numeros Apostados: %d", AP.qtd_aposta);
				printf("\n[B]Numeros Apostados: [");
				for (i =0; i<AP.qtd_aposta-1; i++)
					printf(" %d,", AP.NumApost[i]);
				printf(" %d]", AP.NumApost[AP.qtd_aposta-1]);
				printf("\n\nQual dos dados deseja Alterar?");
				opcao = toupper(getche());
				switch(opcao)
				{
					case 'A':printf("\n\n Digite a nova quantidade de numeros: ");
							 scanf("%d",&AP.qtd_aposta);
							 for (i = 0; i < AP.qtd_aposta; i++)
								{
									repetido = 0;
									printf("\nDigite o %do numero apostado: ",i+1);
									scanf("%d",&aux_max_ap);
									
									// Verifica se o número já foi gerado antes
						            for (j = 0; j < i; j++) {
						                if (AP.NumApost[j] == aux_max_ap) {
						                    repetido = 1;
						                }
						            }
									
									while((aux_max_ap > 60 || aux_max_ap<=0) || (repetido == 1))
									{
										repetido = 0;
										printf("\nNumero invalido, fora do intervalo de 1 a 60 ou repetido");
										printf("\nDigite o %do numero apostado: ",i+1);
										scanf("%d",&aux_max_ap);
										
										// Verifica se o número já foi gerado antes
							            for (j = 0; j < i; j++) {
							                if (AP.NumApost[j] == aux_max_ap) {
							                    repetido = 1;
							                }
							            }
									}
									
									AP.NumApost[i] = aux_max_ap;
									printf("Registro Alterado!");
								}
							 break;	
					
					case 'B':printf("\n\n Vamos digitar os numeros novamente!");
						     for (i = 0; i < AP.qtd_aposta; i++)
								{
									repetido = 0;
									printf("\nDigite o %do numero apostado: ",i+1);
									scanf("%d",&aux_max_ap);
									
									// Verifica se o número já foi gerado antes
						            for (j = 0; j < i; j++) {
						                if (AP.NumApost[j] == aux_max_ap) {
						                    repetido = 1;
						                }
						            }
									
									while((aux_max_ap > 60 || aux_max_ap<=0) || (repetido == 1))
									{
										repetido = 0;
										printf("\nNumero invalido, fora do intervalo de 1 a 60 ou repetido");
										printf("\nDigite o %do numero apostado: ",i+1);
										scanf("%d",&aux_max_ap);
										
										// Verifica se o número já foi gerado antes
							            for (j = 0; j < i; j++) {
							                if (AP.NumApost[j] == aux_max_ap) {
							                    repetido = 1;
							                }
							            }
									}
									
									AP.NumApost[i] = aux_max_ap;
									printf("Registro Alterado!");
								}
							 break;	
					
				}
				
				
			}
			else
			{
				printf("Registro nao existe!");
				Sleep(3000);
			}
			
			
			Sleep(2000);
			RecebeASConcurso (PtrApostador, PtrConcurso, aux, auxi);
		}		
	}	
	fclose(PtrAposta);
	fclose(PtrApostador);
	fclose(PtrConcurso);
}
void ExAposta_logico()
{
	int i, auxi, achou=0;
	char aux[TFNM], opcao;
	TpAposta AP;
	FILE *PtrAposta = fopen("Apostas.dat", "rb+");
	FILE *PtrApostador = fopen("Apostadores.dat", "rb");
	FILE *PtrConcurso = fopen("Concursos.dat", "rb");
	
	system("cls");
	
	if (PtrAposta == NULL)
	{
		printf("\nNenhuma Aposta registrada");
		Sleep(2000);
	}
	else
	{
		printf("### Exclusao de APOSTA ###");
		RecebeASConcurso (PtrApostador, PtrConcurso, aux, auxi);
		
		//Devo colocar um IF aqui para caso Concurso seja 0? Para parar a exec aqui?
		
		while(auxi != 0 && strcmp(aux, "\0") != 0)
		{
			achou = BusAposta_exaust(PtrAposta, aux, auxi);
			if (achou != -1)
			{
				fseek(PtrAposta, achou, SEEK_SET);
				fread(&AP, sizeof(TpAposta), 1, PtrAposta);				
				
				printf("\n\nCPF: %s", AP.CPF);
				printf("\nNumero do Concurso: %d", AP.NumCurso);
				printf("\nQtde de Numeros Apostados: %d", AP.qtd_aposta);
				printf("\nNumeros Apostados: [");
				for (i =0; i<AP.qtd_aposta-1; i++)
					printf(" %d,", AP.NumApost[i]);
				printf(" %d]", AP.NumApost[AP.qtd_aposta-1]);
				printf("\n\nDeseja excluir esse registro?(S/N)");
				opcao = toupper(getche());
				switch(opcao)
				{
					case 'S': 
							  AP.status = 'I';
							  fseek(PtrAposta, achou, SEEK_SET);
							  fwrite(&AP, sizeof(TpAposta), 1, PtrAposta);
							 printf("\n Registro Excluido!");
							 
							 break;	
					
					case 'N':printf("\nRegistro mantido");
							 break;	
					
				}
				
			}
			else
			{
				printf("Registro nao existe!");
			}
			
			printf("\n\nNovo registro a ser excluido");
			RecebeASConcurso (PtrApostador, PtrConcurso, aux, auxi);
				
		}
	}
	fclose(PtrApostador);
	fclose(PtrConcurso);
	fclose(PtrAposta);
}

void ExAposta_fisico()
{
	FILE *PtrAposta = fopen("Apostas.dat", "rb");
	FILE *PtrTemp = fopen("Temporario.dat","wb");
	TpAposta AP;
	rewind(PtrAposta);  // fseek(PtrVeic,0,0);
	fread(&AP,sizeof(TpAposta),1,PtrAposta);
	while(!feof(PtrAposta))
	{						
		if (AP.status == 'A')
			fwrite(&AP,sizeof(TpAposta),1,PtrTemp);
		
		fread(&AP,sizeof(TpAposta),1,PtrAposta);	
	}
	fclose(PtrTemp);
	fclose(PtrAposta);
	remove("Apostas.dat");
	rename("Temporario.dat","Apostas.dat");
	getch();
}


void RelEspec()
{
	int i, j, k, pos, num_curso, num_acerto, qtd_acerto, acertou, ngm;
	FILE *PtrAposta = fopen("Apostas.dat", "rb");
	FILE *PtrApostador = fopen("Apostadores.dat", "rb");
	FILE *PtrConcurso = fopen("Concursos.dat", "rb");
	TpAposta AP;
	TpConcurso C;
	TpApostadores Apostadores;
	
	system("cls");
	if (PtrAposta == NULL || PtrApostador == NULL || PtrConcurso == NULL)
	{
		printf("Nao ha dados suficientes para a busca, verifique os cadastros");
		Sleep(2000);
	}
	else
	{
		system("cls");
		printf(" ### Relatorio de Acertos Especifico ###");
		printf("\n\nDigite o Numero do Concurso que deseja consultar: ");
		scanf("%d", &num_curso);
		
		while(num_curso != 0 && VeriNum(PtrConcurso, num_curso) == -1)
		{
			printf("\nNao existe esse concurso!");
			printf("\n\nDigite o Numero do Concurso que deseja consultar: ");
			scanf("%d", &num_curso);
		}
		
		printf("\nDigite agora a quantidade de numeros acertados: ");
		scanf("%d", &num_acerto);
		while(num_acerto > 5)
		{
			printf("\nNao e possivel acerta mais de 5 numeros em um concurso");
			printf("\nDigite agora a quantidade de numeros acertados: ");
			scanf("%d", &num_acerto);
		}
		
		while(num_curso !=0 && num_acerto!=0)
		{	ngm = 1;
			rewind(PtrAposta);
			fread(&AP, sizeof(TpAposta), 1, PtrAposta);
			while (!feof(PtrAposta))
			{
				if (AP.status == 'A')
				{
					acertou = 0;
					if(AP.NumCurso == num_curso)
						{ qtd_acerto = 0;
						 for (j=0; j<AP.qtd_aposta && qtd_acerto != num_acerto && acertou == 0;j++)
							{
								pos = 0;
								fseek(PtrConcurso, VeriNum(PtrConcurso, num_curso), SEEK_SET);
								fread(&C, sizeof(TpConcurso), 1, PtrConcurso);
								for(k = 0; k<TFNS && C.NumSort[k] != AP.NumApost[j]; k++)
									pos++;
								if(pos < TFNS)
									qtd_acerto++;
								
							}
							if (qtd_acerto == num_acerto)
								{
									acertou = 1;
									fseek(PtrApostador, BuscarCPF(PtrApostador, AP.CPF), SEEK_SET);
									fread(&Apostadores, sizeof(TpApostadores), 1, PtrApostador);
									printf("\nO %s acertou %d numeros do %do concurso",Apostadores.Nome, num_acerto, num_curso);
									Sleep(2000);
									ngm = 0;
								}		
						}	
				}
				
			}
			if (ngm ==1)
				printf("Ninguem acertou %d numeros no %do concurso", num_acerto, num_curso);
			getch();
			printf("\n\nDigite o Numero do proximo Concurso que deseja consultar: ");
			scanf("%d", &num_curso);
			
			while(num_curso != 0 && VeriNum(PtrConcurso, num_curso) == -1)
			{
				printf("\nNao existe esse concurso!");
				printf("\n\nDigite o Numero do Concurso que deseja consultar: ");
				scanf("%d", &num_curso);
			}
			
			printf("\nDigite agora a quantidade de numeros acertados: ");
			scanf("%d", &num_acerto);
		}
		
		fclose(PtrAposta);
		fclose(PtrApostador);
		fclose(PtrConcurso);	
	}
	
		
}

void MaisMenoSorteio()
{
	int i, j, k, num, cont, achou;
	FILE *PtrConcurso = fopen("Concursos.dat", "rb");
	TpConcurso Con;
	char opcao;
	
	if(PtrConcurso == NULL)
	{
		printf("\nNao ha registros");
		Sleep(1000);
	}
	else
	{
		system("cls");
		printf(" ### Mais ou Menos aparicoes em Sorteios ###");
		printf("\n\nQual voce deseja visualizar, os que mais aparecem o os que menos aparecem?(+/-)");
		fflush(stdin);
		opcao = getche();
		
		if (opcao == 43) // mais
			{ achou = 0;
			  for (i=0; i<60;i++)
			  	{
			  		cont = 0;	
		  			rewind(PtrConcurso);
		  			fread(&Con, sizeof(TpConcurso), 1, PtrConcurso);
		  			while (!feof(PtrConcurso))
		  				{
		  					if (Con.status == 'A')
		  					{
		  						for(k = 0; k<TFNS; k++)
				  					if(i == Con.NumSort[k])
				  						cont++;	
		  					}
							fread(&Con, sizeof(TpConcurso),1,PtrConcurso);	
		  				}
		  		
				  		
					if(cont > 1)
					{
						printf("\nO numero %d e um dos mais encontrados, aparecendo %d vezes", i,cont);	
						Sleep(1000);	
						achou =1;
					}
						
			  	}
			  if (achou == 0)
			  	{
			  	  printf("\nNenhum regitro aparece mais de uma vez");
			  	  Sleep(1000);	
			  	}
			}
		else
			if(opcao == 45) // menos
			{
				achou = 0;
			  for (i=0; i<60;i++)
			  	{
			  		cont = 0;
			  		if (BusNumSorteio(PtrConcurso, i) != -1)
			  		{
			  				rewind(PtrConcurso);
				  			fread(&Con, sizeof(TpConcurso), 1, PtrConcurso);
				  			while (!feof(PtrConcurso))
				  				{
				  						if (Con.status == 'A')
					  					{
					  						for(k = 0; k<TFNS; k++)
							  					if(i == Con.NumSort[k])
							  						cont++;	
					  					}
									fread(&Con, sizeof(TpConcurso),1,PtrConcurso);
		  						}
					  	if(cont <2)
						{
							printf("\nO numero %d e um dos menos encontrados, aparecendo uma unica vez", i);	
							Sleep(1000);
							achou =1;
						}
			  		}		
			  	}
			  if (achou == 0)
			  	{
			  	  printf("\nNenhum regitro aparece menos de uma vez");
			  	  Sleep(1000);	
			  	}	
			}
			else
				{
					printf("\nopcao Invalida");
					Sleep(1000);
				}
			getch();
			fclose(PtrConcurso);	
	}
	
	
}

void MaisMenoAposta()
{
	int i, j, k, num, cont, achou;
	char opcao;
	FILE *PtrAposta = fopen("Apostas.dat", "rb");
	TpAposta AP;
	
	if(PtrAposta == NULL)
	{
		printf("\nNao ha registros");
		Sleep(1000);
	}
	else
	{
		system("cls");
		printf(" ### Mais ou Menos aparicoes em Apostas ###");
		printf("\n\nQual voce deseja visualizar, os que mais aparecem o os que menos aparecem?(+/-)");
		fflush(stdin);
		opcao = getche();
		
		if (opcao == 43) // mais
			{ achou = 0;
			  for (i=0; i<60;i++)
			  	{
			  		cont = 0;
			  		rewind(PtrAposta);
			  		fread(&AP, sizeof(TpAposta), 1, PtrAposta);
			  		while (!feof(PtrAposta))
			  		{
			  			if (AP.status == 'A')
			  			{
		  					for(k = 0; k<AP.qtd_aposta; k++)
				  				if(i == AP.NumApost[k])
				  					cont++;	
			  			}
					  	fread(&AP, sizeof(TpAposta), 1, PtrAposta);
			  		}
				  		
					if(cont > 1)
					{
						printf("\nO numero %d e um dos mais encontrados, aparecendo %d vezes", i, cont);	
						Sleep(1000);	
						achou =1;
					}
						
			  	}
			  if (achou == 0)
			  	{
			  	  printf("\nNenhum regitro aparece mais de uma vez");
			  	  Sleep(1000);	
			  	}
			}
		else
			if(opcao == 45) // menos
			{
				achou = 0;
			  for (i=0; i<60;i++)
			  	{
			  		cont = 0;
			  		if (BusNumAposta(PtrAposta, i) != -1)
			  		{
			  			rewind(PtrAposta);
				  		fread(&AP, sizeof(TpAposta), 1, PtrAposta);
				  		while (!feof(PtrAposta))
				  		{
				  				if (AP.status == 'A')
					  			{
				  					for(k = 0; k<AP.qtd_aposta; k++)
						  				if(i == AP.NumApost[k])
						  					cont++;	
					  			}
						  	fread(&AP, sizeof(TpAposta), 1, PtrAposta);
				  		}	
					  	if(cont <2)
						{
							printf("\nO numero %d e um dos menos encontrados, aparecendo uma unica vez", i);
							Sleep(1000);	
							achou =1;
						}
			  		}		
			  	}
			  if (achou == 0)
			  	{
			  	  printf("\nNenhum regitro aparece menos de uma vez");
			  	  Sleep(1000);	
			  	}	
			}
			else
				{
					printf("\nopcao Invalida");
					Sleep(1000);
				}
			getch();
			fclose(PtrAposta);	
	}
	
	
}

void InsereTeste()
{
	TpAposta C;
	TpConcurso Con;
	TpApostadores AS;
	FILE *PtrAposta = fopen("Apostas.dat", "ab");
	FILE *PtrApostador = fopen("Apostadores.dat", "ab");
	FILE *PtrConcurso = fopen("Concursos.dat", "ab");
	strcpy(C.CPF, "5555");
	C.NumCurso = 1;
	C.qtd_aposta = 5;
	C.NumApost[0] = 50;
	C.NumApost[1] = 0;
	C.NumApost[2] = 3;
	C.NumApost[3] = 28;
	C.NumApost[4] = 36;
	C.status = 'A';
	fwrite(&C, sizeof(TpAposta), 1, PtrAposta);
	
	strcpy(C.CPF, "5555");
	C.NumCurso = 3;
	C.qtd_aposta = 5;
	C.NumApost[0] = 2;
	C.NumApost[1] = 28;
	C.NumApost[2] = 3;
	C.NumApost[3] = 4;
	C.NumApost[4] = 5;
	C.status = 'A';
	fwrite(&C, sizeof(TpAposta), 1, PtrAposta);
	
	strcpy(C.CPF, "22");
	C.NumCurso = 1;
	C.qtd_aposta = 5;
	C.NumApost[0] = 50;
	C.NumApost[1] = 0;
	C.NumApost[2] = 3;
	C.NumApost[3] = 28;
	C.NumApost[4] = 36;
	C.status = 'A';
	fwrite(&C, sizeof(TpAposta), 1, PtrAposta);
	
	strcpy(C.CPF, "22");
	C.NumCurso = 2;
	C.qtd_aposta = 5;
	C.NumApost[0] = 2;
	C.NumApost[1] = 1;
	C.NumApost[2] = 3;
	C.NumApost[3] = 4;
	C.NumApost[4] = 9;
	C.status = 'A';
	fwrite(&C, sizeof(TpAposta), 1, PtrAposta);
	
	strcpy(C.CPF, "22");
	C.NumCurso = 3;
	C.qtd_aposta = 5;
	C.NumApost[0] = 2;
	C.NumApost[1] = 28;
	C.NumApost[2] = 3;
	C.NumApost[3] = 4;
	C.NumApost[4] = 5;
	C.status = 'A';
	fwrite(&C, sizeof(TpAposta), 1, PtrAposta);
	
	
	strcpy(AS.CPF, "5555");
	strcpy(AS.Nome, "Teste");
	AS.DDD = 18;
	AS.NumTel = 191;
	AS.status = 'A';
	fwrite(&AS, sizeof(TpApostadores), 1, PtrApostador);
	
	strcpy(AS.CPF, "22");
	strcpy(AS.Nome, "Josias");
	AS.DDD = 18;
	AS.NumTel = 191;
	AS.status = 'A';
	fwrite(&AS, sizeof(TpApostadores), 1, PtrApostador);
	
	
	Con.NumCurso = 1;
	Con.NumSort[0] = 50;
	Con.NumSort[1] = 0;
	Con.NumSort[2] = 3;
	Con.NumSort[3] = 4;
	Con.NumSort[4] = 5;
	Con.status = 'A';
	strcpy(Con.data, "12/12/2024");
	fwrite(&Con, sizeof(TpConcurso), 1, PtrConcurso);
	
	Con.NumCurso = 2;
	Con.NumSort[0] = 1;
	Con.NumSort[1] = 2;
	Con.NumSort[2] = 3;
	Con.NumSort[3] = 4;
	Con.NumSort[4] = 5;
	Con.status = 'A';
	strcpy(Con.data, "12/12/2024");
	fwrite(&Con, sizeof(TpConcurso), 1, PtrConcurso);
	
	Con.NumCurso = 3;
	Con.NumSort[0] = 28;
	Con.NumSort[1] = 2;
	Con.NumSort[2] = 3;
	Con.NumSort[3] = 4;
	Con.NumSort[4] = 5;
	Con.status = 'A';
	strcpy(Con.data, "12/12/2024");
	fwrite(&Con, sizeof(TpConcurso), 1, PtrConcurso);
	
	fclose(PtrConcurso);
	fclose(PtrAposta);
	fclose(PtrApostador);
}



void CadApostador(){
	TpApostadores Apostador;
	int posi;
	
	FILE *PtrApostador = fopen("Apostadores.dat", "ab+");
	system("cls");
	
		//Moldura-----------------------------------------------
       	int largura = 60, altura = 20;
	    int x = 35;
		int y = 3;
	    Moldura(x, y, largura, altura);
		//-----------------------------------------------------
	gotoxy(x + 15, y + 1);	
	printf("*** Cadastrar Apostador ***");
	gotoxy(x + 2, y + 3);	
	printf("Digite o CPF do Apostador: "); fflush(stdin); 
	gets(Apostador.CPF);
	
	while(strcmp(Apostador.CPF,"\0")!=0){
		posi = BuscarCPF(PtrApostador,Apostador.CPF);	
		if(posi == -1){
			gotoxy(x + 2, y + 4);	
			printf("Digite o Nome do apostador: "); fflush(stdin);
			gets(Apostador.Nome);
			gotoxy(x + 2, y + 5);	
			printf("DIgite o DDD: ");scanf("%d", &Apostador.DDD);
			gotoxy(x + 2, y + 6);	
			printf("Digite o Numero de Telefone(apenas numeros): ");
			scanf("%d", &Apostador.NumTel);
			Apostador.status = 'A';
			fwrite(&Apostador,sizeof(TpApostadores),1,PtrApostador);
			gotoxy(x + 2, y + 8);
			printf("Apostador cadastrado com sucesso!!");
		}
		else{
			gotoxy(x + 2, y + 5);	
			printf("CPF ja Cadastrado!!!");
		}
		
		Sleep(1000);
		
		system("cls");
	
		//Moldura-----------------------------------------------
	    Moldura(x, y, largura, altura);
		//-----------------------------------------------------
		gotoxy(x + 15, y + 1);	
		printf("*** Cadastrar APostador ***");
		gotoxy(x + 2, y + 3);
		printf("Digite o CPF do Apostador: "); fflush(stdin);
		gets(Apostador.CPF);
		
	}
	fclose(PtrApostador);
	
}


// Função para verificar se o CPF já existe
int BuscarCPF(FILE *PtrApostador, char auxCPF[10]){
	TpApostadores Apostador;
	fseek(PtrApostador,0,SEEK_SET);
	
	fread(&Apostador,sizeof(TpApostadores),1,PtrApostador);
	
	while(!feof(PtrApostador) && !(strcmp(Apostador.CPF,auxCPF)==0 && Apostador.status == 'A')){
		fread(&Apostador,sizeof(TpApostadores),1,PtrApostador);
	}
	
	if(!feof(PtrApostador)){
		return ftell(PtrApostador) - sizeof(TpApostadores);
	}
	else{
		return -1;
	}

}


void BuscarApostadores(){
	TpApostadores Apostador;
	FILE *PtrApostador = fopen("Apostadores.dat", "rb");
	int desl;
	system("cls");
	
		//Moldura-----------------------------------------------
       	int largura = 60, altura = 20;
	    int x = 35;
		int y = 3;
	    Moldura(x, y, largura, altura);
		//-----------------------------------------------------
	
	gotoxy(x + 12, y + 1);	
	printf("*** Consultar Apostador pelo CPF ***");
	if(PtrApostador == NULL){
		gotoxy(x + 2, y + 3);
		printf("Erro de Abertura!");
		getch();
	}
	else{
		gotoxy(x + 2, y + 3);
		printf("CPF a consultar: "); fflush(stdin);
		gets(Apostador.CPF);
		while(strcmp(Apostador.CPF,"\0")!=0){
			desl = BuscarCPF(PtrApostador,Apostador.CPF);
			if(desl == -1){
				gotoxy(x + 2, y + 5);
				printf("CPF nao encontrado!!");
			}
			else{
				gotoxy(x + 2, y + 5);
				printf("*** Detalhes do Apostador ***");
				fseek(PtrApostador,desl,SEEK_SET);
				fread(&Apostador,sizeof(TpApostadores),1,PtrApostador);
				gotoxy(x + 2, y + 7);
				printf("CPF: %s\n", Apostador.CPF);
				gotoxy(x + 2, y + 8);
				printf("Nome: %s\n", Apostador.Nome);
				gotoxy(x + 2, y + 9);
				printf("Telefone: (%d)%d\n", Apostador.DDD, Apostador.NumTel);
	
			}
			getch();
			
			system("cls");
			Moldura(x, y, largura, altura);
			gotoxy(x + 15, y + 1);	
			printf("*** Consultar Apostador pelo CPF ***");
			gotoxy(x + 2, y + 3);
			printf("CPF a consultar: ");fflush(stdin);
			gets(Apostador.CPF);
		}
		
		fclose(PtrApostador);
		
	}

}

void AlterarDadosApostador(){
	TpApostadores Apostador;
	char AuxCPF[10];
	int encont=0;
	
	FILE *PtrApostador = fopen("Apostadores.dat","rb+");
	
	system("cls");
	
		//Moldura-----------------------------------------------
       	int largura = 60, altura = 20;
	    int x = 35;
		int y = 3;
	    Moldura(x, y, largura, altura);
		//-----------------------------------------------------
	
	gotoxy(x + 17, y + 1);
	printf("*** ALterar Dados ***");
	
	if(PtrApostador == NULL){
		gotoxy(x + 2, y + 3);
		printf("Erro de Abertura!");
		getch();
	}
	else{
		
		gotoxy(x + 2, y + 3);
		printf("Digite o CPF do Apostador que deseja Alterar: "); fflush(stdin);
		gets(AuxCPF);
		
		while(fread(&Apostador,sizeof(TpApostadores),1,PtrApostador) == 1){
			if(strcmp(Apostador.CPF,AuxCPF)==0){
				encont = 1;
				int desl = ftell(PtrApostador) - sizeof(TpApostadores);
				
				int opcao;
				gotoxy(x + 2, y + 5);
				printf("Apostador encontado!!");
				gotoxy(x + 2, y + 7);
				printf("CPF: %s ",Apostador.CPF);
				gotoxy(x + 2, y + 8);
				printf("Nome: %s ",Apostador.Nome);
				gotoxy(x + 2, y + 9);
				printf("Telefone: (%d)%d",Apostador.DDD, Apostador.NumTel); 
			
				
				do{
					gotoxy(x + 2, y + 11);
					printf("O que deseja Alterar?");
					gotoxy(x + 2, y + 12);
					printf("1 - Nome");
					gotoxy(x + 2, y + 13);
					printf("2 - Telefone");
					gotoxy(x + 2, y + 14);
					printf("0 - Sair");
					gotoxy(x + 2, y + 15);
					printf("Escolha: ");
					scanf("%d", &opcao);
					
					switch(opcao){
						case 1:
							system("cls");
							//Moldura-----------------------------------------------
						    Moldura(x, y, largura, altura);
							//-----------------------------------------------------
							
							gotoxy(x + 17, y + 1);
							printf("*** Alteração de Nome ***");
							gotoxy(x + 2, y + 3);
							printf("Novo Nome: ");fflush(stdin);
							gets(Apostador.Nome);
							break;
							
						case 2:
							system("cls");
							//Moldura-----------------------------------------------
						    Moldura(x, y, largura, altura);
							//-----------------------------------------------------
							
							gotoxy(x + 17, y + 1);
							printf("*** Alteração de Telefone ***\n");
							gotoxy(x + 2, y + 3);
							printf("Novo DDD: ");
							scanf("%d", &Apostador.DDD);
							gotoxy(x + 2, y + 4);
							printf("Novo Telefone(apenas numeros): ");
							scanf("%d", &Apostador.NumTel);
							break;
							
						case 0:
							gotoxy(x + 2, y + 17);
							printf("Alteracoes Finalizadas!!");
							break;
						default:
							gotoxy(x + 2, y + 17);
							printf("Opcao Invalida!!\n");
							break;
					}
				}while(opcao != 0);
				
				fseek(PtrApostador,desl,SEEK_SET);
				fwrite(&Apostador,sizeof(TpApostadores),1,PtrApostador);
				gotoxy(x + 2, y + 18);
				printf("--Registro Realizado com Sucesso!!--");
				break;
			}
		}
		
		if(!encont){
			gotoxy(x + 2, y + 5);
			printf("CPF nao Encontrado!\n");
		}
		
		fclose(PtrApostador);
	}
	getch();
	
	
}

void ExclusaoLogica_Apostador(){
	FILE *PtrApostador = fopen("Apostadores.dat","rb+");
	TpApostadores Apostador;
	FILE *PtrConcurso = fopen("Concursos.dat","rb");
	TpConcurso Concurso;
	FILE *PtrAposta = fopen("Apostas.dat", "rb");
	char AuxCPF[10];
	int desl, permite_exc;
	
	
	
	if(PtrApostador == NULL){
	
		printf("Erro de Abertura!");
	
	}
	else{
		system("cls"); printf("\n*** Excluir Apostador (Logica) ***\n");
		printf("\nDigite o CPF que deseja Excluir (Logicamente): "); fflush(stdin);
		gets(Apostador.CPF);
		
		while(strcmp(Apostador.CPF,"\0")!=0){
			
			desl = BuscarCPF(PtrApostador,Apostador.CPF);
			
			if(desl == -1){
				printf("\nCPF nao encontrado!!\n");
			}
			else{
				
				printf("\n*** Detalhes do Apostador ***\n");
				fseek(PtrApostador,desl,SEEK_SET);
				fread(&Apostador,sizeof(TpApostadores),1,PtrApostador);
				printf("\nCPF: %s\n", Apostador.CPF);
				printf("\nNome: %s\n",Apostador.Nome);
				printf("\nTelefone: (%d)%d", Apostador.DDD, Apostador.NumTel);
				printf("\nDeseja realizar a Exclusão(S/N)? ");
				if(toupper(getche())=='S'){
					
					permite_exc = -1;
					rewind(PtrConcurso);
					fread(&Concurso, sizeof(TpConcurso), 1, PtrConcurso);
					while (!feof(PtrConcurso) && permite_exc == -1)
					{
						permite_exc = BusAposta_exaust(PtrAposta, Apostador.CPF, Concurso.NumCurso);
						fread(&Concurso, sizeof(TpConcurso), 1, PtrConcurso);
					}
					
					if (permite_exc == -1)
					{
						Apostador.status = 'I';
						fseek(PtrApostador,desl,SEEK_SET);
						fwrite(&Apostador,sizeof(TpApostadores),1,PtrApostador);
					
						printf("\nApostador Excluido (Logicamente)!");
						
					}
					else
					{
						printf("\n Nao sera possivel realizar a exclusao!");
						printf("\n Registro correspondente em Apostas");
					}
						
					
				}			
			}
			Sleep(2000);
			
			printf("\nDigite o CPF que deseja Excluir (Logicamente): "); fflush(stdin);
			gets(Apostador.CPF);
		}
		fclose(PtrApostador);
		fclose(PtrConcurso);
		fclose(PtrAposta);
	}
	
}

void Exc_Fisi_Apostador()
{
	TpApostadores Apostador;
	FILE *PtrApostador = fopen("Apostadores.dat", "rb");
	char AuxCPF[10];
	int desl;
	system("cls");
	
		//Moldura-----------------------------------------------
       	int largura = 60, altura = 20;
	    int x = 35;
		int y = 3;	
	    Moldura(x, y, largura, altura);
		//-----------------------------------------------------
		
    
	gotoxy(x + 17, y + 1);
	printf("*** Excluir Apostador ***");
	if(PtrApostador == NULL){
		gotoxy(x + 2, y + 3);
		printf("Erro de Abertura!");
		getch();
	}
	else{
		
		gotoxy(x + 2, y + 4);
		printf("Digite o CPF: "); fflush(stdin);
		gets(AuxCPF);
		if(strcmp(Apostador.CPF,"\0")!=0){
			
			desl = BuscarCPF(PtrApostador,AuxCPF);
			
			if(desl == -1){
				gotoxy(x + 2, y + 4);
				printf("CPF nao encontrado!!\n");
				fclose(PtrApostador);
				getch();
			}
			else{
				gotoxy(x + 2, y + 7);
				printf("*** Detalhes do Apostador ***\n");
				fseek(PtrApostador,desl,SEEK_SET);
				fread(&Apostador,sizeof(TpApostadores),1,PtrApostador);
				gotoxy(x + 2, y + 8);
				printf("CPF: %s", Apostador.CPF);
				gotoxy(x + 2, y + 9);
				printf("Nome: %s", Apostador.Nome);
				gotoxy(x + 2, y + 10);
				printf("Telefone: (%d)%d", Apostador.DDD, Apostador.NumTel);
				gotoxy(x + 2, y + 13);
				printf("Confirma a Exclusao (S/N)? ");
				if (toupper(getche())=='S'){
					
					FILE *PtrTemp_Apostador = fopen("Temp_Apostadores.dat","wb");
					fseek(PtrApostador,0,SEEK_SET);
					fread(&Apostador,sizeof(TpApostadores),1,PtrApostador);
					while(!feof(PtrApostador)){
						
						if(strcmp(AuxCPF,Apostador.CPF)!=0){
							fwrite(&Apostador,sizeof(TpApostadores),1,PtrTemp_Apostador);
							
						}
							
							fread(&Apostador,sizeof(TpApostadores),1,PtrApostador);

		
					}
						fclose(PtrTemp_Apostador);
						fclose(PtrApostador);
						remove("Apostadores.dat");
						rename("Temp_Apostadores.dat","Apostadores.dat");
							
						printf("Apostadores excluidos!!!\n");
						getch();
				}
			}
		}
		else {
			fclose(PtrApostador);
		}
	}
}
		
//Funcao para exibir apostadores cadastrados
void ExibeApostadores() {
    FILE *PtrApostador = fopen("Apostadores.dat", "rb");
    TpApostadores Apostador;
    
    system("cls");

    int largura = 50, altura = 20;
    int x = 35;
	int y = 3;
    Moldura(x, y, largura, altura);


	int linha = y + 2;
    gotoxy(x + 10, linha++);
    printf("*** Relatorio de Apostadores ***");
		
    if (PtrApostador == NULL) {
        gotoxy(x + 2, y + 3);
		printf("Erro de Abertura!");
		getch();
    }

    linha++; // Espaço após o título

    while (fread(&Apostador, sizeof(TpApostadores), 1, PtrApostador) == 1) {
        if (Apostador.status == 'A') {

            // Verifica se a próxima exibição ultrapassará o limite da moldura
            if (linha + 5 >= y + altura - 1) {
                
                getch();

                system("cls");
                Moldura(x, y, largura, altura);
                linha = y + 2;

                gotoxy(x + 10, linha++);
                printf("*** Relatorio de Apostadores ***");
                linha++; // Espaço após o título
            }

            gotoxy(x + 2, linha++);
            printf("CPF: %s", Apostador.CPF);

            gotoxy(x + 2, linha++);
            printf("Nome: %s", Apostador.Nome);

            gotoxy(x + 2, linha++);
            printf("Telefone: (%d)%d", Apostador.DDD, Apostador.NumTel);

            gotoxy(x + 2, linha++);
            printf("-----------------------------------------------");

            linha++; // Linha em branco entre registros
        }
    }
        fclose(PtrApostador);
    
    getch();
}


int contar_acertos(int numsApost[], int qtd_aposta, int numsSort[], int Pos[5]){
    int acertos = 0;
    for (int i = 0; i < qtd_aposta; i++){
    	
        for (int j = 0; j < TFNS; j++){
        	
            if (numsApost[i] == numsSort[j]){
            	
                Pos[acertos++] = numsApost[i];
                if (acertos == 5){
                	
                	return acertos;
                }
            }
        }
    }
    return acertos;
}



void ExibeApostadoresPremiados() {
	FILE *PtrApostador = fopen("Apostadores.dat", "rb");
	FILE *PtrAposta = fopen("Apostas.dat", "rb");
	FILE *PtrConcurso = fopen("Concursos.dat", "rb");

	TpApostadores Apostador;
	TpAposta Aposta;
	TpConcurso Concurso;

	int acertos, Pos[TFNS];
	
	
	system("cls");

	int largura = 70, altura = 20;
	int x = 25;
	int y = 3;
	Moldura(x, y, largura, altura);
	
	int linha = y + 2;
	
	gotoxy(x + 17, linha++);
	printf("*** APOSTADORES PREMIADOS ***");

	if (PtrApostador == NULL || PtrAposta == NULL || PtrConcurso == NULL) {
		gotoxy(x + 2, y + 3);
		printf("Erro de Abertura!");
		getch();
	}
	

	rewind(PtrConcurso);
	while (fread(&Concurso, sizeof(TpConcurso), 1, PtrConcurso) == 1){
		if (Concurso.status == 'A') {

			if (linha + 10 >= y + altura - 2){
				getch();
				system("cls");
				Moldura(x, y, largura, altura);
				linha = y + 2;
				gotoxy(x + 17, linha++);
				printf("*** APOSTADORES PREMIADOS ***");
			}

			gotoxy(x + 2, linha++);
			printf("===================================================================");
			gotoxy(x + 2, linha++);
			printf("Concurso: %d - Data: %s", Concurso.NumCurso, Concurso.data);
			gotoxy(x + 2, linha++);
			printf("Numeros Sorteados: ");
			for (int i = 0; i < TFNS; i++) {
				printf("%d ", Concurso.NumSort[i]);
			}
			linha++;

			rewind(PtrAposta);
			while (fread(&Aposta, sizeof(TpAposta), 1, PtrAposta) == 1){
				if (Aposta.NumCurso == Concurso.NumCurso){
					
					acertos = contar_acertos(Aposta.NumApost, Aposta.qtd_aposta, Concurso.NumSort, Pos);
					
					if (acertos >= 3){
						
						rewind(PtrApostador);
						
						int premiado_exibido = 0;

						while (fread(&Apostador, sizeof(TpApostadores), 1, PtrApostador) == 1 && !premiado_exibido){
							if (strcmp(Aposta.CPF, Apostador.CPF) == 0 && Apostador.status == 'A') {

								if (linha + 4 >= y + altura - 2){
								
									getch();

									system("cls");
									
									Moldura(x, y, largura, altura);
									linha = y + 2;
									gotoxy(x + 17, linha++);
									printf("*** APOSTADORES PREMIADOS ***");
								}

								gotoxy(x + 2, linha++);
								printf("Premiado: %s (%s)", Apostador.Nome, Apostador.CPF);
								gotoxy(x + 2, linha++);
								printf("Acertos: %d - Numeros Acertados: ", acertos);
								for (int i = 0; i < acertos; i++) {
									printf("%d ", Pos[i]);
								}
								linha++;
								premiado_exibido = 1;
							}
						}
					}
				}
			}
			linha++;
		}
	}

	fclose(PtrApostador);
	fclose(PtrAposta);
	fclose(PtrConcurso);


	getch();
}



	

void CADCOncurso()
{
	int i, posi;
	char resp;
	TpConcurso Concurso;
	FILE *PtrConcurso = fopen("Concursos.dat", "ab+");
	system("cls"); printf("\n*** Cadastrar Concurso ***\n");
	printf("\nDigite o Numero do Concurso: \n"); 
	scanf("%d",&Concurso.NumCurso);
	
	while(Concurso.NumCurso!=0){
		posi = VeriNum(PtrConcurso,Concurso.NumCurso);	
		if(posi == -1){
			printf("\nDigite a Data da Realizacao: \n"); 
			fflush(stdin);
			gets(Concurso.data);
			printf("\n\n***Numeros Sorteados***\n");
			Sotnum(Concurso.NumSort);
			Concurso.status = 'A';
			fwrite(&Concurso,sizeof(TpConcurso),1,PtrConcurso);
			
		}
		else{
			printf("\n Concurso ja Cadastrado!!!\n");
		}
		
		Sleep(1000);
		
		printf("\nDigite o Numero do Concurso: \n"); 
		scanf("%d",&Concurso.NumCurso);
		
	}
	fclose(PtrConcurso);
}

int VeriNum(FILE *PtrConcurso , int AuxBus)
{
	TpConcurso Concurso;
	fseek(PtrConcurso,0,SEEK_SET);
	
	fread(&Concurso,sizeof(TpConcurso),1,PtrConcurso);
	
	while(!feof(PtrConcurso) && !(Concurso.NumCurso == AuxBus && Concurso.status == 'A')){
		fread(&Concurso,sizeof(TpConcurso),1,PtrConcurso);
	}
	
	if(!feof(PtrConcurso)){
		return ftell(PtrConcurso) - sizeof(TpConcurso);
	}
	else{
		return -1;
	}

	
}
void Sotnum(int Num[5]) {
    int i, j, Nuns;
    
    for (i = 0; i < 5; i++) {
        do {
            Nuns = (rand() % 60)+1; // Gera um número aleatório entre 0 e 60
            int repetido = 0;

            // Verifica se o número já foi gerado antes
            for (j = 0; j < i; j++) {
                if (Num[j] == Nuns) {
                    repetido = 1;
                    break;
                }
            }

            // Se for repetido, gera outro número
            if (!repetido) {
                Num[i] = Nuns;
                break;
            }
        } while (1);
    }
    
        printf("Numeros sorteados: ");
    	for (int i = 0; i < 5; i++) 
		{
        printf("\n%d ", Num[i]);
        
    }
    
    getchar();
}


void relatorioConcurso(TpConcurso Concurso[TFB], int TLC)
 {
    system("cls");
    for (int i = 0; i < TLC; i++) 
	{
        printf("\n############################\n");
        printf("Num: %d\n", Concurso[i].NumCurso);
        printf("Data: %s\n", Concurso[i].data);
        printf("Numeros sorteados: ");
        for (int j = 0; j < TFNS; j++)
		 {
            printf("%d ", Concurso[i].NumSort[j]);
        }
        printf("\n############################\n");
        getchar();
    }
}

void AltNum(TpConcurso Concurso[TFB], int TLC)
{
	int i, AuxBus, numeros[5], verifica;
	char resp, opcao, NovData[12];
	
	system("cls");
	/*
	do
	{
		do
		{
			printf("\n### Auteracao do Comcurso ###");
			printf("\nNumero do Concurso: \n");
			scanf("%d", &AuxBus);
			
			verifica = VeriNum(Concurso, TLC, AuxBus);
			
			if(verifica == -1)
			{
				printf("\nConcurso nao Cadastrado!!");
				getchar();
			}
		
		}while(verifica == -1);

				system("cls");
				printf("\n### MENU DE ALTERACAO ###\n");
				printf("\n[A] Alterar Data");
				printf("\n[B] Alterar Numeros Sorteados\n");
				opcao = toupper(getche());
			    switch(opcao)
				{
					case 'A':
						printf("\nDigite a Nova Data de Realizacao: \n"); 
						fflush(stdin);
						gets(NovData);
						strcpy(Concurso[verifica].data, NovData);
														break;
					case 'B':
						int num = Sotnum(Concurso[TLC].NumSort);
					   	  					break;	
				}	
			 	
			 		
			
			printf("\nQuer Cadastrar Mais Um concurso? [S-Sim | N-Nao] \n");
			resp = toupper(getche());
			getchar();
			system("cls");
			
	  
	}while(resp == 'S');*/
}

void ExConc(TpConcurso Concurso[TFB], int &TLC, TpAposta C[TFB*TFB], int TLAP)
{
	int AuxBus, verifica, j, i;
	char resp;

	system("cls");
    /*
	do
	{
		do
		{
				printf("\n### Exclusao de Concurso ###");
				printf("\nNumero do Concurso Para Exclusão: ");
				scanf("%d", &AuxBus);
				
				verifica = VeriNum(Concurso, TLC, AuxBus);
			
					if(verifica == -1)
					{
						printf("\nConcurso nao Cadastrado!!");
						getchar();
					}
					
				j = 0;
				while(j<TLAP && C[j].NumCurso != AuxBus)
					j++;
					
				if (j < TLAP)
					{
						printf("Esse registro existe dentro das apostas, nao sera possivel exlcuir");
						Sleep(1000);
						return;
					}
				
		}while(verifica == -1 || j<TLAP);
		
			system("cls");
			printf("\n### Dados Encontrados ###\n");
			printf("\nData do Concurso: %s", Concurso[verifica].data);
			printf("\nNumeros Sorteados: ");
			
			for(i = 0; i<TFNS; i++)
				printf("\n%d", Concurso[verifica].NumSort[i]);
				
				
			printf("\nConfirma Exclusao (s/n)? ");
		   	if (toupper (getche()) == 'S')
		   	{
		   	    for ( ; verifica<TLC-1; verifica++)
		     	   Concurso[verifica] = Concurso[verifica+1];
		   		   
		    	TLC--;
		   		printf("\nConcurso Deletado!");
		   	}
		   	
			printf("\nQuer Excluir Mais Um concurso? [S-Sim | N-Nao] \n");
			resp = toupper(getche());
			getchar();
			system("cls");
		
	}while(resp == 'S');*/	
}
	
void Rel_aposta()
{
	int i, j;
	TpAposta c;
	FILE *PtrAposta = fopen("Apostas.dat", "rb");
	system("cls");
	printf(" ### APOSTAS ###");
	rewind(PtrAposta);
	fread(&c, sizeof(TpAposta), 1, PtrAposta);
	while(!feof(PtrAposta))
	{
		if (c.status=='A')
		{
			printf("\n==================================\n");
    		printf("CPF: %s\n", c.CPF);
    		printf("Numero do Concurso: %d\n", c.NumCurso);
    		printf("Qtd numeros apostados: %d\n", c.qtd_aposta);
    		printf("Numeros apostados: ");
    	
    		for(j= 0; j<c.qtd_aposta; j++)
    			printf(" %d", c.NumApost[j]);
    		printf("\n====================================\n");	
		}
		
    	fread(&c, sizeof(TpAposta), 1, PtrAposta);
    	
	}
	getch();
	fclose(PtrAposta);
}

void BusConcurso()
{
	int i, verifica, AuxBus;
	char resp;
	FILE *PtrConcurso = fopen("Concursos.dat", "rb");
	TpConcurso Concurso;
	
	system("cls");
	
	do
	{
		do
		{
			printf("\n### Buscar Concurso ###");
			printf("\n Digite Numero do Concurso: ");
			scanf("%d", &AuxBus);
			
				verifica = VeriNum(PtrConcurso, AuxBus);
			
					if(verifica == -1)
					{
						printf("\nConcurso nao Cadastrado!!");
						getchar();
					}
		}while(verifica == -1);
			
			system("cls");
			fseek(PtrConcurso,verifica,SEEK_SET);
			fread(&Concurso,sizeof(TpConcurso),1,PtrConcurso);
			printf("\nData da Realizacao: %s", Concurso.data);
			printf("\nNumeros Sorteados: ");
			
			for(i = 0; i<TFNS; i++)
				printf(" %d", Concurso.NumSort[i]);
			
			printf("\nQuer Buscar Mais Um concurso? [S-Sim | N-Nao] \n");
			resp = toupper(getche());
			getchar();
			system("cls");
	}while(resp == 'S');
}

void Rel_terno()
{
	int aux_curso=0, nums_acertos[5], p=0, acertos=0;
	system("cls");
	FILE *PtrAposta = fopen("Apostas.dat", "rb");
	FILE *PtrApostador = fopen("Apostadores.dat", "rb");
	FILE *PtrConcurso = fopen("Concursos.dat", "rb");
	TpAposta Aposta;
	TpConcurso Concurso;
	TpApostadores Apostadores;
	if(PtrConcurso == NULL || PtrApostador == NULL)
	{
		printf("\nNenhum Concurso ou Aposta Cadastrados!!");
		getchar();
	}
	else{
		printf(" ### Terno, Quadra e Quina ###\n");
		for (int i = 3; i <= 5; i++) {  
	        printf("\n==========================================\n");
	        if (i == 3) 
				{ 
	                printf("\nApostadores que Acertaram a Terno:\n");
	            }
	            if(i == 4)
	            {
	            	printf("\nApostadores que Acertaram a Quadra:\n");
	            }
	            if(i == 5)
	            {
	            	printf("\nApostadores que Acertaram a Quina:\n");
	            }
	
	        int premiado = 0;
	        rewind(PtrAposta);
	        fread(&Aposta, sizeof(TpAposta),1, PtrAposta);
	        while (!feof(PtrAposta)) 
			{
	            if (Aposta.status == 'A')
	            {
	            	acertos = 0;
	            	aux_curso = VeriNum(PtrConcurso, Aposta.NumCurso);
					fseek(PtrConcurso, aux_curso, SEEK_SET);
					fread(&Concurso, sizeof(TpConcurso),1, PtrConcurso);
					if (Concurso.status == 'A')
	                	acertos = contar_acertos(Aposta.NumApost, Aposta.qtd_aposta, Concurso.NumSort, nums_acertos);
	                
	                if (acertos == i)
	                {
	                	rewind(PtrApostador);
	                	fread(&Apostadores, sizeof(TpApostadores), 1, PtrApostador);
	                	while (!feof(PtrApostador)) 
						{
	                        if (strcmp(Aposta.CPF, Apostadores.CPF) == 0 && Apostadores.status== 'A') 
							{
	                            printf("CPF: %s | Nome: %s | ", Apostadores.CPF, Apostadores.Nome, i);
	                            printf("Acertou os numeros: ");
	                            for(p=0; p<acertos-1; p++)
	                            	printf(" %d,", nums_acertos[p]);
	                            printf(" %d\n", nums_acertos[p]);
	                            premiado = 1;
	                        }
	                        fread(&Apostadores, sizeof(TpApostadores), 1, PtrApostador);
	                    }	
	                }	
	            }
					
	             fread(&Aposta, sizeof(TpAposta),1, PtrAposta);   
	        }
	
	        if (!premiado) {
	            printf("Nenhum apostador premiado neste concurso.\n");
	        }
		}
	    printf("\nPressione ENTER para continuar...");
	    getchar();
	    fclose(PtrAposta);
	fclose(PtrApostador);
	fclose(PtrConcurso);
	}
	 
}

void RecebeASConcurso (	FILE *PtrApostador, FILE *PtrConcurso,char aux[TFNM], int &aux_con)
{
	printf("\nDigite o CPF do Apostador: ");
	fflush(stdin);
	gets(aux);
	rewind(PtrApostador);
	rewind(PtrConcurso);


	while (strcmp(aux, "\0") != 0 && BuscarCPF(PtrApostador, aux) ==-1)
	{
		printf("\nCPF nao existe");
		printf("\nDigite o CPF do Apostador: ");
		fflush(stdin);
		gets(aux);
	}
	

	printf("\nDigite o numero do Concurso: ");
	scanf("%d", &aux_con);
	
	while (aux_con != 0 && VeriNum(PtrConcurso, aux_con) == -1)
	{
		printf("\n Concurso nao existe");
		printf("\nDigite o numero do Concurso: ");
		scanf("%d", &aux_con);
	}
}
