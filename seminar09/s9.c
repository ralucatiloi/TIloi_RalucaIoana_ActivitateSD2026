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

//creare structura pentru un nod dintr-un arbore binar de cautare
struct NodArbore {
	Masina info;
	struct NodArbore* left;
	struct NodArbore* right;


};
typedef struct NodArbore NodArbore;

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
	//strcpy_s(m1.model, strlen(aux) + 1, aux);
    strcpy(m1.model, aux);


	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	//strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
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


void adaugaMasinaInArbore(NodArbore **root,  Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID

	if (*root) {
		if ((*root)->info.id > masinaNoua.id) {
			adaugaMasinaInArbore(&(*root)->left, masinaNoua);
		}
		else {
			adaugaMasinaInArbore(&(*root)->right, masinaNoua);
		}
	}
	else {
		NodArbore* nou = (NodArbore*)malloc(sizeof(NodArbore));
		nou->info = masinaNoua;
		nou->left = NULL;
		nou->right = NULL;
		*root = nou;
	}

}

NodArbore* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	NodArbore* root = NULL;
	if (f) {
		while (!feof(f)) {
			Masina m = citireMasinaDinFisier(f);
			adaugaMasinaInArbore(&root, m);
		}
		fclose(f);
		return root;
	}
	

}

void afisareInordine(NodArbore* root) {

	if (root != NULL) {
		afisareInordine(root->left);
		afisareMasina(root->info);
		afisareInordine(root->right);

	}
}

void afisareMasiniDinArbore(NodArbore* root) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
	//moduri : radacina stanga dreapta (preordine), stanga dreapta radacina (postordine), stanga radacina dreapta (inordine)

	//preordine
	if (root != NULL) {
		afisareMasina(root->info);
		afisareMasiniDinArbore(root->left);
		afisareMasiniDinArbore(root->right);

	}



}

void dezalocareArboreDeMasini(NodArbore** radacina) {
	//sunt dezalocate toate masinile si arborele de elemente
	if (*radacina != NULL) {
		dezalocareArboreDeMasini(&(*radacina)->left);
		dezalocareArboreDeMasini(&(*radacina)->right);
		free((*radacina)->info.model);
		free((*radacina)->info.numeSofer);
		free((*radacina));
		*radacina = NULL;
	}

}

Masina getMasinaByID(NodArbore* radacina, int id) {
	
	if (radacina == NULL) {
		Masina m;
		m.id = -1;
		return m;
	}
	else {
		if (id < radacina->info.id) {
			return getMasinaByID(radacina->left, id);
		}
		else {
			if (id>radacina->info.id)
				return getMasinaByID(radacina->right, id);
			else {
				Masina m = radacina->info;
				m.model = malloc(strlen(radacina->info.model) + 1);
				strcpy(m.model, radacina->info.model);
				m.numeSofer = malloc(strlen(radacina->info.numeSofer) + 1);
				strcpy(m.numeSofer, radacina->info.numeSofer);
				return  m;

			}
		}
	}
}

int determinaNumarNoduri(NodArbore* radacina) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	if (radacina) {
		
			return 1 + determinaNumarNoduri(radacina->left) + determinaNumarNoduri(radacina->right);
	}
	else {
		return 0;
	}


	
}

int calculeazaInaltimeArbore(NodArbore* radacina) {
	if (radacina) {
		return 1+ max(calculeazaInaltimeArbore(radacina->left), calculeazaInaltimeArbore(radacina->right));

	}
	else {
		return 0;
	}

	
}

float calculeazaPretTotal(NodArbore* radacina) {
	//calculeaza pretul tuturor masinilor din arbore.
	if (radacina) {
		return radacina->info.pret + calculeazaPretTotal(radacina->left) + calculeazaPretTotal(radacina->right);
	}
	else {
		return 0;
	}

	
}

float calculeazaPretulMasinilorUnuiSofer(NodArbore* radacina, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	if (radacina) {
		if (strcmp(radacina->info.numeSofer, numeSofer) == 0) {
			return radacina->info.pret + calculeazaPretulMasinilorUnuiSofer(radacina->left, numeSofer) + calculeazaPretulMasinilorUnuiSofer(radacina->right, numeSofer);

		}
		else {
			return calculeazaPretulMasinilorUnuiSofer(radacina->left, numeSofer) + calculeazaPretulMasinilorUnuiSofer(radacina->right, numeSofer);
		}

	}
	else {
		return 0;
	}

	
}

int main() {
	NodArbore* radacina = citireArboreDeMasiniDinFisier("masini.txt");
	afisareInordine(radacina);

	afisareMasina(getMasinaByID(radacina, 3));

	
	printf("numar noduri: %d\n", determinaNumarNoduri(radacina));

	printf("inaltime arbore: %d\n", calculeazaInaltimeArbore(radacina));

	printf("pret total: %.2f\n", calculeazaPretTotal(radacina));

	printf("pretul pt Ionescu: %.2f\n", calculeazaPretulMasinilorUnuiSofer(radacina, "Ionescu"));


	return 0;
}