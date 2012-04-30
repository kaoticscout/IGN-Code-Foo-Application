var DIGITS = 10;

var CHARS = 26;
//Helper function to print the proper string given digits and characters
//Should print # Char(s) #Digit(s)
function GetPatternString(numDigits, numChars) {
	var string = "";
	
	if(numChars > 1) { 
		string += numChars + " Chars";
	}
	else if(numChars ===1) {
		string += "1 Char";
	}
	if(numDigits > 1) {
		if(numChars >=1) { string += " "; }
		string += numDigits + " Digits";
	}
	else if(numDigits === 1) {
		if(numChars >=1) { string += " "; }
		string += "1 Digit";
	}
	
	return string;
}

//object to store data for the pattern
function PatternObject() { 
	this.numPlates = -1;
	this.numDigits = 0;
	this.numChars = 0;
}

function IdentifyPattern(population, patternForm, totalForm, excessForm) { 
	var patternObject = new PatternObject();

	//start with 0 slots for the pattern and increase until a valid pattern is found
	var sizeOfPattern = 0;
	while(patternObject.numPlates < 0) {
		patternObject.numPlates = GetPattern(sizeOfPattern, patternObject, population);
		sizeOfPattern++;
	}
	
	//Print pattern data to forms
	patternForm.value = GetPatternString(patternObject.numDigits, patternObject.numChars);
	totalForm.value = patternObject.numPlates;
	excessForm.value = patternObject.numPlates - population;
}

//Takes in the size of the pattern and tries to build out the pattern with all valid combinations of letters and digits
//If a valid pattern is found, return the number of plates made
//Otherwise returns -1 (invalid flag)
function GetPattern(sizeOfPattern, patternObject, population) {
	var numPlates = 0;
	
	//originally start trying using only digits in the pattern, then switch a character in for one of the digits and try again until using only all characters
	//if number of plates still isn't great enough using all characters, return -1 (invalid)
	for(patternObject.numDigits = sizeOfPattern; patternObject.numDigits >= 0; patternObject.numDigits--) {
		patternObject.numChars = sizeOfPattern - patternObject.numDigits;
		numPlates = Math.pow(DIGITS, patternObject.numDigits) * Math.pow(CHARS, patternObject.numChars);
		if(numPlates === 1) { numPlates = 0; } // handle the case where numDigits = 0, numChars = 0; should be 0, not 1;
		if(population <= numPlates) {
			return numPlates;
		}
	}
	//return invalid
	return -1;
}