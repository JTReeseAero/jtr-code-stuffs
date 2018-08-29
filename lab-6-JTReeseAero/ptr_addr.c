#include <stdio.h>
int main(){
   // Create a pointer to an int (currently points at a random memory location, why?)
   int* pc;
   
   // Create a normal int variable
   int c;
   
   // Assign the value 22 to variable c
   c=22;
   // Print the memory address of the variable
   printf("Address of c:%u\n",&c);
   // Print the int stored at that memory address
   printf("Value of c:%d\n\n",c);
   
   // Make the value of the pointer the address of c
   pc=&c;
   // Print the location in memory of pc
   printf("Address of pointer pc:%u\n",%pc);
   // Print the value of pointer pc (where it is pointing)
   printf("Value of pointer pc:%u\n",pc);
   // Print the value stored in the memory address stored in pc (dereference)
   printf("Content of pointer pc:%d\n\n",*pc);
   
   // Reassign the value of C
   c=11;
   // Print the value of pointer pc (where it is pointing)                        
   printf("Address of pointer pc:%u\n",pc);
   // Print the value stored in the memory address stored in pc
   printf("Content of pointer pc:%d\n\n",*pc);    
   
   // Set the value of the variable pointed to by pc to 2
   *pc=2;
   // Print the address in memory of variable c                
   printf("Address of c:%u\n",&c);
   // Print the value of variable c    
   printf("Value of c:%d\n\n",c);
   
   return 0;
}

