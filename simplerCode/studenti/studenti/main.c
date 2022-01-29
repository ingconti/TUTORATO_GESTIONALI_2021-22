//
//  main.c
//  studenti
//
//  Created by ing.conti on 29/01/22.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define MAX_PATH 1024
#define MAX_COLS 10 // ipotesi
#define MAX_LEN_NOME_COLONNA 35


// da cambiare..
#define DIR              "/Users/ingconti/Documents/"

#define PRIMARY_FNAME   "maindat.txt"

// tipi di colonne
typedef enum {
    unknown = 0,
    intero = 1,
    carattere = 2
} TipoColonna;


// colonne
typedef struct Colonna{
    char nome[MAX_LEN_NOME_COLONNA];
    TipoColonna tipoColonna;
}Colonna;


// model:
typedef struct ModelloDati{
    bool ok;
    char fname[MAX_PATH];
    unsigned int nColonne;
    // other data....
    Colonna colonne[MAX_COLS];
}ModelloDati;


typedef struct Riga{
    void * ptrs[MAX_COLS];
    unsigned int nColonne; // potrebbero essere di MENO delle colonne del modello
}Riga;


typedef struct{
   bool ok;
   unsigned int nRighe;
Riga * righe;
}Dati;




ModelloDati leggiFilePrincipale(void);
Dati leggiFileSecondario(ModelloDati modelloDati);
void stampaDati(ModelloDati modelloDati, Dati dati);


int main(int argc, const char * argv[]) {
    
    ModelloDati md = leggiFilePrincipale();
    if (md.ok){
        Dati dati = leggiFileSecondario(md);
        if (dati.ok)
            stampaDati(md, dati);
    }else{
        printf("%s non si apre\n", PRIMARY_FNAME);
    }
    return 0;
}


TipoColonna TrovaTipoColonna(char * puntStrTipoCol){
    // ipotizziamo valori fissi: (solo 2 casi, altriment FOR su array di coppie stringa, enum)
    if (strcasecmp(puntStrTipoCol, "carattere") == 0) // case isenstivie
        return carattere;
    
    if (strcasecmp(puntStrTipoCol, "intero") == 0)
        return intero;
    
    return unknown;
}


void aggiungiColonna(ModelloDati * modello,
                     char *nomeCol, char *tipoCol){
    
    TipoColonna tipo = TrovaTipoColonna(tipoCol);
    int nCol = modello->nColonne;
    if (tipo!=unknown){
        modello->colonne[nCol].tipoColonna = tipo;
        strcpy(modello->colonne[nCol].nome, nomeCol);
    }
    
    modello->nColonne++;
}

ModelloDati leggiFilePrincipale(){
    ModelloDati md = {};
    int righe = 0;
    char bufNomeCol[1024];
    char bufTipoCol[1024];
    
    char fullname[MAX_PATH]=DIR;
    strcat(fullname, PRIMARY_FNAME);
    FILE*fp=fopen(fullname, "r");
    
    if (fp){
        md.ok = true;
        while (!feof(fp)) {
            if (righe==0){
                fscanf(fp, "%s", md.fname);
            }else{
                fscanf(fp, "%s%s", bufNomeCol, bufTipoCol);
                if (!feof(fp))
                    aggiungiColonna(&md, bufNomeCol, bufTipoCol);
            }
            righe++;
        }
        
        fclose(fp);
    }

    
    return md;
}



void * allocaBuffXCella(TipoColonna tipo, char * Str){
    size_t len;
    void * result = NULL;
    switch(tipo){
        case carattere:
            len = strlen(Str);
            result = malloc(len+1);
            strcpy(result, Str);
            break;
        case intero:
                len = sizeof(int);
                int * intPtr = (int*)malloc(len);
                int n = atoi(Str);
                *intPtr = n;
                result = intPtr;
            break;
        case unknown:
            break;
    }
    return result;
}




Dati leggiFileSecondario(ModelloDati modelloDati){
    Dati dati = {
        true,
    };
    
    int nRighe = 0;
    int nColonne = 0;
    char buf[1024]="";
    char fullname[MAX_PATH]=DIR;
    strcat(fullname, modelloDati.fname);
    FILE*fp=fopen(fullname, "r");
    size_t buffSize;
    if (fp){
        modelloDati.ok = true;
        while (!feof(fp)) {
            // reallochiamo x la NUOVA dimemsione: deve sswre 1 + numero righe finora allocate
            buffSize = sizeof(Riga) * (nRighe+1);
            dati.righe = realloc(dati.righe, buffSize);

            for (nColonne=0; nColonne<modelloDati.nColonne; nColonne++) {
                fscanf(fp, "%s", buf);
                if(!feof(fp)){
                    //printf("%20s |", buf);
                    TipoColonna tipo = modelloDati.colonne[nColonne].tipoColonna;
                    dati.righe[nRighe].ptrs[nColonne] = allocaBuffXCella(tipo, buf);
                    //dati.righe[nColonne] = riga;
                }
            }
            if(!feof(fp))
                nRighe++;
            printf("\n");

        }
        
        dati.nRighe = nRighe;
        dati.ok = true;
        fclose(fp);
    }
    return dati;
}


void stampaCella(void * ptr, TipoColonna tipo){
    int * pi;
    char * pc;
    switch (tipo) {
            
        case intero:
            pi = ptr;
            printf("%20d|", *pi);
            break;
            
        case carattere:
            pc = ptr;
            printf("%20s|", pc);
            break;
            
        default:
            break;
    }
}

void stampaDati(ModelloDati modelloDati, Dati dati){
    
    int col, row;
    for (col=0; col<modelloDati.nColonne; col++) {
        printf("%20s|", modelloDati.colonne[col].nome);
    }
    
    printf("\n");

    void *ptrCell;
    for (row=0; row<dati.nRighe; row++) {
        for (col=0; col<modelloDati.nColonne; col++) {
            ptrCell = dati.righe[row].ptrs[col];
            TipoColonna tipo = modelloDati.colonne[col].tipoColonna;
            stampaCella(ptrCell, tipo);
        }
        printf("\n");

    }
    
}
