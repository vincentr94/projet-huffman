/**
 * @file projet.c
 * @brief Fichier contenant les fonctions secondaires pour le projet Huffman
 * @author Faël MOULOUDJ
 * @version 1.0
 * @date 4/12/2020
 */
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include <math.h>


/** @brief Fonction qui permet d'ajouter un maillon à la liste.
 *
 * @param List
 * @param int
 * @param char
 * @return List
 *
 */
List insert_list(List li, int occ, char car){

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

/** @brief Fonction qui supprime le premier maillon d'une liste
 *
 * @param List
 * @return List
 *
 */
List delete_list(List li){

    if(li == NULL)
        return li;

    ListElement *element;
    element = malloc(sizeof(*element));


    element = li->next;
    free(li);
    li = NULL;

    return element;

}

/** @brief Fonction qui permet de vider la liste et la libérer.
 *
 * @param List
 * @return List
 */
List clear_list(List li){
    if(li == NULL)
        return NULL;

    while(li != NULL)
        li = delete_list(li);

}

/** @brief Fonction qui affiche tout les maillons d'une liste
 *
 * @param List
 */
void print_list(List li){
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



/** @brief Fonction qui permet de creer un nouveau noeud
 *
 * @param int x
 * @param char car
 * @return Tree*
 *
 */
Tree *create_node(int x, char car){

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

/** @brief Fonction qui permet de nettoyer un arbre
 *
 * @param Tree* tr
 *
 */
void clear_tree(Tree *tr){
	if(tr == NULL)
		return;
    clear_tree(tr->sag);
	clear_tree(tr->sad);

	free(tr);
}

/** @brief Fonction qui permet de creer un arbre en joignant deux noeuds
 *
 * @param Tree* left
 * @param Tree* right
 * @param int poids
 * @return Tree*
 *
 */
Tree *create_tree(Tree *left, Tree *right, int poids){
	Tree *tr = create_node(poids,0);

	tr->sag = left;
	tr->sad = right;

	if(left != NULL)
		left->parent = tr;
	if(right != NULL)
		right->parent = tr;

	return tr;
}

/** @brief Fonction qui permet d'afficher un arbre en préfixe
 *
 * @param Tree* tr
 *
 */
void print_tree(Tree *tr){
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




/** @brief Fonction qui ajoute un noeud a la liste de noeud
 *
 * @param Tree_list** li
 * @param Tree *node
 *
 */
void insert_node(Tree_list** li,Tree *node){

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

/** @brief Fonction qui affiche tout les noeuds d'une liste de noeuds
 *
 * @param Tree_list* li
 *
 */
void print_list_node(Tree_list *li){

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

/** @brief Fonction qui compare deux noeuds de la liste de noeuds
 *
 * @param Tree* n1
 * @param Tree* n2
 * @return int
 *
 */
int comparer_noeud (Tree* n1,Tree* n2){
    if (n1 == n2)return 1;
    if ((n1 == NULL) || (n2 == NULL))return 0;
    return ((n1->caractere == n2->caractere) && (n1->occurence == n2->occurence)&& comparer_noeud (n1->sag, n2->sag)&& comparer_noeud (n1->sad, n2->sad));
}

/** @brief Fonction qui supprime un noeud de la liste de noeuds
 *
 * @param Tree_list** li
 * @param Tree* node
 *
 */
void delete_node(Tree_list **li,Tree *node){

    if (*li != NULL && node != NULL){
        if(comparer_noeud((*li)->node,node) == 1 ){
            Tree_list *temp = *li;
            *li = (*li)->next;
            free(temp);
        }
        else delete_node(&((*li)->next),node);

    }
}

/** @brief Fonction qui retourne le noeud avec l'occurence la plus basse
 *
 * @param Tree_list** li
 * @return Tree*
 *
 */
Tree *minimum_TreeList(Tree_list** li){

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

/** @brief Fonction qui retourne la taille d'une liste de noeuds
 *
 * @param Tree_list *li
 * @return int
 *
 */
int Treelist_length(Tree_list *li){
	int size = 0;

	if(li == NULL)return size;

	while(li != NULL)
	{
		size++;
		li = li->next;
	}

	return size;
}




/** @brief Fonction qui permet d'initialiser une pile
 *
 * @param char car
 * @return Stack
 *
 */
Stack create_pile(char car){
    PileElement* P = malloc(sizeof(PileElement));
    P->caractere = car;
    P->next = NULL;
    return P;
}

/** @brief Fonction qui permet d'empiler une pile
 *
 * @param Stack P
 * @param char car
 * @return Stack
 *
 */
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

/** @brief Fonction qui permet de dépiler une pile
 *
 * @param Stack P
 * @return Stack
 *
 */
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

/** @brief Fonction qui affiche tout les maillons d'une pile
 *
 * @param Stack P
 *
 */
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




/** @brief Fonction qui ecrit le codage d'Huffman dans une pile
 *
 * @param Stack P
 * @param FILE* dico
 *
 */
void ecrire_dico_pile(Stack P,FILE* dico){
    if (P != NULL){
        ecrire_dico_pile(P->next,dico);
        fputc(P->caractere,dico);

    }
}

/** @brief Fonction qui lit le codage d'Hufffman
 *
 * @param FILE* dico
 * @return char*
 *
 */
char* lire_charactere(FILE* dico){

    char* tab = malloc(30*sizeof(char));
    fscanf(dico,"%s",tab);
    return tab;
}

/** @brief Fonction qui permet de creer une liste qui contient l'encodage pour chaque caractere du dictionnaire.
 *
 * @param FILE* dico
 * @return List_encodage*
 *
 */
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
