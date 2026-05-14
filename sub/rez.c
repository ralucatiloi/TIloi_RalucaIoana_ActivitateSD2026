#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Moneda{
    char* tara;
    int valNom;
    float greutate;
    int emitere;


};
typedef struct Moneda Moneda;

struct Nod{
    Moneda info;
    struct Nod* next;

};
typedef struct Nod Nod;

void AdaugareInLS(Nod** cap, Moneda moneda){
    Nod *nou=malloc(sizeof(Nod));
    nou->info=moneda;
    nou->next=NULL;
    if((*cap)){
        Nod *temp=*cap;
        while(temp->next)
        {
            temp=temp->next;
        }
        temp->next=nou;
        

    }
    else{
        (*cap)=nou;

    }

}

Moneda CitireMoneda(FILE* file){

    char linie[256];
    fgets(linie,255,file);
    char delimitator[3]=",\n";
    Moneda moneda;
    char* aux=strtok(linie,delimitator);
    moneda.tara=malloc((strlen(aux)+1)*sizeof(char));
    strcpy(moneda.tara,aux);
    moneda.valNom=atoi(strtok(NULL,delimitator));
    moneda.greutate=atof(strtok(NULL,delimitator));
    moneda.emitere=atoi(strtok(NULL,delimitator));

    return moneda;

}

void* CitireListaMonezi(const char* numeFisier){
    FILE* f=fopen(numeFisier,"r");
    Nod *cap=NULL;
    while(!feof(f)){
        AdaugareInLS(&cap,CitireMoneda(f));

    }
    fclose(f);
    return cap;
    
}

void AfisareMoneda(Moneda moneda){
    printf("tara: %s, valoare nominala: %d , greutate: %.2f , emitere: %d \n", moneda.tara,moneda.valNom, moneda.greutate,moneda.emitere);
}

void AfisareLs(Nod* cap){
    while(cap){
        AfisareMoneda(cap->info);
        cap=cap->next;
    }
}

Moneda MonedaGreutateMax(Nod* cap){
    Moneda max=cap->info;
    Nod* temp=cap->next;

    while(temp!=NULL){
        if(temp->info.greutate>max.greutate){
            max=temp->info;
        }
        temp=temp->next;
    }
    Moneda clona;
    clona.emitere=max.emitere;
    clona.greutate=max.greutate;
    clona.tara=malloc(strlen(max.tara)+1);
    strcpy(clona.tara,max.tara);
    clona.valNom=max.valNom;

    return clona;
}

void StergeMoneda(Nod** cap, float greutate){
    Nod* temp=*cap;
    if(temp->info.greutate==greutate){
        (*cap)=temp->next;
        free(temp->info.tara);
        free(temp);
        return;
    }
    else{
        Nod* anterior;
        while(temp->info.greutate!=greutate){
         
            anterior=temp;
            temp=temp->next;
        }
        if(temp==NULL){
            return;

        }
        anterior->next=temp->next;
        free(temp->info.tara);
        free(temp);
        
    }

}

void dezalocare(Nod** cap){
    while(*cap){
        Nod *temp=(*cap)->next;
        free((*cap)->info.tara);
        free((*cap));
        (*cap)=temp;
    }
    (*cap)=NULL;


}






int main(){


    Nod* monede=CitireListaMonezi("monede.txt");
    AfisareLs(monede);
    printf("\n\n\n\n");
    Moneda moneda= MonedaGreutateMax(monede);
    AfisareMoneda(moneda);
    printf("\n\n\n\n");
    StergeMoneda(&monede, 9.50);
    AfisareLs(monede);




    return 0;
}