#include <stdio.h>
#include <string.h>

#define MAXSIZE 100
void formatKey(char myKey[]);
char* getText();
void setUp(char myText[]);
char encrypt(char p, char k);
char decrypt(char c, char k);

char key[MAXSIZE];
char pctext[MAXSIZE];
int keySize;
int en;

int main(int argc, char* argv[])
{
	// first, check for correct number of arguments
	if(argc < 3 || argc > 3)
	{
		printf("Need two arguments.. You gave %d\n", argc - 1);
		return 1;
	}
	
	// now format the key
	formatKey(argv[2]);

	while(1)
	{
		char *p = getText(); 
		
		// check if user is encrypting or decrypting a message
		if(strcmp(argv[1],"-e") == 0)
		{
			en = 1;	
		}
		else if(strcmp(argv[1], "-d") == 0)
		{
			en = 0;
		}
		else
		{
			printf("Sorry, you can only encrypt '-e' and decrypt '-d'\n");
		}
		setUp(p);
		
	}
	return 0;
}

// removes spaces from key
void formatKey(char myKey[])
{
	int i, j = 0;

	for(i = 0; myKey[i] != '\0'; i++)
	{
		if(myKey[i] != ' ')
		{
			key[j] = myKey[i];
			j++;
		}
	}
	key[j] = '\0';
	keySize = j;
}

// get plain/ciphertext from user
char* getText()
{
	int c, n = 0;

	while((c = getchar()) != '\n')
	{
		pctext[n++] = c;			
	}

	pctext[n] = '\0';
	return pctext;
}

// sets up encryption/decryption  
void setUp(char myText[])
{
	int l, k;
	int i, j = 0;
	for(i = 0; myText[i] != '\0'; i++)
	{
		// only make shifts to letters of alphabet
		if((myText[i] >= 'A' && myText[i] <= 'Z') || (myText[i] >= 'a' && myText[i] <= 'z'))
		{
			k = j % keySize;
			if(key[k] >= 'a')
			{
				l = key[k] - 'a';	
			}
			else if(key[k] >= 'A')
			{
				l = key[k] - 'A';
			}
			
			if(myText[i] >= 'a')
			{
				if(en == 1)
				{
					putchar(encrypt(myText[i] - 'a', l) + 'a');
				}
				else 
				{
					putchar(decrypt(myText[i] - 'a', l) + 'a');
				}
			}
			else if(myText[i] >= 'A')
			{
				if(en)
				{
					putchar(encrypt(myText[i] - 'A', l) + 'A');
				}
				else
				{
					putchar(decrypt(myText[i] - 'A', l) + 'A');
				}
			}
			
			j++;
		}
		else
		{
			putchar(myText[i]);
		}
	}

	putchar('\n');
}

char encrypt(char p, char k)
{
	return ((p + k) % 26);
}

char decrypt(char c, char k)
{
	return (((c - k) + 26) % 26);
}
