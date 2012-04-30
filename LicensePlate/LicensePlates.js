var CHARS = 26;
var NUMBERS = 10;

function Power(base, exponent)
{
	var value = base;

	if(exponent == 0)
		return 1;
	if(exponent == 1) 
		return value;
	for(i = 2; i <= exponent; i++)
		value *= base;

	return value;
}

function PrintPattern(num_letters, num_numbers, form)
{
	var pattern = "";

	//create the pattern based on number of letters and numbers needed	
	//this is mainly text format
	if(num_letters > 1) {
		pattern = pattern + num_letters + " letters";
	}
	else if(num_letters == 1) {
		pattern = pattern + "1 letter";
	}
	if(num_numbers > 1) {
		if(num_letters >= 1) {
			pattern = pattern +  ", ";
		}
		pattern = pattern +  num_numbers + " numbers";
	}
	else if(num_numbers == 1) {
		if(num_letters >= 1) {
			pattern = pattern + ", ";
		}
		pattern = pattern +  "1 number";
	}
	
	form.value = pattern;
}

function IdentifyPattern(population_form, pattern_form, total_form, excess_form )
{		
	var population_size = population_form.value
	var min_numbers_needed = 0;
	var min_plates_needed = 0;
	var min_letters_needed = 0;
	var lowest_remainder = 9999;
	var excess_plates = 0;

	if(population_size === 0) {
		population_form.value = 100000;
		total_form.value = min_plates_needed;
		excess_form.value = excess_plates;
		return;
	}
	
	min_letters_needed = 1;
	var highest_value = CHARS;
	while(highest_value < population_size) {
		highest_value *= CHARS;
		min_letters_needed++;
	}
	
	//originally fill using only letters, then remove a letter and try to fill with numbers instead
	for(temp_letters_needed = min_letters_needed; temp_letters_needed >= 0; temp_letters_needed--) {
		var num_plates_made = Power(CHARS, temp_letters_needed);
		if(temp_letters_needed == 0) { num_plates_made = 0; } //0 plates are made if there are no letters used
		
		//fill in with 10s until value is greater than number of plates needed
		var temp_numbers_needed = 0;
		while(num_plates_made < population_size) {
			//if num_plates made is 0, just add 10, as we only have one digit
			if(num_plates_made == 0) {
				num_plates_made = NUMBERS;
				temp_numbers_needed++;
			}
			//otherwise multiply by 10 since we are adding another digit to the premutations
			else {
				num_plates_made *= NUMBERS;
				temp_numbers_needed ++;
			}
		}

		//check if remainder is lower than current lowest remainder
		//if it is, store new values
		var temp_remainder = num_plates_made - population_size;
		if(temp_remainder < lowest_remainder){
			min_plates_needed = num_plates_made;
			lowest_remainder = temp_remainder;
			min_numbers_needed = temp_numbers_needed;
			min_letters_needed = temp_letters_needed;
		}
	}
	excess_plates = lowest_remainder;
	PrintPattern(min_letters_needed, min_numbers_needed, pattern_form);
	total_form.value = min_plates_needed;
	excess_form.value = excess_plates;
}