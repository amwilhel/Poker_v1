#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

#include <iostream>
#include <stdlib.h> 
#include <string>
#include <algorithm>

using namespace std;

struct card {
	int suit;
	int number;
	bool keep;
	card* next;
	card* prev;
};

struct deck {
	card* head;
};

int player_bank;
card player_hand[5];
char player_move[4];
string player_movestr;
deck* ll_deck;
deck* discard_deck;


//count items in the deck
int count_items(deck* ll_deck)
{
	int count = 0;
	card* c = ll_deck->head;
	while (c != NULL)
	{
		++count;
		c = c->next;
	}
	return count;
}

//gets a card at certain index in the deck
card get_item(deck* ll_deck, int index)
{
	card* c = ll_deck->head;
	while (index > 0)
	{
		c = c->next;
		--index;
	}
	return *c;
}

//adds card to the beginning of the linked list deck
void add(deck* ll_deck, int c_num, int c_suit) {
	card* c = new card;
	c->number = c_num;
	c->suit = c_suit;
	c->next = ll_deck->head;
	ll_deck->head = c;
}

//removes first item from deck
void remove_first(deck* ll_deck)
{
	if (ll_deck->head == NULL)
		return;

	card* c = ll_deck->head;
	ll_deck->head = c->next;
	delete c;
}

//remove item at index x
void remove_item(deck* ll_deck, int index)
{
	if (index == 0)
	{
		remove_first(ll_deck);
		return;
	}

	card* prev = ll_deck->head;
	while (index > 1)
	{
		prev = prev->next;
		--index;
	}

	card* c = prev->next;
	prev->next = c->next;
	delete c;
}


//creates new linked list deck
deck* create_deck() {
	deck* ll_deck = new deck;
	ll_deck->head = NULL;

	//adds 52 cards to the deck //n < 15
	for (int n = 2; n < 15; n++)
	{
		for (int y = 0; y < 4; y++)
		{
			add(ll_deck, n, y);
		}
	}

	//checks for cards in current hand and removes them --> This isn't working
	/*for (int x = 0; x < 5; x++){
		for (int y = 0; y < count_items(ll_deck); y++) {
			card* c = *ll_deck[y];
			if (player_hand[x].number == c->number && player_hand[x].suit == c->suit)
				remove_item(ll_deck, y);
		}
	}
	*/
	return ll_deck;
}


//prints deck --> dealing uses a random number generator
void printDeck(deck* ll) {
	cout << "Number of cards remaining: " << count_items(ll) << endl;
	cout << "The deck contains: "<< endl;
	card* c = ll->head;
	while (c != NULL)
	{
		string cardNumber;

		if (c->number == 11)
			cardNumber = "Jack";
		else if (c->number == 12)
			cardNumber = "Queen";
		else if (c->number == 13)
			cardNumber = "King";
		else if (c->number == 14)
			cardNumber = "Ace";
		else
			cardNumber = to_string(c->number);

	if (c->suit == 0)
		cout << cardNumber << " of Hearts." << endl;
	else if (c->suit == 1)
		cout << cardNumber << " of Diamonds." << endl;
	else if (c->suit == 2)
		cout << cardNumber << " of Clubs." << endl;
	else if (c->suit == 3)
		cout << cardNumber << " of Spades." << endl;
	c = c->next;
	}
}

//prints what's currently in the Bank
void printBank() {
	cout << "You currently have $" << player_bank << "." << endl;
}



//prints each card correctly 
void printCard(int x) {
	string cardNumber;

	if (player_hand[x].number == 11)
		cardNumber = "Jack";
	else if (player_hand[x].number == 12)
		cardNumber = "Queen";
	else if (player_hand[x].number == 13)
		cardNumber = "King";
	else if (player_hand[x].number == 14)
		cardNumber = "Ace";
	else
		cardNumber = to_string(player_hand[x].number);

	if (player_hand[x].keep == true) {
		if (player_hand[x].suit == 0)
			cout << cardNumber << " of Hearts.";
		else if (player_hand[x].suit == 1)
			cout << cardNumber << " of Diamonds.";
		else if (player_hand[x].suit == 2)
			cout << cardNumber << " of Clubs.";
		else if (player_hand[x].suit == 3)
			cout << cardNumber << " of Spades.";

	cout << "(Kept)" << endl;
	}
	else {
	if (player_hand[x].suit == 0)
		cout << cardNumber << " of Hearts." << endl;
	else if (player_hand[x].suit == 1)
		cout << cardNumber << " of Diamonds." << endl;
	else if (player_hand[x].suit == 2)
		cout << cardNumber << " of Clubs." << endl;
	else if (player_hand[x].suit == 3)
		cout << cardNumber << " of Spades." << endl;
	}
}

//print players hand
void printHand() {
	cout << "Your Hand :" << endl;
	cout << "A : "; printCard(0);
	cout << "B : "; printCard(1);
	cout << "C : "; printCard(2); 
	cout << "D : "; printCard(3);
	cout << "E : "; printCard(4); 
}

