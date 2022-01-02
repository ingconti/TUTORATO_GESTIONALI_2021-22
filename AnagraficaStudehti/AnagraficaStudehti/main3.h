//
//  main3.h
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
            printf("file secondario %s\n", buff);
            strcpy(md.fname, buff);
        }else{
            printf("%3d %s\n", righe, buff);
            md.nColonne++;
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

void stampaDati(Dati md){
    printf("stampa dati\n");
}




