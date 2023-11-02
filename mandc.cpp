#include <iostream>
#include <iomanip>
#include <stdio.h>

void printBoard(int boatSide, int state, int ml, int cl, int mr, int cr){
    if (boatSide == 1) {
        std::cout << "State " << state << ": [" << ml << "m, " << cl << "c]v ~~~  [" << mr << "m, " << cr << "c]" << std::endl;
    } else if (boatSide == 0){
        std::cout << "State " << state << ": [" << ml << "m, " << cl << "c]  ~~~ v[" << mr << "m, " << cr << "c]" << std::endl;
    }
}

int main()
{
    bool gameOver = false;
    // For storing game state
    int m_left, c_left, b_left = 1; // 1 means boat is on the left.
    int gameState[] = {m_left, c_left, b_left};

    // For storing M&C problem
    int m_total, c_total, b_capacity;
    int problem[] = {m_total, c_total, b_capacity};

    while (true) {
        std::cout << "Enter boat capcity: ";
        std::cin >> b_capacity;
        std::cout << "Enter #missionaries: ";
        std::cin >> m_total;
        std::cout << "Enter #cannibals: ";
        std::cin >> c_total;

        if (b_capacity < 2 || m_total < 1 || c_total < 1) {
            std::cout << "Invalid input!" << std::endl;

        } else if (b_capacity == 2 && (c_total > m_total || m_total > 3 || c_total > 3)) {
            std::cout << "Invalid input!" << std::endl;

        } else if (b_capacity == 3 && !(m_total > c_total) && !(m_total <= 5) && !(c_total <= 5)) {
            std::cout << "Invalid input!" << std::endl;

        } else if (b_capacity >= 4 && m_total < c_total) {
            std::cout << "Invalid input!" << std::endl;
        } else {
            break;
        }
    }
    
    m_left = m_total;
    c_left = c_total;
    int m_right = m_total - m_left, c_right = c_total - c_left;
    int count = 1;
    int m_b, c_b;

    while (!gameOver) {
        printBoard(b_left, count, m_left, c_left, m_right, c_right);
        while (true) {
            std::cout << "Enter #m #c aboard boat: ";
            std::cin >> m_b >> c_b;

            if ((m_b + c_b) > b_capacity || (m_b + c_b) < 1 || (m_b < c_b && m_b > 0) ) {
                std::cout << "Invalid Input!" << std::endl;

            } else if (b_left == 1 && (m_b > m_left || c_b > c_left)) {
                std::cout << "Invalid Input!" << std::endl;

            } else if (b_left == 0 && (m_b > m_right || c_b > c_right)) {
                std::cout << "Invalid Input!" << std::endl;

            } else {
                break;
            }
        }

        if (b_left == 0) { // If boat was on the right.
            c_right -= c_b;
            m_right -= m_b;
            m_left += m_b;
            c_left += c_b;
            b_left = 1;

        } else if (b_left == 1){ // If boat was on the left.
            c_left -= c_b;
            m_left -= m_b;
            m_right += m_b;
            c_right += c_b;
            b_left = 0;
        }

        // Game over condition
        if (((m_left > 0) && (m_left < c_left)) || ((m_right > 0) && (m_right < c_right))) {
            // Print board again one last time before game ends
            printBoard(b_left, count, m_left, c_left, m_right, c_right);
            std::cout << "Game over! Missionaries eaten!" << std::endl; 
            gameOver = true;

        } else if (m_left == 0 && c_left == 0 && b_left == 0) {
            // Print board again one last time before game ends
            printBoard(b_left, count, m_left, c_left, m_right, c_right);
            std::cout << "Congratulations! You win!" << std::endl;
            gameOver = true;
        }
        count++;
    }
    return 0;
}