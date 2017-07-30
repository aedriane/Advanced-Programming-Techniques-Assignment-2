#include "addressbook_array.h"

/*Creates a array for Telephones. Returns NULL if memory could not be
    allocated. Otherwise, returns struct if all values are allocated
    correctly.*/
AddressBookArray * createAddressBookArray()
{
    AddressBookArray * aba = malloc(sizeof(AddressBookArray));

    if(aba == NULL)
    {
        return NULL;
    }

    aba -> size = 0;
    aba -> telephones = NULL;  
    return aba;   
}

/*Frees the current node's array.*/
void freeAddressBookArray(AddressBookArray * array)
{
    if(array != NULL)
    {
        free(array -> telephones);
    }
    free(array);
}

/*Adds a telephone to a current Node. If Telephone exists, return FALSE. 
    Otherwise allocate memory to the new Telephone and reallocate memory of
    the array to expand its size for a new block of memory. Array size count
    will swell upon succession.*/
Boolean addTelephone(AddressBookArray * array, char * telephone)
{
    char * newTelephone;
    char * checkTelephone;

    checkTelephone = findTelephone(array, telephone);

    if(checkTelephone != NULL)
    {
        return FALSE;         
    }

    newTelephone = (char *)malloc(TELEPHONE_LENGTH);

    strcpy(newTelephone, telephone);

    array -> telephones = realloc(array -> telephones, 
    sizeof(* array -> telephones) * (array -> size + 1));

    array -> telephones[array -> size] = newTelephone;

    array -> size++; 

    return TRUE;   
}

/*Removes a telephones from the current node. If Telephone does not exist,
    OR the array is NULL, return FALSE. Otherwise, loop through the array to 
    check for valid telephone. Reallocate memory to shrink by the size of the
    removed telephone. Decrement array's size by 1 on succession.*/
Boolean removeTelephone(AddressBookArray * array, char * telephone)
{
    /*Variable declarations*/
    char * checkTelephone;
    int i;

    checkTelephone = findTelephone(array, telephone);

    if(!checkTelephone || array -> telephones == NULL)
    {
        return FALSE;
    }

    for(i = 0; i < array -> size; ++i)
    {
        if(checkTelephone && array -> size > 1)
        {
            array -> telephones = realloc(array -> telephones, 
                                                sizeof(* array -> telephones)
                                                * (array -> size - 1));
            
            array -> size--;
            break;
        }

        else if(checkTelephone && array -> size == 1)
        {
            array -> size--;            

            free(array -> telephones);

            array -> telephones = NULL;

            break;
        }
    }
    return TRUE;
}

/* Searches array for record with matching Telephone.
    If the Telephone is found, Telephone will be returned, otherwise
    NULL is returned */
char * findTelephone(AddressBookArray * array, char * telephone)
{
     int i;
     Boolean check; 
     
     check = FALSE;

     for(i = 0; i < array -> size; ++i)
     {
         if(strcmp(array -> telephones[i], telephone) == 0)
         {
             check = TRUE;
             break;
         }
     }

     if(check == TRUE)
     {
         return telephone;
     }

     else
     {
         return NULL;
     }    
}
