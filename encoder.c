#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

typedef struct {
    char* segmentMesaj;
    double complexitate;
} task3 ;

char* subString (char* mesaj,int start,int lungime)  //impartirea pe componente
{
    char *rezultat;
    rezultat=malloc ( ( lungime + 1 ) * sizeof ( char ) );
    strncpy ( rezultat, mesaj + start -1, lungime );
    rezultat[lungime] = '\0';
    return rezultat;
}


char *strdel(char *d, int n) //stergerea de n caractere
{
    char aux[120];
    if (n<strlen(d)){
        strcpy(aux, d+n);
        strcpy(d, aux);
    }
    else strcpy ( d, "\0" );
    return d;
}

char* reverse(char *mesaj)
{
    char *rezultat;
    char *temp;
    int len = (int)strlen(mesaj);
    rezultat=calloc(len,sizeof(char));
    for (int i=0; i<len; i++){
        temp = strcat(rezultat,subString(mesaj,len-i,1));
        rezultat=temp;
    }
    return rezultat;
}

int existaNumar(char* mesaj)
{
    for(int i=0; i<strlen(mesaj); i++){
        int aschii = mesaj[i];
        if (aschii>47 && aschii<58) return 1;
    }
    return 0;
}

int divizor (char* mesaj)
{
    int nr=(int)strlen(mesaj);
    int maxDivizor = 0;
    int jumatate = nr/2;
    for( int i=0; i<jumatate; i++) {
        if (nr % ( jumatate-i ) ==0) {
            maxDivizor=(jumatate-i);
            break;
        }
    }
    return maxDivizor;
}


int isDigit(char c)
{
    if (c >'0' && c <= '9') {
        return 1;
    }
    return 0;
}

int verificareNumar(char* mesaj)
{
    for (int i = 1; i < strlen(mesaj); i++) {
        int aschii = mesaj[i];
        
        
        if (aschii < '1' || aschii > '9') {
            return 1;
        }
    }
    
    if (atoi(mesaj) >= -2147483647 && atoi(mesaj) <= 2147483647) {
        return 0;
    }
    
    return 1;
}

char* aparitii(char* mesaj)
{
    //returnez pe prima pozitie char cu maxim de aparitii urmat de char cu minim aparitii
    int aparitiiMin=5000;
    int aparitiiMax=0;
    int nrApar = 0;
    char *chrMin = calloc(1,sizeof(char));
    char *chrMax = calloc(1,sizeof(char));
    char *cCautat = calloc(1,sizeof(char));
    char *cExistent = calloc(1,sizeof(char));
    int len = (int)strlen(mesaj);
    for(int i=0; i<len; i++){
        cCautat=subString(mesaj,i+1,1);
        nrApar = 0;
        for(int j=0; j<len; j++){
            cExistent = subString(mesaj,j+1,1);
            if (strcmp(cCautat,cExistent)==0) nrApar=nrApar+1;
        }
        if (nrApar<aparitiiMin || aparitiiMin==0) {
            aparitiiMin=nrApar;
            strcpy(chrMin,cCautat);
        }
        if (nrApar>aparitiiMax || aparitiiMax==0) {
            aparitiiMax=nrApar;
            strcpy(chrMax,cCautat);
        }
    }
    free(cCautat);
    free(cExistent);
    return strcat(chrMax,chrMin);
}

int tipMesaj(char* mesaj)
//1 pentru cuvinte, 2 caractere, 3 numere
{
    if (strlen(mesaj) == 1) {
        int aschii = mesaj[0];
        
        if ((aschii > '0') && (aschii <= '9')) {
            return 3;
        } else {
            return 2;
        }
    } else {
        if (verificareNumar(mesaj) == 0) {
            return 3;
        } else {
            return 1;
        }
    }
}

double complex(char* mesaj)
{
    double suma=0;
    double retur;
    for(int i=0; i<strlen(mesaj); i++) {
        int ascii = mesaj[i];
        suma += ascii;
    }
    retur =suma/strlen(mesaj);
    return retur;
}

task3 *order(task3* tmpStruct, int lungime) {	//Bubble Sort pentru a sorta in functie de complexitate
    for (int i = 0; i < lungime; ++i) {
        for (int j = i + 1; j < lungime; ++j) {
            if (tmpStruct[i].complexitate < tmpStruct[j].complexitate) {
                task3 temp  =  tmpStruct[i];
                tmpStruct[i] = tmpStruct[j];
                tmpStruct[j] = temp;
            }
            else {
            		if (tmpStruct[i].complexitate == tmpStruct[j].complexitate) 
            		{
            			if (strcmp(tmpStruct[i].segmentMesaj,tmpStruct[j].segmentMesaj)>0) {
            																				task3 temp=tmpStruct[i];
            																				tmpStruct[i]=tmpStruct[j];
            																				tmpStruct[j]=temp;}
            		}
            	}
        }
    }
    return tmpStruct;
}

