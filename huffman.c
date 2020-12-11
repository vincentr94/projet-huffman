/**
 * @file huffman.c
 * @brief Fichier contenant les fonctions pour le projet Huffman
 * @author Faël MOULOUDJ
 * @version 1.0
 * @date 4/12/2020
 */
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include <math.h>


/** @brief Permet de convertir un entier **n** en nombre binaire sous forme d'un tableau de caracteres
 *
 * @param int n  L'entier a convertir
 * @return char*
 *
 */
char *conversion_binaire(int n){

    int i;
    int p;
    char* bin = (char*)malloc(8*sizeof(char));

    for (i=0;i<8;i++){

        p = (int)pow(2,7-i);

        if (n >= p){
            bin[i] = '1';
            n = n - p;
        }
        else{
            bin[i] = '0';
        }
    }
    return bin;
}


/// Question A
/** @brief Fonction qui lit un texte dans un fichier et qui le traduit en son équivalent binaire dans un autre fichier.
 *
 * @return int
 *
 */
int traduction_simple(void){

    FILE* f1 = fopen("Alice.txt","r");
    FILE* f2 = fopen("new.txt","w");
    int caractere;
    int i;
    char* bin;

    if (f1 == NULL)
        return 1;



    while( (caractere = fgetc(f1)) != EOF )
    {
        bin = conversion_binaire(caractere);
        for (i=0;i<8;i++)
            fputc(bin[i],f2);
    }

    fclose(f2);
    fclose(f1);
    return 0;
}


/// Question B
/** @brief Fonction qui affiche le nombre de caracteres dans un fichier txt.
 *
 * @param FILE* le fichier à parcourir
 * @return int
 *
 */
int size_fic(FILE* fic){

    int compteur = 0;
    int caractere;
    if (fic == NULL)
        return 0;
    while( (caractere = fgetc(fic)) != EOF )
        compteur++;
    return compteur;
}


///Question C
/** @brief Fonction qui retourne une liste contenant le nombre d'occurence que contient chaque caracteres dans le texte.
 *
 * @param FILE* f1 le fichier a convertir en codage Huffman
 * @return List
 *
 */
List list_huffman(FILE* f1){


    char car;
    int check_validity = 0;

    if (f1 == NULL)
        return NULL;

    ListElement *li;
    li = malloc(sizeof(*li));
    li->next = NULL;
    li->occurence = 1;
    li->caractere = fgetc(f1);


    ListElement *temp;
	temp = li;

    while( (car = fgetc(f1)) != EOF )
    {
        while(temp != NULL)
        {
            if(car == temp->caractere)
            {
                temp->occurence++;
                check_validity = 1;
            }
            temp = temp->next;
        }
        if(check_validity == 0)
        {
            li = insert_list(li, 1, car);
        }
        check_validity = 0;
        temp = li;
    }
    printf("           .           \n");
    return li;
}


///Question D
/** @brief Fonction qui retourne un arbre de Huffman à partir d'une liste de Huffman
 *
 * @param List **li** la liste d'Huffman à convertir en arbre de Huffman
 * @return Tree*
 *
 */
Tree *arbre_huffman(List li){
    ListElement *temp = li;
    Tree *arbre,*ax, *ay;
    int x;
    int poids;
    char car_x;
    Tree_list *listeDeNoeud = NULL;

    while(temp != NULL)
    {
        x = temp->occurence;
        car_x = temp->caractere;
        temp = delete_list(temp);

        ax = create_node(x, car_x);
        insert_node(&listeDeNoeud, ax);
    }
    while(Treelist_length(listeDeNoeud) != 1)
    {
        ax = minimum_TreeList(&listeDeNoeud);
        ay = minimum_TreeList(&listeDeNoeud);
        poids = ax->occurence + ay->occurence;

        arbre = create_tree(ax, ay, poids);
        insert_node(&listeDeNoeud, arbre);
    }
    arbre = minimum_TreeList(&listeDeNoeud);
    printf("           .           \n");
    return arbre;
}


