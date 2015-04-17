
void printString(char* String);             // Prints a string in the screen
void readString(char* String,int index);              // Reads a string from the input in the keyboard
void readSector(char* buffer, int sector);  // Reads a sector of the image in the disk.
void writeSector(char *buffer, int sector);
void handleInterrupt21(int ax, int bx, int cx, int dx); // For the execution of interrupt21
int mod(int a, int b);       // For Calculating mod function
void readFile(char* filename, char* buffer);
void printFileName();
void writeFile(char *name,char* buffer,int sector);
void deleteFile(char* name);
int ifFound(char* dir, int index, char* filename);
void executeProgram(char* name, int segment);
void addFile(char* dir, int index, char* filename);
void terminate();
char line[80];
int count;
int output, j;



int main() 
{
      
  	char buffer[13312];
	makeInterrupt21();                    
	count=1;
	interrupt(0x21, 4, "shell\0", 0x2000, 0);       
    
	while(1) 
	{
	                 //todo
	}
	return 0;
} 


void printString(char* String) 
{
        int i = 0;
        char c = String[i];
        while (c != 0) 
        {
                interrupt(0x10, 0xE * 256 + c, 0, 0, 0);          //interrupt for printing on the screen.
                c = String[++i];
        }
}


void readString(char* String, int index) 
{
        
        char c = 0,x;

        while(1) 
        {
                c = interrupt(0x16, 0, 0, 0, 0);          // Interrupt for Accepting from keyboard,
                interrupt(0x10, 0xE * 256 + c, 0, 0, 0);  // Interrupt for printing on screen.
                if(c == 0xD) 
                {                            // if ENTER
                        String[index] = '\n';
                    	String[index + 1] = '\0';
                        break;
                }                 
                else
                { 
                	if(c == 0x8) 
                	{            	                // if BACKSPACE
                  	      if(index > 0) 
                  	      {
                  	      		 
                                      x=' ';
                  		      interrupt(0x10, 0xE*256+x,0,0,0);
                  	              interrupt(0x10, 0xE*256+c,0,0,0);
                  	              index = index -1;         
                  	      }                
           	 	}
           	 }
           	 if(c!=0x8)
           	 { 
                	String[index] = c;
                	++index;
                 }                      
        }    
}


void readSector(char* buffer, int sector) {
        int CL = mod(sector, 18);   
        int DH = mod(sector/18, 2);
        int CH = sector/36;

        interrupt(0x13, 2 * 256 + 1, buffer, CH * 256 + CL + 1, DH * 256 + 0);         // interrupt for reading a sector.

}


int mod(int a, int b) {
        while(a >= b)
                a = a - b;
        return a;
}


void handleInterrupt21(int ax, int bx, int cx, int dx) {
	printString("\n");
        if(ax == 0)
        {
                printString(bx);
        }
        else if(ax == 1) 
        {
                printString("Enter a line: ");
                readString(bx,cx);
        }
        else if(ax == 2) 
        {
                readSector(bx, cx);
        } 
        else if(ax == 3) 
        {
                readFile(bx, cx);
        } 
        else if(ax == 4) 
        {
                executeProgram(bx, cx);
        } 
        else if(ax == 5) 
        {
                terminate();
        }
        else if(ax == 6)
        {
        	writeSector(bx,cx);
        }
        else if(ax == 7)
        {
        	deleteFile(bx);
        }
        else if(ax == 8)
        {
        	writeFile(bx,cx,dx);
        } 
        else if(ax == 9)
        {
        	printFileName();
        }
        else 
        {
                printString("ERROR! Enter again...\0\n");
        }
}


void writeSector(char *buffer, int sector)
{
	int CL = mod(sector, 18);   
        int DH = mod(sector/18, 2);
        int CH = sector/36;

        interrupt(0x13, 3 * 256 + 1, buffer, CH * 256 + CL + 1, DH * 256 + 0);	
}


void readFile(char* filename, char* buffer) {                   // Used for reading file from memory.
        char dir[512];
        int index = 0;
        int max = 16;
                                                          // max 16 bytes file can be stored. 
        readSector(dir, 2);
        output = 0;
        output = ifFound(dir, index*32, filename);                    //every directory entry is 32 bytes.
        while(output != 1 && index < max) 
        {
                index++;
                output = ifFound(dir, index*32, filename);
        }
        if(output != 1) 
        {
                interrupt(0x21, 0, "\nError!!File not found", 0, 0);
                buffer[0]='\0';
        } 
        else 
        {
                addFile(dir, index*32, buffer);
        }
}



