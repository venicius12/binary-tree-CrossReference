/*
NOME: VENICIUS BREGALDA

*/


#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>


struct nodo {
    char palavra[30];
    int cont;
    struct nodo *pEsquerda;
    struct nodo *pDireita;
};

struct hash{
struct hash *ant;
  char texto[40];
  struct nodo *pal;
  struct hash *prox;
}textos;


void insereArq ( struct hash ** prim , struct hash ** ultm ,char val[] , struct hash **par_memoria )
{
struct hash * ptaux =( struct hash *) malloc ( sizeof ( textos ));
strcpy(ptaux -> texto, val);
ptaux ->pal=NULL;
*par_memoria=ptaux;
if (* prim == NULL || strcmp((* prim )->texto,val)==0 )
{
ptaux -> prox =* prim ;
ptaux -> ant = NULL ;
if (* prim != NULL )
{ (* prim )-> ant = ptaux ;}
else * ultm = ptaux ;
{* prim = ptaux ;}

return ;
}
struct hash * ptaux2 =* prim ;
while ( ptaux2 -> prox != NULL && strcmp(ptaux2 ->prox ->texto,val)==0 )
ptaux2 = ptaux2 -> prox ;
ptaux -> prox =ptaux2 -> prox ;
ptaux -> ant = ptaux2 ;
ptaux2 -> prox = ptaux ;
if (ptaux -> prox == NULL ) // inserção no final da lista
(* ultm )= ptaux ;
else
ptaux ->prox -> ant = ptaux ;
return ;
}

void in_ordem (struct nodo *raiz ){

    if (raiz == NULL ) return ;

    in_ordem (raiz->pEsquerda );
    printf (" %s - %d \n",raiz ->palavra,raiz ->cont );
    in_ordem (raiz ->pDireita );
}

void in_ordem_In (struct nodo *raiz ){

    if (raiz == NULL ) return ;

    in_ordem_In (raiz ->pDireita );
     printf (" %s - %d \n",raiz ->palavra,raiz ->cont );
    in_ordem_In (raiz->pEsquerda );

}

void pre_ordem ( struct nodo *raiz ){

    if ( raiz == NULL ) return ;

    printf (" %s ",raiz ->palavra );
    pre_ordem (raiz ->pEsquerda );
    pre_ordem (raiz ->pDireita );
}

void pos_ordem(struct nodo *raiz){

    if(raiz == NULL) return;

    pos_ordem(raiz->pEsquerda);
    pos_ordem(raiz->pDireita);
    printf(" %s ",raiz->palavra);

}

struct nodo *inserir(struct nodo **pRaiz, char palavra[]){

    if (*pRaiz == NULL){
        *pRaiz = (struct nodo *) malloc(sizeof(struct nodo));
        (*pRaiz)->pEsquerda = NULL;
        (*pRaiz)->pDireita = NULL;
        strcpy((*pRaiz)->palavra , palavra);
        (*pRaiz)->cont =  1;
    }

    else if(strcmp(palavra ,(*pRaiz)->palavra)<0){
        inserir(&(*pRaiz)->pEsquerda, palavra);

    }
    else{
        inserir(&(*pRaiz)->pDireita, palavra);

    }
    return *pRaiz;
}


int existeArq(struct hash *inicio,char arq[]){

    while(inicio != NULL){
        if(strcmp(inicio->texto,arq) == 0 ){
            return 1;
        }
        inicio = inicio->prox;
    }
    return 0;
};

struct nodo * pesquisaPalavras( struct nodo * raiz, char d[] ){
        struct nodo * res = NULL;
		if( raiz != NULL ){

		  if(strcmp(raiz->palavra , d)==0){
             res = raiz;
          }
          else{
               if(strcmp(d,raiz->palavra)<0){
                    res = pesquisaPalavras( raiz->pEsquerda, d );
               }
               else{
                    res = pesquisaPalavras( raiz->pDireita, d );
               }
          }
        }
        return res;
	}


	int pesq_pal( struct nodo * raiz, char d[] ){

		if( raiz != NULL ){

		  if(strcmp(raiz->palavra , d)==0){
             return 1;
          }
          else{
               if(strcmp(d,raiz->palavra)<0){
                    pesq_pal( raiz->pEsquerda, d );
               }
               else{
                    pesq_pal( raiz->pDireita, d );
               }
          }
        }
	}


int  pesq_arv_rec( struct nodo * raiz, char d[] ){
        struct nodo * res = NULL;
		if( raiz != NULL ){

		  if(strcmp(raiz->palavra , d)==0){
              raiz->cont=raiz->cont+1;

              return 1;
          }
          else{
               if(strcmp(d,raiz->palavra)<0){
                    return pesq_arv_rec( raiz->pEsquerda, d );
               }
               else{
                     return pesq_arv_rec( raiz->pDireita, d );
               }
          }
        }
        return 0;
	}





