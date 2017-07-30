# Advanced-Programming-Techniques-Assignment-2
Advanced Programming Techniques Assignment 2 Semester 1 2017

This program is a simple phone book that holds an array of people with one or more phone numbers in memory. 

Each specific node holds information such as Identification, Name, and/or one or more phone numbers. Phone numbers aren't 
mandatory for a specific person but they still remain in the phone book.

Concepts utilised are pointers, arrays, doubly linked lists, tokenizer, handling and releasing of memory on a stack, nodes
with an array containing one or more elements, etc.

Before execution of this program, one must firstly use 'make' to utilise the MakeFile executable which contains dynamic 
compilation of all the .c and .h files in the directory. This creates the .o extension files. 

After 'make' has been successfully utilised, ./addressbook may be used to execute the program.

To use the program:

load test.txt
[Loads specified file into memory]

unload
[Frees the current list from memory]

quit
[Quits the application]

display
[Displays current Linked List in a formatted table]

forward # -- # indicating any number to move forward in the list
[Moves the current pointer in the list fowards a specified amount of times as indicated by the user]

backward # -- # indicating any number to move backwards in the list
[Moves the current pointer in the list backwards a specified amount of times as indicated by the user]

insert id,name,number
[Insert a new node into the list by inputting a id, name, and one phone number]

add 0412292819
[Inserts a telephone number into the node's array at the current position of the node pointer]

remove 0412292819
[Removes an existing telephone number from the node's array at the current position of the node pointer]

find Daniel
[Scours through the list to find an existing name and sets the current position pointer to the found node]

delete
[Deletes the node that the current position pointer is set to. After deletion, the current position pointer will set itself
to the node that is in the position after the deleted node]
  
save savedfile.txt
[saves the current state of the list into a file]




