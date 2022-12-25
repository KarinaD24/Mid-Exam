#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

struct Node{
	int idx;
	char name[100];
	int price;
	int qty;
	
	Node *next, *previous;
} *head, *tail;

Node *createNode(int idx, char name[100], int price, int qty){
	Node *newNode = (Node*) malloc(sizeof(Node));
	
	newNode->idx = idx;
	strcpy(newNode->name, name);
	newNode->price = price;
	newNode->qty = qty;
	
	newNode->next = NULL;
	newNode->previous = NULL;
	
	return newNode;
}

void pushTail(int idx, char name[100], int price, int qty){
	Node *temp = createNode(idx, name, price, qty);
	
	if(!head){
		head = tail = temp;
	}
	else{
		tail->next = temp;
		temp->previous = tail;
		tail = temp;
	}
}

void popHead(){
	if(!head){ // kalau tidak ada node
		return;
	}
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	else{
		Node *newHead = head->next;
		head->next = newHead->previous = NULL;
		free(head);
		head = newHead;
	}
}

void popTail(){
	if(!head){
		return;
	}
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	else{
		Node *newTail = tail->previous;
		newTail->next = tail->previous = NULL;
		free(tail);
		tail = newTail;
	}
}

void popMid(char findThisName[100]){
	if(!head){
		return;
	}
	else if(strcmp(head->name, findThisName) == 0){
		popHead();
	}
	else if(strcmp(tail->name, findThisName) == 0){
		popTail();
	}
	else{
		Node *current = head;
		
		while(current->next != NULL){
			if(strcmp(current->next->name, findThisName) == 0){
				break;
			}
			current = current->next;
		}
		
		Node *temp = current->next;
		current->next = temp->next;
		free(temp);
		current = NULL;
	}
}

void readNode(Node *currentNode){
	printf("%d\t", currentNode->idx);
	printf("%s\t", currentNode->name);
	printf("%03d\t\t", currentNode->qty);
	printf("Rp%d\n", currentNode->price);
}

void printMenu(){
	int i = 1;
	puts("\t\tBude's Menu");
	puts("======================================================");
	puts("No.\tName\t\tQuantity\tPrice");
	
	for(Node *temp = head; temp != NULL; temp = temp->next){
//		printf("%d\t", i);
		readNode(temp);
//		i++;
	}
	
	puts("======================================================");
}

// hash table
const int bucketVal = 15;

struct Node_H{
	char cust_name[100];
	
	Node_H *next_H;
} *head_H[bucketVal], *tail_H[bucketVal];

Node_H *createNode_H(char cust_name[100]){
	Node_H *newNode_H = (Node_H*) malloc(sizeof(Node_H));
	
	strcpy(newNode_H->cust_name, cust_name);
	newNode_H->next_H = NULL;
	
	return newNode_H;
}

unsigned long int djb2(char cust_name[100]){
	unsigned long int key = 5381;
	
	for(int i = 0; cust_name[i] != '\0'; i++){
		int asciiVal = int(cust_name[i]);
		key = (key << 5) + key + asciiVal;
	}
	
	return key % bucketVal;
}

void insert_H(char cust_name[100]){
	Node_H *newNode_H = createNode_H(cust_name);
	
	int idx = djb2(cust_name);
	
	if(!head_H[idx]){
		head_H[idx] = tail_H[idx] = newNode_H;
	}
	else{
		tail_H[idx]->next_H = newNode_H;
		tail_H[idx] = newNode_H;
	}
}

void searchCust(Node_H *head, char findThisName[100]){
	Node_H *current_H = head;
	
	while(current_H != NULL){
		if(strcmp(current_H->cust_name, findThisName) == 0){
			printf("%s is present.\n", findThisName);
		}
		
		current_H = current_H->next_H;
	}
	
	printf("%s is not present.\n", findThisName);
}

void view_H(){
	int found = 0;
	for(int i = 0; i < bucketVal; i++){
		if(head_H[i]){
			Node_H *current_H = head_H[i];
			
			while(current_H){
				printf("%d. %s\n", i, current_H->cust_name);
				found = 1;
				current_H = current_H->next_H;
			}
		}
	}
	
	if(found == 0){
		printf("Sorry, there's no customer! :(");
	}
}

