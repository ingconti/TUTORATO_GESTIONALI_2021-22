//
//  main2.h
//  AnagraficaStudehti
//
//  Created by ing.conti on 02 JAN 2022.

//protos:

bool leggiFilePrincipale(void);
bool leggiFileSecondario(void);
void stampaDati(void);



int main(int argc, const char * argv[]) {
    
    if (leggiFilePrincipale()){
        if (leggiFileSecondario()){
            stampaDati();
        }
    }else{
        printf("file principale mancante\n");
    }
    
    return 0;
}

// implementation:

// Sezione FILE

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

bool leggiFilePrincipale(void){
    char fname[MAX_PATH] = STD_DIR;
    strcat(fname, STD_NAME);
    FILE * f = fopen(fname, "rt");
    if (f==NULL)return false;
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
        }else{
            printf("%3d %s\n", righe, buff);
        }
        
    }
    return true;
}

bool leggiFileSecondario(void)
{
    return true;
}

void stampaDati(void)
{
    printf("stampa dati\n");
}



