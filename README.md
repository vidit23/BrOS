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


The commands which work right now:
1) list a - to list all files present in floppyimg
2) exec "progname" - To execute the binary file in progname
3) copy "Fromfile" "Tofile" - to copy the contents of file Fromfile to Tofile (Tofile is a new file name)
4) delete "filename" - To delete all trces of filename in floppyimg
5) type "filename" - To display the contents of filename
6) create "filename" - To create a text file



