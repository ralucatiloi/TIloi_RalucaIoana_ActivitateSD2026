#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Telefon{
    int id;
    char* producator;
    int RAM;
    float pret;
};

void AdaugaTelefon( struct  Telefon** t, int* nrTelefoane, struct Telefon telefonNou)
{
   struct Telefon* temp;
   temp= malloc((*nrTelefoane+1)*sizeof(struct Telefon));
   for(int i=0;i<*nrTelefoane;i++)
   {
    temp[i]=(*t)[i];
   }

   temp[*nrTelefoane]= telefonNou;

   if(*t!=NULL)
   {
    free(*t);
   }

   *t=temp;
   (*nrTelefoane)++;
}

struct Telefon* citireDinFisier (const char* numeFisier, int *nrTelefoane)
{
    FILE* file  = fopen(numeFisier, "r");
    if(!file)
    {
        printf("Eroare\n");
        return NULL;
    }
    else{
        printf("bine\n");
        struct Telefon *vectorTelefon=NULL;
        *nrTelefoane=0;
        while(!feof(file))
        {
        struct Telefon t;
        char linie[255];
        fgets(linie,255,file);
        char delimitator[3]=",\n";
        t.id=atoi(strtok(linie,delimitator));
        char* aux= strtok(NULL,delimitator);
        t.producator=malloc((strlen(aux)+1)*sizeof(char));
        strcpy(t.producator,aux);
        t.RAM=atoi(strtok(NULL,delimitator));
        t.pret=atof(strtok(NULL,delimitator));

        AdaugaTelefon(&vectorTelefon, nrTelefoane, t);
        
        }
        fclose(file);
        return vectorTelefon;
        

    }
}

void afisareTelefon(struct Telefon t )
{
    printf("id: %d, producator: %s, RAM: %d, pret: %.2f\n", t.id, t.producator, t.RAM, t.pret);

}

void afisareVectorTelefonae(struct Telefon* t,  int *nrTelefoane)
{
    for(int i=0;i<*nrTelefoane;i++)
    {
        afisareTelefon(t[i]);
    }
}


void copiazaTelefoaneScumpe(struct Telefon* telefonvechi, int nrVechi, struct Telefon** telefonNou, int *nrNou, int prag)
{
    *nrNou=0;
    for(int i=0;i<nrVechi;i++)
    {
        if(telefonvechi[i].pret>=prag)
        {
            (*nrNou)++;
        }
    }

    if(*nrNou>0)
    {
        *telefonNou=malloc((*nrNou)*sizeof(struct Telefon));
        int index=0;

        for(int i=0;i<nrVechi;i++)
        {
            if(telefonvechi[i].pret>=prag)
            {
                (*telefonNou)[index].id=telefonvechi[i].id;
                (*telefonNou)[index].pret=telefonvechi[i].pret;
                (*telefonNou)[index].RAM=telefonvechi[i].RAM;
                (*telefonNou)[index].producator=malloc(strlen((telefonvechi[i].producator)+1)*sizeof(char));
                strcpy((*telefonNou)[index].producator,telefonvechi[i].producator);

                index++;

            }
        }
    }
    else{
        *telefonNou=NULL;
    }
}



void dezalocare(struct Telefon** t, int *nrTelefoane)
{
    for (int i=0;i<*nrTelefoane;i++)
    {
        free((*t)[i].producator);
        (*t)[i].producator=NULL;

    }

    free(*t);

    *t=NULL;
    *nrTelefoane=0;
}



int main()
{
    int nrTelefoane=0;
    struct Telefon *t= citireDinFisier("telefonae.txt", &nrTelefoane);
    struct Telefon *t1;
    int nrTel=0;
    afisareVectorTelefonae(t,&nrTelefoane);
    printf("\n");
    copiazaTelefoaneScumpe(t, nrTelefoane, &t1, &nrTel, 3000 );
    afisareVectorTelefonae(t1,&nrTel);
    dezalocare(&t,&nrTelefoane);
    return 0;
}