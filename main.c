#include <stdio.h>
#include <stdlib.h>

struct pixel{
    int r,g,b;
};

typedef struct pixel pixel;

pixel getpixel(FILE *in){
    pixel temp;
    fscanf(in,"%i",&temp.r);
    fscanf(in,"%i",&temp.g);
    fscanf(in,"%i",&temp.b);
    return temp;
}

pixel negatyw(pixel p,int wybrany_kolor){
    switch(wybrany_kolor){
        case 1:p.r=255-p.r;
        case 2:p.g=255-p.g;
        case 3:p.b=255-p.b;
    }
    return p;
}

pixel szary(pixel p){
    int avg;
    avg=(p.r+p.g+p.g)/3;
    p.b=avg;
    p.g=avg;
    p.r=avg;
    return p;
}

pixel zeruj(pixel p,int wybrany_kolor){
    switch(wybrany_kolor){
        case 1:p.r=0;
                break;
        case 2:p.g=0;
                break;
        case 3:p.b=0;
                break;
    }
    return p;
}

void zapisz(FILE *out,pixel p){
    fprintf(out,"%i ", p.r);
    fprintf(out,"%i ", p.g);
    fprintf(out,"%i ", p.b);
}

void obrot(FILE *in,FILE *out,int kol,int wie,long pozycja){
    int i,j;
    j=1;
    for(i=0;i<wie;i++){
            clearerr(in);
            while(!feof(in)){
                if(j%kol==0){
                    zapisz(out,getpixel(in));
                }else{
                    getpixel(in);
                }
                 j++;
            }
            fseek(in,pozycja,SEEK_SET);
            printf("...");


    }
}


int menu(FILE *in, FILE *out,int kol, int wie,long pozycja){
	int sw;
	int sw2;

	printf("Wybierz operacje: 1 - negacja koloru , 2 - konwersje do szarosci , 3 - zerowanie koloru , 4 - obrot o 90 stopni, 5 - wyjscie\n");

	scanf("%i", &sw);

	switch(sw){
		case 1:
			printf("Wybierz kolor: 1-czerwony, 2-zielony,3-niebieski \n");
			scanf("%i",&sw2);
			    if(sw2<4 && sw2 >0){
                    while(!feof(in)){
                        zapisz(out,negatyw(getpixel(in),sw2));
                    }
			    } else{
                    printf("Nieprawidlowy zakres");
			    }
                return 1;
                break;
		case 2:
		    while(!feof(in)){
                    zapisz(out,szary(getpixel(in)));
                }
                return 1;
                break;

		case 3:
		    printf("Wybierz kolor: 1-czerwony, 2-zielony,3-niebieski\n ");
		    scanf("%i",&sw2);
		    if(sw2<4 && sw2 >0){
                    while(!feof(in)){
                        zapisz(out,zeruj(getpixel(in),sw2));
                    }
			    } else{
                    printf("Nieprawidlowy zakres");
			    }
            break;
            return 1;
		case 4:
		    obrot(in,out,kol,wie,pozycja);
		    return 1;
		    break;

        case 5:
            return 0;
	}

}




int main() {

char in[256];
    char out[256];

	printf("Podaj nazwe pliku wejsciowego: \n");

	scanf("%s",in);

	printf("Podaj nazwe pliku wyjsciowego: \n");

	scanf("%s",out);

	FILE *plikin = fopen(in, "r");
	if(plikin == NULL){
		printf("Nie udalo sie otworzyc pliku\n");
		return 1;
	}

	FILE *plikout = fopen(out, "w");
	if(plikout == NULL){
		printf("Nie udalo sie stworzyc pliku\n");
		return 1;
	}

	int kol;
	int wie;
	int zakres;
	int pozycja;
	char temp=0;

    while(temp!='\n'){
        fscanf(plikin,"%c",&temp);
        fprintf(plikout,"%c",temp);
    }


    fscanf(plikin,"%i",&kol);

    printf("Ilosc kolumn: %i \n",kol);

    fprintf(plikout,"%i",kol);

    fscanf(plikin,"%i",&wie);

    fprintf(plikout,"\n%i",wie);

    printf("Ilosc wierszy: %i \n",wie);

    fscanf(plikin,"%i",&zakres);

    fprintf(plikout,"\n%i\n",zakres);

    printf("Zakres: %i \n",zakres);

    long punkt;
    punkt = ftell(plikin);

    menu(plikin,plikout,kol,wie,punkt);



	fclose(plikin);
	fclose(plikout);

	system("PAUSE");

	return 0;
}
