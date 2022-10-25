#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>


typedef struct food                                                     		//YEMEK YAPISINI TUTAN STRUCT YAPISI
{					
	char name[50];
	int weight;																	//YEMEK AGIRLIGI
	float price;																//YEMEK FIYATI
	struct food *next;
}FOOD;


void displayList(FOOD *root)                                            		//BUTUN YEMEKLERI LISTELEYEN FONKSIYON
{						
	FOOD *iter = root;
	printf("\nListelenen Yemekler:\n\n");	
	
	if(root != NULL)                                                    		//LISTENIN ILK ELEMANINI TUTAN ROOT NULL YANI BOS DEGILSE YEMEKLERI YAZDIRIYOR
	{								
		printf("Food Name: %s\nFood Weight: %d\nFood Price: %.2f\n\n",iter->name, iter->weight, iter->price);
		iter = iter->next;
		
		while(iter != root)						                        		//LISTE CEMBER YAPISINDA OLDUGU ICIN EN SON ELEMANDAN SONRA ILK ELEMAN GELENE KADAR EKRANA YAZDIRMA ISLEMI
		{
			printf("Food Name: %s\nFood Weight: %d\nFood Price: %.2f\n\n",iter->name, iter->weight, iter->price);
			iter = iter->next;	
		}	
	}	
	
	else
	{
		printf("Listelenecek Eleman Yok!\n");
	}
}


FOOD* createNode(char name[50], int weight, float price)						//LISTEYE EKLENILECEK YEMEGIN BILGILERINE GORE NODE OLUSTURAN FONKSIYON
{
	FOOD *node;
	node = (FOOD*)malloc(sizeof(FOOD));
	strcpy(node->name, name);
	node->weight = weight;
	node->price = price;
	return node;
}	
	


FOOD* addToList(FOOD *root, FOOD *node)								    		//OLUSTURULAN YEMEK NODE'UNU LISTEDE FIYATLARA GORE UYGUN YERE YERLESTIREN FONKSIYON
{
		
	FOOD *iter;
	
	if(root == NULL)															//EGER LISTE BOS ISE ILK ELEMAN YANI ROOT EKLENILECEK OLAN YEMEK OLACAK
	{
		root = node;	
		root->next = root;
		return root;
	}	

	
	if(node->price < root->price)												//EGER EKLENILECEK OLAN YEMEGIN FIYATI LISTENIN EN BASINDAKI YEMEKTEN KUCUK ISE YANI YENI ROOT OLACAK ISE CALISAN UYGUN KOD BLOGU
	{
		node->next = root;
		iter = root;
		
		while(iter->next != root)										        //LISTE CEMBER SEKLINDE OLDUGU ICIN LISTEDEKI SON ELEMANI BULUP ARTIK ONDAN SONRA GELECEK YEMEGI YENI EKLEDIGIMIZ YEMEK ILE DEGISTIRIYORUZ
		{	
			iter = iter->next;
		}
		
		iter->next = node;
		root = node;
		return root;
	}
	
	iter = root;
	
	while(iter->next != root && iter->next->price < node->price)				//YENI GELEN YEMEK ARAYA YA DA EN SONA GELECEK ISE CALISAN KOD BLOGU
    {
		iter = iter->next;
	}
	
	if(iter->next == root)														//EGER SON ELEMAN ISE CALISAN BLOK
	{	
		node->next = root;
		iter->next = node;
	}
	
	else																		//LISTEDE ARAYA EKLENECEK ISE CALISAN BLOK
	{	
		node->next = iter->next;
		iter->next = node;
	}
	
	return root;
}


FOOD* deleteNode(FOOD *root ,char name[50])									    //LISTEDEN YEMEK SILEN FONKSIYON
{	
	FOOD *iter = root;
	if(strcmp(root->name, name) == 0)											//SILINECEK OLAN YEMEK LISTENIN ILK ELEMANI ISE YANI ROOT DEGISECEK
	{	
		if(root->next == root)													//EGER LISTEDE TEK ELEMAN VAR ISE LISTE BOS OLACAGI ICIN ROOT DEGISKENI NULL OLUYOR
		{
			root = NULL;	
		}	
		
		else																	//LISTEDE BIRDEN FAZLA ELEMAN VAR ISE ROOT DEGISIYOR VE LISTENIN SON ELEMANINDAN SONRA GELEN ELEMAN ROOTTAN SONRA GELEN YENI ROOT OLUYOR
		{
			while(iter->next != root)
		    {
				iter = iter->next;
			}
			
			iter->next = root->next;
			root = root->next;
		}
		return root;
	}
	
	while(iter->next != root && strcmp(iter->next->name, name) != 0)			//ARADAN YA DA SONDAN ELEMAN SILME ISLEMI
	{	
		iter = iter->next;
	}
	
	if(strcmp(iter->next->name, name) == 0)
	{	
		iter->next = iter->next->next;
	}
	else                                                                       //EGER SILINECEK ELEMAN YOK ISE
	{	
		printf("Bulunamadi!\n");														
	}
	return root;
}

