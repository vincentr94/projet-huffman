#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include <math.h>


///-------------------------------------------------- LISTE --------------------------------------------------

List insert_list(List li, int occ, char car){   //Fonction qui permet d'ajouter un maillon à la liste.

    ListElement *element;

	element = malloc(sizeof(*element));

	if(element == NULL)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	element->occurence = occ;
	element->caractere = car;

	if(li == NULL)
		element->next = NULL;
	else
		element->next = li;

	return element;

}

List delete_list(List li){                      //Fonction qui supprime le premier maillon d'une liste

    if(li == NULL)
        return li;

    ListElement *element;
    element = malloc(sizeof(*element));


    element = li->next;
    free(li);
    li = NULL;

    return element;

}

List clear_list(List li){                       //Fonction qui nettoie une liste et la libère
    if(li == NULL)
        return NULL;

    while(li != NULL)
        li = delete_list(li);

}

void print_list(List li){                       //Fonction qui affiche tout les maillons d'une liste
    if(li == NULL)
    {
        printf("Rien  afficher, la liste est vide.\n");
        return;
    }
    while(li != NULL)
    {

        printf("[%c|%d]->", li->caractere, li->occurence);

        li = li->next;

    }

    printf("\n");
}

///-------------------------------------------------- ARBRE --------------------------------------------------


Tree *create_node(int x, char car){                     //Fonction qui permet de créer un nouveau noeud

	Tree *tr = malloc(sizeof(*tr));

	if(tr == NULL)
	{
		fprintf(stderr, "Erreur allocation memoire.\n");
		exit(EXIT_FAILURE);
	}

	tr->occurence = x;
	tr->caractere = car;
	tr->parent = NULL;
	tr->sag = NULL;
	tr->sad = NULL;
	return tr;
}

void clear_tree(Tree *tr){                              //Fonction qui permet de nettoyer un arbre
	if(tr == NULL)
		return;
    clear_tree(tr->sag);
	clear_tree(tr->sad);

	free(tr);
}

Tree *create_tree(Tree *left, Tree *right, int poids){  //Fonction qui permet de créer un arbre en joignant deux noeuds
	Tree *tr = create_node(poids,0);

	tr->sag = left;
	tr->sad = right;

	if(left != NULL)
		left->parent = tr;
	if(right != NULL)
		right->parent = tr;

	return tr;
}

void print_tree(Tree *tr){                              //Fonction qui permet d'afficher un arbre en préfixe
	if(tr == NULL)
		return;

	if(tr->parent != NULL)
        if(tr->caractere == 126)
            printf("[%d] -> [%d]\n",tr->parent->occurence, tr->occurence);
    	else
            printf("[%d] -> [%c|%d]\n",tr->parent->occurence,tr->caractere, tr->occurence);
    else
    	printf("[%d]\n", tr->occurence);

    if(tr->sag != NULL)
    	print_tree(tr->sag);

    if(tr->sad != NULL)
    	print_tree(tr->sad);
}


///-------------------------------------------------- LISTE DE NOEUDS --------------------------------------------------


void insert_node(Tree_list** li,Tree *node){  //Fonction qui ajoute un noeud à la liste de noeud

    Tree_list* element = malloc(sizeof(Tree_list));
    element->node = node;
    element->next = NULL;

    if (*li == NULL)*li = element;
    else
    {
        Tree_list *temp = *li;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = element;
    }
}

void print_list_node(Tree_list *li){          //Fonction qui affiche tout les noeuds d'une liste de noeuds

    if(li == NULL)return;
    while(li != NULL)
    {
        printf("---------------------------------------------------------\n");
        print_tree(li->node);
        printf("---------------------------------------------------------\n");
        li = li->next;
    }
    printf("\n");
}

int comparer_noeud (Tree* n1,Tree* n2){       //Fonction qui compare deux noeuds de la liste de noeuds
    if (n1 == n2)return 1;
    if ((n1 == NULL) || (n2 == NULL))return 0;
    return ((n1->caractere == n2->caractere) && (n1->occurence == n2->occurence)&& comparer_noeud (n1->sag, n2->sag)&& comparer_noeud (n1->sad, n2->sad));
}

void delete_node(Tree_list **li,Tree *node){  //Fonction qui supprime un noeud de la liste de noeuds

    if (*li != NULL && node != NULL){
        if(comparer_noeud((*li)->node,node) == 1 ){
            Tree_list *temp = *li;
            *li = (*li)->next;
            free(temp);
        }
        else delete_node(&((*li)->next),node);

    }
}

Tree *minimum_TreeList(Tree_list** li){       //Fonction qui retourne le noeud avec l'occurence la plus basse

    if (*li != NULL)
    {
        Tree_list* temp = *li;
        Tree* node = NULL;
        int min;
        min = (*li)->node->occurence;

        while(temp != NULL)
        {
            if (temp->node->occurence <= min)
            {
                min = temp->node->occurence;
                node = temp->node;
            }
            temp = temp->next;
        }
        delete_node(li,node);
        return node;
    }
}

int Treelist_length(Tree_list *li){           //Fonction qui retourne la taille d'une liste de noeuds
	int size = 0;

	if(li == NULL)return size;

	while(li != NULL)
	{
		size++;
		li = li->next;
	}

	return size;
}


///-------------------------------------------------- PILE --------------------------------------------------

Stack create_pile(char car){
    PileElement* P = malloc(sizeof(PileElement));
    P->caractere = car;
    P->next = NULL;
    return P;
}

Stack empiler(Stack P,char car){

    if (P == NULL){
        return create_pile(car);
    }
    else{
        Stack new_p = create_pile(car);
        new_p->next = P;
        return new_p;
    }

}

Stack depiler(Stack P){
    if (P == NULL){
        return P;
    }
    else{

        Stack temp = P->next;
        free(P);
        return temp;
    }
}

void print_stack(Stack P){

	if(P == NULL)
	{
		printf("Rien a afficher, la Pile est vide.\n");
		return;
	}

	while(P != NULL)
	{
		printf("[%c]\n", P->caractere);
		P = P->next;
	}
}


///-------------------------------------------------- DICO ET ENCODAGE --------------------------------------------------


void ecrire_dico_pile(Stack P,FILE* dico){
    if (P != NULL){
        ecrire_dico_pile(P->next,dico);
        fputc(P->caractere,dico);

    }
}

char* lire_charactere(FILE* dico){

    char* tab = malloc(40*sizeof(char));
    fscanf(dico,"%s",tab);
    return tab;
}

List_encodage* create_ListEncodage(FILE* dico){

    int caractere;

    if ( (caractere = fgetc(dico)) == EOF ){
        return NULL;
    }

    List_encodage* li = malloc(sizeof(List_encodage));
    li->caractere = caractere;

    caractere = fgetc(dico);
    fseek(dico,2, SEEK_CUR);

    li->codage = lire_charactere(dico);


    caractere = fgetc(dico);

    li->next = create_ListEncodage(dico);
    return li;
}
