#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void merge(float *time,int ,int ,int );
void mergeSort(float *time,int ,int );
void mergeString(char **city,float *,int l,int m,int r); // �ehir de�i�tiriken saatleri de de�i�tirmem gerekti�inden iki tane merge sort fonksiyonu olu�turdum. 
void mergeSortString(char **city,float *,int l,int r);
	
int main (){
	FILE *fs;
	char **city;
	int sayac=0,sayac2,i;
	float *time;
		
	city = (char **)malloc(15*sizeof(char*)); // city i�in yer a��yorum.
	if( city == NULL ) {
		printf( "Yetersiz bellek!" );
	}
	for( i = 0; i < 15; i++ ) {
		city[i] = (char *)malloc(15*sizeof(char));
		if( city[i] == NULL )
			printf( "Yetersiz bellek!" );
	}
	
	time = (float *)malloc(15*sizeof(float)); // time i�in yer a��yorum.
	if( time == NULL ) {
		printf( "Yetersiz bellek!" );
	}
	fs=fopen("Cities.txt","r");  // Dosyadan t�m bilgileri okuyorum.
	 	while(!feof(fs)){ 
		 	fscanf(fs,"%s",city[sayac]); // Sehirleri city'e saatlere time'a at�yorum.
		 	fscanf(fs,"%f",&time[sayac]);
		 	sayac++;
	  	}  	
   	fclose(fs); 
   	
	printf("Sirasiz \n");
   	printf("------- \n");
   	for( i = 0; i < sayac; i++ ){ // S�ras�z olarak t�m bilgiyi yazd�r�yorum.
	 	printf("%-10s %.02f \n",city[i],time[i]);  
	}
   	
	mergeSortString(city,time,0,sayac-1); // Sehirlerin isimlerine g�re s�ral�yorum.
   	
	printf("\nSehre Gore Sirali \n"); 
   	printf("----------------- \n");
	for( i = 0; i < sayac; i++ ){ // Sehre g�re s�ral� �ekilde yazd�r�yorum.
	 	printf("%-10s %.02f \n",city[i],time[i]);  
	}
   	
	i=0; // i ve sayac2 yi s�f�rl�yorum ��nk� �ehirlere ilk indisten bakarak devam edip saatlere g�re s�ralama yap�cam
   	sayac2=0;
	while(i<sayac){ // t�m sehirler bitene kadar devam ediyorum 
		if(strcmp(city[i],city[i+1])==0){ // ilk �ehirden ba�lay�p e�er bir sonraki indistekide ayn� �ehirse i yi artt�r�yorum 
			i++;
		}
		else{
			mergeSort(time,sayac2,i); // art�k ba�ka �ehire ge�ti�inde i benim rigthim sayac2 ise leftim oluyor ��nk� sayac2 bundan �nceki �ehirin indisinden sonraki indis
			i++;
			sayac2=i;
		}		
	}
   	
   	printf("\nSehre Gore Sirali Iken Saate Gore Sirali \n"); // �ehre ve saate g�re s�ral� �ekilde yazd�r�yorum.
   	printf("---------------------------------------- \n");
   	for( i = 0; i < sayac; i++ ){
	 	printf("%-10s %.02f \n",city[i],time[i]);  
	}
   	
	return 0;
   	
}

void mergeSort(float array[],int l,int r){
	int m;
	if(l<r){
		m=(l+r)/2; // orta indisi buluyorum
		mergeSort(array,l,m); // tek bir tane olana kadar solu ve sa� taraf�n� b�lerek devam ediyorum
		mergeSort(array,m+1,r);
		merge(array,l,m,r);
	}
}

void merge(float array[],int l,int m,int r){
	int i,j,k,n;
	float *yedek;
	n=r-l+1; // n'yi ne kadarl�k yer a�mam gerekti�i i�in hesapl�yorum
	yedek = (float *)malloc (n*sizeof(float));
	i=l; // l yi ve m yi kaybetmemek i�in i ve j(m+1) ye at�yorum
	j=m+1;
	k=0;
	while((i<=m)&&(j<=r)){ // i midden k���k olduk�a ve j righttan k���k olduk�a devam ediyorum.
		if(array[i]<array[j]){ // e�er dizideki i j den k���kse dizideki i. indisi yedek dizisine yazd�r�yorum her seferinden ikisinide artt�r�oyorum
			yedek[k++]=array[i++]; 
		}
		else{ // e�er j indisindeki de�er daha k���kse o zaman yede�e j. indisteki de�eri yazd�r�p ikisinide artt�yorum
			yedek[k++]=array[j++];
		}	
	}
	while(i<=m){ // while d�ng�s�nde iki �art oldu�u i�in hangisinden ��kt���n� bilmedi�imiz i�in tekrar kontrol yap�p t�m dizideki elemanlar� yede�e at�yoruz
		yedek[k++]=array[i++];
	}
	while(j<=r){
		yedek[k++]=array[j++];
	}
	for(i=l,j=0;i<=r;i++,j++){ // art�k yede�e att���m�z s�ral� elemanlar� ana dizimize at�yoruz.
		array[i]=yedek[j];
	}
}

void mergeSortString(char **city,float *time,int l,int r){ // �ehirleri de�i�tirirken saatleride de�i�tirmem gerekti�inden time'� da fonksiyona al�yorum 
	int m;
	if(l<r){
		m=(l+r)/2;
		mergeSortString(city,time,l,m);
		mergeSortString(city,time,m+1,r);
		mergeString(city,time,l,m,r);
	}
}
void mergeString(char **city,float *time,int l,int m,int r){ // yukar�da mergeSort fonksiyonunda yapt���m �eyleri stringler i�inde ayn�s�n� yap�yorum.
	int i,j,k,n;
	char **yedek,temp[15];
	float tmp[15]; // �ehirleri de�i�tirirken ayn� de�i�iklikleri saatler i�inde yapmam gerekti�inden tmp adl� dizi olu�turuyorum.
	n=r-l+1;
	yedek = (char **)malloc(15*sizeof(char*)); 
	for( i = 0; i < n; i++ ) {
		yedek[i] = (char *)malloc(15*sizeof(char));
	}
	i=l;
	j=m+1;
	k=0;
	while((i<=m)&&(j<=r)){
		if(strcmp(city[i],city[j])<=0){
			strcpy(yedek[k],city[i]);
			tmp[k]=time[i]; // �ehir de�i�tirirken ne yapt�ysam ayn�s�n� saatler i�inde yap�yorum 
			k++; 
			i++;
		}
		else{
			strcpy(yedek[k],city[j]);
			tmp[k]=time[j];
			k++;
			j++;
		}	
	}
	while(i<=m){
		strcpy(yedek[k],city[i]);
		tmp[k]=time[i];
		k++;
		i++;
	}
	while(j<=r){
		strcpy(yedek[k],city[j]);
		tmp[k]=time[j];
		k++;
		j++;
	}
	for(i=l,j=0;i<=r;i++,j++){
		strcpy(city[i],yedek[j]); // en son iki bilgiyide s�ral� �ekilde ana dizilere at�yorum.
		time[i]=tmp[j];
	}
}

