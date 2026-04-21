#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//heap structura de date liniara omogena folosita pt cozi de prioritati
//funct princ sa mi aduca val min sau max din acea colectie de elem 


//facem max heap
//se face arbore
//val nodului tb sa fie mai mare decat informatiile din copiii directi - asta pt max 
//ultimul parinte formula: p=(n-2)/2



struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru Heap
//un vector de elemente, lungimea vectorului si numarul de elemente din vector
struct Heap {
	int lungime;
    int nrElemViz;
    Masina* vector;
};
typedef struct Heap Heap;

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

Heap initializareHeap(int lungime) {
    Heap heap;
    heap.lungime=lungime;
    heap.nrElemViz=0;
    heap.vector=malloc(lungime*sizeof(Masina));
    return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	//filtreaza heap-ul pentru nodul a carei pozitie o primeste ca parametru

    //facem dupa pret
    int stanga=2*pozitieNod+1;
    int dreapta=2*pozitieNod+2;
    int pozmax=pozitieNod;
    if(stanga<heap.nrElemViz &&   heap.vector[stanga].pret>heap.vector[pozmax].pret)
    //pt min :  if(stanga<heap.nrElemViz &&   heap.vector[stanga].pret < heap.vector[pozmax].pret)
    {
        pozmax=stanga;

    }
    if(dreapta<heap.nrElemViz &&   heap.vector[dreapta].pret>heap.vector[pozmax].pret)
    //pt min if(dreapta<heap.nrElemViz &&   heap.vector[dreapta].pret < heap.vector[pozmax].pret)
    {
        pozmax=dreapta;

    }
    if(pozmax!=pozitieNod)
    {
        Masina aux=heap.vector[pozmax];
        heap.vector[pozmax]=heap.vector[pozitieNod];
        heap.vector[pozitieNod]=aux;
        if(pozmax<((heap.nrElemViz-2)/2));
        {
            filtreazaHeap(heap, pozmax);
        }
    }


}

Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
	//citim toate masinile din fisier si le stocam intr-un heap 
	// pe care trebuie sa il filtram astfel incat sa respecte 
	// principiul de MAX-HEAP sau MIN-HEAP dupa un anumit criteriu
	// sunt citite toate elementele si abia apoi este filtrat vectorul

    FILE* f=fopen(numeFisier,"r");
     Heap heap;
    heap= initializareHeap(10);
    if(f)
    {
       
        while(!feof(f))
        {
            
            heap.vector[heap.nrElemViz++]=citireMasinaDinFisier(f);
        }
    }
    fclose(f);

    for(int i=(heap.nrElemViz-2)/2; i<=0;i--)
    {
        filtreazaHeap(heap,i);

    }
    return heap;


}

void afisareHeap(Heap heap) {
	//afiseaza elementele vizibile din heap
    for(int i=0; i<heap.nrElemViz;i++)
    {
        afisareMasina(heap.vector[i]);

    }
}

void afiseazaHeapAscuns(Heap heap) {
	//afiseaza elementele ascunse din heap
    for(int i=heap.nrElemViz ; i<heap.lungime;i++)
    {
        afisareMasina(heap.vector[i]);

    }
}

Masina extrageMasina(Heap* heap) {
	
    Masina aux;
    aux.id=-1;

    if(heap->nrElemViz>0)
    {
        heap->nrElemViz--;
        aux=heap->vector[0];
        heap->vector[0]=heap->vector[heap->nrElemViz];
        heap->vector[heap->nrElemViz]=aux;
        filtreazaHeap(*heap,0); //asa exita riscul sa existe noduri care nu repsecta pt arbori mai mari
        
    }

    
    return aux;
}


void dezalocareHeap(Heap* heap) {
	//sterge toate elementele din Heap
    for(int i=0;i<heap->lungime;i++)
    {
        free(heap->vector[i].numeSofer);
        free(heap->vector[i].model);

    }
    free(heap->vector);
    heap->vector=NULL;
    heap->nrElemViz=0;
    heap->lungime=0;
}

int main() {

    Heap heap= citireHeapDeMasiniDinFisier("masini.txt");
    afisareHeap(heap);
    printf("extrageri\n");
    afisareMasina(extrageMasina(&heap));
    afisareMasina(extrageMasina(&heap));
    afisareMasina(extrageMasina(&heap));

    printf("print ascuns:\n ");
    afiseazaHeapAscuns(heap);

    dezalocareHeap(&heap);





	return 0;
}