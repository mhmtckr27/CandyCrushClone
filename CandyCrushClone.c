
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
void sayiatma(char*,int,int);
void yazdirma(char*,int,int);
int patlatma(char*);//skor'u patlatma fonksiyonu ile döndürüyorum.
int kaydirma(char*,int,int);
void yerdegistirme(char*);
int main(){
	setlocale(LC_ALL, "Turkish");
	system("COLOR FC");
	srand(time(NULL));
	static char oyun[100][100];	//[Bir alt satýr için açýklama]=sayac, ne zaman üstten yeni sayý düþürüleceðinin kontrolünü yapýyor.
	int satir,sutun,i,j,sayac=0,sayac2=1,sayac3=0,skor=0; //sayac2, patlayacak eleman kalmadýðý ve matrisin tamamen dolu olduðu—
	char *bas,*patlaindis,devam;//patlaindis, komþuluk baðlantýlarý kontrol edilecek olan elemaný temsil ediyor.devam, kullanýcýdan—
	bas=&oyun[0][0];//bas, matrisin baþlangýç adresini tutuyor.
	printf("\x1b[35m>Oyun alanýnýn büyüklüðünü giriniz: ");
	scanf("%d %d",&satir,&sutun);
	for(i=0;i<satir;i++)		//Matrisin her elemanýný
	{				//
		for(j=0;j<sutun;j++)//
		{			//
			oyun[i][j]=32;//
		}			//
	}				//'boþluk' karakteriyle ilklendiriyor.
	printf("\n");
	while(sayac!=1)
		{
			sayiatma(bas,satir,sutun);//Ýlk rastgele sayý atama ve
			yazdirma(bas,satir,sutun);//ekrana yazdýrma iþlemi
			getch();
			printf("\n");

			while(sayac!=1)
			{
				sayac=1;
				for(i=0;i<satir;i++)
				{
					for(j=0;j<sutun;j++)
					{
						patlaindis=&oyun[i][j];
						if(((*(patlaindis)==*(patlaindis+1))||(*(patlaindis)==*(patlaindis+100))||(*(patlaindis)==*(patlaindis-1))||(*(patlaindis)==*(patlaindis-100)))&&*(patlaindis)!=32)
						{//[üst satýr için açýklama]=Sayýnýn herhangi bir komþu baðlantýsý varsa patlama fonksiyonu--
			
							skor=patlatma(patlaindis);	//Son kontrol ise eleman='boþluk' ise gereksiz fonksiyon—
			
							sayac++;
							sayac2++;
						}
					}
				}
				if(sayac!=1)//Eðer patlama gerçekleþmemiþse sayac=1 olarak kalacak ve zaten patlama--
				{			//Olmadýðý için bu bloðun içindeki ekrana yazma ve kaydýrma fonksiyonlarý boþ yere--              
	
					yazdirma(bas,satir,sutun);
					getch();
					printf("\n");
					sayac3=kaydirma(bas,satir,sutun);
					if(sayac3!=0)
					{
						yazdirma(bas,satir,sutun);
						getch();
						printf("\n");
						sayac3=0;
					}
				}
			}
				sayac=0;
				if(sayac2==1)   //Sayac2 artmadýysa patlama gerçekleþmemiþ demektir ayný zamanda matris de dolu olduðu için 
	
				{	
					printf("\x1b[35m>Devam etmek istiyor musunuz? (e/h): ");
					devam=getch();
					printf("\x1b[35m%c",devam);
					while(devam!=101&&devam!=104)  //Kullanýcý yanlýþ tuþ girerse program uyarý verir.
					{
						printf("\n>Hatalý giriþ yaptýnýz. Tekrar deneyiniz: ");
						devam=getch();
						printf("\x1b[35m%c",devam);
					}
					if(devam==104)
					{     //Devam etmek istemezse oyun sonlandýrýlýp skoru ekrana yazýlýr.
						printf("\n>Oyun bitti.Skorunuz: %d",skor);
						getch();
						return 0;
					}
					else
					{
						yerdegistirme(bas);  //Devam etmek isterse yerdegistir fonksiyonu baþlatýlýr.
					}
				}
				sayac2=1;   //Daha önce patlama fonksiyonunun içinde artmýþ olabilitesi olan sayac2 ilk deðerine döndürülür--
		}
}
void sayiatma(char* baslangic,int N,int M){	//Matrise sayý atamalarýný yapan fonksiyon.
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(*(baslangic+i*100+j)==32){
				if ((i+j)%2==0)
					*(baslangic+i*100+j)=rand()%10+48;
				else
					*(baslangic+i*100+j)=rand()%10+48;
			}
		}
	}
}
void yazdirma(char* baslangic,int N,int M){	//Her adýmda matrisi ekrana yazdýracak fonksiyon.
	int i,j;
	
printf("\n    ");				//Bu satýrlarý matrisin indislerinin kolayca--
	for(j=0;j<M;j++)				//
	{						//
		printf(" \033[1;30m%d",j);		//
	}						//						
	printf("\n");					//
	printf("    ");				//
	for(j=0;j<M;j++)				//
	{						//
		printf("--");				//
	}						//tespit edilebilmesi ve oyun alanýnýn göze hoþ gelmesi için yazdým.	
	printf("\n");									
	for(i=0;i<N;i++)
	{
		if(i<10)
		{
			printf("\033[1;30m  %d|",i);
		}
		else
			printf("\033[1;30m %d|",i);
		for(j=0;j<M;j++)
		{
			if(*(baslangic+i*100+j)==32)
				printf("  ");												
			else if((i+j)%2==0)							//Yazý rengini belirlemek için if kullandým.
				printf("\033[1;31m %c",*(baslangic+i*100+j));		//Ýndisler toplamý çiftse, kýrmýzý;
			else if((i+j)%2!=0)							//tek ise yeþil
				printf("\033[1;32m %c",*(baslangic+i*100+j));		//fontta yazýlacak.
		}
		printf("\n");
	}
}
int patlatma(char* patlayer){		//Patlatmalarý yapan fonksiyon.
	static int skor=0;
	if((*(patlayer)!=*(patlayer+1))&&(*(patlayer)!=*(patlayer+100))&&(*(patlayer)!=*(patlayer-1))&&(*(patlayer)!=*(patlayer-100)))
	{																		
		*patlayer=32;			//Komþuluk baðlantýsý kalmayan nesnenin kendisinin de patlamasý olayý.
		skor++;
	}
	else					//Nesnenin herhangi bir komþuluk baðlantýsý varsa bu else bloðu çalýþacak.
	{					//Ve recursive fonksiyon aracýlýðýyla patlamalar komþular arasýnda yayýlacak.
	if(*(patlayer)==*(patlayer+1))	//Nesnenin ilerisinde ayný nesne var mý?
	{
		patlatma(patlayer+1);                                               
	}
	if(*(patlayer)==*(patlayer-1))	//Nesnenin gerisinde ayný nesne var mý?
	{
		*(patlayer-1)=32;
	}
	if(*(patlayer)==*(patlayer-100))	//Nesnenin üstünde ayný nesne var mý?
	{
		*(patlayer-100)=32;
	}
	if(*(patlayer)==*(patlayer+100))	//Nesnenin altýnda ayný nesne var mý?
	{
		patlatma(patlayer+100);
	}
	*patlayer=32;													
	skor++;
	return skor*skor;
	}
}
int kaydirma(char* baslangic,int N,int M){	//Patlamalardan sonra sayýlarý aþaðý düþüren fonksiyon.
	int i,j,count=0,sayac3=0;
	for(i=0;i<M;i++)			//Fonksiyon temelde, her kolon için tek tek, satýrlarýn en sondan baþlanarak yukarý doðru taranarak
	{			//'boþluk' karakterine denk geldikçe count deðiþkenini arttýrmasý ve boþluk dýþýnda bir nesneye denk gelince;
		for(j=N-1;j>=0;j--)	//denk gelinen nesneyi count kadar aþaðý kaydýrmasý üzerine kurulu.
		{
			if(*(baslangic+i+j*100)==32)			
			{
				count++;
			}
			else if(count>0)   
			{
				*(baslangic+j*100+count*100+i)=*(baslangic+j*100+i);
				*(baslangic+j*100+i)=32;
				sayac3++;
			}
		}
		count=0;	//Her kolon bitince count sýfýrlanýr ve sonraki kolonun son satýrýndan devam edilir ayný iþleme.
	}
	return sayac3;
}
void yerdegistirme(char* baslangic){		//Kullanýcý devam etmeyi dilerse bu fonksiyon çalýþýr.
	int temp,indis11,indis12,indis21,indis22;	//Ýlk eleman için===>indis11=oyun[i1][]   indis12=oyun[][j1]    ikinci eleman için===> indis21=oyun[i2][] indis22=oyun[][j2]
	printf("\x1b[35m\n>Yer deðiþtirilecek eleman indislerini giriniz: ");  
	scanf("%d %d %d %d",&indis11,&indis12,&indis21,&indis22); //Kullanýcýdan yer deðiþtirmek istediði elemanlarýn indisleri alýnýr.
	temp=*(baslangic+indis11*100+indis12); //temp deðiþkeni ile bunlarýn yer deðiþtirmesi yapýlýr, sonrasýnda oyun devam eder.
	*(baslangic+indis11*100+indis12)=*(baslangic+indis21*100+indis22);
	*(baslangic+indis21*100+indis22)=temp;
}
