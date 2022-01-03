//
//  main5.h
//  AnagraficaStudenti
//
//  Created by ing.conti on 02 JAN 2022.


#define MAX_PATH 1024
#define MAX_LEN_NOME_COLONNA 35
#define MAX_N_COLONNE 10

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


typedef struct ModelloDati{
    bool ok;
    char fname[MAX_PATH];
    unsigned int nColonne;
    Colonna colonne[MAX_N_COLONNE];
}ModelloDati;

//righe:
typedef struct Riga{
    //vuota... x ora
}Riga;

typedef struct Dati{
    bool ok;
    unsigned int nRighe;
    Riga * righe;
}Dati;

//protos:
ModelloDati leggiFilePrincipale(void);
Dati leggiFileSecondario(ModelloDati md);
void stampaDati(Dati dati, ModelloDati md);
void stampaTipiColonna(ModelloDati md);


int main(int argc, const char * argv[]) {
    
    ModelloDati md = leggiFilePrincipale();
    Dati dati;
    if(md.ok) {
        stampaTipiColonna(md);
        dati = leggiFileSecondario(md);
        if(dati.ok) {
            stampaDati(dati, md);
        }
    }
    return 0;
}

// implementation:

#define STD_DIR "/Users/ingconti/Documents/"
#define STD_NAME "maindat.txt"
#define MAX_PATH 1024
#define MAX_BUFF 1024*16

// f accessorie:
size_t grandezzaFile(FILE *f){
    // save current position:
    long qui = ftell( f );
    fseek(f, 0, SEEK_END);
    long dim = ftell( f );
    fseek(f, qui, SEEK_SET);
    return dim;
}

TipoColonna TrovaTipoColonna(char * puntStrTipoCampo){
    // ipotizziamo valori fissi: (solo 2 casi, altriment FOR su array di coppie stringa, enum)
    if (strcasecmp(puntStrTipoCampo, "carattere") == 0) // case isenstivie
        return carattere;
    
    if (strcasecmp(puntStrTipoCampo, "intero") == 0)
        return intero;
    
    return unknown;
}



void aggiungiColonna(ModelloDati * md, char * rigaTesto){
    //check su limite raggiunto
    if (md->nColonne == MAX_N_COLONNE)return;
    //usiamo strtok: (vista in lab..) cmq: https://man7.org/linux/man-pages/man3/strtok.3.html

    const char *  separators = " ";
    int contToken = 0;
    char * puntStrNomeCampo = NULL;
    char * puntStrTipoCampo = NULL;

    // al primo giro va psssata stringa da analizzare.
    char * found = strtok (rigaTesto, separators);
    while (found)
    {
        //printf("%s ", found);
        contToken++;
        if (contToken>=MAX_N_COLONNE * 2) break; //ogni colonna DUE stringhe
        // creo coppie:
        if (contToken %2 == 1){
            puntStrNomeCampo = found;
        }else{
            puntStrTipoCampo = found;
            printf("%s|%s", puntStrNomeCampo, puntStrTipoCampo);
            TipoColonna tipo = TrovaTipoColonna(puntStrTipoCampo);
            if (tipo!=unknown){
                md->colonne[md->nColonne].tipoColonna = tipo;
                strcpy(md->colonne[md->nColonne].nome,puntStrNomeCampo);
                md->nColonne++;
            }
        }
        found = strtok (NULL, separators);
    }
    
    printf("\n");
}



char CharTipoCol(TipoColonna tipo){
    switch (tipo) {
        case intero:
            return 'I';
            break;

        case carattere:
            return 'C';
        default:
            break;
    }
    return '?';
}

void stampaTipiColonna(ModelloDati md){
    printf("\n%d  colonne\n", md.nColonne);
    for (int i=0; i<md.nColonne; i++) {
        printf("%d col: %s %c\n", i+1, md.colonne[i].nome, CharTipoCol( md.colonne[i].tipoColonna) );
    }
}



ModelloDati leggiFilePrincipale(void){
    ModelloDati md = {}; // C99 init struct.
    
    char fname[MAX_PATH] = STD_DIR;
    strcat(fname, STD_NAME);
    FILE * f = fopen(fname, "rt");
    if (f==NULL)return md;
    // proviamo a leggere i dati:
    char buff[MAX_BUFF];
    int righe=0;
    for (; ; righe++) {
        char * pointerToBuf = fgets(buff, MAX_BUFF, f);
        if (pointerToBuf==NULL)break;
        long len = strlen(buff);
        // replace ending CR with 0:
        buff[len-1] = 0;
        if (righe==0){
            //printf("file secondario %s\n", buff);
            // copia nel modello
            strcpy(md.fname, buff);
        }else{
            //printf("%3d %s\n", righe, buff);
            // parse colonna:
            aggiungiColonna(&md, buff);
        }
    }

    md.ok = true;
    return md;
}

// copiato da quella sopra come "core"
Dati leggiFileSecondario(ModelloDati md){
    Dati dati = {};
    
    char fname[MAX_PATH] = STD_DIR;
    strcat(fname, md.fname);
    FILE * f = fopen(fname, "rt");
    if (f==NULL)return dati;
 
    // proviamo a leggere i dati:
    char buff[MAX_BUFF];
    int righe=0;
    for (; ; righe++) {
        char * pointerToBuf = fgets(buff, MAX_BUFF, f);
        if (pointerToBuf==NULL)break;
        long len = strlen(buff);
        // replace ending CR with 0:
        buff[len-1] = 0;
       printf("%s\n", buff);
    }

    dati.ok = true;
    return dati;
}

void stampaDati(Dati dati, ModelloDati md){
    printf("stampa dati\n");
    
}




