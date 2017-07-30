#include "commands.h"
#include <limits.h>

/*Loads a text file into the system. Reads each line of the file. If the first 
    element of the line is #, skip. Otherwise, continue to read until new line
    is reached. Once ID, Name, and Telephone are ready into functions, 
    InsertNode() inserts them into the list one by one.*/
AddressBookList * commandLoad(char * fileName)
{
     FILE * fp;
     char line[MAX_LINE_LENGTH];
     char * token;
     int id;
     char * name;

     AddressBookNode * node;
     AddressBookList * list;
  
     list = createAddressBookList();

     fp = fopen(fileName, "r");

     printf("> Opening the file %s.\n", fileName);

     if(fp == NULL)
     {
         printf("> Error: Unable to find the specified file!\n\n");
         return list;
     }

     else
     {
        printf("> Loading the file ...\n");

		if(list -> size > 0)
		{
			printf("> Freeing current list before loading another!\n\n");
			commandUnload(list);
		}

        while(fgets(line, sizeof(line), fp) != NULL)
        {
            if(line[0] == '#')
            {
                continue;
            }
            token = strtok(line, DELIM);

            id = get_Int(token);  
 
            token = strtok(NULL, DELIM);  

            name = token;

            node = createAddressBookNode(id, name);

            node -> array = createAddressBookArray();

            while((token = strtok(NULL, TELEPHONEDELIM)) != NULL)
            {
                addTelephone(node -> array, token);
            }
            insertNode(list, node);
        }                 
    }

    if(list -> size != 0)
    {
        printf("> %d phone book entries have been loaded from the file.\n", list -> size);
    }
    fclose(fp);

    printf("> Closing the file.\n\n");
                
    return list;
}

/*Unloads current list. If the list is empty, prints a message. Otherwise,
    utilise freeAddressBookList() to unload the list.*/
void commandUnload(AddressBookList * list)
{
    if(list -> size == 0)
    {
        printf("> There is no list to unload!\n\n");
    } 
    
    else 
    {
        freeAddressBookList(list);
        printf("> The list is unloaded!\n\n");
    }
}

/*Displays current data in a formatted table. Calculates the width of the ID 
    name column to handle an instance if an ID/Name is longer than expected.*/
void commandDisplay(AddressBookList * list)
{
    int i;   
    int serial = 1;     
    int max_width;
    int max_width_id;
    int width;
    int widthID; 

    AddressBookNode * column, * node;
    column = list -> head;
    node = list -> head;

    while(column != NULL)
    {
        widthID = nDigits(column -> id);    

        if(widthID > max_width_id)
        {
            max_width_id = widthID;
        }

        width = strlen(column -> name);

        if(width > max_width)
        {
            max_width = width;
        }
        column = column -> nextNode;
    }
	repeat_string(LINE, (46));

	printf("\n| %-s | %-5s | %-*s | %-*s | %s \n", 
    POS_HEADING, SERIAL_HEADING, max_width_id, ID_HEADING, max_width, NAME_HEADING, 
		TELEPHONE_HEADING);

	repeat_string(LINE, (46));

    printf("\n");

    if(list -> size == 0)
    {
        printf("|                                            |\n");
    }

    else
    {
        while(node != NULL)
        {
            if(node == list -> current)
            {
                printf("| %s |", CUR);
            }

            else
            {
                printf("|     |");
            }

            printf(" %-6d | %-*d | %-*s | ",
                    serial, 
                    max_width_id,
                    node -> id, 
                    max_width, 
                    node -> name);

            if(node -> array -> size > 0)
            {
                for(i = 0; i < node -> array -> size; ++i)
                {         
                    if(i != node -> array -> size - 1)
                    {
                        printf("%s, ", node -> array -> telephones[i]);
                    } 

                    else
                    {
                        printf("%s", node -> array -> telephones[i]);
                    }              
                }
             }
             printf("\n");

             node = node -> nextNode;
             serial++;
        }
    }
    repeat_string(LINE, (46));

    printf("\n| Total phone book entries: %d \n", list -> size);

    repeat_string(LINE, (46));  
    printf("\n\n");  
}

