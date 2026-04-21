#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-o lista simplu inlantuita
struct Nod
{
    Masina info;
    struct Nod* next;
};
typedef struct Nod Nod;

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	int dim;
    Nod** vector;
};
typedef struct HashTable HashTable;

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
	//strcpy_s(m1.model, strlen(aux) + 1, aux);
	strcpy(m1.model,aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	//strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
	strcpy(m1.numeSofer,aux);

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
	
    if(cap)
    {
        while(cap)
        {
            afisareMasina(cap->info);
            cap=cap->next;
        }
    }

}

void adaugaMasinaInLista(Nod** lista, Masina masinaNoua) {
	Nod* nou=malloc(sizeof(Nod));
    nou->info=masinaNoua;
    nou->next=NULL;
    if((*lista))
    {
        Nod* temp=*lista;
        while(temp->next)
        {
            temp=temp->next;
        }
        temp->next=nou;
    }
    else{
        (*lista)=nou;
    }
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
    ht.dim=dimensiune;
    ht.vector=malloc(ht.dim*sizeof(Nod*));
    for(int i=0;i<dimensiune;i++)
    {
        ht.vector[i]=NULL;
    }
	return ht;
}

int calculeazaHash(int id, int dimensiune) {
	return (id*3)%dimensiune;
}

void inserareMasinaInTabela(HashTable hash, Masina masina) {
	
    int hashCode=calculeazaHash(masina.id, hash.dim);
   if (!hash.vector[hashCode]) {
		// nu avem coliziune
		adaugaMasinaInLista(&hash.vector[hashCode], masina);
	}
	else {
		// avem coliziune
		adaugaMasinaInLista(&hash.vector[hashCode], masina);
	}

}

HashTable citireMasiniDinFisier(const char* numeFisier) {

    FILE * f =fopen(numeFisier,"r");
    HashTable ht=initializareHashTable(5);
	if(!f){
		printf("eroare");
	}
    while(!feof(f))
    {

        inserareMasinaInTabela(ht,citireMasinaDinFisier(f));
    }
    fclose(f);
    return ht;


}

void afisareTabelaDeMasini(HashTable ht) {

	for(int i=0;i<ht.dim;i++)
	{
		printf("clusterul %d:\n", i+1);
		Nod* curent=ht.vector[i];
		if(curent==NULL)
		{
			printf("gol!\n");
		}
		else
		{
			while(curent)
			{
				printf("--");
				afisareMasina(curent->info);
				curent=curent->next;
			}
			
		}
		printf("\n");
		
	}
}

void dezalocareTabelaDeMasini(HashTable *ht) {

	Nod* aux;
	for(int i=0;i<ht->dim;i++)
	{
		aux=ht->vector[i];
		while(aux){ 
			free(aux->info.numeSofer);
			free(aux->info.model);
			Nod* temp=aux->next;
			free(aux);
			aux=temp;

		}
		ht->vector[i]=NULL;

	}
	free(ht->vector);
	ht->vector=NULL;
	ht->dim=0;
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {

	*nrClustere=0;
	for(int i=0;i<ht.dim;i++)
	{
		if(ht.vector[i]!=NULL)
		{
			(*nrClustere)++;
		}
	}
	if(nrClustere==0)
	return NULL;

	else{
		float* valoriMedii=(float*)malloc((*nrClustere)*sizeof(float));
		int index=0;

		for(int i=0;i<ht.dim;i++)
		{
			if(ht.vector[i]!=NULL){
			Nod* aux;
			aux=ht.vector[i];
			float suma=0;
			int nr=0;
			while(aux)
			{
				suma+=aux->info.pret;
				nr++;
				aux=aux->next;

			}
			valoriMedii[index]=suma/nr;
			index++;

		}
		

		}
		return valoriMedii;
	}
	
}

Masina getMasinaDupaId(HashTable ht , int id) {
	Masina m;

	m.id=-1;
	int hashcode= calculeazaHash(id,ht.dim);
	Nod* aux=ht.vector[hashcode];
	while(aux)
	{
		if(aux->info.id==id)
		{
			m=aux->info;
			return m;
		}
		aux=aux->next;
	}
	return m;
}

int main() {

	HashTable hash= citireMasiniDinFisier("masini.txt");
	afisareTabelaDeMasini(hash);
	printf("\n\n\nPreturi medii per cluster:\n");
	Masina m=getMasinaDupaId(hash,8);
	afisareMasina(m);
	dezalocareTabelaDeMasini(&hash);




	return 0;
}