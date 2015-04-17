# BrOS
This was taken up as the project in our Operating System course and has been implemented based on the paper in the link below
http://nw08.american.edu/~mblack/papers/sigcse09.pdf

The project has been completed to ProjectD

To get the OS running-
1) Windows - 
    You'll have to download Bochs 2.3.5.
    After installation, just double click on floppya.img
    
2) Linux - 
    Run the command - "sudo apt-get install bochs bochs-x bochs-sdl"
    Go to the directory containing the floppya.img and run the command "bochs -f opsys.bxrc".
    
For development purposes (only for linux) -
The following packages need to be installed - 
- Bochs                                 
- bin86 toolset: as86, ld86, bcc
- hexedit
- nasm
(sudo apt-get install bochs bochs-x bochs-sdl bin86 hexedit nasm)
Then go to the directory of floppya.img and run the following commands - 
chmod -x compileOS.sh
./compileOS.sh
There maybe a chance that a new window open but is blank, then you have to type "c" in the terminal and press Enter.




