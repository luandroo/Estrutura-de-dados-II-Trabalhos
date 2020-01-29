//Luandro Marcos Inseschi
//Universidade Federal da Fronteira Sul
//Professor Jean Carlos Fenner
#include<stdio.h>
#include<stdlib.h> 

typedef struct nodo
{
    int info;
    struct nodo *esquerda,*direita;
    int fb;
}nodo;
 
nodo *inserir(nodo *,int);
nodo *Delete(nodo *,int);
void preordem(nodo *);
void emordem(nodo *);
void posordem(nodo *);
int altura( nodo *);
nodo *rotacaodireita(nodo *);
nodo *rotacaoesquerda(nodo *);
nodo *RR(nodo *);
nodo *LL(nodo *);
nodo *LR(nodo *);
nodo *RL(nodo *);
int FB(nodo *);
 
int main()
{
    nodo *root=NULL;
    int x,n,i,op;
    
    do
    {
        printf("\n1)Criar");
        printf("\n2)Inserir");
        printf("\n3)Deletar");
        printf("\n4)Imprimir");
        printf("\n5)Sair");
        printf("\n\nInforme a sua escolha: ");
        scanf("%d",&op);
        
        switch(op)
        {
            case 1: printf("\nInforme o número de elemetos: ");
                    scanf("%d",&n);
                    printf("\nEntre com o elementos da árvore: ");
                    root=NULL;
                    for(i=0;i<n;i++)
                    {
                        scanf("%d",&x);
                        root=inserir(root,x);
                    }
                    break;
                
            case 2: printf("\nInforme um dado: ");
                    scanf("%d",&x);
                    root=inserir(root,x);
                    break;
                    
            case 3: printf("\nInforme um dado:");
                    scanf("%d",&x);
                    root=Delete(root,x);
                    break;
            
            case 4: printf("\nSequência em Pré Ordem:\n");
                    preordem(root);
                    printf("\n\nSequência Em Ordem:\n");
                    emordem(root);
		    printf("\n\nSequência Pós Ordem:\n");
                    posordem(root);
                    printf("\n");
                    break;            
        }
    }while(op!=5);
    
    return 0;
}

nodo *aloca(int novo){
		nodo *alocar=(nodo*)malloc(sizeof(nodo));
		alocar->info=novo;
		alocar->esquerda=alocar->direita=NULL;
		return alocar;
}
 
nodo * inserir(nodo *T,int x)
{
    if(T==NULL)
    {
		return aloca(x);
    }
    else{
        if(x > T->info)        // insira na subárvore direita
        {
            T->direita=inserir(T->direita,x);
            if(FB(T)==-2){
                if(x>T->direita->info)
                    T=RR(T);
             
                else
                    T=RL(T);
			}
        }
        else
            if(x<T->info)
            {
                T->esquerda=inserir(T->esquerda,x);
                if(FB(T)==2){
                    if(x < T->esquerda->info)
                        T=LL(T);
                    else
                        T=LR(T);
                 }
            }
	}
        T->fb=altura(T);
        
        return(T);
}
 
nodo * Delete(nodo *T,int x)
{
    nodo *p;
    
    if(T==NULL)
    {
        return T;
    }
    else
        if(x > T->info)        // Insira na subárvore esquerda
        {
            T->direita=Delete(T->direita,x);
            if(FB(T)==2){
                if(FB(T->esquerda)>=0)
                    T=LL(T);
                else
                    T=LR(T);
			}
        }
        else
            if(x<T->info)
            {
                T->esquerda=Delete(T->esquerda,x);
                if(FB(T)==-2){    // Rebalancear durante a conclusão
                    if(FB(T->direita)<=0)
                        T=RR(T);
                    else
                        T=RL(T);
                }
            }
            else
            {
                // Os dados a serem excluídos são encontrados
                if(T->direita!=NULL)
                {    // Delete seu sucessor Em Ordem
                    p=T->direita;
                    
                    while(p->esquerda!= NULL)
                        p=p->esquerda;
                    
                    T->info=p->info;
                    T->direita=Delete(T->direita,p->info);
                    
                    if(FB(T)==2){// Rebalancear durante a conclusão
                        if(FB(T->esquerda)>=0)
                            T=LL(T);
                        else
                            T=LR(T);\
                     }
                }
                else
                    return(T->esquerda);
            }
    T->fb=altura(T);
    return(T);
}
 
int altura(nodo *T)
{
    int sae,sad;
    if(T==NULL)
        return(0);
    
    if(T->esquerda==NULL)
        sae=0;
    else
        sae=1+T->esquerda->fb;
        
    if(T->direita==NULL)
        sad=0;
    else
        sad=1+T->direita->fb;
    
    if(sae>sad)
        return(sae);
    
    return(sad);
}
 
nodo * rotacaodireita(nodo *x)
{
	nodo *alocar;
	alocar=x->esquerda;
	x->esquerda=alocar->direita;
	alocar->direita=x;
	return alocar;
}
 
nodo * rotacaoesquerda(nodo *x)
{
	nodo *alocar;
    alocar=x->direita;
    x->direita=alocar->esquerda;
    alocar->esquerda=x;
    return alocar;
}
 
nodo * RR(nodo *T)
{
    T=rotacaoesquerda(T);
    return(T);
}
 
nodo * LL(nodo *T)
{
    T=rotacaodireita(T);
    return(T);
}
 
nodo * LR(nodo *T)
{
    T->esquerda=rotacaoesquerda(T->esquerda);
    T=rotacaodireita(T);
    
    return(T);
}
 
nodo * RL(nodo *T)
{
    T->direita=rotacaodireita(T->direita);
    T=rotacaoesquerda(T);
    return(T);
}
 
int FB(nodo *T) //FB - Fator de Balanceamento
{
    int sae,sad; //sae - sub-árvore-esquerda | sad - sub-árvore-direita
    if(T==NULL)
        return(0);
 
    if(T->esquerda==NULL)
        sae=0;
    else
        sae=1+T->esquerda->fb;
 
    if(T->direita==NULL)
        sad=0;
    else
        sad=1+T->direita->fb;
 
    return(sae-sad);
}
 
void preordem(nodo *T)
{
    if(T!=NULL)
    {
        printf("%d(FB=%d) ", T->info, FB(T));
        preordem(T->esquerda);
        preordem(T->direita);
    }
}
 
void emordem(nodo *T)
{
    if(T!=NULL)
    {
        emordem(T->esquerda);
        printf("%d(FB=%d) ", T->info, FB(T));
        emordem(T->direita);
    }
} 

void posordem(nodo *T)
{
    if(T!=NULL)
    {
        posordem(T->esquerda);
        posordem(T->direita);
        printf("%d(FB=%d) ", T->info, FB(T));
    }
} 