///Question E
/** @brief Fonction qui permet de créer un dictionnaire
 *
 * @param Tree* **a** l'arbre de Huffman
 * @param PileElement** P
 * @param FILE* dico fichier dictionnaire ouvert en mode écriture
 *
 */
void create_dico(Tree* a,PileElement** P,FILE* dico){

    if (a != NULL)
    {
        if (a->sag != NULL)
        {
            if (a->sag->caractere != 0)
            {
                (*P) = empiler((*P),'0');
                fprintf(dico,"%c : ",a->sag->caractere);
                ecrire_dico_pile((*P),dico);
                fputc('\n',dico);
                create_dico(a->sag,P,dico);
            }
            else
            {
                (*P) = empiler((*P),'0');
                create_dico(a->sag,P,dico);
            }
            (*P) = depiler((*P));
        }

        if (a->sad != NULL)
        {
            if (a->sad->caractere != 0)
            {
                (*P) = empiler((*P),'1');
                fprintf(dico,"%c : ",a->sad->caractere);
                ecrire_dico_pile((*P),dico);
                fputc('\n',dico);
                create_dico(a->sad,P,dico);
            }
            else
            {
                (*P) = empiler((*P),'1');
                create_dico(a->sad,P,dico);
            }
            (*P) = depiler((*P));
        }
    }
}


///Question F
/** @brief Fonction qui effectue l'encodage dans un nouveau fichier.txt. Cet encodage n'est pas optimisé
 *
 */
void encodage(void){

    FILE* input = fopen("Alice.txt","r");
    FILE* new_file = fopen("new.txt","w");
    FILE* dico = fopen("dico.txt","r");


    char caractere;
    char car;
    char ca;
    int i=0;


    while((caractere = fgetc(input)) != EOF)
    {
        printf("[%d]\n",i);
        i++;
       while((car = fgetc(dico)) != EOF)
       {

           if ((car == caractere))
           {
                fseek(dico,3, SEEK_CUR);
                while((ca = fgetc(dico)) != '\n')
                {

                    fputc(ca, new_file);
                }
            }
            else
            {
                while((ca = fgetc(dico)) != '\n')
                {
                    fseek(dico,1, SEEK_CUR);
                }
            }

       }
       rewind(dico);
    }

    printf("L'encodage s'est realiser.\n");
    fclose(new_file);
    fclose(input);
    fclose(dico);

}


///Question G
/** @brief Fonction qui fait une compression grâce au codage Huffman
 *
 * @param FILE* input fichier input a compresser grâce au codage de Huffman
 */
void Compression(FILE *input){
    printf("Debut de la compression\n");

    FILE* dico_write = fopen("dico.txt","w");
    FILE* dico_read = fopen("dico.txt","r");

    ListElement *li = list_huffman(input);
    Tree *arbre = arbre_huffman(li);

    Stack pile = NULL;
    create_dico(arbre, &pile, dico_write);
    fclose(dico_write);

    rewind(input);
    encodage_opti(input, dico_read);
    fclose(dico_read);

    clear_tree(arbre);

    printf("Fin de la compression\n");

}


///Question M
/** @brief Fonction qui effectue l'encodage dans un nouveau fichier.txt. Cet encodage est optimisé
 *
 * @param FILE* input fichier en mode lecture
 * @param FILE* dico  fichier en mode lecture
 */
void encodage_opti(FILE* input,FILE* dico){

    FILE* new_file = fopen("new.txt","w");

    int caractere = 0;
    int check_validity = 0;

    List_encodage *li = create_ListEncodage(dico);
    List_encodage *temp = li;

    while( (caractere = fgetc(input)) != EOF ){
        while (temp != NULL || check_validity == 0 ){
            if (temp->caractere == caractere)
            {
                fputs(temp->codage,new_file);
                check_validity = 1;
            }
            temp = temp->next;
        }
        temp = li;
    }
    printf("           .           \n");
    fclose(new_file);
}







