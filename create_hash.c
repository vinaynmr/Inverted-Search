#include "main.h"

status Create_hashtable(m_node *hash[], s_node **s_head,slist *f_head)
{
	slist *fname_temp = f_head;
	status ret;
	//run loop for input files list to fetch data
	while(fname_temp !=  NULL)
	{
		//open files
		FILE *fp = fopen(fname_temp -> f_name,"r");
		if(fp == NULL){
			printf("%s file open has been failed!\n",fname_temp -> f_name);
			return FAILURE;
		}
		//fetch each word by word
		char word[100],ch = 0;
		while(fscanf(fp,"%s",word) != EOF)
		{
			//read confirmation
			if(word[0] == '\0')
			{
				printf("Reading of the word has been failed!\n");
				return FAILURE;
			}
			ch = 0;
			int flag = 0;
			//check for index postion
			if(word[0] >= 97 && word[0] <= 122)
				ch = word[0];
			else if(word[0] >= 65 && word[0] <= 90)
				ch = word[0] + 32;
			//call funtion to add for hashtable
			ret	= update_for_create_hashtable(hash,s_head,fname_temp,word,ch);
			if(ret == FAILURE)
			{
				printf("Update HashTable has been failed!\n");
				return FAILURE;
			}
		}
		//list traverse
		fname_temp = fname_temp -> s_next;
	}
	return SUCCESS;
}


status update_for_create_hashtable(m_node **hash,s_node **s_head,slist * temp,char *word,char ch)
{
	//check is letter or special character for index
	if(ch >= 97 && ch <= 122)
	{
		//index is empty doesn't have any node
		if(hash[ch - 97] == NULL)
		{
			//create main node
			m_node *main_new = create_main_node(word);
			if(main_new == NULL)
				return FAILURE;
			//create sub node
			s_node *sub_new = create_sub_node(temp -> f_name);
			if(sub_new == NULL)
				return FAILURE;
			main_new -> sub_link = sub_new;
			hash[ch - 97] = main_new;
			return SUCCESS;
		}
		//if index has existing nodes
		m_node *main_temp = hash[ch - 97];
		m_node *main_prev = NULL;
		s_node *sub_prev = NULL,*sub_temp = NULL;
		//traverse to check each words
		while(main_temp != NULL)
		{
			//check word is already exists
			if(!strcmp(main_temp -> word,word))
			{
				//if exits check for file
				sub_temp = main_temp -> sub_link;
				while(sub_temp != NULL)
				{
					//check if file is already added
					if(!strcmp(sub_temp -> file_name,temp -> f_name))
					{
						sub_temp -> word_count++;
						return SUCCESS;
					}
					sub_prev = sub_temp;
					sub_temp = sub_temp -> sub_link;
				}
				//if file is not added then add it by creating new sub node
				s_node *sub_new = create_sub_node(temp -> f_name);
				if(sub_new == NULL)
					return FAILURE;
				sub_prev -> sub_link = sub_new;
				main_temp -> file_count++;
				return SUCCESS;	
			}
			//traverse through main nodes
			main_prev = main_temp;
			main_temp = main_temp -> main_link;	
		}
		//if main nodes doesn't match then create new node and update
		m_node *main_new = create_main_node(word);
		if(main_new == NULL)
			return FAILURE;
		main_prev -> main_link = main_new;
		//create sub node
		s_node *sub_new = create_sub_node(temp -> f_name);
		if(sub_new == NULL)
			return FAILURE;
		main_new -> sub_link = sub_new;
		return SUCCESS;
	}else{
		//for special character
		if(hash[26] == NULL)
		{
			// if index is null update main and sub node
			m_node *main_new = create_main_node(word);
			if(main_new == NULL)
				return FAILURE;
			s_node *sub_new = create_sub_node(temp -> f_name);
			if(sub_new == NULL)
				return FAILURE;
			main_new -> sub_link = sub_new;
			hash[26] = main_new;
			return SUCCESS;
		}
		//if not null traverse to find in worst case
		m_node *main_front = hash[26],*main_prev = NULL;
		s_node *sub_front = NULL,*sub_prev = NULL;
		while(main_front != NULL)
		{
			//check if word already exists in table
			if(!strcmp(main_front -> word,word))
			{
				sub_front = main_front -> sub_link;
				sub_prev = NULL;
				//check for file in subnodes
				while(sub_front != NULL)
				{
					//if it exists increase it count
					if(!strcmp(sub_front -> file_name,temp -> f_name))
					{
						sub_front -> word_count++;
						return SUCCESS;
					}
					sub_prev = sub_front;
					sub_front = sub_front -> sub_link;
				}
				//if not add new sub node
				s_node *sub_new = create_sub_node(temp -> f_name);
				if(sub_new == NULL)
					return FAILURE;
				sub_prev -> sub_link = sub_new;
				main_front -> file_count++;
				return SUCCESS;	
			}
			main_prev = main_front;
			main_front = main_front -> main_link;
		}
		//if main node doesn't exists add new main node and sub node
		m_node *main_new = create_main_node(word);
		if(main_new == NULL)
			return FAILURE;
		main_prev -> main_link = main_new;
		s_node *sub_new = create_sub_node(temp -> f_name);
		if(sub_new == NULL)
			return FAILURE;
		main_new -> sub_link = sub_new;
		return SUCCESS;
	}
}