void encontraTexto(struct hash *inicio, char t[],struct hash **par_retorno)
{
    while(inicio != NULL){
       if(strcmp(inicio->texto,t)==0)
        {
            *par_retorno=inicio;
        }

        inicio = inicio->prox;
    }
}

	int imprimeH(struct hash **ini){
struct hash *inicio = *ini;
    while(inicio != NULL){
        printf("hash %s \n",inicio->texto);
        inicio = inicio->prox;
    }

    return 0;

}


int contarNos(struct nodo *pRaiz){
   if(pRaiz == NULL)
        return 0;
   else
        return 1 + contarNos(pRaiz->pEsquerda) + contarNos(pRaiz->pDireita);
}

int contaTotalPal(struct hash *inicio, char p[])
{
    int cont = 0;
    int existe;
    while(inicio != NULL){
        existe = pesq_pal(inicio->pal,p);
        if(existe==1)
            {
                cont++;
            }
        inicio = inicio->prox;
    }
    return cont;
}

//------------------------------------------------------------------------------------------------------------------------

struct nodo *MaiorpDireita(struct nodo **no){
    if((*no)->pDireita != NULL)
       return MaiorpDireita(&(*no)->pDireita);
    else{
      struct nodo *aux = *no;
       if((*no)->pEsquerda != NULL)
          *no = (*no)->pEsquerda;
       else
          *no = NULL;
       return aux;
       }
}

struct nodo *MenorpEsquerda(struct nodo **no){
    if((*no)->pEsquerda != NULL)
       return MenorpEsquerda(&(*no)->pEsquerda);
    else{
       struct nodo *aux = *no;
       if((*no)->pDireita != NULL)
          *no = (*no)->pDireita;
       else
          *no = NULL;
       return aux;
       }
}

void remover(struct nodo **pRaiz, char palavra[]){
    if(*pRaiz == NULL){
       printf("palavra nao existe na arvore!");
       getch();
       return;
    }
    if(strcmp(palavra,(*pRaiz)->palavra)<0)
       remover(&(*pRaiz)->pEsquerda, palavra);
    else
       if(strcmp(palavra,(*pRaiz)->palavra)>0)
          remover(&(*pRaiz)->pDireita, palavra);
       else{
         struct nodo *pAux = *pRaiz;
          if (((*pRaiz)->pEsquerda == NULL) && ((*pRaiz)->pDireita == NULL)){
                free(pAux);
                (*pRaiz) = NULL;
               }
          else{     // so tem o filho da pDireita
             if ((*pRaiz)->pEsquerda == NULL){
                (*pRaiz) = (*pRaiz)->pDireita;
                pAux->pDireita = NULL;
                free(pAux); pAux = NULL;
                }
             else{            //so tem filho da pEsquerda
                if ((*pRaiz)->pDireita == NULL){
                    (*pRaiz) = (*pRaiz)->pEsquerda;
                    pAux->pEsquerda = NULL;
                    free(pAux); pAux = NULL;
                    }
                else{
                   pAux = MaiorpDireita(&(*pRaiz)->pEsquerda);
                   pAux->pEsquerda = (*pRaiz)->pEsquerda;
                   pAux->pDireita = (*pRaiz)->pDireita;
                   (*pRaiz)->pEsquerda = (*pRaiz)->pDireita = NULL;
                   free((*pRaiz));  *pRaiz = pAux;  pAux = NULL;
                   }
                }
             }
          }
}

//------------------------------------------------------------------------------------------------------------------------




int menu(){
    printf("-----Menu-----\n");
    printf("1 - Inserir na arvore\n");
    printf("2 - Listar arvore em ordem pre fixada\n");
    printf("3 - Mostra quantas vezes uma palavra aparece no texto informado\n");
    printf("4 - Mostra a quantidade de palavras do texto informado\n");
    printf("5 - Mostra a quantidade de vezes que a palavra informada aparece na estrutura \n");
    printf("6 - Remover uma palavra especifica do texto informado\n");
    printf("7 - Exibe a lista de palavras do texto informado em ordem alfabetica ou alfabetica inversa\n");
    printf("8 - Exibe a lista de palavras da estrutura em ordem alfabatica ou alfabetica inversa \n");

}


