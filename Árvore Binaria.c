/*	
	Universidade Federal da Fronteira Sul – UFFS	
	Campus Chapecó Curso de Ciência da Computação	
	Professor Jean Assmann Ferro					
	Acadêmico: Luandro Marcos Inseschi				
	Estrutura de Dados II – 2018/2					
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct ArvBin
{
    int info;
    struct ArvBin *esq;
    struct ArvBin *dir;
    
} NO;

// Uma função para criar um novo nó na Árvore de Busca Binária
NO *novoNo(int item)
{
    NO *temp =  (NO *)malloc(sizeof(NO));
    temp->info = item;
    temp->esq = temp->dir = NULL;
    return temp;
}

// Uma função para fazer o percurso EmOrdem na Árvore de Busca Binária
void emordem(NO *raiz)
{
    if (raiz != NULL)
    {
        emordem(raiz->esq);
        printf("%d ", raiz->info);
        emordem(raiz->dir);
    }
}

// Uma função para inserir um novo nó com uma dada chave (info) na Árvore de Busca Binária
NO *insere(NO *no, int info)
{
    // Se a árvore estiver vazia, retorne um novo nó
    if (no == NULL) return novoNo(info);

    // Caso contrário, volte pela árvore
    if (info < no->info){
      no->esq  = insere(no->esq, info);
     }
    else if (info > no->info){
        no->dir = insere(no->dir, info);
	}
    // retorna o ponteiro do nó (inalterado)
    return no;
}
NO *remover(NO *no, int valor)
{
	NO *aux;//serve para guardar as variaveis logo apos os excluidos e fazer as trocar e um aux para isso
	if(no==NULL){ //os nó estao vazios
	printf("valor nao inserido na arvore\n ");
	return NULL;
		}else if(valor < no->info){//esta parte e para procurar para que lado vc vai ir com a arvore e achar o valor para remover
			no->esq =remover(no->esq,valor);
		}else if(valor >no->info){
			no->dir=remover(no->dir,valor);//daqui para baixos são as verificações
		}else{//achei  agora vou verificar quantos filhos tem
			if(no->esq==NULL && no->dir==NULL){
				free(no);
				no=NULL;
			}else if(no->esq== NULL){//este caso e que so tem um filho so direita
				aux=no;
				no=no->dir;
				free(aux);
			}else if(no->dir == NULL){//este caso e quanto tem um filho so a esquerda
				aux=no;
				no=no->esq;
				free(aux);
			}else {//este caso e quanto tem 2 filhos
				NO *maior=no->esq;//variavel que aponsta para o filho da esquerda 
				while(maior->dir!=NULL){//loop para achar o maior valor da direita
					maior=maior->dir;
				}
				no->info=maior->info;//depois disso eu pego o valor do no a ser removido e subtituido pelo maior valor achado
				maior->info=valor;//sem isso os valor deletado não poderia ocoorrer 
				no->esq=remover(no->esq,valor);// depois de copiar os valores eu removo  os valores iguais da sub-arvores esquerda
			}
		}
	return no;
}

void preOrdem(NO* raiz){
	if (raiz ==NULL)
		return;
	if(raiz !=NULL){
	printf("%d,",(raiz)->info);
	preOrdem(raiz->esq);
	preOrdem(raiz->dir);
	}
}

void posOrdem(NO* raiz){
	if (raiz==NULL)
			return;
	if(raiz!=NULL){
		posOrdem(raiz->esq);
		posOrdem(raiz->dir);
		printf("%d,",(raiz->info));
	}
}

// Teste das funções
int main()
{
  int op,valor;
    /* Criar a seguinte Árvore de Busca Binária
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */

    NO *raiz = NULL;
    raiz = insere(raiz, 50);
    insere(raiz, 30);
    insere(raiz, 20);
    insere(raiz, 40);
    insere(raiz, 70);
    insere(raiz, 60);
    insere(raiz, 80);
    do{
		printf("\n*********************************************");
		printf("\nValores inseridos: 50, 30, 20, 40, 70, 60 e 80.\n");
		printf("\n1 para remover");
		printf("\n2 pre Ordem");
		printf("\n3 pos Ordem");
		printf("\n4 pos Ordem");
		printf("\n0 para sair\n");
		printf("*********************************************\n");
		printf("Escolha umas as opcoes a cima\n");
		scanf("%d", &op);
		system("clear");
		if(op==1){
			printf("\n\n\n\t\t\tDigite o valor que vai ser removido\n");
			scanf("%d",&valor);
			remover(raiz,valor);
		 }
		if(op==2){
			printf("\n\n\n\t\t\tPre Ordem: ");
			preOrdem(raiz);
			
		}
		if(op==3){
			printf("\n\n\n\t\t\tPos Ordem: ");
			posOrdem(raiz);
		}
		if(op==4){
		   printf("\n\n\n\t\t\tPercurso Em Ordem: ");
			emordem(raiz);
		}
   }while(op!=0);
  return 0;
}