char* rearanjare(char *mesaj,int cntComponente)
{
    int lungimeSegment=floor(strlen(mesaj)/cntComponente);
    int lungimeRest =strlen(mesaj) % cntComponente;
    task3* solutie ;
    solutie = malloc(cntComponente*(sizeof(char)+sizeof(double)));
    
    for(int i=0; i<cntComponente -1 ; i++){
        solutie[i].segmentMesaj = subString(mesaj, i*lungimeSegment+1, lungimeSegment);
        solutie[i].complexitate=complex(solutie[i].segmentMesaj);
    }
    solutie[cntComponente - 1].segmentMesaj = subString(mesaj, (cntComponente - 1 )*lungimeSegment+1, lungimeSegment + lungimeRest);
    solutie[cntComponente-1].complexitate=complex(solutie[cntComponente-1].segmentMesaj);
    order(solutie, cntComponente);
    	char *ord;
    	ord=(char *)malloc(strlen(mesaj)*sizeof(task3));
    	for(int i=0; i<cntComponente/2; i++){
  		strcpy(ord,solutie[i].segmentMesaj);
    	strcpy(ord,solutie[cntComponente-i-1].segmentMesaj);
    	}
    	if (cntComponente%2==1) strcpy(ord,solutie[cntComponente/2].segmentMesaj);
    	return ord;  
}


int main()
{
    int m, nrNr = 0, nrCuv = 0, nrCar = 0, min, max, nr;
    char *v, *x;
    int i=0, j;
    char str[50];
    char *aux, *aux2, *aux3, *aux4;
    char *mesajCod, *mesajCod2;
    mesajCod=calloc(5000, sizeof(char));
    mesajCod2=calloc(5000, sizeof(char));
    aux2=(char*)malloc(50*sizeof(char));
    aux=(char*)malloc(50*sizeof(char));
    aux3=(char*)malloc(3*sizeof(char));
    aux4=(char*)malloc(3*sizeof(char));
    v = (char*) malloc(50 * sizeof(char));
    x= (char*) malloc(2*sizeof(char));
    strcpy(mesajCod, "\0");
    strcpy(mesajCod2, "\0");
    char **input = (char**) malloc(1000 * sizeof(char*));
    int index = 0;
    while (strcmp(v, "END")) { //citirea se opreste cand intalneste END
        fgets(v, 60, stdin);
        v[strlen(v) - 1] = '\0';
        input[index] = (char*) malloc(strlen(v) * sizeof(v));
        strcpy(input[index], v);
        index++;
    }
    for (i = 0; i < index - 2; i++) {
        v = input[i];
        if (tipMesaj(v)==1){
            nrCuv++;
            if (strcmp(v, "END")) {
                if (existaNumar(v)==0) {
                    aux=strcpy(aux, v+divizor(v));
                    aux2=strncpy(aux2, v, divizor(v));
                    aux2[divizor(v)]='\0';
                    aux=strcat(aux, aux2);
                }
                else {
                    aux=strcpy(aux, v+divizor(v));
                    aux=reverse(aux);
                    aux2=strncpy(aux2, v, divizor(v));
                    aux2[divizor(v)]='\0';
                    aux=strcat(aux, aux2);
                }
                mesajCod=strcat(mesajCod, aux);
            }
        }
        if (tipMesaj(v)==2) {
            nrCar++;
            if (mesajCod[0]!='\0') {
                
                x=aparitii(mesajCod);
                aux3[0]=x[0];
                aux3[1]=v[0];
                aux3[2]=x[1];
                aux3[3]='\0';
                mesajCod=strcat(mesajCod, aux3);}
            else mesajCod=strcat(mesajCod, v);}
        if (tipMesaj(v)==3){
            nrNr++;
            if (v[0] == '-') {
                strdel(v,1);
                min = atoi(v);
                for (j = 1; j<strlen(v); j++) {
                    aux4[0] = v[0];
                    aux4[1] = '\0';
                    strdel(v , 1);
                    strcat(v, aux4); //primul caracter se muta la sfarsit
                    nr = atoi(v);
                    if (nr<min) min = nr;
                }	
                sprintf(str, "%d", min);
                mesajCod = strcat(mesajCod, str);
            }
            else {
                max = atoi(v);
                for (j = 0; j<strlen(v); j++) {
                    aux4[0] = v[0];
                    aux4[1] = '\0';
                    strdel(v, 1);
                    strcat(v, aux4);
                    nr = atoi(v);
                    if (nr>max) max = nr;
                }
                sprintf(str, "%d", max);
                mesajCod=strcat(mesajCod, str);
            }
        }
    }
	m=atoi(input[index-2]);
    strcpy(mesajCod2, mesajCod);
    printf("%d %d %d\n", nrCuv, nrCar, nrNr);
    printf("%s\n", mesajCod);
    printf("%s\n", rearanjare(mesajCod2, m));
    return 0;
}
