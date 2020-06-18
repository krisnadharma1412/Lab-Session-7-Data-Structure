/* 

		   LAB Session 7 Data Structure
By : 
  
  Nama : I Putu Krisna Dharma Saputra
  NIM  : 2301924353
  
*/

//Header File
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//Deklarasi Struct
struct movie_node{
	char name[50];
	char genre[50];
	int price;
	struct movie_node *next;
	struct movie_node *prev;
};

//Deklarasi pointer head dan tail
struct movie_node *head = NULL;
struct movie_node *tail = NULL;

//Deklarasi variabel global
int choice;

//Deklarasi Fungsi
int main_menu();
void movie_list();
void add();
void take();
void delete_node();

//Fungsi Main
int main(){
	do{
		system("cls");
		main_menu();
		switch(choice){
			case 1 : movie_list();
					 break;
			case 2 : add();
					 break;
			case 3 : take();
					 break;
		}
	}while(choice != 4);
	
	system("cls");
	printf("Thanks For Using This Program");
	getch();
	
	return 0;	
}

//Fungsi Main Menu
int main_menu(){
	printf(" EXTRAVAGANT MOVIE SHOP");
	printf("\n ----------------------");
	printf("\n\n 1. View Movie List");
	printf("\n 2. Add New Movie");
	printf("\n 3. Take Movie");
	printf("\n 4. Exit");
	printf("\n\n >> Input Choice : ");
	scanf("%d",&choice);
}

//Fungsi Menu 1 yaitu View Movie List
void movie_list(){
	system("cls");
	struct movie_node *temp = (struct movie_node*) malloc(sizeof(struct movie_node));
	int i = 1;
	printf("\n\t\t\t\t\t--- MOVIE LIST ---\n");
	printf("\n+----+--------------------------------+-----------------------------------------+------------------+");
	printf("\n| No.|          Name of Movie         |                   Genre                 |       Price      |");
	printf("\n+----+--------------------------------+-----------------------------------------+------------------+\n");
	if(tail == NULL){
		printf("+----+--------------------------------+-----------------------------------------+------------------+\n");
	}else{
		temp = head;
		while(temp->next != head){
			printf("| %-2d | %-30s | %-30s          | %-16d |\n",i,temp->name,temp->genre,temp->price);
			temp = temp->next;
			i++;
		}
		printf("| %-2d | %-30s | %-30s          | %-16d |\n",i,temp->name,temp->genre,temp->price);
		printf("+----+--------------------------------+-----------------------------------------+------------------+\n");
	}
	getch();
}

//Fungsi Menu ke 2 yaitu Add New Movie
void add(){
	system("cls");
	fflush(stdin);
	char name[100],genre[100];
	int price;
	
	//Input Movie's Name
	do{
		printf("\n Input Movie's Name [3...21] : ");
		gets(name);
		if(strlen(name) < 3 || strlen(name) > 21){
			printf("\n Name Character's length must be between 3...21! \n");
			getch();
		}
	}while(strlen(name) < 3 || strlen(name) > 21);
	
	//Input Movie's Genre
	do{
		printf("\n Input Movie's Genre [3...30] : ");
		gets(genre);
		if(strlen(genre) < 3 || strlen(genre) > 30){
			printf("\n Genre Character's length' must be between 3...30! \n");
			getch();
		}
	}while(strlen(genre) < 3 || strlen(genre) > 30);
	
	//Input Movie's Price
	do{
		printf("\n Input Movie's Price [$ 10...1000] : ");
		fflush(stdin);
		scanf("%d",&price);
		if(price < 10 || price > 1000 ){
			printf("\n Movie's Price must be between 9...11! \n");
			getch();
		}
	}while(price < 10 || price > 1000 );
	
	insert(name,genre,price);
	
}

//Fungsi Insert pada Queue circular double linked list
int insert(char *name,char *genre,int price){
	fflush(stdin);
	struct movie_node *temp = (struct movie_node*)malloc(sizeof(struct movie_node));
	struct movie_node *ptr;
	
	strcpy(temp->name,name);
	strcpy(temp->genre,genre);
	temp->price = price;
	
	if(head == NULL){
		temp->next = temp->prev = temp;
		head = temp;
		tail = temp;
	}else{
		tail = head->prev;
		temp->next = head;
		temp->prev = tail;
		tail->next = temp;
		head->prev = temp;
	}
	return 0;
}

//Fungsi Menu ke 3 Take Movie
void take(){
	int counter = 1,number;
	struct movie_node *temp = (struct movie_node*)malloc(sizeof(struct movie_node));
	
	if(head == NULL){
		printf("\n Tidak ada data!");
		getch();
		return;
	}
	temp = head;
	while(temp->next != head){
		temp = temp->next;
		counter++;
	}
	
	system("cls");
	movie_list();
	
	do{
	printf("\n\n Input Number of The Movie [1...%d] : ",counter);
	scanf("\n%d",&number);
	}while(number > counter);
	
	delete_node(number);
	
	printf("\n\n --- Buy a Movie Success ---");
	getch();
}


//Fungsi Untuk menghapus data pada queue
void delete_node(int index){
	int counter = 1;
	struct movie_node *ptr = (struct movie_node*)malloc(sizeof(struct movie_node));
	struct movie_node *preptr;
	ptr = head;
	while(counter != index){
		preptr = ptr;
		ptr = ptr->next;
		counter++;
	}
	if(ptr->next == head && ptr == head){
		head = NULL;
		tail = NULL; 
	}else if(ptr == head){
		preptr = head->prev;
		head = head->next;
		preptr->next = head;
		head->prev = preptr;
	}else if(ptr->next == head){
		preptr->next = head;
		head->prev = preptr;
		tail = preptr;
	}else{
		preptr->next = ptr->next;
		ptr->next->prev = preptr;
	}
	free(ptr);
}