/*Moves Forward in the list. Checks to understand if list is empty.
    If Forward() Boolean function returns FALSE, handle check with print
    message. Otherwise, print message to detail the succession of the move.*/
void commandForward(AddressBookList * list, int moves)
{ 
    if(list -> head == NULL)
    {
        printf("> No List available to move forward in!\n\n");
    }

    else if(forward(list, moves) == FALSE)
    {
        printf("> Unable to move forward for %d move(s)!\n\n", moves);
    }

    else
    {
        printf("> Moved forward %d node(s)!\n\n", moves);
    }
}

/*Moves Backwards in the list. Checks to understand if list is empty.
    If Backward() Boolean function returns FALSE, handle check with print
    message. Otherwise, print message to detail the succession of the move.*/
void commandBackward(AddressBookList * list, int moves)
{ 
    if(list -> size == 0)
    {
        printf("> No List available to move backward in!\n\n");
    }

    else if(backward(list, moves) == FALSE)
    {
        printf("> Unable to move backward for %d move(s)!\n\n", moves);
    }

    else
    {
        printf("> Moved backward %d node(s)!\n\n", moves);
    }
}

/*Inserts a NEW node into the list. Checks too identify whether the provided
    ID and Name exist in the list by the use of FindByID() and FindByName()functions.
    If they are not found, new node is created and inserted into the list at 
    the tail. Print Messages to handle inability to insert node ie. Name or ID
    exists in list.*/
void commandInsert(AddressBookList * list, int id, char * name, char * telephone)
{ 
    Boolean insertion;

    AddressBookNode * node;


    insertion = TRUE;

    if(!(node = findByID(list, id)))
    {
        if(!(node = findByName(list, name)))
        {
            if(isValidTelephone(telephone))
            {
                insertion = TRUE;
            }

            else
            {
                printf("> Telephone format not valid.\n\n");
                insertion = FALSE;
            }
        }

        else
        {
            printf("> Name exists.\n\n");
            insertion = FALSE;
        }
    }

    else
    {
        printf("> ID exists.\n\n");
        insertion = FALSE;
    }

    if(insertion)
    {
        node = createAddressBookNode(id, name);    

        if(node == NULL)
        {
            printf("> Error: Unable to create node.\n\n");
        }

        if(!addTelephone(node -> array, telephone))
        {
            printf("> Error: Unable to insert telephone.\n\n");
        }

        if(!insertNode(list, node))
        {
            printf("> Error: Unable to insert node.\n\n");
        }

        else
        {
            printf("> %d, %s, %s, Inserted into list!\n\n", id, name, telephone);
        }
    }
}

/*Add Telephone to a current node. Checks is the List is empty and if the 
    Telephone for insertion is in a valid format. Otherwise, print error 
    messages explaining to the user that their inputs are wrong.*/
void commandAdd(AddressBookList * list, char * telephone)
{   
	if(list -> head != NULL) 
    {
		if(isValidTelephone(telephone)) 
        {
			if(!addTelephone(list->current->array, telephone)) 
            {
 				printf("> Error: Telephone could not be added!\n\n");                            
			}

            else
            {
                printf("> Added Telephone entry %s.\n\n", telephone);    
            }
		} 
        
        else 
        {
			printf("> Error: Invalid telephone format\n");
		}
	} 
    
    else 
    {
		printf("> Error: No list has been loaded\n");
	}
}    

/*Finds a specific name in the list. If name is found, print message.
    Otherwise, print error message if name not found.*/
void commandFind(AddressBookList * list, char * name)
{
    AddressBookNode * node;

    if((node = findByName(list, name)))
    {
        list -> current = node;
        printf("> Entry found!\n\n");
    }

    else
    {
        printf("> Error: Unable to find node!\n\n");
    }
}

/*Deletes current node in list. If deleteCurrentNode() Boolean return is
    equal to FALSE, then print out an error Message. Otherwise, print 
    out succession of deleted node message.*/
void commandDelete(AddressBookList * list)
{
    if(list -> size == 0)
    {
        printf("> List is empty, no nodes to delete!\n\n");
    }

    else if(deleteCurrentNode(list) == FALSE)
    {
        printf("> Error: Unable to delete current node!\n\n");
    }

    else
    {
        printf("> Node has been deleted from the list!\n\n");
    }
}

