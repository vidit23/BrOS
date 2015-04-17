//int strCmp(char*, char*);

int compare(char*, char*);
void parseInput(char*, char*, char*);
void type(char*);
void execute(char*);

main()
{
	char str[80], command[40], argm[40],arg1[40],arg2[40];
	char buffer[13312],check[512];
	int i,j,k;
	k=0;
	i=0;
	while(1)
	{
		
		interrupt(0x21, 0, "\nSHELL>", 0, 0);
		interrupt(0x21, 1, str, 0, 0);	
		k=0;
		j=0;
		i=0;
		parseInput(str, command, argm);
		//interrupt(0x21, 0, argm, 0, 0);
		
		if(compare(command,"type\0"))
		{
			interrupt(0x21, 0, "\n", 0, 0);
			interrupt(0x21, 3, argm, buffer, 0);
			interrupt(0x21, 0, buffer, 0, 0);
			
		}
		else if(compare(command,"execute\0"))
		{
			interrupt(0x21, 0, "\n", 0, 0);
			//interrupt(0x21, 0, argm, 0, 0);
			interrupt(0x21, 4,argm, 0x2000, 0);
						
		}
		else if(compare(command,"delete\0"))
		{
			
			interrupt(0x21, 0, "\n", 0, 0);
			interrupt(0x21, 7,argm, 0, 0);
			for(i=0;buffer[i]='\0';i++)
			{
				buffer[i]='\0';
			}
		}
		else if(compare(command,"list\0"))
		{
			interrupt(0x21, 0, "\n", 0, 0);
			interrupt(0x21, 9, argm, 0, 0);
		}
		else if(compare(command,"copy\0"))
		{
			parseInput(argm,arg1,arg2);
			interrupt(0x21, 3, arg1, buffer, 0);
			interrupt(0x21, 8, arg2, buffer, 1); 
			
		}
		else if(compare(command,"create\0"))
		{
			interrupt(0x21, 0, "\nEnter your file content>", 0, 0);
			interrupt(0x21, 1, buffer, 0, 0);
			while(1)
			{
				//interrupt(0x21, 0, "\n", 0, 0);
				//interrupt(0x21, 0, buffer, 0, 0);
				interrupt(0x21, 0, "\n", 0, 0);
				interrupt(0x21, 1, check, 0, 0);
				//interrupt(0x21, 0, "\n", 0, 0);
				//interrupt(0x21, 0, check, 0, 0);
				if(check[0]=='\n')
				{
					interrupt(0x21, 8, argm, buffer, 1);
					break; 
				}
				else
				{
					j=0;
					while(buffer[j]!='\0')
					{
						j++;
					}
					
					i=0;
					while(check[i]!='\0')
					{
						buffer[j]=check[i];
						i++;
						j++;
					}
					buffer[j]='\0';				 
				}
				
			}
		}
		else
		{
			interrupt(0x21,0,"\nError!!Wrong command.",0,0);
		}
		
	
	}
}

void parseInput(char* str, char* command, char* argm)
{
	int i, j, flag;
	i=0;
	j=0;
	flag=0;
	while(str[i]!=' ')
	{
		command[i] = str[i];
		command[i+1] ='\0';
		i++;
		if(str[i]=='\0')
		{
			flag=1;
			break;
		}
	}
	command[i] = '\0';
	if(flag!=1)
	{
		i++;
	
		while(str[i]!='\0')
		{
			argm[j] = str[i];
			argm[j+1] = '\0';
			i++;
			j++;
		}
	}
	argm[j] = '\0';
}
/*
int strCmp(char* str1, char* str2)
{
	int i;
	int output =1;
	for(i=0; str1[i]!=0x0 || str2[i]!=0x0; i++)
	{
		if(str1[i]!=str2[i])
			return 0;
	}
	if(str1[i]!=0x0 || str2[i]!=0x0)
		return 0;
	return output;
}
*/

int compare(char* String1, char* String2) 
{
	int i = 0;
	int output = 1;

	while(String2[i] != '\0' || String1[i] != '\0') 
	{         // run till one of the array is \0
		if(String1[i] != String2[i])
		{
			return 0;
		}
		i++;

	}
	if(String2[i] != '\0' || String1[i] != '\0')
	{
		return 0;
	} 
	return output;
}
