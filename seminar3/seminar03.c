#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id ;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
	
	printf ("ID: %d || Numar usi: %d || Pret: %f || Model: %-10s || Nume Sofer: %-10s || Serie: %c \n", masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);

}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	if (masini == NULL || nrMasini == 0) {
		printf("vectorul de masini este gol\n");
		return;
	}
	for (int i = 0; i < nrMasini; i++)
		afisareMasina(masini[i]);
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
	Masina* temp = (Masina*)malloc(((*nrMasini) + 1) * sizeof(Masina));
	for (int i = 0; i < *nrMasini; i++)
		temp[i] = (*masini)[i];
	temp[*nrMasini] = masinaNoua;
	free(*masini);
	*masini = temp;
	(*nrMasini)++;
}

Masina citireMasinaFisier(FILE* file) {
	
	
	char linie[256];
	fgets(linie, 255, file);
	char delimitator[3] = ",\n";
	Masina masina;
	masina.id = atoi(strtok(linie, delimitator)); //atoi in int
	masina.nrUsi = atoi(strtok(NULL, delimitator));
	masina.pret = atof(strtok(NULL, delimitator)); //atof in float
	char* aux = strtok(NULL, delimitator);
	masina.model = (char*)malloc((strlen(aux) + 1) * sizeof(char));
	strcpy(masina.model, aux);
	aux = strtok(NULL, delimitator);
	masina.numeSofer = (char*)malloc((strlen(aux) + 1) * sizeof(char));
	strcpy(masina.numeSofer, aux);
	masina.serie = strtok(NULL, delimitator)[0];
	return masina;
}

	

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	FILE* file = fopen(numeFisier, "r");
	if (!file) {
		printf("eroare la deschidere\n");
		return;
		

	}
	else {
		Masina* vectorMasini = NULL;
		while (!feof(file)) {
			Masina masina = citireMasinaFisier(file);
			adaugaMasinaInVector(&vectorMasini, nrMasiniCitite, masina);
//este & la vectormasini pt ca se asteapta la ** si atunci tb sa extrag adresa la pointe

		}
		return vectorMasini;
	}
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
}

int main() {

	int nrmasini=0;
	Masina* masini=citireVectorMasiniFisier("masini.txt", &nrmasini);
	afisareVectorMasini(masini, nrmasini);


	 
	return 0;
}