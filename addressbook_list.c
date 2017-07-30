#include "addressbook_list.h"

/*Creates a new Doubly Linked List. Returns NULL if memory could not be
    allocated. Otherwise, returns struct if all values are allocated
    correctly.*/
AddressBookList * createAddressBookList()
{
    AddressBookList * list = malloc(sizeof(AddressBookList));

    if(list == NULL)
    {
        printf("> Error: Unable to allocate memory for list.\n\n");
        return NULL;
    }

    list -> size = 0;
    list -> head = list -> tail = list -> current = NULL;

    return list;
}

/*Frees the List. Loops through all nodes and frees them individually.
    Compresses the list's size to 0 when all nodes have been freed.*/
void freeAddressBookList(AddressBookList * list) 
{
    AddressBookNode * node;

    node = list -> head; 

    while(node != NULL) 
    { 
        AddressBookNode * temp;

        temp = node;
        node = node -> nextNode;
        freeAddressBookNode(temp);
    } 
    free(list);

    list -> size = 0; 
}

/*Creates a new node. Returns NULL if memory could not be allocated.
    Otherwise, return struct if all values are allocated correctly.*/
AddressBookNode * createAddressBookNode(int id, char * name)
{
    AddressBookNode * node = malloc(sizeof(AddressBookNode));

    if(node == NULL)
    {
        printf("> Error: Unable to allocate memory for node.\n\n");
        return NULL;
    }

    node -> array = createAddressBookArray();

    node -> id = id;
    strcpy(node -> name, name);
    node -> nextNode = node -> previousNode = NULL;

    return node;
}

/*Frees a node in the list. Function handles freeing of the Array also.*/
void freeAddressBookNode(AddressBookNode * node) 
{ 
    if(node -> array != NULL) 
    { 
        if(node -> array -> size > 0) 
        { 
            freeAddressBookArray(node -> array); 
        } 
    }

    else
    {
        if(node -> nextNode != NULL)
        {
            freeAddressBookNode(node -> nextNode);
        }
        free(node); 
    } 
}

/*Function to Insert node into list. If list is empty, sets the node to head,
    tail and current. Otherwise, The tail of the list's next node is equal 
    node. Then its previous node is equals tail. Afterwards, sets tail to node
    then swells size by 1.*/
Boolean insertNode(AddressBookList * list, AddressBookNode * node)
{
    if(list -> head == NULL)
    {
        list -> head = list -> tail = list -> current = node;
    }

    else
    {
        list -> tail -> nextNode = node;
        node -> previousNode = list -> tail;
        list -> tail = node;
    }
    list -> size++;

    return TRUE;
}

/*Function to delete the current node. If list is empty then return FALSE.
    Return TRUE if successful in deleting node. If node to remove is head node,
    sets the node after it to current. If node to remove is tail node, sets 
    nextNode to NULL and the node before it to current.*/
Boolean deleteCurrentNode(AddressBookList * list)
{
    AddressBookNode * currentNode;
    AddressBookNode * headNode;
    AddressBookNode * tailNode;

    if(list -> head == NULL)
    {
        return FALSE;
    }

    currentNode = list -> current;
    headNode = currentNode -> nextNode;
    tailNode = currentNode -> previousNode;

    if(currentNode == list -> head)
    {
        if(headNode != NULL)
        {
            list -> current = headNode;
            list -> head = headNode;
        }
        freeAddressBookNode(currentNode);

        list -> size--;

        return TRUE;
    }

    else if(currentNode == list -> tail)
    {
        tailNode -> nextNode = NULL;
        list -> tail = tailNode;
        list -> current = tailNode;

        freeAddressBookNode(currentNode);

        list -> size--;

        return TRUE;
    }
    headNode -> previousNode = tailNode;
    tailNode -> nextNode = headNode;
    list -> current = headNode;

    freeAddressBookNode(currentNode);

    list -> size--;

    return TRUE;    
}

/*Moves the current pointer forward in the list by a given amount of times.
    Returns NULL if list is empty OR user tries to move forward an amount of 
    times that is outside of the list. Returns TRUE on succession of move.*/
Boolean forward(AddressBookList * list, int forward)
{
     int i;
     AddressBookNode * node;

     if(list -> head == NULL)
     {
         return FALSE;
     }

     if(forward > 0)
     {
         node = list -> current;

         for(i = 0; i < forward; ++i)
         {
             node = node -> nextNode;

             if(node == NULL)
             {
                 return FALSE;
             }
         }
         list -> current = node;
     } 
    return TRUE;
}

/*Moves the current pointer backwards in the list by a given amount of times.
    Returns NULL if list is empty OR user tries to move backwards an amount of 
    times that outside of the list. Returns TRUE on succession of move.*/
Boolean backward(AddressBookList * list, int backward)
{
    int i;

    AddressBookNode * node;

    if(list -> head == NULL)
    {
        return FALSE;
    }

    if(backward > 0)
    {
        node = list -> current;

        for(i = 0; i < backward; ++i)
        {
            node = node -> previousNode;

            if(node == NULL)
            {
                return FALSE;
            }
        }
        list -> current = node;
    }
    return TRUE;
}

/* Searches Address Book List for record with matching id.
    If the ID is found, boolean will be TRUE and return node.
    Otherwise, NULL is returned. */
AddressBookNode * findByID(AddressBookList * list, int id)
{
     Boolean found;

     AddressBookNode * node;
     node = list -> head;

     found = TRUE;

     while(node != NULL)
     {
         if(id == node -> id)
         {
             found = TRUE;
             break;
         }
         node = node -> nextNode;
     } 

     if(found)
     {
        return node;
     }  

     else
     {
         return NULL;
     }
}

/* Searches Address Book List for record with matching name.
    If the name is found, boolean is TRUE and will 
    return node. Otherwise, NULL is returned */
AddressBookNode * findByName(AddressBookList * list, char * name)
{
    Boolean found;

    AddressBookNode * node;
    node = list -> head;

    found = TRUE;

    while(node != NULL)
    {
        if(strcmp(name, node -> name) == 0)
        {
            found = TRUE;
            break;
        }
        node = node -> nextNode;
    }
    
    if(found)
    {
        return node;
    }

    else
    {
        return NULL;
    }
}