void delete_ll(deck* ll_deck) {
		card* c = ll_deck->head;
		while (c != NULL)
		{
			card* c2 = c;
			c = c->next;
			delete c2;
		}

		delete ll_deck;
}

void promptAgain(string move) {
	while (!cin.good())
	{
		cout << "You've entered an invalid move.  Please try again and enter a card A - E (case-sensitive)." << endl;
		cout << "Enter the three cards you would like to keep: ";
		cin.clear(); // Clear error flags.
		cin.ignore(1000, '\n'); // Ignore rest.
		cin >> move; // Try again.
	}
	cin.ignore(1000, '\n'); // Ignore rest.
}

bool SwapCard(int suit, int number, card* swap_card) {
	card* card_ptr = ll_deck->head;
	while (card_ptr) {
		if (card_ptr->suit == suit && card_ptr->number == number) {
			card card_in_hand = *swap_card; //I dont think I can do this
			swap_card->number = card_ptr->number;
			swap_card->suit = card_ptr->suit;
			card_ptr->number = card_in_hand.number;
			card_ptr->suit = card_in_hand.suit;
			// this is what you do if player_hand is a deck
			//card_ptr->prev->next = swap_card;
			//swap_card->prev = card_ptr;
			//swap_card->next = card_ptr->next;
			//card_ptr->next->prev = swap_card;

			return true;
		}
		card_ptr = card_ptr->next;
	}
	return false;
}

//Checks input for errors
bool handle_move(string move) {

	if (move == "DECK") {
		printDeck(ll_deck);
		cout << "Ready Player: ";
		player_movestr.clear();
	}

	else if (move == "EXIT") {
		delete_ll(ll_deck);
		discard_deck = NULL;
	}

	else if (move == "SWAP") {
		char letter;
		int number;
		int suit;
		int letter_num;

		cout << "Enter the letter of your hand: ";
		cin >> letter;
		if (letter == 'A')
			letter_num = 0;
		else if (letter == 'B')
			letter_num = 1;
		else if (letter == 'C')
			letter_num = 2;
		else if (letter == 'D')
			letter_num = 3;
		else if (letter == 'E')
			letter_num = 4;
		cout << "Enter the number of the card you want. 2 - 14: ";
		cin >> number;
		cout << "Enter the suit (0 for Hearts; 1 for Diamonds; 2 for Clubs; 3 for Spades): ";
		cin >> suit;
		// TODO - you want to check if these values are within range. all 3 vars
		printCard(letter_num);
		bool swap_result = SwapCard(suit, number, &player_hand[letter_num]);
		cin.clear();
		cin.ignore(1000, '\n');
		printHand();
		return swap_result;
	}

	else if (move.length() == 3) {
		for (int x = 0; x < 3; x++) {
			if (move[x] == 'A') {
				player_hand[0].keep = true;
			}
			else if (move[x] == 'B') {
				player_hand[1].keep = true;
			}
			else if (move[x] == 'C') {
				player_hand[2].keep = true;
			}
			else if (move[x] == 'D') {
				player_hand[3].keep = true;
			}
			else if (move[x] == 'E') {
				player_hand[4].keep = true;
			}
			else {
				cout << "You've entered an invalid move.  Please try again and enter a card A - E (case-sensitive)." << endl;
				cout << "Enter the three cards you would like to keep: ";
				cin.clear(); // Clear error flags.
				cin.ignore(1000, '\n'); // Ignore rest.
				//cin >> move; // Try again.
				// you need to break from this for loop.
				return false;
				
			}
		}
	}
	else if (move.length() != 3) {
		cout << "You've entered an invalid move.  Please try again and enter a card A - E (case-sensitive)." << endl;
		cout << "Enter the three cards you would like to keep: ";
		cin.clear(); // Clear error flags.
		cin.ignore(1000, '\n'); // Ignore rest.
		//cin >> move; // Try again.
		return false;
	}
	cin.ignore(1000, '\n');
	return true;
}
//void swap() {
//}

//Deal the cards 
void deal() {
	for (int x = 0; x < 5; x++) {
		if (player_hand[x].keep != true) {
			int index = rand() % count_items(ll_deck);
			player_hand[x] = get_item(ll_deck, index);
			remove_item(ll_deck, index);
			if (count_items(ll_deck) == 0) {
				delete ll_deck;
				ll_deck = create_deck();
				cout << "A new deck was created: " << count_items(ll_deck) << "cards" << endl;
			}
		}
	}
	cout << "This many cards are left : " << count_items(ll_deck) << endl;
}


