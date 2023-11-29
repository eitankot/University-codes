tester: mainAsembler.o macroFixer.o firstMove.o linkedList.o dataImageAndCodeFixer.o codeImageHelper.o externalsAndEnteries.o binaryOtherHelper.o buildBinaryCode.o printToFile.o checkLength.o
	gcc -ansi -Wall -g mainAsembler.o macroFixer.o firstMove.o linkedList.o dataImageAndCodeFixer.o codeImageHelper.o externalsAndEnteries.o binaryOtherHelper.o buildBinaryCode.o printToFile.o checkLength.o -o tester
macroFixer.o: macroFixer.c asembler.h
	gcc -c -ansi -Wall macroFixer.c -o macroFixer.o 
firstMove.o: firstMove.c asembler.h
	gcc -c -ansi -Wall firstMove.c -o firstMove.o
linkedList.o: linkedList.c asembler.h
	gcc -c -ansi -Wall linkedList.c -o linkedList.o
dataImageAndCodeFixer.o: dataImageAndCodeFixer.c asembler.h
	gcc -c -ansi -Wall dataImageAndCodeFixer.c -o dataImageAndCodeFixer.o
codeImageHelper.o: codeImageHelper.c asembler.h
	gcc -c -ansi -Wall codeImageHelper.c -o codeImageHelper.o 
mainAsembler.o: mainAsembler.c asembler.h
	gcc -c -ansi -Wall mainAsembler.c -o mainAsembler.o
binaryOtherHelper.o: binaryOtherHelper.c asembler.h
	gcc -c -ansi -Wall binaryOtherHelper.c -o binaryOtherHelper.o
externalsAndEnteries.o: externalsAndEnteries.c asembler.h
	gcc -c -ansi -Wall externalsAndEnteries.c -o externalsAndEnteries.o
buildBinaryCode.o: buildBinaryCode.c asembler.h
	gcc -c -ansi -Wall buildBinaryCode.c -o buildBinaryCode.o
printToFile.o: printToFile.c asembler.h
	gcc -c -ansi -Wall printToFile.c -o printToFile.o
checkLength.o: checkLength.c asembler.h
	gcc -c -ansi -Wall checkLength.c -o checkLength.o
