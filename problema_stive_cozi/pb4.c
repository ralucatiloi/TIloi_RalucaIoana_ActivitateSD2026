#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
    char linie[256];
    fgets(linie,255,file);
    char delimitator[3]=",\n";
    Masina masina;
    masina.id=atoi(strtok(linie,delimitator));
    masina.nrUsi=atoi(strtok(NULL,delimitator));
    masina.pret=atof(strtok(NULL,delimitator));
    char* aux=strtok(NULL,delimitator);
    masina.model=malloc((strlen(aux)+1)*sizeof(char));
    strcpy(masina.model,aux);
    aux=strtok(NULL,delimitator);
    masina.numeSofer=malloc((strlen(aux)+1)*sizeof(char));
    strcpy(masina.numeSofer,aux);
    masina.serie=*strtok(NULL,delimitator);

    return masina;

	
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//STACK
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector
struct Nod{
    Masina info;
    struct Nod* next;

};
typedef struct Nod Nod;


void pushStack(Nod** cap, Masina masina) {

    Nod* nou=malloc(sizeof(Nod));
    nou->info=masina;
    nou->next=(*cap);
    (*cap)=nou;

}

Masina popStack(Nod** cap) {

    if((*cap)==NULL)
    {
        Masina rez;
        rez.id=-1;
        return rez;
    }
    else
    {
        Masina rez=(*cap)->info;
        Nod* temp=(*cap)->next;
        free(*cap);
        (*cap)=temp;
        return rez;


    }
}

int emptyStack(Nod *cap) {

    return cap==NULL;
}

Nod* citireStackMasiniDinFisier(const char* numeFisier) {
    FILE * f=fopen(numeFisier,"r");
    Nod* cap=NULL;
    while(!feof(f))
    {
        Masina masina=citireMasinaDinFisier(f);
        pushStack(&cap, masina);
    }
    fclose(f);
    return cap;

}

void dezalocareStivaDeMasini(Nod **stiva) {
	while(!emptyStack(*stiva))
    {
        Masina masina=popStack(stiva);
        free(masina.numeSofer);
        free(masina.model);

    }
}

int size(Nod** cap) {

    int nr=0;
    Nod* stivanoua=NULL;
    while(!emptyStack(*cap))
    {
        Masina masina= popStack(cap);
        nr++;
        pushStack(&stivanoua, masina);
        

    }
    while(!emptyStack(stivanoua))
    {
        Masina temp=popStack(&stivanoua);
        pushStack(cap, temp);

    }
    return nr;
}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector

struct NodDublu{

    Masina info;
    struct NodDublu* prev;
    struct NodDublu* next;

};
typedef struct NodDublu NodDublu;

struct ListaDubla{
    NodDublu* last;
    NodDublu* first;

};
typedef struct ListaDubla ListaDubla;



void enqueue(ListaDubla* coada, Masina masina) {
	
    NodDublu *temp= malloc(sizeof(NodDublu));
    temp->info=masina;
    temp->next=NULL;
    temp->prev= coada->last;

    if(coada->last)
    {
        coada->last->next= temp;

    }
    else{
        coada->first=temp;
    }
    coada->last=temp;

}

Masina dequeue(ListaDubla* coada) {
	//extrage o masina din coada
    Masina rezultat;
    rezultat.id=-1;
    if(coada->first)
    {
        rezultat=coada->first->info;
        NodDublu *temp = coada->first;
        coada->first=temp->next;
        free(temp);

    }
    return rezultat;



}

ListaDubla citireCoadaDeMasiniDinFisier(char* const numeFisier) {
	FILE * f= fopen(numeFisier,"r");
    ListaDubla coada;
    coada.first=NULL;
    coada.last=NULL;
    if(f)
    {
        while(!feof(f))
        {
            enqueue(&coada,citireMasinaDinFisier(f));
        }
        fclose(f);
    }
    return coada;

}

void dezalocareCoadaDeMasini(ListaDubla* coada) {
	NodDublu* aux=coada->first;
    if(coada->first)
    {
        while(aux)
        {
           free( (aux->prev->info).model);
           free((aux->prev->info).numeSofer);
           aux=aux->next;

        }
        free((coada->last->info).model);
        free((coada->last->info).numeSofer);
        free(coada->last);
        coada->first=NULL;
        coada->last=NULL;
    }
}


//metode de procesare
Masina getMasinaByID(Nod** stiva,int id)
{
    Masina rezultat;
    if((*stiva)==NULL)
    {
        rezultat.id=-1;
        return rezultat;
    }
    else
    {
        Nod* stivanoua=NULL;
        while(!emptyStack(*stiva))
        {
            Masina masina=popStack(stiva);

            if(masina.id==id)
            {
                rezultat=masina;
                pushStack(&stivanoua, masina);
                break;
            }
            else
            {
                
                pushStack(&stivanoua,masina); //!!!!
            }
        }
        while(!emptyStack(stivanoua))
        {
            Masina temp=popStack(&stivanoua);
            pushStack(stiva, temp);
        }
    }
    return rezultat;
}

float calculeazaPretTotal(/*stiva sau coada de masini*/);

int main() {

    Nod* stiva=citireStackMasiniDinFisier("masini.txt");
    afisareMasina(popStack(&stiva));
    afisareMasina(popStack(&stiva));
	afisareMasina(popStack(&stiva));
	afisareMasina(getMasinaByID(&stiva, 4));

    printf("\n\n\n");
    ListaDubla coada=citireCoadaDeMasiniDinFisier("masini.txt");
    afisareMasina(dequeue(&coada));
    afisareMasina(dequeue(&coada));
    afisareMasina(dequeue(&coada));
    afisareMasina(dequeue(&coada));



	return 0;
}