int main()
{
    struct hash *prim = NULL;
    struct hash *ultm = NULL;
    struct hash *par_memoria = NULL;
    char pal[30];
    char c;
    const char s[2] = " ";
    char *token;
    char str[256];
    char pesqPalav[30];
    char pesqTexte[30];
    int verifica,existe, exisP, x;

    struct nodo *raiz_principal = NULL;

    struct nodo *raiz = (struct nodo *)malloc(sizeof(struct nodo *));
    raiz = NULL;
    struct nodo *retorno = NULL;
    struct nodo *teste = NULL;

    menu();
    printf("Digite a opcao: ");
    fflush(stdin);
    c = getch();
    system("cls");

    while(c>'0' && c<='8'){
        switch(c){

            case '1': printf("Digite o nome da referencia: \n ");
                      gets(pal);
                      fflush(stdin);
                     verifica = existeArq(prim,pal);
                      if (verifica==1)
                       {
                            printf("Ja existe uma referencia com este nome.\n");
                        }
                      else if(!verifica)
                        {
                            insereArq(&prim,&ultm,pal,&par_memoria);

                            //printf("passou \n");

                      printf("Digite a frase: \n ");
                      gets(str);

                        token = strtok(str, s);

                        while( token != NULL )
                        {
                            // printf( "1 %s\n", token );

                           existe = pesq_arv_rec(par_memoria->pal,token);
                              exisP = pesq_arv_rec(raiz_principal,token);
                              if(exisP != 1)
                                {
                                    inserir(&raiz_principal,token);
                                }
//                           printf("existe %d \n",existe);
                             if(existe != 1){
                             inserir(&par_memoria->pal,token);

                            }
                             token = strtok(NULL, s);
                          }
                       }

                      break;


            case '2': printf("Digite em qual texto para imprimir a arvore em ordem pre fixada \n");
                      gets(pesqTexte);

                      verifica = existeArq(prim,pesqTexte);
                      if (verifica==1)
                       {
                        encontraTexto(prim,pesqTexte,&par_memoria);
                        pre_ordem(par_memoria->pal);
                       }
                       else
                        {
                            printf("texto nao existe \n");
                        }
                      break;

            case '3': printf("Digite em qual texto para procurar a palavra \n");
                      gets(pesqTexte);

                      verifica = existeArq(prim,pesqTexte);
                      if (verifica==1)
                       {
                           printf("digite a palavra para ser encontrada no texto \n");
                           gets(pesqPalav);
                            encontraTexto(prim,pesqTexte,&par_memoria);

                           retorno = pesquisaPalavras(par_memoria->pal,pesqPalav);

                           if(retorno==NULL)
                            {
                                printf("Palavra nao existe neste texto \n");
                            }
                            else
                                {
                                    printf("Numero de vezes que a palavra aparece: %d \n",retorno->cont);
                                }
                        }
                         else if(!verifica)
                         {
                          printf("Texto nao existe \n");
                         }
                      break;

           /* case '6': imprimeH(&prim);
                       break;*/

            case '4':   printf("Digite em qual texto para procurar a palavra \n");
                      gets(pesqTexte);

                      verifica = existeArq(prim,pesqTexte);
                      if (verifica==1)
                       {
                           encontraTexto(prim,pesqTexte,&par_memoria);
                           printf("Numero de palavras do texto %d \n",contarNos(par_memoria->pal));
                       }
                       else
                        {
                            printf("Nao existe texto \n");
                        }
                       break;
            case '5': printf("digite qual a palavra \n");
                     gets(pesqPalav);

                     printf("quantidade de vezes que aparece a palavre na estrutura %d \n",contaTotalPal(prim,pesqPalav));
                     break;

            case '6': printf("Digite em qual texto para procurar a palavra para remover \n");
                      gets(pesqTexte);

                      verifica = existeArq(prim,pesqTexte);
                      if (verifica==1)
                       {
                        printf("digite a palavra para ser removida da arvore \n");
                        gets(pesqPalav);
                        encontraTexto(prim,pesqTexte,&par_memoria);
                        remover(&par_memoria->pal,pesqPalav);
                        printf("removido com sucesso \n");
                       }
                       else
                        {
                            printf("Nao existe texto \n");
                        }
                break;
        case '7': printf("Digite em qual texto para imprimir a arvore em ordem alfabetica \n");
                      gets(pesqTexte);

                      verifica = existeArq(prim,pesqTexte);
                      if (verifica==1)
                       {
                    printf("Digite 0 - zero se for em ordem alfabetico e 1 - um se for alfabetica reversa\n");
                     scanf("%d",&x);

                    printf("PALAVRA  -  QUANTIDADE \n");
                     if(x==0)
                        {
                        encontraTexto(prim,pesqTexte,&par_memoria);

                        in_ordem(par_memoria->pal);
                        }
                        else
                            {
                                 in_ordem_In(par_memoria->pal);
                            }
                        //in_ordem_In(par_memoria->pal);
                       }
                       else
                        {
                            printf("texto nao existe \n");
                        }
                      break;


          case '8': printf("Digite 0 - zero se for em ordem alfabetico e 1 - um se for alfabetica reversa\n");
                     scanf("%d",&x);

                    printf("PALAVRA  -  QUANTIDADE \n");
                     if(x==0)
                        {
                            in_ordem(raiz_principal);
                        }
                    else {
                       in_ordem_In(raiz_principal);
                         }
                      break;



        }

        printf("\n");
        menu();
        fflush(stdin);
        printf("Digite a opcao: ");
        c = getch();
        system("cls");

    }
}
