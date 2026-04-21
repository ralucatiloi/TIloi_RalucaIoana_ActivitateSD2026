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

struct Nod{
    Masina info;
    struct Nod *prev; 
    struct Nod *next;

};
typedef struct Nod Nod;

struct ListaDubla
{
    Nod* last;
    Nod* first;

};
typedef struct ListaDubla Lista;

Masina citireMasinaDinFisier(FILE * file) {
	
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
    masina.serie=strtok(NULL,delimitator)[0];

    return masina; //!!!!!!!


}

void afisareMasina(Masina masina) {

    printf(" id: %d, nrusi: %d, pret: %.2f, model: %s, numesofer: %s, serie: %c\n", masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie) ;
	
}

void afisareListaMasini(Lista lista) {
	
    Nod* aux= lista.first;     //!!!!!!
    while(aux)
    {
        afisareMasina(aux->info);
        aux=aux->next;
    }


}

void afisareListaMasiniDeLaSfarsit(Lista lista)
{
    Nod *aux=lista.last;
    while(aux)
    {
        afisareMasina(aux->info);
        aux=aux->prev;
    }
}

void adaugaMasinaInLista(Lista *lista, Masina masinaNoua) {
	
    Nod *nou= (Nod*)malloc(sizeof(Nod));
    nou->info=masinaNoua;
    nou->prev=lista->last;
    nou->next=NULL;

    if(lista->last)
    {
        lista->last->next=nou;

    }
    else
    {
        lista->first=nou;
    }
    lista->last=nou;

}

void adaugaLaInceputInLista(Lista *lista, Masina masinaNoua) {
	
    Nod* nou=(Nod*)malloc(sizeof(Nod));
    nou->info=masinaNoua;
    nou->prev=NULL;
    nou->next=lista->first;

    if(lista->first)
    {
        lista->first->prev=nou;

    }
    else{
        lista->last=nou;
    }

    lista->first=nou;



}

Lista citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f=fopen(numeFisier,"r");
    Lista lista;
    lista.first=NULL;
    lista.last=NULL;
    Masina masina;
    while(!(feof(f)))
    {
        masina= citireMasinaDinFisier(f);
        adaugaMasinaInLista(&lista, masina);

    }
    fclose(f);
    return lista;


}

void dezalocareLDMasini(Lista* lista) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
    Nod *aux= lista->first;
    if(lista->first)
    {
        while(aux)
        {
            free((aux->prev->info).numeSofer);
            free((aux->prev->info).model);
            free(aux->prev);
            aux=aux->next;
        }
        free(lista->last->info.model);
        free(lista->last->info.numeSofer);
        free(lista->last);
        lista->first=NULL;
        lista->last=NULL;
    }


}

float calculeazaPretMediu(Lista lista) {
	//calculeaza pretul mediu al masinilor din lista.
    int nrmasini=0;
    float suma=0;
    Nod *aux=lista.first;
    while(aux)
    {
        suma+=aux->info.pret;
        nrmasini++;
        aux=aux->next;

    }
    if(nrmasini==0)
	return 0;
    else
    return suma/nrmasini;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(Lista lista) {
	Nod *aux=lista.first;
    float pretmax=0;
    char* nume;
    while(aux)
    {
        if(aux->info.pret>=pretmax)
        {
            pretmax=aux->info.pret;
            strcpy(nume,aux->info.numeSofer);
        }
        aux=aux->next;
    }
	return nume;
}

int main() {

    Lista lista=citireLDMasiniDinFisier("masini.txt");
    afisareListaMasini(lista);
    printf("\n");
    afisareListaMasiniDeLaSfarsit(lista);
    printf("\n");
    printf("media: %.2f", calculeazaPretMediu(lista));
    printf("\n");
    dezalocareLDMasini(&lista);
    afisareListaMasini(lista);



	return 0;
}