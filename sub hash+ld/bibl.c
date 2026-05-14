#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Carte{
    int id;
    char* titlu;
    char* autor;
    int anPublicare;
    int esteDisponibila;
};
typedef struct Carte Carte;


struct Nod{
    Carte info;
    struct Nod* prev;
    struct Nod* next;
};
typedef struct Nod Nod;

struct ListaDubla{
    Nod* first;
    Nod* last;
};
typedef struct ListaDubla ListaDubla;

struct HashTable{
    int dim;
    ListaDubla* vector;

};
typedef struct HashTable Hash;

void InserareLaSfarsit(ListaDubla* lista, Carte carte){
    Nod *nou=malloc(sizeof(Nod));
    nou->info=carte;
    nou->next=NULL;
    nou->prev=lista->last;
    if(lista->last){
        lista->last->next=nou;
    }
    else{
        lista->first=nou;
    }
    lista->last=nou;
}

int calculeazaHashCode(int dimensiune, Carte carte){
    return strlen(carte.autor)%dimensiune;

}
void InserareTabela(Hash ht, Carte carte){
    int hashcode= calculeazaHashCode(ht.dim,carte);
    InserareLaSfarsit(&ht.vector[hashcode],carte);
}

Hash Disponibilitate(ListaDubla lista, Hash ht){
    
    Nod *temp=lista.first;
    while(temp){
        if(temp->info.esteDisponibila==1){
            Carte clona;
            clona.anPublicare=temp->info.anPublicare;
            clona.autor=malloc((strlen(temp->info.autor)+1)* sizeof(char));
            strcpy(clona.autor,temp->info.autor);
            clona.esteDisponibila=temp->info.esteDisponibila;
            clona.id=temp->info.id;
            clona.titlu=malloc((strlen(temp->info.titlu)+1)*sizeof(char));
            strcpy(clona.titlu,temp->info.titlu);
            InserareTabela(ht,clona);
            

        }
        temp=temp->next;
    }
    return ht;

}

void dezalocare(Hash *ht){
   
    for(int i=0;i<ht->dim;i++){
        
        Nod* temp= ht->vector[i].first;
        while(temp){
            free(temp->info.autor);
            free(temp->info.titlu);
            
            Nod* sters=temp;
            temp=temp->next;
            free(sters);

        }
        ht->vector[i].first=NULL;
        ht->vector[i].last=NULL;
        

        }
        
        
        ht->vector->first=NULL;
        ht->vector->last=NULL;
        free(ht->vector);
        ht->dim=0;
        ht->vector=NULL;

}

Carte CitesteCarte(FILE* file){
    char linie[256];
    fgets(linie,255,file);
    char delimitator[3]=",\n";
    Carte carte;
    carte.id=atoi(strtok(linie,delimitator));
    char* aux=strtok(NULL,delimitator);
    carte.titlu=malloc((strlen(aux)+1)*sizeof(char));
    strcpy(carte.titlu,aux);
    aux=strtok(NULL,delimitator);
    carte.autor=malloc((strlen(aux)+1)*sizeof(char));
    strcpy(carte.autor,aux);
    carte.anPublicare=atoi(strtok(NULL,delimitator));
    carte.esteDisponibila=atoi(strtok(NULL,delimitator));

    return carte;
}

Hash initializareHashTable(int dimensiune) {
	Hash ht;
    ht.dim=dimensiune;
    ht.vector=malloc(ht.dim*sizeof(ListaDubla));
    for(int i=0;i<dimensiune;i++)
    {
        ht.vector[i].first=NULL;
        ht.vector[i].last=NULL;
    }
	return ht;
}

Hash CitireHash(const char* numeFisier){
    FILE* f=fopen(numeFisier,"r");
    Hash ht=initializareHashTable(5);
    if(!f){
        printf("eroare");
        return ht;
    }
    while(!feof(f)){
        InserareTabela(ht,CitesteCarte(f));
    }
    fclose(f);
    return ht;
}

ListaDubla citireLD(const char* numeFisier){
    FILE* f=fopen(numeFisier,"r");
    ListaDubla lista;
    lista.first=NULL;
    lista.last=NULL;
    while(!feof(f)){
        InserareLaSfarsit(&lista, CitesteCarte(f));

    }
    fclose(f);
    return lista;
}

void AfiseazaCarte(Carte carte){
    printf("id: %d , titlu: %s , autor: %s, anpublicare: %d, estedisp: %d", carte.id,carte.titlu,carte.autor,carte.anPublicare,carte.esteDisponibila);
}

void AfiseazaTabela(Hash ht){
    for(int i=0;i<ht.dim;i++){
        Nod *aux=ht.vector[i].first;
        printf("clusterul %d \n", i+1);
        if(aux==NULL){
            printf("gol!\n");
        }
        while(aux){
           
            AfiseazaCarte(aux->info);
            aux=aux->next;
            printf("\n\n");
        }
        printf("\n");
    }
}

int main(){

    Hash hash= CitireHash("date.txt");
    AfiseazaTabela(hash);
    printf("\n\n\n\n\n");
    ListaDubla lista=citireLD("date.txt");
    Hash ht=initializareHashTable(7);
    Hash filtrata= Disponibilitate(lista,ht);
    printf("filtrata: \n");
    AfiseazaTabela(filtrata);
   
    printf("\n\n\n\nn");
    dezalocare(&filtrata);
        printf("\n\n\n\nn");

    AfiseazaTabela(ht);
    dezalocare(&hash);
    
    printf("\n\n\n\nn");
    AfiseazaTabela(hash);


    return 0;


}

    







