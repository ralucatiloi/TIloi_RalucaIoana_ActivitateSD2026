#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//tb fisierul masini.txt

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
    struct Nod* next;
};

typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux); //ASTA E DE LA SEM
    //strcpy(m1.model, aux);


	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux); //ASTA E DE LA SEM 
    //strcpy(m1.numeSofer, aux);

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

void afisareListaMasini(Nod* cap) {
	while (cap)
    {
        afisareMasina(cap->info);
        cap=cap->next; //ia urm val din lista 
    }
}

void adaugaMasinaInLista(Nod** cap,  Masina masinaNoua) {
    // in cazul in care primim null tb sa modificam
    //cap tb deferentiat de fiecare data
    Nod* temp= malloc(sizeof(Nod));
    temp->info=masinaNoua; //putem sa facem low copy pt ca masina asta nu o sa mai fie niciodata folosita
    temp->next=NULL;
    //de fiecare data cand avem lucru cu o lista verificam daca avem o lista sau este null
    if(!(*cap))
    {
        //cap= &temp; nu poate fi asa pt ca noi luam adresa din stiva a lui temp, dupa se sterge adresa si nu mai fac nimic
        //e pe stiva curenta care o sa dispara 
        //temp e pe stiva si adresa lui e pe stiva deci nu ma interseaza 
        *cap=temp;
    }

    else
    {
        Nod* p=*cap;
        while(p->next)
        {
            p=p->next;  
        }
        p->next=temp;
    }
    
}

void adaugaLaInceputInLista(/*lista de masini*/ Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
}

void* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* file= fopen(numeFisier, "r");
    Nod* cap=NULL;
    while(!feof(file))
    {
        adaugaMasinaInLista(&cap, citireMasinaDinFisier(file)); 
    }
    fclose(file);
    return cap;

}

void dezalocareListaMasini(Nod** temp) {

    while(*temp)
    {
        free((*temp)->info.numeSofer);
        free((*temp)->info.model);
        Nod* nou = *temp;
        nou=(*temp)->next;
        free(*temp);
        *temp=nou;
    }
	
}

float calculeazaPretMediu(/*lista de masini*/) {
	//calculeaza pretul mediu al masinilor din lista.
	return 0;
}

void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

float calculeazaPretulMasinilorUnuiSofer(/*lista masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {

    //ca sa pot sa declar o lista tb sa declar un pointer la nod
        Nod* cap=citireListaMasiniDinFisier("masini.txt");
    afisareListaMasini(cap);
    dezalocareListaMasini(&cap); //primeste adresa la adresa si cap e un sg pointer si adresa mi o da & 
    afisareListaMasini(cap);
	return 0;
}