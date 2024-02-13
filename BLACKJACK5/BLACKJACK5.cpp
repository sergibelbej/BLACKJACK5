#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;


void cards(string& card, int& cardValue, bool& gotAnAce);
void checkWin(int& playerPts, bool& playerWin, int& croupierPts, bool& draw, bool& croupierWin);
void lastTurn(int& playerPts, string& card, int& cardValue, bool& gotAnAce, int& croupierPts, bool& playerWin, bool& draw, bool& croupierWin);

int main() {
    srand(time(0));

    int playerPts = 0, croupierPts = 0, firstCard, secondCard, firstValue, secondValue, cardValue, contDrawCards, newValue;
    bool playerWin = false, gotAnAce = false, firstCardAce = false, draw = false, croupierWin = false, newcardAce = false;
    string card;


    cards(card, cardValue, gotAnAce); //You get your first card. It checks if its an ace, if it is, it's saved on a bool for later.  
    cout << "You've been given a " << card;
    firstCard = cardValue;
    if (gotAnAce == true) {
        firstCardAce = true;
    }
    gotAnAce = false;
    cards(card, cardValue, gotAnAce); //You get your second card. Same as before. 
    cout << " and a " << card << endl;
    secondCard = cardValue;
    if (gotAnAce == true) {
        do {
            cout << "What value do you want your second ace to be?\n1-. 1 Point\n2-. 11 Points\n"; //Changes the second ace value.
            cin >> secondValue;

        } while (secondValue != 1 && secondValue != 2);
        switch (secondValue) {
        case 1:
            secondCard = 1;
            break;
        case 2:
            secondCard = 11;
            break;
        }
    }
    if (firstCardAce == true) {
        cout << "What value do you want your first ace to be?\n1-. 1 Point\n2-. 11 Points\n"; //Changes the first ace value. 
        cin >> firstValue;
        switch (firstValue)
        {
        case 1:
            firstCard = 1;
            break;
        case 2:
            firstCard = 11;
        }
    }
    playerPts = firstCard + secondCard; //Total of the points of the cards. 
    cout << "You have " << playerPts << " points.";

    cards(card, cardValue, gotAnAce); //The croupier gets his card.
    cout << "\nThe croupier got a " << card << endl;
    if (gotAnAce == true) {
        cardValue = 11;
    }
    croupierPts += cardValue;
    lastTurn(playerPts, card, cardValue, gotAnAce, croupierPts, playerWin, draw, croupierWin); //If you get 21 points, we go to the last turn. 

    if (!playerWin && !croupierWin) {
        do {
            do {
                cout << "Do you want another card?\n1-. Yes\n2-. No" << endl;
                cin >> contDrawCards;
            } while (contDrawCards != 2 && contDrawCards != 1);

            if (contDrawCards == 1) {
                cards(card, cardValue, gotAnAce);
                cout << "You've been given a " << card << endl;

                if (gotAnAce) {
                    cout << "What value do you want your first ace to be?\n1-. 1 Point\n2-. 11 Points\n"; //Changes the first ace value. 
                    cin >> newValue;
                    switch (newValue)
                    {
                    case 1:
                        cardValue = 1;
                        break;
                    case 2:
                        cardValue = 11;
                        break;
                    }
                }
                playerPts += cardValue;
                cout << "You have " << playerPts << " points total." << endl;

            }


        } while (contDrawCards != 2 && playerPts <= 21); // You can't draw more cards after you decline the offer or exceed 21. 
        cards(card, cardValue, gotAnAce); //The croupier gets his other card. 
        cout << "\nThe croupier got a " << card << endl; //
        if (gotAnAce == true) {
            if (11 + croupierPts > 21) {
                cardValue = 1;
            }
            else {
                cardValue = 11;
            }
        }
        croupierPts += cardValue;
        cout << "The croupier has a total of " << croupierPts << " points. " << endl;
        checkWin(playerPts, playerWin, croupierPts, draw, croupierWin); 

    }
    return 0;
}

void cards(string& card, int& cardValue, bool& gotAnAce) { //The deck. Randomly generates a card with the two arrays.  
    string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    string values[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

    int suitIndex = rand() % 4;
    int valueIndex = rand() % 13;

    card = values[valueIndex] + " of " + suits[suitIndex];
    cardValue = min(valueIndex + 2, 10);
    if (valueIndex == 12) {
        gotAnAce = true;
    }
    else {
        gotAnAce = false;
    }
}

void checkWin(int& playerPts, bool& playerWin, int& croupierPts, bool& draw, bool& croupierWin) { //At the end, check if you whether win, lose or draw.
    //Player wins
    if (playerPts == 21 && croupierPts < 21) {
        playerWin = true;
        cout << "The player has won! Either the player got 21 points or the croupier got more than 21 points.";
    }
    else if (playerPts < 21 && croupierPts > 21) {
        playerWin = true;
        cout << "The player has won! The croupier got more than 21 points. ";
    }
    else if (playerPts > croupierPts && playerPts < 21) {
        playerWin = true;
        cout << "The player has won! The player total point is higher than the croupier's.";
    }
    //Draw
    else if (playerPts == 21 && croupierPts == 21) {
        draw = true;
        cout << "Draw! Both the croupier and the player got 21 points. ";
    }
    //Player fails
    else if (playerPts > 21) {
        croupierWin = true;
        cout << "The croupier has won! The player got more than 21 points.";
    }
    else if (playerPts < 21 && (croupierPts > playerPts)) {
        croupierWin = true;
        cout << "The croupier has won! The player had less than 21 points, but the croupier had a greater number, without surpassing 21 points.";
    }
}

void lastTurn(int& playerPts, string& card, int& cardValue, bool& gotAnAce, int& croupierPts, bool& playerWin, bool& draw, bool& croupierWin) {
    if (playerPts == 21) { // Start last turn. If the croupier does get to 21 points, it's a draw. 
        cout << "This is the last turn, since you got 21 points on the first go! The croupier will try to reach 21 points to draw." << endl;
        cards(card, cardValue, gotAnAce);
        if (gotAnAce == true) {
            cardValue = 11;
        }
        croupierPts += cardValue;
        cout << "The croupier got a " << card << ", that's " << croupierPts << " points total. " << endl;
        checkWin(playerPts, playerWin, croupierPts, draw, croupierWin);

    }

}
