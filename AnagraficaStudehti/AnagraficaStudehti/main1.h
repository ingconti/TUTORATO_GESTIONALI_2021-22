//
//  main1.h
//  AnagraficaStudehti
//
//  Created by ing.conti on 02 JAN 2022.


#define MAX_PATH 1024

// colonne
typedef struct ModelloDati{
    bool ok;
    char fname[MAX_PATH];
    unsigned int nColonne;
    // other data....
    //Colonna colonne[....]
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
void stampaDati(Dati dati);



int main(int argc, const char * argv[]) {
    ModelloDati md = leggiFilePrincipale();
    Dati dati;
    if(md.ok) {
        dati = leggiFileSecondario(md);
        if(dati.ok) {
            stampaDati(dati);
        }
    }
    return 0;
}

// implementation:

ModelloDati leggiFilePrincipale(void){
    ModelloDati md = {}; // C99 init struct.
    md.ok = true;
    return md;
}

Dati leggiFileSecondario(ModelloDati md){
    Dati dati = {};
    dati.ok = true;
    return dati;
}

void stampaDati(Dati md){
    printf("stampa dati\n");
}