void score_turn() {
	const int SIZE = 5;
	int numbers[SIZE];

	for (int x = 0; x < 5; x++) {
		numbers[x] = player_hand[x].number;
	}

	sort(numbers, numbers + SIZE);
	//cout << "Sorted array: " << numbers[0] << numbers[1] << numbers[2] << numbers[3] << numbers[4] << endl;
	  
	//check for royal flush
	if (numbers[0] == 10 && numbers[1] == 11 && numbers[2] == 12 && numbers[3] == 13 && numbers[4] == 14 && player_hand[0].suit == player_hand[1].suit && player_hand[0].suit == player_hand[2].suit && player_hand[0].suit == player_hand[3].suit && player_hand[0].suit == player_hand[4].suit) {
		cout << "Congratulations! You have a Royal Flush and earned $800!" << endl;
		player_bank += 800;
	}

	//check for straight flush
	else if ((numbers[1] - numbers[0]) == 1 && (numbers[2] - numbers[1]) == 1 && (numbers[3] - numbers[2]) == 1 && (numbers[4] - numbers[3]) == 1 && player_hand[0].suit == player_hand[1].suit && player_hand[0].suit == player_hand[2].suit && player_hand[0].suit == player_hand[3].suit && player_hand[0].suit == player_hand[4].suit) {
		cout << "Congratulations! You have a Straight Flush and earned $50!" << endl;
		player_bank += 50;
	}

	//check for four of a kind
	else if ((numbers[0] - numbers[1] - numbers[2]) - numbers[3] == 0) {
		cout << "Congratulations! You have a Four of a Kind and earned $25!" << endl;
		player_bank += 25;
	}

	//check for four of a kind
	else if ((numbers[1] - numbers[2] - numbers[3]) - numbers[4] == 0) {
		cout << "Congratulations! You have a Four of a Kind and earned $25!" << endl;
		player_bank += 25;
	}

	//check for flush
	else if (player_hand[0].suit == player_hand[1].suit && player_hand[0].suit == player_hand[2].suit && player_hand[0].suit == player_hand[3].suit && player_hand[0].suit == player_hand[4].suit){
		cout << "Congratulations! You have a Flush and earned $6!" << endl;
		player_bank += 6;
	}

	//check for straight
	else if (((numbers[1] - numbers[0]) == 1) && ((numbers[2] - numbers[1]) == 1) && ((numbers[3] - numbers[2]) == 1) && ((numbers[4] - numbers[3]) == 1)) {
		cout << "Congratulations! You have a Straight and earned $4!" << endl;
		player_bank += 4;
	}

	//check for three of a kind
		for (int x = 0; x < 3; x++) {
			if ((numbers[x] - numbers[x + 1] - numbers[x + 2]) == 0) {
				cout << "Congratulations! You have a Three of a Kind and earned $3!" << endl;
				player_bank += 3;
				break;
			
		}
	}

	//check for two pair
	if ((numbers[0] - numbers[1]) == 0 && (numbers[2] - numbers[3]) == 0) {
		cout << "Congratulations! You have Two Pair and earned $2!" << endl;
		player_bank += 2;
	}

	else if ((numbers[1] - numbers[2]) == 0 && (numbers[3] - numbers[4]) == 0) {
		cout << "Congratulations! You have Two Pair and earned $2!" << endl;
		player_bank += 2;
	}

	else if ((numbers[0] - numbers[1]) == 0 && (numbers[3] - numbers[4]) == 0) {
		cout << "Congratulations! You have Two Pair and earned $2!" << endl;
		player_bank += 2;
	}

	//check for a pair
	for (int x = 0; x < 4; x++) {
		if ((numbers[x] > 10) && (numbers[x] - numbers[x + 1]) == 0) {
			cout << "Congratulations! You have a Pair (Jacks or higher) and earned $1!" << endl;
			player_bank += 1;
			break;
		}
	}
}


//Player one's turn
void player_turn() {
	int round = 0;

	while (player_bank != 0) {
		++round;
		cout << "Ready? Round: " << round << ". The ante is $1." << endl;
		//player_bank = --player_bank;
		--player_bank;
		printBank();
		deal();

		//Resets player_hand
		for (int x = 0; x < 5; x++) {
			player_hand[x].keep = false;
		}
		printHand();

		//Read in the move
		cout << "Enter the three cards you would like to keep: ";
		//cin >> player_movestr;

		//Check for valid input
		//check_move(player_movestr);
		do {
			cin >> player_movestr;
		} while (!handle_move(player_movestr));

		// You need to check whether the user entered 'exit'
		if (player_movestr == "EXIT") {
			cout << " Hope you enjoyed your game.";
		}else {
			deal();

			printHand();
			score_turn();
			printBank();
		}
		cout << "---------------------------------" << endl;
		cout << endl;

		//Resets player_hand
		for (int x = 0; x < 5; x++) {
			player_hand[x].keep = false;
		}
	}
		cout << "GAME OVER.  You ran out of money.  :(  Type 'exit' to quit.";
}

//Play the game;
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);

	player_bank = 10;
	cout << "Welcome to Poker! ";
	printBank();
	ll_deck = create_deck();
	player_turn();
	
	cin.get();

	ll_deck = NULL;
	return 0;
}