void printMain(){
	// detect n print the user's OS here
	#ifdef _WIN32
		printf("System: WINDOWS OS\n");
		
	#elif __APPLE__
		printf("System: MAC OS\n");
		
	#elif __linux__
		printf("System: LINUX OS\n");
		
	#elif TARGET_OS_EMBEDDED
		printf("System: iOS EMBEDDED OS\n");
		
	#elif TARGET_IPHONE_SIMULATOR
		printf("System: iOS SIMULATOR OS\n");
		
	#elif TARGET_OS_IPHONE
		printf("System: IPHONE OS\n");
		
	#elif TARGET_OS_MAC
		printf("System: MAC OS\n");
		
	#elif __ANDROID__
		printf("System: ANDORID OS\n");
		
	#elif __unix__
		printf("System: UNIX OS\n");
		
	#elif _POSIX_VERSION
		printf("System: POSIX BASED OS\n");
		
	#elif __sun
		printf("System: SOLARIS OS\n");
		
	#elif _hpux
		printf("System: HP UX OS\n");
		
	#elif BSD
		printf("System: SOLARIS OS\n");
		
	#elif __DragonFly__
		printf("System: DRAGONFLY BSD OS\n");
		
	#elif __FreeBSD__
		printf("System: FREE BSD OS\n");
		
	#elif __NetBSD__
		printf("System: NET BSD OS\n");
		
	#elif __OpenBSD__
		printf("System: OPEN BSD OS\n");
		
	#else
		printf("System: UNKNOWN\n");
	#endif	
		
	// print date here
	time_t tgl = time(NULL);
	struct tm t = *localtime(&tgl);
	// hari bulan tgl jam tahun
	printf("%s", ctime(&tgl));
	
	puts("1. Add Dish");
	puts("2. Remove Dish");
	puts("3. Add Customer");
	puts("4. Search Customer");
	puts("5. View Warteg");
	puts("6. Order");
	puts("7. Payment");
	puts("8. Exit Warteg");
	printf(">> ");	
}

void cls(){
	for(int i = 0; i < 36; i++){
		printf("\n");
	}
}

int main(){
	
	int opt = 0;
	int index = 0;
	int maxIndex = 0;
	
	do{
		cls();
		
		printMain();
		scanf("%d", &opt);  getchar();
		
		if(opt == 1){ // add dish
			char d_name[100];
			
			
			int valid = 1;
			
			// dish name
			do{
				
				printf("Insert the name of the dish Lowercase letters]: ");
				scanf("%[^\n]", &d_name); getchar();
				
				valid = 1;
				for(int i = 0; i < strlen(d_name); i++){
					if(d_name[i] >= 'A' && d_name[i] <= 'Z'){
						valid = 0;
					}
					// validasi lg biar namanya unik
				}
				
			} while(valid == 0);
			
			// dish price
			
			int d_price;
			do{
				
				printf("Insert the price of the dish [1000..50000]: ");
				scanf("%d", &d_price); getchar();
				
				valid = 1;
				
				if(d_price < 1000 || d_price > 50000){
					valid = 0;
				}
				
			} while(valid == 0);
			
			// dish quantity
			int d_qty;
			do{
				
				printf("Insert the quantity of the dish [1..999]: ");
				scanf("%d", &d_qty); getchar();
				
				valid = 1;
				if(d_qty < 1 || d_qty > 999){
					valid = 0;
				}
				
			} while(valid == 0);
			
			index++;
			maxIndex = index;
			
			pushTail(index, d_name, d_price, d_qty);
			
			puts("\nThe dish has been added!");
			
			printf("\nPress enter to continue...");
			getchar();
		
		}
		else if(opt == 2){ // remove dish
			char find_dName[100];
			
			if(!head){ // if there's not a single dish in the LL
				puts("There is not a single dish here!");
				printf("Press enter to continue..."); getchar();
			}
			else{
				printMenu();
				
				printf("Insert dish's name to be deleted: ");
				scanf("%[^\n]", &find_dName); getchar();
				
				popMid(find_dName);
				
				printf("\nThe dish has been removed!\n\n");
				
				printf("Press enter to continue..."); getchar();
			}		
		}
		else if(opt == 3){ // add customer
			int valid = 1;
			char c_name[100];
			
			do{
				printf("Insert the customer's name [Without space]: ");
				scanf("%[^\n]", &c_name); getchar();
				
				valid = 1;
				for(int i = 0; i < strlen(c_name); i++){
					if(c_name[i] == ' '){
						valid = 0;
						break;
					}
					else if(isalpha(c_name[i]) == 0){
						valid = 0;
						break;
					}
				}
			} while(valid != 1);
			
			insert_H(c_name);
			
			printf("Customer has been added!\n");
			
			printf("\nPress enter to continue..."); getchar();
			
		}
		else if(opt == 4){ // search customer
			char searchThisCust[100];
			int valid = 1;
			
			do{
				printf("Insert the customer's name to be searched: ");
				scanf("%[^\n]", &searchThisCust); getchar();
				
				valid = 1;
				for(int i = 0; i < strlen(searchThisCust); i++){
					if(searchThisCust[i] == ' '){
						valid = 0;
						break;
					}
					else if(isalpha(searchThisCust[i]) == 0){
						valid = 0;
						break;
					}
				}
				
			} while(valid == 0);
			
//			searchCust(head_H, searchThisCust);
			
			printf("\nPress enter to continue..."); getchar();
			
		}
		else if(opt == 5){ // view warteg
			puts("Customer's List");
			view_H();
			printf("\nPress enter to continue..."); getchar();
		}
		else if(opt == 6){ // order
			
		}
		else if(opt == 7){ // payment
			
		}
		else if(opt == 8){ // exit warteg
			cls();
			puts("Please expand your terminal to full screen!\n");
			
			FILE* fp = fopen("start.txt", "r");
			char startText;
			
			do{
				Sleep(1);
				startText = getc(fp);
				printf("%c", startText);
			}
			while(!feof(fp));
				
			printf("\n\nPress enter to continue..."); getchar();
			
			fclose(fp);
		}
		
	} while(opt != 8);
	
	return 0;
}
