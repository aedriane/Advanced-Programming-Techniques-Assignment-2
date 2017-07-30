#include "addressbook.h"

int main(int argc, char ** argv)
{
	/*Variable Declarations.*/
	Boolean loop;
	int forward, backward;
	int id;
	char userInput[MAX_LINE_LENGTH];
	char * tokenizer;
	char * name;
	char * telephone;

	/*Create list.*/
	AddressBookList * list = createAddressBookList();

	/*Print Student Information.*/
	information();

	/*Command Line Loading.*/
	if(argc == 2)
	{
		printf("> File name specified through the command-line argument.\n");	
		list = commandLoad(argv[1]);		
	}

	else
	{
		if(argc > 2)
		{
			printf("> Could not load file from command line. Number of arguments exceed necessary input.\n\n");
		}	
	}

	loop = TRUE;

	/*Main program loop.*/
	while(loop)
	{
		printf("Enter your command: ");

		if(!get_Input(userInput))
	    {
	      	printf("> Invalid Input!\n\n");
	    }
	    printf("\n");

	    tokenizer = strtok(userInput, DELIM);

    	if(tokenizer == NULL)
    	{
      		printf("> Invalid Input!\n\n");
      		continue;
    	}

    	if(strcmp(tokenizer, COMMAND_LOAD) == 0)
    	{

    		tokenizer = strtok(NULL, SPACE);

    		if(tokenizer == NULL)
    		{
    			printf("> Invalid Input!\n\n");
    			continue;
    		}

			if(list -> size > 0)
			{
				printf("> Freeing current list before loading another!\n\n");
				commandUnload(list);
			}	
			list = commandLoad(tokenizer);						
		}

		else if(strcmp(tokenizer, COMMAND_DISPLAY) == 0)
		{
    		if(tokenizer == NULL)
    		{
    			printf("> Invalid Input!\n\n");
    			continue;
    		}				
			commandDisplay(list);						
		}

		else if(strcmp(tokenizer, COMMAND_UNLOAD) == 0)
		{
    		if(tokenizer == NULL)
    		{
    			printf("> Invalid Input!\n\n");
    			continue;
    		}				
			commandUnload(list);
		}

		else if(strcmp(tokenizer, COMMAND_QUIT) == 0)
		{

						commandUnload(list);

			printf("> See you!\n\n");
			loop = FALSE;
		}

		else if(strcmp(tokenizer, COMMAND_DELETE) == 0)
		{
    		if(tokenizer == NULL)
    		{
    			printf("> Invalid Input!\n\n");
    			continue;
    		}			
			commandDelete(list);
		}

		else if(strcmp(tokenizer, COMMAND_FORWARD) == 0)
		{
			tokenizer = strtok(NULL, SPACE);

			if(tokenizer == NULL)
			{
				printf("> Invalid Input!\n\n");
				continue;
			}
			forward = get_Int(tokenizer);

			commandForward(list, forward);
		}

		else if(strcmp(tokenizer, COMMAND_BACKWARD) == 0)
		{
			tokenizer = strtok(NULL, SPACE);

			if(tokenizer == NULL)
			{
				printf("> Invalid Input!\n\n");
				continue;
			}
			backward = get_Int(tokenizer);

			commandBackward(list, backward);			
		}

		else if(strcmp(tokenizer, COMMAND_INSERT) == 0)
		{
			tokenizer = strtok(NULL, COMMA);

			if(tokenizer == NULL)
			{
				printf("> Error: Unable to insert node!\n\n");
				continue;
			}
			id = get_Int(tokenizer);

			tokenizer = strtok(NULL, COMMA);			

			if(tokenizer == NULL)
			{
				printf("> Error: Unable to insert node!\n\n");
				continue;
			}
			name = tokenizer;

			tokenizer = strtok(NULL, NEWLINE);		

			if(tokenizer == NULL)
			{
				printf("> Error: Unable to insert node!\n\n");
				continue;
			}	
			telephone = tokenizer;

			commandInsert(list, id, name, telephone);		

		}

		else if(strcmp(tokenizer, COMMAND_ADD) == 0)
		{
			tokenizer = strtok(NULL, SPACE);
			
			if(tokenizer == NULL)
			{
				printf("> Invalid Input!\n\n");
				continue;
			}
			commandAdd(list, tokenizer);
		}

		else if(strcmp(tokenizer, COMMAND_REMOVE) == 0)
		{
			tokenizer = strtok(NULL, SPACE);
			
			if(tokenizer == NULL)
			{
				printf("> Invalid Input!\n\n");
				continue;
			}
			commandRemove(list, tokenizer);			
		}

		else if(strcmp(tokenizer, COMMAND_FIND) == 0)
		{
			tokenizer = strtok(NULL, SPACE);

			if(tokenizer == NULL)
			{
				printf("> Invalid Input!\n\n");
				continue;
			}
			commandFind(list, tokenizer);
		}

		else if(strcmp(tokenizer, COMMAND_SAVE) == 0)
		{
			tokenizer = strtok(NULL, SPACE);

			if(tokenizer == NULL)
			{
				printf("> Invalid Input!\n\n");
				continue;
			}

			if(list -> size > 0)
			{
				commandSave(list, tokenizer);
				printf("> Saved to %s!\n\n", tokenizer);
			}

			else if(list -> size == 0)
			{
				printf("> Nothing to save!\n\n");
			}			
		}
		
		else
		{
			printf("> Invalid Input!\n\n");
		}
	}
	return EXIT_SUCCESS;
}

/*Print out my information!*/
void information()
{
    repeat_string(LINE, 65);
    printf("\nStudent name: Aedriane Hernan\n");
    printf("Student number: s3541804\n");
    printf("Advanced Programming Techniques, Assignment 2, Semester 1, 2017\n");
    repeat_string(LINE, 65);
	printf("\n\n");	
}
