#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//lista dublu inlantuita un tablou unidimensional/colectie de elemente de acelasi timp adc omogena nu ocupa o zona de mem contigua 
//fiecare elem are adresa urm ele si celui precedent 
//am leg si la nodul urm si la cel precedent atunci imi permite sa accesam vecinii si sa ne deplasam si inainte si inapoi
//primul si ultimul au NULL 

//lista simplu inlantuita 
//lista dublu inlantuita ca sa o parcurgem de la fin la inceput retinem adresa ultimului nod dupa ce am parcurs de la incep la fin 
//adc tb sa i dau doi param primu si ult 


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//structura pentru un nod dintr-o lista dublu inlantuita
struct Nod{

    struct Nod* prev;
    struct Nod* next;
    Masina info;
};


typedef struct Nod Nod; 
//structura pt lista dubla
struct ListaDubla
{
    Nod* first;
    Nod* last;

};
//fac asta pt incapsulare 

typedef struct ListaDubla ListaDubla;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	//strcpy_s(m1.model, strlen(aux) + 1, aux); //de la sem 
    strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	//strcpy_s(m1.numeSofer, strlen(aux) + 1, aux); //de la sem 
    strcpy(m1.numeSofer, aux);


	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasiniDeLaInceput(ListaDubla ListaDubla) {
	//o primim prin val ca nu modif nmc 
    Nod* aux;
    aux=ListaDubla.first;
    while(aux)
    {
        afisareMasina(aux->info);
        aux=aux->next;
    }
}

void afisareListaMasinaDeLaSfarsit(ListaDubla ListaDubla)
{
    Nod* aux;
    aux= ListaDubla.last;
    while(aux)
    {
        afisareMasina(aux->info);
        aux=aux->prev;
    }
}


void adaugaMasinaInLista(ListaDubla* listaDubla , Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
    Nod* nou;
    nou=malloc(sizeof(Nod));
    nou->info=masinaNoua;
    nou->next=NULL;
    nou->prev=listaDubla->last;
    if(listaDubla->last)
    {
        listaDubla->last->next=nou;
    }
    else{
        listaDubla->first=nou;
        
    }
    listaDubla->last=nou;


}

void adaugaLaInceputInLista(ListaDubla* listaDubla,  Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
    Nod* nou;
    nou=malloc(sizeof(Nod));
    nou->info=masinaNoua;
    nou->prev=NULL;
    nou->next=listaDubla->first;
    if(listaDubla->first)
    {
        listaDubla->first->prev=nou;
    }
    else{
        
        listaDubla->last=nou;
    }
    listaDubla->first=nou;
    
}

ListaDubla* citireLDMasiniDinFisier(const char* numeFisier) {
    FILE *fisier=fopen(numeFisier,"r");
    Masina masina;
    ListaDubla listaMasini;
    listaMasini.first=NULL;
    listaMasini.last=NULL;

    while(!feof(fisier))
    {
        masina=citireMasinaDinFisier(fisier);
        adaugaMasinaInLista(&listaMasini, masina);
    }
    fclose(fisier);
    return &listaMasini;
}

void dezalocareLDMasini(ListaDubla* listaMasini) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
    Nod* aux;
    if(listaMasini->first)
    {
        if(listaMasini->first->next)
        {
          aux=listaMasini->first->next;
          while(aux)
            {
               free((aux->prev->info).model);
               free((aux->prev->info).numeSofer);
               free(aux->prev);
               aux=aux->next;

             }
       }
      free(listaMasini->last->info.model);
      free(listaMasini->last->info.numeSofer);
      free(listaMasini->first);
      listaMasini->first=NULL;
      listaMasini->last=NULL;
       
    }
    
}

float calculeazaPretMediu(ListaDubla listaMasini) {
	Nod* aux= listaMasini.first;
    float Suma=0;
    int nrMasini=0;
    while(aux)
    {
        nrMasini++;
        Suma+=aux->info.pret;
        aux=aux->next;    
    }
    if(nrMasini!=0)
    {
        return Suma/nrMasini;
    }
	return 0;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}

int main() {

    ListaDubla* listaMasini=citireLDMasiniDinFisier("masini.txt");
    
    afisareListaMasiniDeLaInceput(*listaMasini);
    dezalocareLDMasini(&listaMasini);
    printf("medie: %2f", calculeazaPretMediu(*listaMasini));
	return 0;
}