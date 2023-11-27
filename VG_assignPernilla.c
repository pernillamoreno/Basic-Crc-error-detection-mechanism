/**
 * @file VG_assignPernilla.c
 * @author {Nilla Moreno} ({stahlbring@gmail.com})
 * @brief A crc calculating program 
 * @version 0.1
 * @date 2023-11-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <string.h>

int main()
{
  /*    Variable Declarations:
        i, j: Loop counters.
        keyLen, msgLen: Variables to store the length of the key and input data.
        flag: Variable to indicate whether an error is detected.
        input[100], key[30], temp[30], quot[100], rem[30], key1[30]: 
        Arrays to store input data, key, temporary values, quotient, 
        remainder, and a copy of the original key. */
  int i, j, keyLen, msgLen, flag = 0;
  char input[100], key[30], temp[30], quot[100], rem[30], key1[30];
  
  /*INPUT data and key*/
  printf("Input Data: ");
  scanf("%s", input);
  printf("Input Key: ");//
  scanf("%s", key);
  /* Initialize Variables:
   Calculate the lengths of the key and input data using strlen.
   Create a copy of the original key (key1).*/
  keyLen = strlen(key);
  msgLen = strlen(input);
  strcpy(key1, key);
  
  /*Find out the lenght of the divisor
  to make place for reminder. 0 are add in the end of the input*/
  for (i = 0; i < keyLen - 1; i++)
  {
    input[msgLen + i] = '0';
  }

  /*copying the data from previus forloop
  crc calculation using plynomial division. 
  quotient and reminder.Initialize the temporary array (temp) with the initial values of the input.*/
  for (i = 0; i < keyLen; i++)
    temp[i] = input[i];
 /* CRC Calculation (1 Pass):
  Perform CRC (Cyclic Redundancy Check) calculation on the input data using polynomial division.
  Update the quotient (quot) and remainder (rem) arrays.*/
  for (i = 0; i < msgLen; i++)
  {
    quot[i] = temp[0];
     // Update the key based on the current quotient valu
    if (quot[i] == '0')
      for (j = 0; j < keyLen; j++)
        key[j] = '0';
    else
      for (j = 0; j < keyLen; j++)
        key[j] = key1[j];

    // Update the remainder based on the current key and temp values
    for (j = keyLen - 1; j > 0; j--)
    {

      if (temp[j] == key[j])
        rem[j - 1] = '0';
      else
        rem[j - 1] = '1';
    }
     // Update the last element of the remainder
    rem[keyLen - 1] = input[i + keyLen];
     // Update temp with the current remainder
    strcpy(temp, rem);
  }
  strcpy(temp, rem);

  /*Solution of the calculation is printed */
  printf("\n Quot is: ");
  for (i = 0; i < msgLen; i++)
    printf("%c", quot[i]);
  printf("\n Reminder is: ");
  for (i = 0; i < keyLen - 1; i++)
    printf("%c", rem[i]);

  /*Final data printed  whit orginal input and reminder*/
  printf("\nFinal Data is: ");
  for (i = 0; i < msgLen; i++)
    printf("%c", input[i]);


  for (i = 0; i < keyLen - 1; i++)
    printf("%c", input[i]);

  printf("\n");

  /* User Input (2 Pass):
  Prompt the user to enter the received data.*/
  char temp1[20];
  printf("Input recieved data: ");
  scanf("%s", temp1);

 /*Initialize Temp Array (2 Pass):
  Initialize the temporary array (temp) with the received data.*/
  for (i = 0; i < keyLen; i++)
    temp[i] = temp1[i];

   /*CRC Calculation (2 Pass):
   Perform CRC calculation on the received data using polynomial division.
  Update the quotient (quot) and remainder (rem) arrays.*/ 
  for (i = 0; i < msgLen; i++)
  {
    quot[i] = temp[0];
    // Update the key based on the current quotient value
    if (quot[i] == '0')
      for (j = 0; j < keyLen; j++)
        key[j] = '0';
    else
      key[j] = key1[j];
    for (j = keyLen - 1; j > 0; j--)
    {
      if (temp[j] == key[j])
        rem[j - 1] = '0';
      else
        rem[j - 1] = '1';
    }
      // Update the last element of the remainder
    rem[keyLen - 1] = temp1[i + keyLen];
      // Update temp with the current remainder
    strcpy(temp, rem);
  }
  strcpy(temp, rem);

  /*The  quotient  and remainder are printed*/
  printf("\n Quot is: ");
  for (i = 0; i < msgLen; i++)
    printf("%c", quot[i]);
  printf("\n Reminder is: ");
  for (i = 0; i < keyLen - 1; i++)
    printf("%c", rem[i]);


/*ERROR detection program checks of reminder bits are non 0.If thats the case its an error.
Flag = 0 = no errors */
  flag = 0;
  for (i = 0; i < keyLen - 1; i++)
  {
    if (rem[i] == '1')
      flag = 1;
    else
      flag = 0;
  }
  // Print whether an error is detected or not
  if (flag == 0)
    printf("No Error \n");
  else
    printf("Error detected\n");
  return 0;
