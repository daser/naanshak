#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This is an array of register mnemonics in y86
const char* register_names[] =
{
 "%eax",
 "%ecx",
 "%edx",
 "%ebx",
 "%esp",
 "%ebp",
 "%esi",
 "%edi",
 "UNKNOWN_REGSITER"
};

int convertStrToByteCode( const char *str, unsigned char inst[], int size );

int main ( int argc, char** argv )
{
  FILE *pFile = NULL;
  
  char buffer[15];

  if (argc < 2 )
  {
    pFile = fopen("./test1.txt", "r");
  }
  else
  {
    pFile = fopen(argv[1], "r");
  }
  
  if ( pFile == NULL )
  {
    printf("Error open test file, please make sure they exist.\n");
    
    return 0;
  }

  while( fgets(buffer, 15, pFile ) )
  {
      //This unsigned char array stores an instruction read from the file
      //As the largest y86 instruction is 6 bytes, there are 6 unsigned char in the array where
      //each represents a byte.
      unsigned char instruction[6] = {0,0,0,0,0,0};
      convertStrToByteCode(buffer, instruction, 6);
      
      //TODO: You only need to put the statements for decoding the instruction inside this loop.
      //The following code shows the decoding of halt, nop and ret instruction.
      //Your task is to complete the implementation so that all y86 opcode and operands can be disassembled.
      //Any undisassembled opcode will display as "TODO: undisaasembled opcode and operands"
      if( instruction[0] == 0x00 )
      {
        printf("halt\n");
      }
      else if ( instruction[0] == 0x10 )
      {
        printf("nop\n");
      }
      else if ( instruction[0] == 0x90 )
      {
        printf("ret\n");
      }
      else
      {
        printf("TODO: Undisassembled Opcode and operands\n");
      }
  }

  fclose(pFile);

  return 0;
}




/****************************************************************************
N.B. You do not need to modify or work in this function.
Description:
This function converts a line of machine code read from the text file
into machine byte code.
The machine code is stored in an unsigned char array.
******************************************************************************/
int convertStrToByteCode( const char *str, unsigned char inst[], int size )
{
  int numHexDigits = 0;
  char *endstr;
  //Each instruction should consist of at most 12 hex digits
  numHexDigits = strlen(str) - 1;
  //Convert the string to integer, N.B. this integer is in decimal
  long long value = strtol(str, &endstr, 16);

  int numBytes = numHexDigits >> 1;
  int byteCount = numHexDigits >> 1;

  while ( byteCount > 0)
  {
    unsigned long mask = 0xFF;
    unsigned long shift = (numBytes - byteCount) << 3; 

    inst[byteCount - 1] = (value & (mask<<shift))>>shift;
    byteCount --;
  }

  //Return the size of the instruction in bytes
  return numHexDigits >> 1;
}


