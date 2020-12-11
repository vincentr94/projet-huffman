/**
 * @file huffman.h
 * @brief Fichier contenant les prototypes et definitions de structure pour le projet Huffman
 * @author Faël MOULOUDJ
 * @version 1.0
 * @date 4/12/2020
 */
#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

/**< Definition de la liste */
typedef struct ListElement{
    int occurence;
    char caractere;
    struct ListElement *next;
}ListElement,Element, *List;

/**< Definition de l'arbre */
typedef struct Tree{
	int occurence;
	char caractere;
	struct Tree *sag;
	struct Tree *sad;
	struct Tree *parent;
}Tree;

/**< Definition de la liste de noeuds */
typedef struct Tree_list{
    Tree* node;
    struct Tree_list* next;
}Tree_list;

/**< Definition de la Pile */
typedef struct PileElement{
    char caractere;
    struct PileElement* next;
}PileElement, *Stack;

/**< Definition de la liste servant à l'encodage */
typedef struct List_encodage{
    char caractere;
    int* codage;
    struct List_encodage* next;
}List_encodage;


char* conversion_binaire(int n);
int traduction_simple(void);
int size_fic(FILE* fic);
List list_huffman(FILE* f1);
Tree *arbre_huffman(List li);
void create_dico(Tree* a,PileElement** nbr,FILE* dico);
void encodage();
void Compression(FILE *input);
void encodage_opti(FILE* input,FILE* dico);


List insert_list(List li, int occ, char car);
List delete_list(List li);
List clear_list(List li);
void print_list(List li);


Tree *create_node(int x, char car);
void clear_tree(Tree *tr);
Tree *create_tree(Tree *left, Tree *right, int poids);
void print_tree(Tree *tr);


void insert_node(Tree_list** List_node,Tree *node);
void print_list_node(Tree_list* li);
int comparer_noeud(Tree* n1,Tree* n2);
void delete_node(Tree_list **li,Tree *node);
Tree* minimum_TreeList(Tree_list** li);
int Treelist_length(Tree_list *li);


Stack create_pile(char car);
Stack empiler(Stack P,char car);
Stack depiler(Stack P);
void print_stack(Stack P);


void ecrire_dico_pile(Stack P,FILE* dico);
char* read_char(FILE* dico);
List_encodage* create_ListEncodage(FILE* dic);



#endif // HUFFMAN_H_INCLUDED
