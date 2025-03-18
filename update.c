#include "main.h"
status update_hashtable(m_node *hash[],FILE *fp,slist **fname_head)
{
	int count = 0;
	//check if hashtable already has data
	for(int i = 0; i < 27; i++)
	{
		if(hash[i] != NULL)
			count++;
	}
	if(count > 0)
		return HASHTABLE_IS_NOT_EMPTY;
	char file[100];
label:
	//to update ask file name
	printf("Enter file name to update hashtable: ");
	scanf("%s",file);
	//file should be csv file
	if(!strstr(file,".csv"))
	{
		printf("Enter the proper file extension!\n");
		printf("\nDo you want to contniue [YES -> 1] / [NO -> 0]: ");
		int cont;
		scanf("%d",&cont);
		if(cont == 1)
			goto label;
		else
			return FAILURE;
	}
	//open file to read
	fp = fopen(file,"r");
	if(fp == NULL)
		return FAILURE;
	//check for size to run loop
	fseek(fp,0,SEEK_END);
	int end = ftell(fp);
	//printf("file size = %d\n",end);
	fseek(fp,0,SEEK_SET);
	status ret; 
	while(ftell(fp) != end)
	{
		//call function read data from file and update to hashtble
		ret = reading_file_to_update_hash(hash,fp,fname_head);
		if(ret == FAILURE)
		{
			printf("Reading from file has been failed!!\n");
			return FAILURE;
		}
	}
	return SUCCESS;
}


