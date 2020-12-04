#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

///----------------------------------------------  DEFINITION DE LA LISTE ----------------------------------------------

typedef struct ListElement{
    int occurence;
    char caractere;
    struct ListElement *next;
}ListElement,Element, *List;

///----------------------------------------------  DEFINITION DE L'ARBRE ----------------------------------------------

typedef struct Tree{
	int occurence;
	char caractere;
	struct Tree *sag;
	struct Tree *sad;
	struct Tree *parent;
}Tree;

///----------------------------------------------  DEFINITION DE LA LISTE DE NOEUDS ----------------------------------------------

typedef struct Tree_list{
    Tree* node;
    struct Tree_list* next;
}Tree_list;

///----------------------------------------------  DEFINITION DE LA PILE ----------------------------------------------

typedef struct PileElement{
    char caractere;
    struct PileElement* next;
}PileElement, *Stack;

///----------------------------------------------  DEFINITION DE LA LISTE D'ENCODAGE ----------------------------------------------


typedef struct List_encodage{
    char caractere;
    int* codage;
    struct List_encodage* next;
}List_encodage;


///----------------------------------------------  PROTOTYPES DE FONCTION ----------------------------------------------

///-- PARTIE I --
char* conversion_binaire(int n); ///Fontion pour convertir un nombre décimal en nombre binaire.
int traduction_simple(void);     ///Fonction qui lit un texte dans un fichier, et qui le traduit en son équivalent 0 et 1 dans un autre fichier.
int size_fic(FILE* fic);         ///Fonction qui affiche le nombre de caractères dans un fichier txt.

///-- PARTIE II --
List list_huffman(FILE* f1);                            ///Fonction qui retourne une liste contenant le nombre d'occurence que contient chaque caractères dans le texte.
Tree *arbre_huffman(List li);                           ///Fonction qui retourne un arbre de Huffman
void create_dico(Tree* a,PileElement** nbr,FILE* dico); ///Fonction qui permet de créer un dictionnaire
void encodage();                                        ///Fonction qui effectue l'encodage dans un nouveau fichier .txt
void Compression(FILE *input);                          ///Fonction qui fait une compression grâce au codage Huffman

///-- PARTIE III --
void encodage_opti(FILE* input,FILE* dico);             ///Fonction d'encodage plus optimisé

    ///LISTE
List insert_list(List li, int occ, char car);   ///Fonction qui permet d'ajouter un maillon à la liste.
List delete_list(List li);                      ///Fonction qui permet de supprimer le premier maillon de la liste.
List clear_list(List li);                       ///Fonction qui permet de vider la liste et la libérer.
void print_list(List li);                       ///Fonction qui affiche tout les maillons d'une liste

    ///ARBRE
Tree *create_node(int x, char car);                         ///Fonction qui permet de créer un nouveau noeud
void clear_tree(Tree *tr);                                  ///Fonction qui permet de nettoyer un arbre
Tree *create_tree(Tree *left, Tree *right, int poids);      ///Fonction qui permet de créer un arbre en joignant deux noeuds
void print_tree(Tree *tr);                                  ///Fonction qui permet d'afficher un arbre en préfixe


    ///LISTE DE NOEUDS
void insert_node(Tree_list** List_node,Tree *node);  ///Fonction qui ajoute un noeud à la liste de noeud
void print_list_node(Tree_list* li);                 ///Fonction qui affiche tout les noeuds d'une liste de noeuds
int comparer_noeud(Tree* n1,Tree* n2);               ///Fonction qui compare deux noeuds de la liste de noeuds
void delete_node(Tree_list **li,Tree *node);         ///Fonction qui supprime un noeud de la liste de noeuds
Tree* minimum_TreeList(Tree_list** li);              ///Fonction qui retourne le noeud avec l'occurence la plus basse
int Treelist_length(Tree_list *li);                  ///Fonction qui retourne la taille d'une liste de noeuds

    ///PILE
Stack create_pile(char car);      ///Fonction qui permet d'initialiser une pile
Stack empiler(Stack P,char car);  ///Fonction qui permet d'empiler une pile
Stack depiler(Stack P);           ///Fonction qui permet de dépiler une pile
void print_stack(Stack P);        ///Fonction qui affiche tout les maillons d'une pile

    ///Dico et Encodage
void ecrire_dico_pile(Stack P,FILE* dico);      ///Fonction qui écrit le codage d'Huffman dans une pile
char* read_char(FILE* dico);                    ///Fonction qui lit le codage d'Hufffman
List_encodage* create_ListEncodage(FILE* dic);  ///Fonction qui créé une liste qui contient l'encodage pour chaque caractère du dictionnaire.



#endif // HUFFMAN_H_INCLUDED
