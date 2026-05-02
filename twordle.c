#include <stdio.h>

#define max 6
#define word_l 5
void read_wordle(FILE *fp, char w[]);
void get_word(char guess[]);
void response(char guess[], char wordle[], char display[], char symbol[]);
int win(char display[]);
void reset(char display[], char symbol[]);
void history(char prev_display[][word_l + 1], char prev_symbol[][word_l + 1], char display[], char symbol[], int attempt);
int main(){
	char wordle[word_l + 1];
	char guess[word_l + 2];
	char display[word_l + 1];
	int attempt;
	char symbol[word_l + 1];
	char prev_display[max][word_l + 1];
	char prev_symbol[max][word_l + 1];
	int i;
	int won = 0;
	FILE *in;
	in = fopen("word.txt", "r");
	if (in == NULL) {
		printf("Can't open file\n");
		return 1;
	}
	read_wordle(in, wordle);
	fclose(in);
	for (attempt =0; attempt < max; attempt++){
		if(attempt == max - 1){
			printf("FINAL GUESS : ");
		}
		else {
			printf("GUESS %d! Enter your guess: ", attempt + 1);
		}
		get_word(guess);
		printf("================================\n");
		reset (display, symbol);
		response(guess, wordle, display, symbol);
		history(prev_display, prev_symbol, display, symbol, attempt);
		if (win(display)){
			won = 1;
			printf("		%s\n", display);
			printf("	You won in %d guesses!\n", attempt + 1);
			printf("		Amazing!\n");
			break;
		}
		else{
			for (i = 0; i <= attempt; i++){
				printf("%s\n", prev_display[i]);
				printf("%s\n", prev_symbol[i]);
			}
		}
	}
	if (!won){
		printf("You lost, better luck next time!\n");
	}
	return 0;
}
void read_wordle(FILE *fp, char w[]) {
	int i;
	fgets (w,word_l + 1, fp);
	i = 0;
	while (w[i] != '\0' && w[i] != '\n'){
		i++;
	}
	w[i] ='\0';
}
void get_word(char guess[]){
	int i;
	int length;
	while(1){
		fgets(guess, word_l + 2, stdin);
			i=0;
			while (guess[i] != '\0'){
				if (guess[i] == '\n'){
					guess[i] = '\0';
					break;
				}
				i++;
			}
			for (i = 0; i < word_l; i++) {
				if (guess[i] >= 'A' && guess[i] <= 'Z'){
					guess[i] += 32;
				}
			}
			length = 0;
			while (guess[length] != '\0'){
				length++;
			}
		if (length == word_l){
			return;
		}
		printf("Your guess must be 5 letters long.\n");
		printf("Please try again: ");
		}
}
void response(char guess[], char wordle[], char display[], char symbol[]){
	int i;
	int j;
	for (i = 0; i < word_l; i++){
		if(guess[i] == wordle [i]) {
			display[i] = guess[i] - 32;
		}
		else {
		display[i] = guess[i];
		}
	}
	display[word_l] = '\0';
	for (i = 0; i < word_l; i++){
		symbol[i] = ' ';
	}
	for (i = 0; i < word_l; i++){
		if (display[i] >= 'A' && display[i] <= 'Z') {
		}
		else {
			for (j = 0; j < word_l; j++) {
				if (guess[i] == wordle[j]){
					symbol[i] = '^';
					break;
				}
			}
		}
	}
	symbol[word_l] = '\0';
}	
int win(char display[]){
	int i;
	for (i = 0; i < word_l; i++) {
		if (display[i] >= 'a' && display [i] <= 'z'){
			return 0;
		}
	}
	return 1;
}
void reset(char display[], char symbol[]){
	int i;
	for (i = 0; i < word_l; i++){
		display[i] = '\0';
		symbol[i] = '\0';
	}
}
void history(char prev_display[][word_l + 1], char prev_symbol[][word_l + 1], char display[], char symbol[], int attempt){
	int i;
	for (i = 0; i < word_l; i++){
		prev_display[attempt][i] = display[i];
		prev_symbol[attempt][i] = symbol[i];
	}
	prev_display[attempt][word_l] = '\0';
	prev_symbol[attempt][word_l] = '\0';
}
