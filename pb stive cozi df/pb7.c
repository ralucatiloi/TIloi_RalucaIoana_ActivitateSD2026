#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Colet{
    int id;
    float greutate;
    char* destinatie;

};
typedef struct Colet Colet;

//coada- lsi
struct Nod{
    Colet info;
   struct Nod* next;

};
typedef struct Nod Nod;


//stiva- vector
struct Stiva{
    Colet * vector;
    int capacitate;

};
typedef struct Stiva Stiva;

void enqueue(Nod** cap, Colet colet){
    Nod* nou=malloc(sizeof(Nod));
    nou->info=colet;
    nou->next=NULL;
    if(*cap){
        Nod* temp=*cap;
        while(temp->next){
            temp=temp->next;
        }
        temp->next=nou;
    }
    else{
        *cap=nou;
    }
}

Colet dequeue(Nod** cap){
    Nod* temp=malloc(sizeof(Nod));
    temp=*cap;
    Colet colet;
    colet.id=-1;
    if(*cap){
        colet=temp->info;
        (*cap)=temp->next;
        free(temp);

    }
    return colet;

}

void pushStack(Stiva* stiva, Colet colet){
    Colet *nou=malloc((stiva->capacitate+1)*sizeof(Colet));
    for(int i=0;i<stiva->capacitate;i++){
        nou[i]=stiva->vector[i];

    }
    nou[stiva->capacitate]=colet;
    if(stiva->vector){
        free(stiva->vector);

    }
    stiva->vector=nou;
    stiva->capacitate++;
    

}
Colet popStack(Stiva* stiva){
    Colet nou;
    nou.id=-1;
    nou= stiva->vector[stiva->capacitate-1];
    stiva->capacitate--;
    return nou;
}



