#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Film{

    int id;
    char* titlu;
    float rating;
};


struct Nod{

    struct Film info;
    struct Nod* next;
    
};
typedef struct Nod Nod;



void adaugaLaFinal(Nod** cap,  struct Film f)
{
    Nod *nou=malloc(sizeof(Nod));
    nou->info=f;
    nou->next=NULL;
    if((*cap)==NULL)
    {
        (*cap)=nou;

    }
    else{
        Nod *temp=*cap;
        while(temp->next)
        {
            temp=temp->next;
            
        }
        temp->next=nou;
        
    }


}


struct Film CitireMasinaDinFisier(FILE* file)
{
    char linie[256];
    fgets(linie,255,file);
    char delimitator[3]=",\n";
    struct Film film;
    film.id=atoi(strtok(linie,delimitator));
    char* aux= strtok(NULL,delimitator);
    film.titlu=malloc((strlen(aux)+1)*sizeof(char));
    strcpy(film.titlu,aux);
    film.rating=atof(strtok(NULL,delimitator));
    return film;
}

void* citireListaMasini(const char* numeFisier)
{
    FILE* file=fopen(numeFisier,"r");
    Nod *cap=NULL;
    while(!feof(file))
    {
        adaugaLaFinal(&cap, CitireMasinaDinFisier(file));

    }
    fclose(file);
    return cap;
}

void AfisareMasina(struct Film film)
{
    printf("id: %d, titlu: %s, rating: %.2f\n", film.id, film.titlu, film.rating);


}

void AfisareListaMasini(Nod *cap)
{
    while(cap!=NULL)
    {
        AfisareMasina(cap->info);
        cap=cap->next;
    }
}

void AfisareMasiniRating(Nod *cap)
{
    while(cap)
    {
        if(cap->info.rating>=8)
        {
            AfisareMasina(cap->info);
            
        }
        cap=cap->next;
    }
}

void dezalocare(Nod **cap)
{
    while(*cap)
    {
        free((*cap)->info.titlu);
        Nod *temp=(*cap)->next;
        free((*cap));
        *cap=temp;
    }
}


int main()
{
    Nod* cap= citireListaMasini("filme.txt");
    AfisareListaMasini(cap);
    printf("\n");
    AfisareMasiniRating(cap);
    printf("\n");
    dezalocare(&cap);
}