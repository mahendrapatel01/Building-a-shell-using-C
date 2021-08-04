all: myshell checkcpupercentage checkresidentmemory listFiles sortFile executeCommands

#fmyshell: myshell.o checkcpupercentage.o checkresidentmemory.o listFiles.o sortFile.o executeCommands.o
#	gcc -o myshell.o checkcpupercentage.o checkresidentmemory.o listFiles.o sortFile.o executeCommands.o

myshell: myshell.o
	gcc  myshell.o -o myshell 
#myshell.o: myshell.c
#	gcc myshell.c -c
	
checkcpupercentage: checkcpupercentage.c
	gcc checkcpupercentage.c -o checkcpupercentage
	
checkresidentmemory: checkresidentmemory.c
	gcc checkresidentmemory.c -o checkresidentmemory
	
listFiles: listFiles.c
	gcc listFiles.c -o listFiles
	
sortFile: sortFile.c
	gcc sortFile.c -o sortFile
	
executeCommands: executeCommands.c
	gcc executeCommands.c -o executeCommands
	
clean:
	rm -f *.o fmyshell
