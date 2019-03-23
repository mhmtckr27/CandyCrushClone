
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
void sayiatma(char*,int,int);
void yazdirma(char*,int,int);
int patlatma(char*);//skor'u patlatma fonksiyonu ile d�nd�r�yorum.
int kaydirma(char*,int,int);
void yerdegistirme(char*);
int main(){
	setlocale(LC_ALL, "Turkish");
	system("COLOR FC");
	srand(time(NULL));
	static char oyun[100][100];	//[Bir alt sat�r i�in a��klama]=sayac, ne zaman �stten yeni say� d���r�lece�inin kontrol�n� yap�yor.
	int satir,sutun,i,j,sayac=0,sayac2=1,sayac3=0,skor=0; //sayac2, patlayacak eleman kalmad��� ve matrisin tamamen dolu oldu�u�
	char *bas,*patlaindis,devam;//patlaindis, kom�uluk ba�lant�lar� kontrol edilecek olan eleman� temsil ediyor.devam, kullan�c�dan�
	bas=&oyun[0][0];//bas, matrisin ba�lang�� adresini tutuyor.
	printf("\x1b[35m>Oyun alan�n�n b�y�kl���n� giriniz: ");
	scanf("%d %d",&satir,&sutun);
	for(i=0;i<satir;i++)		//Matrisin her eleman�n�
	{				//
		for(j=0;j<sutun;j++)//
		{			//
			oyun[i][j]=32;//
		}			//
	}				//'bo�luk' karakteriyle ilklendiriyor.
	printf("\n");
	while(sayac!=1)
		{
			sayiatma(bas,satir,sutun);//�lk rastgele say� atama ve
			yazdirma(bas,satir,sutun);//ekrana yazd�rma i�lemi
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
						{//[�st sat�r i�in a��klama]=Say�n�n herhangi bir kom�u ba�lant�s� varsa patlama fonksiyonu--
			
							skor=patlatma(patlaindis);	//Son kontrol ise eleman='bo�luk' ise gereksiz fonksiyon�
			
							sayac++;
							sayac2++;
						}
					}
				}
				if(sayac!=1)//E�er patlama ger�ekle�memi�se sayac=1 olarak kalacak ve zaten patlama--
				{			//Olmad��� i�in bu blo�un i�indeki ekrana yazma ve kayd�rma fonksiyonlar� bo� yere--              
	
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
				if(sayac2==1)   //Sayac2 artmad�ysa patlama ger�ekle�memi� demektir ayn� zamanda matris de dolu oldu�u i�in 
	
				{	
					printf("\x1b[35m>Devam etmek istiyor musunuz? (e/h): ");
					devam=getch();
					printf("\x1b[35m%c",devam);
					while(devam!=101&&devam!=104)  //Kullan�c� yanl�� tu� girerse program uyar� verir.
					{
						printf("\n>Hatal� giri� yapt�n�z. Tekrar deneyiniz: ");
						devam=getch();
						printf("\x1b[35m%c",devam);
					}
					if(devam==104)
					{     //Devam etmek istemezse oyun sonland�r�l�p skoru ekrana yaz�l�r.
						printf("\n>Oyun bitti.Skorunuz: %d",skor);
						getch();
						return 0;
					}
					else
					{
						yerdegistirme(bas);  //Devam etmek isterse yerdegistir fonksiyonu ba�lat�l�r.
					}
				}
				sayac2=1;   //Daha �nce patlama fonksiyonunun i�inde artm�� olabilitesi olan sayac2 ilk de�erine d�nd�r�l�r--
		}
}
void sayiatma(char* baslangic,int N,int M){	//Matrise say� atamalar�n� yapan fonksiyon.
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
void yazdirma(char* baslangic,int N,int M){	//Her ad�mda matrisi ekrana yazd�racak fonksiyon.
	int i,j;
	
printf("\n    ");				//Bu sat�rlar� matrisin indislerinin kolayca--
	for(j=0;j<M;j++)				//
	{						//
		printf(" \033[1;30m%d",j);		//
	}						//						
	printf("\n");					//
	printf("    ");				//
	for(j=0;j<M;j++)				//
	{						//
		printf("--");				//
	}						//tespit edilebilmesi ve oyun alan�n�n g�ze ho� gelmesi i�in yazd�m.	
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
			else if((i+j)%2==0)							//Yaz� rengini belirlemek i�in if kulland�m.
				printf("\033[1;31m %c",*(baslangic+i*100+j));		//�ndisler toplam� �iftse, k�rm�z�;
			else if((i+j)%2!=0)							//tek ise ye�il
				printf("\033[1;32m %c",*(baslangic+i*100+j));		//fontta yaz�lacak.
		}
		printf("\n");
	}
}
int patlatma(char* patlayer){		//Patlatmalar� yapan fonksiyon.
	static int skor=0;
	if((*(patlayer)!=*(patlayer+1))&&(*(patlayer)!=*(patlayer+100))&&(*(patlayer)!=*(patlayer-1))&&(*(patlayer)!=*(patlayer-100)))
	{																		
		*patlayer=32;			//Kom�uluk ba�lant�s� kalmayan nesnenin kendisinin de patlamas� olay�.
		skor++;
	}
	else					//Nesnenin herhangi bir kom�uluk ba�lant�s� varsa bu else blo�u �al��acak.
	{					//Ve recursive fonksiyon arac�l���yla patlamalar kom�ular aras�nda yay�lacak.
	if(*(patlayer)==*(patlayer+1))	//Nesnenin ilerisinde ayn� nesne var m�?
	{
		patlatma(patlayer+1);                                               
	}
	if(*(patlayer)==*(patlayer-1))	//Nesnenin gerisinde ayn� nesne var m�?
	{
		*(patlayer-1)=32;
	}
	if(*(patlayer)==*(patlayer-100))	//Nesnenin �st�nde ayn� nesne var m�?
	{
		*(patlayer-100)=32;
	}
	if(*(patlayer)==*(patlayer+100))	//Nesnenin alt�nda ayn� nesne var m�?
	{
		patlatma(patlayer+100);
	}
	*patlayer=32;													
	skor++;
	return skor*skor;
	}
}
int kaydirma(char* baslangic,int N,int M){	//Patlamalardan sonra say�lar� a�a�� d���ren fonksiyon.
	int i,j,count=0,sayac3=0;
	for(i=0;i<M;i++)			//Fonksiyon temelde, her kolon i�in tek tek, sat�rlar�n en sondan ba�lanarak yukar� do�ru taranarak
	{			//'bo�luk' karakterine denk geldik�e count de�i�kenini artt�rmas� ve bo�luk d���nda bir nesneye denk gelince;
		for(j=N-1;j>=0;j--)	//denk gelinen nesneyi count kadar a�a�� kayd�rmas� �zerine kurulu.
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
		count=0;	//Her kolon bitince count s�f�rlan�r ve sonraki kolonun son sat�r�ndan devam edilir ayn� i�leme.
	}
	return sayac3;
}
void yerdegistirme(char* baslangic){		//Kullan�c� devam etmeyi dilerse bu fonksiyon �al���r.
	int temp,indis11,indis12,indis21,indis22;	//�lk eleman i�in===>indis11=oyun[i1][]   indis12=oyun[][j1]    ikinci eleman i�in===> indis21=oyun[i2][] indis22=oyun[][j2]
	printf("\x1b[35m\n>Yer de�i�tirilecek eleman indislerini giriniz: ");  
	scanf("%d %d %d %d",&indis11,&indis12,&indis21,&indis22); //Kullan�c�dan yer de�i�tirmek istedi�i elemanlar�n indisleri al�n�r.
	temp=*(baslangic+indis11*100+indis12); //temp de�i�keni ile bunlar�n yer de�i�tirmesi yap�l�r, sonras�nda oyun devam eder.
	*(baslangic+indis11*100+indis12)=*(baslangic+indis21*100+indis22);
	*(baslangic+indis21*100+indis22)=temp;
}
