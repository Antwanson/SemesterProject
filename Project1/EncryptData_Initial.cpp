// EncryptData.cpp
//
// This file uses the input data and key information to encrypt the input data
//

#include "Main.h"

// YOU WILL DELETE ALL THIS CODE WHEN YOU DO YOUR PROJECT - THIS IS GIVING YOU EXAMPLES OF HOW TO 
// ACCESS gPasswordHash AND gKey

void encryptData_01(char *data, int datalength)
{

	__asm
	{
		xor ecx, ecx //clearing the ECX and EAX registers
		xor eax, eax

		lea	esi, gPasswordHash //getting starting index
		mov ah, byte ptr[esi]
		mov al, byte ptr[esi+1]
		lea esi, gkey //getting gkey
		mov edi, data //getting the actual data
		
		

		CHECK_NEXT :
		mov bh, 0
		cmp ecx, datalength //seeing if we are at the end of the data
		je DONE
		mov bl, byte ptr[edi + ecx] //moves X value into bl
		mov bh, byte ptr[esi+eax] //moves gkey into bh
		xor bl, bh 
		mov byte ptr[edi + ecx], bl //writes xor-ed value back into where we got it from
		inc ecx //counter increment
		jmp CHECK_NEXT

			DONE :

		//Start order BEACD 

		//Nibble rotate out

		//Rotate 3 bits left
	}

	return;
} // encryptData_01

//////////////////////////////////////////////////////////////////////////////////////////////////
// EXAMPLE code to to show how to access global variables
int encryptData(char *data, int dataLength)
{
	int resulti = 0;

	gdebug1 = 0;				// a couple of global variables that could be used for debugging
	gdebug2 = 0;				// also can have a breakpoint in C code

	// You can not declare any local variables in C, but should use resulti to indicate any errors
	// Set up the stack frame and assign variables in assembly if you need to do so
	// access the parameters BEFORE setting up your own stack frame
	// Also, you cannot use a lot of global variables - work with registers

	__asm {
		// you will need to reference some of these global variables
		// (gptrPasswordHash or gPasswordHash), (gptrKey or gkey), gNumRounds

		// simple example that xors 2nd byte of data with 14th byte in the key file
		lea esi,gkey				// put the ADDRESS of gkey into esi
		mov esi,gptrKey;			// put the ADDRESS of gkey into esi (since *gptrKey = gkey)

		lea	esi,gPasswordHash		// put ADDRESS of gPasswordHash into esi
		mov esi,gptrPasswordHash	// put ADDRESS of gPasswordHash into esi (since unsigned char *gptrPasswordHash = gPasswordHash)

		mov al,byte ptr [esi]				// get first byte of password hash
		mov al,byte ptr [esi+4]				// get 5th byte of password hash
		mov ebx,2
		mov al,byte ptr [esi+ebx]			// get 3rd byte of password hash
		mov al,byte ptr [esi+ebx*2]			// get 5th byte of password hash

		mov ax,word ptr [esi+ebx*2]			// gets 5th and 6th bytes of password hash ( gPasswordHash[4] and gPasswordHash[5] ) into ax
		mov eax,dword ptr [esi+ebx*2]		// gets 4 bytes, as in:  unsigned int X = *( (unsigned int*) &gPasswordHash[4] );

		mov al,byte ptr [gkey+ebx]			// get's 3rd byte of gkey[] data

		mov al,byte ptr [gptrKey+ebx]		// THIS IS INCORRECT - will add the address of the gptrKey global variable (NOT the value that gptrKey holds)

		mov al,byte ptr [esi+0xd];			// access 14th byte in gkey[]: 0, 1, 2 ... d is the 14th byte
		mov edi,data				// Put ADDRESS of first data element into edi
		xor byte ptr [edi+1],al		// Exclusive-or the 2nd byte of data with the 14th element of the keyfile
									// NOTE: Keyfile[14] = 0x21, that value changes the case of a letter and flips the LSB
									// Capital "B" = 0x42 becomes lowercase "c" since 0x42 xor 0x21 = 0x63
	}

	return resulti;
} // encryptData