void selectFood(FOOD *root)                                                     //LISTEDEN YEMEK SECME ISLEMI YAPAN FONKSIYON
{														
	char selection = 'h';
	FOOD *iter = root;
	
	printf("Yemek secimi icin 'e' ,\nbir sonraki yemege gecmek icin 'h' ,\nana menuye donmek icin 'a' degerini giriniz.\n\n");
	while(selection == 'h')
	{																			//e ya da a SECENE KADAR DONEN DONGU
		printf("%s %dgr %.2f TL (e/h/a) : ",iter->name, iter->weight, iter->price);
		
		do
		{
			scanf(" %c",&selection);
		}
		while(selection != 'e' && selection != 'a' && selection != 'h');	    //EGER e a veya h SECMEZ ISE BIR DAHA SECMESINI ISTEYEN KONTROL
		
		printf("\n");
		if(selection != 'e')
		{
			iter = iter->next;
		}
	}
	
	if(selection == 'e')
	{
		printf("%s Sectiniz.\nSiparisiniz en kisa zamanda teslim edilecektir.\nAfiyet Olsun!",iter->name);
	}
}				
	


FOOD* readFile(FOOD *root, char fileName[50])									//DOSYADAN YEMEKLERI OKUYUP LISTEYE EKLEYEN FONKSIYON
{	
	FILE *file;
	char name[50];
	int weight;
	float price;
	FOOD *node;
	
	if((file = fopen(fileName,"r")) != NULL)													
	{	
		while(!feof(file))
		{	
			fscanf(file, "%s %d %f\n", name, &weight, &price);
			if(strcmp(name, "") != 0)											//LISTE BOS ISE ILK SATIRI BOS OKUDUGU ICIN NAME DEGISKENINDE DEGER YOK ISE ONU LISTEYE EKLEMIYOR
			{	
				node = createNode(name, weight, price);							//EKLENILECEK YEMEK BILGILERI ILE NODE OLUSTURUYOR
				root = addToList(root, node);									//VE O NODE'U LISTEYE EKLIYOR
			}
		}		
	}
	else
	{	
		printf("Dosya Bulunamadi!\n");
	}
	return root;
}
	

int main()                                                                      //MAIN FONKSIYON
{	
	FOOD *root = NULL;															//LISTENIN ILK ELEMANINI TUTAN DEGISKEN
	FOOD *node;
	char fileName[50];
	char name[50];
	int weight;
	float price;
	int selection = 1;
	strcpy(fileName, "Foods.txt");												//DOSYA ISMINI BURDA DUZENLIYORUZ
	root = readFile(root, fileName);											//PROGRAM ILK BASLAYINCA DOSYA OKUMA CAGRISI
	printf("Lutfen asagidaki menuden yapmak istediginiz isleme karsilik gelen tusu tuslayiniz");
	
	while(selection != 5)
	{	
		do
		{	
			printf("\n\n1. Yemek Ekleme\n2. Yemek Silme\n3. Yemek Listeleme\n4. Yemek Secimi\n5. Cikis\n\n:Lutfen Seciminizi giriniz... ");
			scanf("%d",&selection);
		}
		while(selection != 1 && selection != 2 && selection != 3 && selection != 4 && selection != 5);									
		
		switch(selection)
		{	
			case 1:																//EGER MENUDEN 1 SECERSE
				
				printf("Eklenilecek olan yemegin ismini giriniz: ");
				scanf("%s",name);
					
				printf("Eklenilecek olan yemegin agirligini giriniz: ");		//YEMEK BILGILERINI ALIYOR
				scanf("%d",&weight);
				
				printf("Eklenilecek olan yemegin fiyatini giriniz: ");
				scanf("%f",&price);
				
				node = createNode(name, weight, price);							//NODE OLUSTURUYOR
		
				root = addToList(root, node);									//LISTEYE EKLIYOR
				break;
				
			case 2:																//EGER MENUDEN 2 SECERSE
				
				printf("Silmek istediginiz yemegin ismini giriniz: ");
				scanf("%s",name);
				
				root = deleteNode(root, name);									//GIRILEN ISIM ILE LISTEDEN ELEMAN SILIYOR
				break;
				
			case 3:																//MENUDEN 3 SECERSE
				
				displayList(root);												//YEMEKLERI LISTELIYOR
				break;
				
			case 4:																//MENUDEN 4 SECERSE
				
				selectFood(root);												//YEMEK SECIMI SAGLAYAN FONKSIYON CAGRIMI
				break;
				
			case 5:																//MENUDEN 5 SECERSE
				
				printf("Basarili Sekilde Cikis Yaptiniz.\n");				    //CIKIS BILGISI YAZDIRILIYOR
				break;
		}
	}
	
	
	
	return 0;
	getch();
}
	
	
	
