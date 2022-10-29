
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxStrLength 200

int main() {

	char inputStr[maxStrLength+1] ;
	scanf_s("%s", inputStr , sizeof inputStr);
	//char inputStr[maxStrLength+1] = "1-2*55*1+2-3+2-1";
	//char inputStr[maxStrLength+1] = "6-6+7*89/23-6*8*57/2";
	//char inputStr[maxStrLength+1] = "2*3/2";
	//char inputStr[maxStrLength+1] = "-112-3*2+2-1";
	//char inputStr[maxStrLength+1] = "-112-3*2/2+2-1";
	//char inputStr[maxStrLength+1] = "-112.000000/-3-2+2-1";
	//char inputStr[maxStrLength+1] = "1+2+3";
	//char inputStr[maxStrLength+1] = "3.000000+3";
	//char inputStr[maxStrLength+1] = "(3*3/2+3-2)+2";
	//char inputStr[maxStrLength+1] = "1/(1-3)*3";
	int isOnlyNumber = 0;
	
	// convert the input the string into standard form
	for (int i = 0; i < strlen(inputStr); i++) {
		if (inputStr[i] == '-' && (inputStr[i - 1] == '.' || (inputStr[i - 1] >= 48 && inputStr[i - 1] <= 57))) {
			inputStr[i] = '+';
			char currentChar = inputStr[i + 1];
			char nextChar = inputStr[i + 2];

			inputStr[i + 1] = '-';
			for (int j = i + 2; j <= strlen(inputStr); j++) {
				inputStr[j] = currentChar;
				currentChar = nextChar;
				nextChar = inputStr[j + 1];
			}
		}
	}
	printf("Standard String : %s", inputStr);
	while (isOnlyNumber == 0)
	{
		//  1st Step      find pos of slicing str
		int prevOp = -1;
		int currentOp = -1;
		int prev_op_pos = -1, prev_prev_op_pos = -1 , current_op_pos = -1;
		int isSliceSelected = 0;
		for (int j = 0; j < strlen(inputStr); j++) {
			if (isSliceSelected)
				break;
			//if it encounters operation
			if (!(inputStr[j] == '.' || inputStr[j] == '-' || (inputStr[j] >= 48 && inputStr[j] <= 57)))
			{
				prev_prev_op_pos = prev_op_pos+1;
				prev_op_pos = current_op_pos;
				current_op_pos = j;
				// here i am translating operator into numerical value
				switch (inputStr[j])
				{
				case '(':
					prev_prev_op_pos = j+1;
					prev_op_pos = j;
					//current_op_pos = j + 1;
					prevOp = 6;
					currentOp = -1;
					break;
				case ')':
					isSliceSelected = 1;
					currentOp = 7;
					break;
				case '/':
					if (prevOp == -1)
						prevOp = 4;
					else
						currentOp = 4;
					break;
				case '*':
					if (prevOp == -1)
						prevOp = 3;
					else
						currentOp = 3;
					break;
				case '+':
					if (prevOp == -1)
						prevOp = 2;
					else
						currentOp = 2;
					break;
				case '-':
					if (prevOp == -1)
						prevOp = 1;
					else
						currentOp = 1;
					break;
				}
				// checking if prev_op has less precedence than current op
				if (isSliceSelected == 1)
				{
					break;
				}
				if (prevOp < currentOp && currentOp != -1 && prevOp != -1)
				{
					prevOp = currentOp;
					currentOp = -1;
				}
				else if (prevOp == 6 && currentOp != -1)
				{
					prevOp = currentOp;
					currentOp = -1;
					//prev_op_pos = j;
					//current_op_pos = j;
				}
				// else if current op is still un initialized then again loop
				//else current op has less precedence than prev op
				// so slice the string fro prev op
				else if(currentOp != -1) {
					isSliceSelected = 1;
				}
			}
		}
		//if current op == -1 it means it has only one operation so
		if (currentOp == -1)
		{
			prev_prev_op_pos = prev_op_pos + 1;
			current_op_pos = strlen(inputStr);
		}
		//  2nd step  Now slice the input string
		char slicedStr[maxStrLength + 1] = "";
		for (int k = 0; k < current_op_pos - prev_prev_op_pos; k++) {
			slicedStr[k] = inputStr[prev_prev_op_pos + k];
		}
		printf("Start : %d  End : %d\n\n", prev_prev_op_pos, current_op_pos);
		printf("\nStr : %s", slicedStr);
		char resultStr[maxStrLength + 1] = "";
		if (!(prevOp == 6 && currentOp == 7)) // it means there is no operation inside bracker
		{								   // so no separation
			// get a string containing two floats and one operation
			//char slicedStr[maxStrLength + 1] = "1/2";
			// 
			//breaking the string into floats and operation 
			float f1 = 0, f2 = 0;
			char sf1[maxStrLength + 1] = "";
			char sf2[maxStrLength + 1] = "";
			char op = '0';
			for (int i = 0; i < strlen(slicedStr); i++) {

				//if current char is number or . dot or - minus
				if (slicedStr[i] == '.' || slicedStr[i] == '-' || (slicedStr[i] >= 48 && slicedStr[i] <= 57))
				{
					sf1[i] = slicedStr[i];
				}
				//if current char is operation || not a number or . dot
				else {
					op = slicedStr[i];
					// now extract second float
					strcpy_s(sf2, sizeof slicedStr, slicedStr + i + 1);
					//convert these string of floats into actual floats
					f1 = atof(sf1);
					f2 = atof(sf2);
					break;
				}
			}
			printf("\nf1 =%f", f1);
			printf("\nf2 = %f", f2);
			// now do calcualtion on this part of string
			float result = 0;
			switch (op) {
			case '+':
				result = f1 + f2;
				break;

			case '-':
				result = f1 - f2;
				break;
			case '*':
			case 'x':
				result = f1 * f2;
				break;
			case '/':
				result = f1 / f2;
				break;

			}
			printf("\n\n\n\n%s = %f", slicedStr, result);

			// Convert the float result into string
			sprintf_s(resultStr, sizeof resultStr, "%f", result);
			printf("\n\nResult str = %s", resultStr);



		}
		else
		{
			strcpy_s(resultStr, sizeof resultStr, slicedStr);
		}
		
		// now update the original string 
		// replace the current operand operation operand with result
		//	char inputStr[maxStrLength+1] = "1-2*55*1+2-3+2-1";

		//---- 2nd step create copy of string after operational string
		char copyAfterStr[maxStrLength + 1] = "";
		int copyIndex;
		if (prevOp == 6 && currentOp == 7) {
			copyIndex = current_op_pos+1;
		}
		else {
			copyIndex = current_op_pos ;
		}
		for (int i = 0; inputStr[copyIndex] != '\0'; i++)
		{
			copyAfterStr[i] = inputStr[copyIndex];
			copyIndex++;
		}
		printf("\n\nCopy After Str = %s", copyAfterStr);
		// 3rd step --- now modify original input string
		int replaceIndex;
		if (prevOp == 6 && currentOp == 7)
		{
			replaceIndex = prev_prev_op_pos - 1;
		}
		else {
			replaceIndex = prev_prev_op_pos;
		}
		for (int i = 0; i < strlen(resultStr); i++ ) {
			inputStr[replaceIndex] = resultStr[i];
			replaceIndex++;
		}
		for (int i = 0; i < strlen(copyAfterStr); i++) {
			inputStr[replaceIndex] = copyAfterStr[i];
			replaceIndex++;
		}
		for (; replaceIndex < sizeof inputStr; replaceIndex++) {
			inputStr[replaceIndex] = '\0';
		}
		printf("\n\nFinal Input Str = %s", inputStr);
		//stop the loop when inputStr contains only numbers
		for (int i = 0; i < strlen(inputStr); i++) {
			if (inputStr[i] == '.' || (inputStr[i] >= 48 && inputStr[i] <= 57) )
				isOnlyNumber = 1;
			else
			{
				if (i != 0)
				{
					isOnlyNumber = 0;
					break;
				}
				else
					isOnlyNumber = 1;
				
			}
		}

	}
	return 0;
}