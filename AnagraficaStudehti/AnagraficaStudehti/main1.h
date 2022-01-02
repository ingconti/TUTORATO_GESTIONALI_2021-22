//
//  main1.c
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
    }
    
    return 0;
}

// implementation:


bool leggiFilePrincipale(void){
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