void printFileName() {                   
        char dir[512];
        char a[7];
        int j;
        char c;
        
        int index = 0;
        c = '\t';                  
        readSector(dir, 2);
        while(index < 16) 
        {
        	if(dir[index*32]==0x00)
        	{
        		
        	}
        	else
                {
                	 
                	 for(j = 0; (j < 6)&&(dir[index*32+j]!=0x00); j++)
                	 {
         		 	a[j]=dir[index*32+j];       
        		 }	
        		 a[j]='\0';
        		 interrupt(0x21, 0, a, 0, 0); 
        		 
        	}
                index++;
                interrupt(0x10, 0xE * 256 + c, 0, 0, 0); 
        }
}

void writeFile(char *name,char* buffer,int sector)
{
	char dir[512];
	char map[512];
	int i=0;
	int max=16;
	int index=0;
	int j=count;
	int k=0;
	int flag=0;
	
	output=0;
	readSector(dir,2);
	readSector(map,1);
	if(dir[index*32]=='\0')
	{
		output=1;
	}
	while(output==0 &&index<max)
	{
		index++;
		if(dir[index*32]=='\0')
		{
			output=1;
		}
	}
	if(output==0)
	{
		printString("\nThere is no space in directory");
	}
	while(name[i]!='\0'&&i<6)
	{
		dir[index*32+i]=name[i];
		i++;
	}
	while(i<6)
	{
		dir[index*32+i]=0x00;
		i++;
	}
	while(j!=0)		
	{
		flag=0;
		while(map[k]!=0x00&&k<512)	
		{
			k++;
			if(map[k]==0x00)
			{
				flag=1;
			}
			
		}
		if(flag==0)
		{
			printString("\nThere is no space in map");
			break;
		}
		else
		{
			j--;
			dir[index*32+i]=k;
			i++;
			map[k]=0xFF;
			writeSector(buffer,k);
		}
	}
	writeSector(dir, 2);
	writeSector(map, 1);
}


int ifFound(char* dir, int index, char* name) 
{
        output = 1;
        j = 0;
        for(j = 0; j < 6; j++) 
        {
                if(name[j] == '\0' && dir[j+index] == '\0' && j != 0) 
                {
              		return output;        
                }
            	if(dir[j+index] != name[j]) 
            	{
                    output = 0;
            	}        
        }
        return output;      
}

void addFile(char* dir, int index, char* buffer) 
{            
        int i = 6;                                               // 6 bytes for each file. 
        int j = 0;
        char sectorBuffer[512];
        int buffer_index = 0;
        int sector_index = 0;
        
        count=0;
        while(dir[index+i] != 0x00 && i < 26) 
        {
                count++;
                sector_index = dir[index+i];
                readSector(sectorBuffer, sector_index);
                for(j = 0; j < 512; j++) 
                {
                        buffer[buffer_index]= sectorBuffer[j];
                        buffer_index++;
                }
                i++;
        }

}

void executeProgram(char* name, int segment) 
{
        char buffer[13312];
        int i = 0;

        readFile(name, buffer);
        if(buffer[0]=='\0')
        {
        	interrupt(0x21, 0, "The file doesnt exist \n", 0, 0);
        }
        else
        {
        	printString("Executing the shell: \n");
  	      while(i < 13312) 
        	{
        	        putInMemory(segment, i, buffer[i]);
        	        i++;
        	}
        	launchProgram(segment);
        }                                // Uses the predefined launchProgram from kernel.asm
}

void terminate() 
{
	interrupt(0x21, 4, "shell\0", 0x2000, 0);  
}

void deleteFile(char* name)
{
	char dir[512],map[512],empty[512];
        int index = 0;
        int k;
        int max = 16;
        int i=6;
        int j=0;  
                                                  // max 16 bytes file can be stored.
        readSector(map,1); 
        readSector(dir, 2);
        for(k=0;k<512;k++)
        {
        	empty[k]=0x00;
        }
        output = 0;
        output = ifFound(dir, index*32, name);                    //every directory entry is 32 bytes.
        while(output != 1 && index < max)
        {
                index++;
                output = ifFound(dir, index*32, name);
        }

        if(output != 1) 
        {
        	printString("Error! File doesn't exist\n\0");
        } 
        else 
        {
        	dir[index*32]=0x00;
               	while(dir[index*32+i]!=0x00)
        	{
        		j=dir[(index*32)+i];
        		map[j]=0x00;
        		writeSector(empty,j);
        		i++;
        	}
               	writeSector(map,1);
        	writeSector(dir,2); 
        }
}

