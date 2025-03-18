/*
NAME: VINAY M R
Date: 9/1/25
Description: INVERTED SEARCH PROJECT
sample input: ./v.out f1.txt f2.txt 1 3 and
sample output: 	Word => [and] present in 1 files:
				In File: f1.txt present 1 time(s)
*/

#include "main.h"
int main(int argc,char *argv[])
{
	//check for arguments
	if(argc < 2)
	{
		printf("ERROR: Give proper arguments!\n");
		return 0;
	}
	slist *fname_head = NULL;
	//call function for validation
	status ret = validation(argc,argv,&fname_head);
	if(ret == FAILURE)
	{
		printf("Give proper arguments!\n");
		return 0;
	}
	//function call for printing file names list
	ret = print_list(fname_head);
	if(ret == FAILURE)
		printf("INFO : List is Empty\n");
	//hashtable declare
	m_node *hash[27]={};
	s_node *s_head = NULL;
	char search_word[100];
	FILE *fp = NULL;
	//loop for running untill requirement
	printf("1. Create Database\n2. Display Database\n3. Search Database\n4. Save Database\n5. Update Database\n6. Exit\n");
	while(1)
	{
		printf("Choose one option: ");
		int s_case;
		scanf("%d",&s_case);
		//cases for different databases
		switch(s_case)
		{
			case 1:
				//create database case and function call
				ret = Create_hashtable(hash,&s_head,fname_head);
				if(ret == FAILURE)
					printf("Hash Table updation is a Failure\n\n");
				else
					printf("Hash Table creation is successfull\n\n");
				break;
			case 2:
				//displaying database function call
				ret = display_hashtable(hash);
				if(ret == FAILURE)
					printf("Display Hashtable failed!\n");
				printf("\n");
				break;
			case 3:
				printf("Enter the word to search: ");
				scanf("%s",search_word);
				//search the specific word in database function call
				ret = search_hashtable(hash,search_word);
				if(ret == DATA_NOT_FOUND)
					printf("Searched data is not available in hashtable!\n");
				else if(ret == HASHTABLE_IS_EMPTY)
					printf("HashTable Does have any data in that parrticular index!\n");
				printf("\n");
				break;
			case 4:
				//validation function call
				ret = save_validation(hash);
				if(ret == HASHTABLE_IS_EMPTY)
				{
					printf("Validation for saving hashtable hash been failed!\n\n");
					return 0;
				}
				fp = NULL;
				//save database function call
				ret = save_hashtable(hash,fp);
				if(ret == FAILURE)
					printf("Saving has failed!\n");
				else
					printf("SuccessFully Saved!\n");
				printf("\n");
				break;
			case 5:
				//update the the database 
				ret = update_hashtable(hash,fp,&fname_head);
				if(ret == FAILURE)
					printf("HashTable updating has been failed!\n");
				else if(ret == SUCCESS)
					printf("Update SuccessFull!!!\n");
				else if(ret == HASHTABLE_IS_NOT_EMPTY)
					printf("ERROR: HashTable is not Empty!\nDataBase should be empty to update!!!\n");
				//print_list(fname_head);
				printf("\n");
				break;
			case 6:
				return 0;
			default:
				printf("Please choose proper option\n");
		}
	}
}

status validation(int argc,char *argv[],slist **head)
{
	//argument checking
	for(int i = 1; i < argc; i++)
	{
		//input files must be .txt files
		if(!strstr(argv[i],".txt"))
		{
			printf("%s is not an .txt file\n",argv[i]);
			continue;
		}
		//files should exist already
		FILE *fp = fopen(argv[i],"r");
		if(fp == NULL)
		{
			printf("%s file does not exist\n",argv[i]);
			continue;
		}
		//should contain data in file
		fseek(fp,0,SEEK_END);
		if(ftell(fp) == 0)
		{
			printf("%s file doesn't contain any data!\n",argv[i]);
			continue;
		}
		//check for duplicate cases
		status ret = check_for_duplicate(argv[i],head);
		if(ret == SUCCESS)
		{
			printf("%s is duplicate case of inputs\n",argv[i]);
			continue;
		}
		//insert to list
		ret = insert_at_last(head,argv[i]);
		if(ret == FAILURE)
			return FAILURE;
		printf("%s file name has been stored to list\n",argv[i]);
	}
}


status check_for_duplicate(char *str,slist **head)
{
	status ret;
	//list is empty
	if(head == NULL)
		return FAILURE;
	slist *temp = *head;
	while(temp != NULL)
	{
		//check for duplicate case
		if(!strcmp(temp -> f_name,str))
			return SUCCESS;
		temp = temp -> s_next;
	}
	return FAILURE;
}
