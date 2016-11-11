/*
Kyele Haynes
N01163090
Nov 10, 2016
*/


#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

int main(void) {
	//Declares required variables
	int jumpnum = -1; //Sets the Jumpers ID number to -1 so it is not 0 initially
	float jump1 = 0, jump2 = 0, jump3= 0, avg = 0;
	int pass = 0; //Used to count qualifying jumpers
	int nopass = 0; //Used to count non-qualifying jumpers
	int tjumpers; //Used to find total number of jumpers
	float min = 1.5; //height needed to qualify
	float highjump = 0; //The highest jump of the jumper with the highest jump
	float highavg = 0; //The average of the jumper with the highest jump
	int highjumper = 0; //The ID number of the jumper with the highest jump
	int check = 0; //Used to avoid crtain code when the user wants to exit

	FILE *wdata; //creates wdata of type FILE

	wdata = fopen("output.txt", "w"); //Sets wdata as a writable .txt file named output.txt

	if (wdata == NULL){ //Enters if the file does not create properly
		printf("The necessary files could not be created, the program will now exit"); //Prints program will exit
		exit(1); //Exits program
	} //Ends if

	fprintf(wdata, "Number		Average		Qualify?\n"); //Prints the headers to output.txt

	while (jumpnum != 0){ //Runs when jumpnum does not equal 0

		printf("Please enter the jumper's number. Enter 0 to terminate data input\n"); //Asks for the identification number of the jumper
		scanf("%d",&jumpnum); //Scans for the jumpers ID number

		if (jumpnum == 0){ //Runs if jumpnum = 0, meaning the user inputted 0 to exit
			printf("\n\nThe final output has been printed in the file named output.txt\nIt is located in the same directory as the .c file for this program\n\n\n"); //States where the output.txt file resides upon exit
			check = 1; //Sets check equal to 1 so the program will avoid asking for the 3 jump heights and avoid checking the average vs the min required for qualification
		} //Ends if

		if (check == 0){
			printf("Now enter their 3 best jump heights and press enter between each number\n"); //Prints a line asking for the 3 best jump heights
			scanf("%f %f %f", &jump1, &jump2, &jump3); //Scans for the 3 best jump heights
			printf("\n"); //Prints a blank line
			avg = (jump1 + jump2 + jump3) / 3; //Calculates the average of the 3
			fprintf(wdata, "%d		%.2f ", jumpnum, avg); //Prints the jumpers ID number and their average to the output.txt file
		} //Ends if

		if (jump1 > highjump || jump2 > highjump || jump3 > highjump){ //Checks if any of the most recent jumpers jumps are higher than the current highest jump
			highavg = avg; //Saves the average of the jumper with the highest jump into the variable highavvg to be used in the final output
			highjumper = jumpnum; //Saves the ID number of the jumper with the highest jump into the variable highjumper to be used in the final output
			if (jump1 >= jump2 && jump1 >= jump3){ highjump = jump1; } //Sets the new highest jump to jump1 if it is the highest of the 3
			if (jump2 >= jump1 && jump2 >= jump3){ highjump = jump2; } //Sets the new highest jump to jump2 if it is the highest of the 3
			if (jump3 >= jump2 && jump3 >= jump1){ highjump = jump3; } //Sets the new highest jump to jump3 if it is the highest of the 3
		} //Ends if

		if (avg >= min && check == 0){ //Checks if the current jumpers average is high enough to qualify
			fprintf(wdata, "		Yes\n"); //Prints Yes to the output.txt file under the Qualify? column
			pass++; //Adds one to the total count of all qualifying jumpers		
		} //Ends if

		if (avg < min && check == 0){ //Checks if the current jumpers average is lower than the qualifying amount
			fprintf(wdata, "		No\n"); //Prints No to the output.txt file under the Qualify? column
			nopass++; //Adds one to the total count of all non-qualifying jumpers
		} //Ends if
	}	
	tjumpers = pass + nopass; //Calculates the total number of jumpers by adding the qualifying and non-qualifying ones together
	fprintf(wdata, "\n\nOut of %d jumper(s) %d qualified while %d did not.", tjumpers, pass, nopass); //Prints the total number of jumpers, the amount that qualified and the amount that did not qualify
	fprintf(wdata, "\nThe highest jump was achieved by jumper number %d.\n", highjumper); //Prints the ID number of the jumper with the highest jump
	fprintf(wdata, "Their highest jump was %.2fm and they ended with an average jump height of %.2fm", highjump, highavg); //Prints the average and highest jump of the jumper with the highest jump
	fclose(wdata); //closes the output.txt file
	Sleep(500); //Adds a small delay
	return 0;
} //Ends main