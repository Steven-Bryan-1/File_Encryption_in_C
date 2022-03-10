//This file includes "system("clear")" which may not work depending on where the code is run, so just comment that out

//Include all header files
//need time.h for srand()
//Need string.h for the string functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Prototypes for reading binary, writing binary, emcryption, finding length of a file, decryption, and to show a file
char * read_file(char file_name[]);
int file_write(char *input, char file_name[]);
void *encrypt_file(char file_name[], char key_name[], char encrypt_name[], int length);
unsigned char *make_rand_key(int length);
void *encrypt(char * array1,unsigned char *array,unsigned char  return_array[],int length);
int buffer_length(char file_name[]);
char * show_contents(char file_name[]);
void *decrypt(char encrypted_name[], char new_key_name[], char decrypt_name[],int length2);



int main(){

//Declaring all chars for the file names
	char fname[100];
	char new_file [100];
	char key_name[100];
	char key_name2[100];
	char decrypt_name[100];
	char encrypted_name[100];
	char txt_file[100];

//declaring variables for variables used in the program
	int length1;
	int decrypt_length=0;
	int choice=0;
	int x=0;
	

//while loop contains a menu to encrypt/ decrypt/ read/ and exit
while(1){

//Clear the screen
	system("clear");

//loop to make space
	for(int g=0;g<10;g++)
		printf("\n");
//loop to make space
	for(int f=0;f<15;f++)
		printf("* ");
//menu items below
	printf("\nWhat would you like to do?\n ");
	printf("Encrypt a file enter 1.\n ");
	printf("Decrypt a file enter 2.\n ");
	printf("Read a file enter 3.\n ");
	printf("Exit press 4.\n");
	for(int f=0;f<15;f++)
		printf("* ");
	printf("\nWhat is your choice: ");
	scanf("%d",&choice);


switch (choice){

//Case 1 is used for encryption 
	case 1:
		
printf("What is the name of the file you would like to encrypt (if its a txt file, add .txt at the end): ");
		scanf("%s",fname);



//Make an integer the length of the file used in the loop to get contents
		length1= buffer_length(fname);


		printf("What would you like to call the encrypted file: ");
		scanf("%s",new_file);

		printf("What would you like to call the key file: ");
		scanf("%s", key_name);
//Calls encryption funtion
		encrypt_file(fname,key_name,new_file,length1);

		printf("\nYour encrypted file is saved as: %s", new_file);
		break;

//Case 2 is used for decryption
	case 2:
		printf("What is the name of the file you would like to decrypt:");
		scanf("%s",encrypted_name);



		printf("What is the name of the key file: ");

		scanf("%s",key_name2);
		length1= buffer_length(key_name2);

		printf("What would you like to call the decrypted file: ");
		scanf("%s", decrypt_name);
//Calls decryption function
		decrypt(encrypted_name,key_name2,decrypt_name,length1);

//calls show_contents function which prints file information to the screen
		show_contents(decrypt_name);
		printf("\n The above text is the decrypted file.\n");
		printf("\n ");	
		 for(int f=0;f<15;f++)
                printf("* ");

		printf("\nTo go back to the main menu press 1\n To exit the program press 2.");
		scanf("%d",&x);
		 for(int f=0;f<15;f++)
                printf("* ");

//if the user enters 2 then the program exists with exit(0)
	if(x==2){
		exit(0);
		}			
//if not 2 then goes back to main menu
	else{
		break;
		}		


	case 3:
		printf("What file would you like to read? ");
		scanf("%s", fname);
		show_contents(fname);
		printf("\n");
	 for(int f=0;f<15;f++)
                printf("* ");

		printf("\nTo go back to the main menu press 1\n To exit the program press 2: ");
		scanf("%d",&x);
	
	 for(int f=0;f<15;f++)
                printf("* ");

//if the user enters 2 then the program exists
	if(x==2){
		exit(0);
		}
//if not 2 then breaks back to the main menu 
	else{
		break;
		}



	case 4:
	printf("\nGood Bye!\n");	
	exit(0);
		break;
//default case is to give the warning that its not a valid choice
	default:
		printf("\nThat is not a valid choice\n");
		break;
		

		}

}
}





void *decrypt(char encrypted_name[], char new_key_name[], char decrypt_name[],int length2){
	printf("\n ");
	//get the variables ready
	int count=0;
	int length3=0;
	char d_array[10000];
	char *decrypted_array=d_array;
//call read_file and save results in encr_file or encrypted file
	char * encr_file=read_file(encrypted_name);

//call read file and save the key file
	char * keyed_name=read_file(new_key_name);
//printf("the length of length is %d",length2);

//this loop XOR to get the original file, but its too long, so will do another loop
	for(int p=0; p<=10000; p++){
	char temp=(encr_file[p]^keyed_name[p]);
	decrypted_array[p]= temp;
	}
	//get the length of the XOR file that now has a NULL terminator in it
	length3=buffer_length(decrypted_array);
//loop to copy the XOR file into the decrypted array pointed at
	for(int p=0; p<=length3-1; p++){
	char temp=(encr_file[p]^keyed_name[p]);
	decrypted_array[p]= temp;
	}


	printf("file has been decrypted.\n");
//Write the decrypted file into a document
	file_write(decrypted_array, decrypt_name);
//free malloc
	free(encr_file);

}