status reading_file_to_update_hash(m_node *hash[],FILE *fp,slist **fname_head)
{
	char line[1000];
	int k = 0;
	char ch;
	//read one line at a time
	while((ch = fgetc(fp)) != '\n')
		line[k++] = ch;
	line[k] = '\0';
	k = 1;
	int index = 0,temp_file_count = 0;
	char temp_word[100];
	//printf("%s\n",line);
	//extract index from line
	while(line[k] != ',')
	{
		index = (index * 10) + (line[k] - 48);
		k++;
	}
	//printf("index = %d\n",index);
	k++;
	int m = 0;
	//extract word from line
	while(line[k] != ',')
		temp_word[m++] = line[k++];
	k++;
	temp_word[m] = '\0';
	//printf("word = %s\n",temp_word);
	//extract file count from line
	while(line[k] != ',')
	{
		temp_file_count = (temp_file_count * 10) + (line[k] - 48);
		k++;
	}
	k++;
	//printf("filecount = %d\n",temp_file_count);
	//allocate memory for file names storage existing in line
	char **filenames = malloc(temp_file_count * sizeof(char *));
	if(filenames == NULL){
		printf("Memory allocation for filenames has failed!!\n");
		return FAILURE;
	}
	//allocate memory for word existance count of file
	int *temp_word_count = calloc(temp_file_count,sizeof(int));
	if(temp_word_count == NULL){
		printf("Memory allocation for word count's has failed!!\n");
		return FAILURE;
	}
	int x = 0,y = 0,z = 0;
	//allocate memory for file names storage existing in line
	filenames[x] = malloc(100 * sizeof(char));
	if(filenames[x] == NULL){
		printf("Index Memory allocation for file names has failed!\n");
		return FAILURE;
	}
	int count = 0;
	//extract filenames
	while(line[k] != '#')
	{
		if(line[k] == ',' && line[k + 1] != '#')
		{
			filenames[x][y] = '\0';
			count++;k++;
			x++;y = 0;
			filenames[x] = malloc(100 * sizeof(char));
			if(filenames[x] == NULL)
			{
				printf("Index Memory allocation for file names has failed!\n");
				return FAILURE;
			}
			// file word existance count
			while(line[k] != ',')
			{
				temp_word_count[z] = (temp_word_count[z] * 10) + line[k] - 48;
				k++;
			}
			k++;z++;
		}else
			filenames[x][y++] = line[k++];
	}
	/*	for(int i = 0; i < x; i++)
		printf("filename => %s\n",filenames[i]);
		for(int i = 0; i < z; i++)
		printf("wordcount = %d\n",temp_word_count[i]);
	 */
//		/*
	//check for repeated files 
	for(int i = 0; i < temp_file_count; i++)
	{
		struct node *check_temp = *fname_head,*prev = NULL;
		while(check_temp != NULL)
		{
			if(!strcmp(check_temp -> f_name,filenames[i]))
			{
				if(prev == NULL)
				{
					*fname_head = (*fname_head) -> s_next;
					free(check_temp);
					check_temp = *fname_head;
				}else{
					prev -> s_next = check_temp -> s_next;
					free(check_temp);
					check_temp = prev -> s_next;
				}
			}else{
				prev = check_temp;
				check_temp = check_temp -> s_next;
			}
		}
	}
	//print_list(*fname_head);
//	*/
	//if hashtable index is empty
	if(hash[index] == NULL)
	{
		//create main node
		m_node *main_new = create_main_node(temp_word);
		if(main_new == NULL)
		{
			printf("New main node creation has been failed!\n");
			return FAILURE;
		}
		//	printf("word = %s\n",main_new -> word);
		main_new -> file_count = temp_file_count;
		s_node *temp = NULL;
		for(int i = 0; i < temp_file_count; i++)
		{
			//create sub nodes and update to hashtable
			s_node *sub_new = create_sub_node(filenames[i]);
			if(sub_new == NULL)
			{
				printf("Creation of subnode has been failed!\n");
				return FAILURE;
			}
			sub_new -> word_count = temp_word_count[i];
			if(main_new -> sub_link == NULL)
			{
				main_new -> sub_link = sub_new;
			//				printf("%p\n",main_new -> sub_link);
				temp = main_new -> sub_link;
			//				printf("%p\n",temp);
			}else{
				temp -> sub_link = sub_new;
				temp = temp -> sub_link;	
			}
		}
		hash[index] = main_new;
		return SUCCESS;
	}
	//index has main nodes
	m_node *main_temp = hash[index];
	m_node *main_prev = NULL;
	while(main_temp != NULL)
	{
		main_prev = main_temp;
		//check if word already exists
		if(!strcmp(main_temp -> word,temp_word))
		{
			for(int i = 0; i < temp_file_count; i++)
			{
				//if exists check for sub node existance
				s_node *sub_temp = main_temp -> sub_link;
				s_node *sub_prev = NULL;
				while(sub_temp != NULL)
				{
					sub_prev = sub_temp;
					if(!strcmp(sub_temp -> file_name,filenames[i]))
					{
						sub_temp -> word_count += temp_word_count[i];
						break;
					}
					sub_temp = sub_temp -> sub_link;
				}
				//sub node doesn't exist
				if(sub_temp == NULL)
				{
					s_node *sub_new = create_sub_node(filenames[i]);
					sub_new -> word_count = temp_word_count[i];
					sub_prev -> sub_link = sub_new;
					(main_temp -> file_count)++;
				}
			}
			return SUCCESS;
		}
		main_temp = main_temp -> main_link;
	}
	//if main node doesn't exist
	if(main_temp == NULL)
	{
		//update hashtable
		//create main node
		m_node *main_new = create_main_node(temp_word);
		if(main_new == NULL)
		{
			printf("New main node creation has been failed!\n");
			return FAILURE;
		}
		main_new -> file_count = temp_file_count;
		s_node *temp = NULL;
		for(int i = 0; i < temp_file_count; i++)
		{
			//create sub nodes and add to main node
			s_node *sub_new = create_sub_node(filenames[i]);
			if(sub_new == NULL)
			{
				printf("Creation of subnode has been failed!\n");
				return FAILURE;
			}
			sub_new -> word_count = temp_word_count[i];
			if(main_new -> sub_link == NULL)
			{
				main_new -> sub_link = sub_new;
				temp = sub_new;
			}else{
				temp -> sub_link = sub_new;
				temp = temp -> sub_link;
			}
		}
		//	printf("%s\n",main_prev -> word);
		//	printf("%s\n",main_new -> word);
		main_prev -> main_link = main_new;	
		return SUCCESS;
	}
	return FAILURE;
}
