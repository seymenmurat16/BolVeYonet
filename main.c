#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void merge(float *time,int ,int ,int );
void mergeSort(float *time,int ,int );
void mergeString(char **city,float *,int l,int m,int r); // Þehir deðiþtiriken saatleri de deðiþtirmem gerektiðinden iki tane merge sort fonksiyonu oluþturdum. 
void mergeSortString(char **city,float *,int l,int r);
	
int main (){
	FILE *fs;
	char **city;
	int sayac=0,sayac2,i;
	float *time;
		
	city = (char **)malloc(15*sizeof(char*)); // city için yer açýyorum.
	if( city == NULL ) {
		printf( "Yetersiz bellek!" );
	}
	for( i = 0; i < 15; i++ ) {
		city[i] = (char *)malloc(15*sizeof(char));
		if( city[i] == NULL )
			printf( "Yetersiz bellek!" );
	}
	
	time = (float *)malloc(15*sizeof(float)); // time için yer açýyorum.
	if( time == NULL ) {
		printf( "Yetersiz bellek!" );
	}
	fs=fopen("Cities.txt","r");  // Dosyadan tüm bilgileri okuyorum.
	 	while(!feof(fs)){ 
		 	fscanf(fs,"%s",city[sayac]); // Sehirleri city'e saatlere time'a atýyorum.
		 	fscanf(fs,"%f",&time[sayac]);
		 	sayac++;
	  	}  	
   	fclose(fs); 
   	
	printf("Sirasiz \n");
   	printf("------- \n");
   	for( i = 0; i < sayac; i++ ){ // Sýrasýz olarak tüm bilgiyi yazdýrýyorum.
	 	printf("%-10s %.02f \n",city[i],time[i]);  
	}
   	
	mergeSortString(city,time,0,sayac-1); // Sehirlerin isimlerine göre sýralýyorum.
   	
	printf("\nSehre Gore Sirali \n"); 
   	printf("----------------- \n");
	for( i = 0; i < sayac; i++ ){ // Sehre göre sýralý þekilde yazdýrýyorum.
	 	printf("%-10s %.02f \n",city[i],time[i]);  
	}
   	
	i=0; // i ve sayac2 yi sýfýrlýyorum çünkü þehirlere ilk indisten bakarak devam edip saatlere göre sýralama yapýcam
   	sayac2=0;
	while(i<sayac){ // tüm sehirler bitene kadar devam ediyorum 
		if(strcmp(city[i],city[i+1])==0){ // ilk þehirden baþlayýp eðer bir sonraki indistekide ayný þehirse i yi arttýrýyorum 
			i++;
		}
		else{
			mergeSort(time,sayac2,i); // artýk baþka þehire geçtiðinde i benim rigthim sayac2 ise leftim oluyor çünkü sayac2 bundan önceki þehirin indisinden sonraki indis
			i++;
			sayac2=i;
		}		
	}
   	
   	printf("\nSehre Gore Sirali Iken Saate Gore Sirali \n"); // Þehre ve saate göre sýralý þekilde yazdýrýyorum.
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
		mergeSort(array,l,m); // tek bir tane olana kadar solu ve sað tarafýný bölerek devam ediyorum
		mergeSort(array,m+1,r);
		merge(array,l,m,r);
	}
}

void merge(float array[],int l,int m,int r){
	int i,j,k,n;
	float *yedek;
	n=r-l+1; // n'yi ne kadarlýk yer açmam gerektiði için hesaplýyorum
	yedek = (float *)malloc (n*sizeof(float));
	i=l; // l yi ve m yi kaybetmemek için i ve j(m+1) ye atýyorum
	j=m+1;
	k=0;
	while((i<=m)&&(j<=r)){ // i midden küçük oldukça ve j righttan küçük oldukça devam ediyorum.
		if(array[i]<array[j]){ // eðer dizideki i j den küçükse dizideki i. indisi yedek dizisine yazdýrýyorum her seferinden ikisinide arttýrýoyorum
			yedek[k++]=array[i++]; 
		}
		else{ // eðer j indisindeki deðer daha küçükse o zaman yedeðe j. indisteki deðeri yazdýrýp ikisinide arttýyorum
			yedek[k++]=array[j++];
		}	
	}
	while(i<=m){ // while döngüsünde iki þart olduðu için hangisinden çýktýðýný bilmediðimiz için tekrar kontrol yapýp tüm dizideki elemanlarý yedeðe atýyoruz
		yedek[k++]=array[i++];
	}
	while(j<=r){
		yedek[k++]=array[j++];
	}
	for(i=l,j=0;i<=r;i++,j++){ // artýk yedeðe attýðýmýz sýralý elemanlarý ana dizimize atýyoruz.
		array[i]=yedek[j];
	}
}

void mergeSortString(char **city,float *time,int l,int r){ // þehirleri deðiþtirirken saatleride deðiþtirmem gerektiðinden time'ý da fonksiyona alýyorum 
	int m;
	if(l<r){
		m=(l+r)/2;
		mergeSortString(city,time,l,m);
		mergeSortString(city,time,m+1,r);
		mergeString(city,time,l,m,r);
	}
}
void mergeString(char **city,float *time,int l,int m,int r){ // yukarýda mergeSort fonksiyonunda yaptýðým þeyleri stringler içinde aynýsýný yapýyorum.
	int i,j,k,n;
	char **yedek,temp[15];
	float tmp[15]; // Þehirleri deðiþtirirken ayný deðiþiklikleri saatler içinde yapmam gerektiðinden tmp adlý dizi oluþturuyorum.
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
			tmp[k]=time[i]; // þehir deðiþtirirken ne yaptýysam aynýsýný saatler içinde yapýyorum 
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
		strcpy(city[i],yedek[j]); // en son iki bilgiyide sýralý þekilde ana dizilere atýyorum.
		time[i]=tmp[j];
	}
}