void *encrypt_file(char file_name[], char key_name[], char encrypt_name[],int length){

//get a pointer to an array that is from the file
	char * buffer=read_file(file_name);

//create an array for the encrypted information
	char encrypted_array[10000];

//create a pointer to an array that is the encrypted array
	char *return_array=encrypted_array;


	char *key=make_rand_key(length);
//Write the key to file
	file_write(key,key_name  );
//encrypt the original file with the key file
	encrypt(buffer,key,encrypted_array,length);	
//write the encrypted string to a file
	file_write(return_array, encrypt_name);
//free the buffer
	free(buffer);
	free(key);
}


//function to encrypt the data
void *encrypt(char *original,unsigned  char *key,unsigned  char return_array[], int length){
	
	int count2=0;
   //Loop to XOR the contents of the two arrays
 	for(int i=0;i<length;i++){
//make a temp value for XOR of arrays and then put that result into an array that gets returned
	int temp=(int)(original[i]^key[i]);
        return_array[i]= temp;
	count2++;
				}	

}



//function to get the length of a files characters
int buffer_length(char file_name[]){
	FILE* fp;
	int count	 = 0;
  
    
  
    // To store a character read from file
	char c;
  
  	
    // Open the file
	fp = fopen(file_name, "rb");
  
    // Check if file exists
	if (fp == NULL) {
      //  printf("Could not open file %s", file_name);
        return 0;
	free(fp);
    }

 
 
    // Extract characters from file
    // and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp)){
  
        // Increment count for this character
        count = count + 1;
}  
    // Close the file
	fclose(fp);

   
//this is the length of the file contents  
    return count;
}



char * read_file(char file_name[]){
 
	int p=0;
//read a file function
        FILE *ptr;
        ptr = fopen(file_name,"rb");

       //check to see if the pointer is NULL
	if(ptr){
        fseek(ptr, 0,SEEK_END); //points to the end of file
        long size = ftell(ptr);

        rewind(ptr);
        char *buffer= (char*) malloc(sizeof(char)*(size+1));
        fread(buffer, size+1,1,ptr);
       //Read the buffer
        fread(&buffer,sizeof(char),size+1,ptr);
	//close the pointer
        fclose(ptr);
        //return the buffer which is a pointer to an array
        return buffer;
	//free the memory used for the buffer
	free(buffer);
	}
	//if the FILE pointer is NULL
	else{
	printf("\nThis file does not exist!\n");
	 for(int f=0;f<15;f++)
                printf("* ");

	printf("\nWould you like to go back to the main menu or exit?\n");
	printf("\nEnter 1 for main menu\n");
	printf("\nEnter 2 to exit program: ");
	scanf("%d",&p);
	 for(int f=0;f<15;f++)
                printf("* ");

	switch (p){
	
	
	case 1:
	printf("\nreturning the main menu\n");
	break;
	case 2:

	printf("\nThank you, have a great day!\n");
	exit(0);
	break;
	
	default:
	printf("\nThats not a valid choice, goodbye!\n");
	exit(0);
	break;
}

}
free(ptr);

}
	
int file_write(char *input, char file_name[]){
//create a pointer to a FILE
	FILE *fpt;  
//open the file in read binary mode
	fpt=fopen(file_name,"wb");
	
	fseek(fpt, 0,SEEK_END); //points to the end of file
        
	long size1 = ftell(fpt);

        rewind(fpt);
       // char *buffer2= (char*) malloc(sizeof(char)*(size1+1));

	//write the data
	fwrite(input,sizeof(input),10000,fpt);
//close the pointer to the data
	fclose(fpt);
	return 0;
}




unsigned char *make_rand_key(int length){
	//create a array of chars
	char *charArray =(char*) malloc(length*sizeof(char));
	//there is no char array return NULL
	if(!charArray){
	return NULL;
			}
        //create the values for the random genorator range to use             
	int upper= 255;
	int lower=0;
	int count=0;    
//srand is used to get a random seed based on the time
	srand(time(0));
    //this loop adds the random number or "char" to the array which will be used for the key
    for (int i = 0; i < length+1; ++i) {
        
      charArray[i] = (char)((rand() % (upper - lower + 1)) + lower);
count++;
   }
   // return the array of random chars
   return charArray;
//free the memory of the char array
    free(charArray);
}


char * show_contents(char file_name[]){
 	//read a file function
        FILE *ptr;
        ptr = fopen(file_name,"rb");
       

        fseek(ptr, 0,SEEK_END); //points to the end of file
        long size = ftell(ptr);

        rewind(ptr);
       //create a buffer that will be used to get the contents of the file from 
	char *buffer1= (char*) malloc(sizeof(char)*(size+1));
        fread(buffer1, size+1,1,ptr);
        printf("%s",buffer1);  //tests, prints contents of file
       
//close the memory that was used for the pointer
        fclose(ptr);
        //return buffer, which will basically give back a pointer to the buffer
        return buffer1;
//free the memory that is being used for the buffer
	free(buffer1);
}