/*Remove specific telephone from a current node. If list is not empty, and if 
    the telephone is valid, print message of succession. Otherwise, if unable 
    to remove telephone, print various errors detailing this.*/
void commandRemove(AddressBookList * list, char * telephone)
{ 
	if(list != NULL) 
    {
        if(isValidTelephone(telephone))
        {
            /*If unable to remove telephone*/
            if(!removeTelephone(list -> current -> array, telephone)) 
            { 
                printf("> Telephone entry %s could not be removed!\n\n", telephone); 
            } 
            
            else 
            { 
                printf("> Telephone entry %s has been removed.\n\n", telephone);             
 
            }
        }

        else
        {
            printf("> Error: Invalid Telephone format!\n\n");
        }
	}       
}

void commandSort(
    AddressBookList * list,
    int sort(const void * node, const void * otherNode))
{
    /* Sort the nodes within list in ascending order using the
     * provided sort function to compare nodes.
     */
}

int compareName(const void * node, const void * otherNode)
{
    /* Compare node name with otherNode name.
     * 
     * return < 0 when node name is smaller than otherNode name.
     * return 0 when the names are equal.
     * return > 0 when node name is bigger than otherNode name.
     */
    return 0;
}

int compareID(const void * node, const void * otherNode)
{
    /* Compare node id with otherNode id.
     * 
     * return < 0 when node id is smaller than otherNode id.
     * return 0 when the ids are equal.
     * return > 0 when node id is bigger than otherNode id.
     */
    return 0;
}

/*Saves current list status into a text file in CSV format.*/
void commandSave(AddressBookList * list, char * fileName)
{ 
    FILE * fp;
    int i;   

    AddressBookNode * node;
    node = list -> head;

    fp = fopen(fileName, "w");

    if(fp == NULL)
    {
        printf("> Error: Could not open file!\n\n");
    }

    while(node != NULL)
    {
        fprintf(fp, "%d,%s", node -> id, node -> name);

        if(node -> array -> size > 0)
        {
            for(i = 0; i < node -> array -> size; ++i)
            {         
                fprintf(fp, ",%s", node -> array -> telephones[i]);
            }
        }
        fprintf(fp, "\n");
        node = node -> nextNode;
    }
    fclose(fp);
}

/*Repeats a character for 'count' amount of times*/
void repeat_string(char *s, int count)
{
   int i;

   for (i = 0; i < count; i++)
   {
      printf("%s", s);
   }
}

/*Function that counts the number of digits in an int*/
int nDigits(int i)
{
  if (i < 0) i = -i;
  if (i <         10) return 1;
  if (i <        100) return 2;
  if (i <       1000) return 3;
  if (i <      10000) return 4;
  if (i <     100000) return 5;
  if (i <    1000000) return 6;      
  if (i <   10000000) return 7;
  if (i <  100000000) return 8;
  if (i < 1000000000) return 9;
  return 10;
}

/*Get Integer function*/
int get_Int(char *input)
{
   char *end;
   int input_num = -1;

   input_num = (int) strtol(input, &end, 0);

   if (*end || input_num < 0)
   {
      input_num = -1;
   }
   return input_num;
}

/*Get char/Input function*/
Boolean get_Input(char input[MAX_LINE_LENGTH])
{
   if (input == NULL || fgets(input, MAX_LINE_LENGTH, stdin) == NULL)
   {
      printf("\n");
      return FALSE;
   }
   
   if (input[strlen(input) - 1] != '\n')
   {
      printf("Input limit reached: %d.\n", MAX_LINE_LENGTH - 1);
      readRestOfLine();
      return FALSE;
   }

   else
   {
      input[strlen(input) - 1] = '\0';
   }
   return TRUE;
}

/*Checks if telephone is a valid format. Ie. only digits and no letters etc.*/
Boolean isValidTelephone(char * telephone) 
{ 
	int i;
	Boolean isValid = TRUE;

	if(strlen(telephone) == 10) 
    {
		for(i = 0; i < strlen(telephone); i++) 
        {
			if(isdigit(telephone[i])) 
            {
				isValid = TRUE;
			}
		}
	} 
    
    else 
    {
		isValid = FALSE;
	}
	return isValid;
}
