#include <iostream>
#include <conio.h>  // for _getch()
#include <windows.h>

#include <set>
#include <random>
using namespace std;


class valuessValue{
    int value;
    string color;
};

class GameComponent {
public:
    virtual void display() const = 0;
    virtual bool isValid() const = 0;
    virtual ~GameComponent() {}        
};
class SudokuBoard : public GameComponent {
    protected:
        int** board;
        const int SIZE;
    public:
        SudokuBoard(int size = 9) : SIZE(size){
            board = new int*[SIZE];
            for (int i = 0; i < SIZE; ++i) {
                board[i] = new int[SIZE];
                for (int j = 0; j < SIZE; ++j) {
                    board[i][j] = 0;  //fill ebverything wiht 0s
                }
            }   
        }

        SudokuBoard(const SudokuBoard& other): SIZE(other.SIZE){ // copy constructorr
            board = new int*[SIZE];
            for (int i = 0; i < SIZE; ++i) {
                board[i] = new int[SIZE];
                for (int j = 0; j < SIZE; ++j) {
                    board[i][j] = other.board[i][j];
                }
            }
        }
        virtual ~SudokuBoard() {
            for (int i = 0; i < SIZE; ++i) {
                delete[] board[i];
            }
            delete[] board;
        }
        void setValue(int row, int col, int value){
            board[row][col] = value;
        }
        int getValue(int row, int col) const { //const so it cant change anything on the board
            return board[row][col];
        }
        //not an obstract class anymore
        virtual void display() const override {
            cout << endl;
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    cout << board[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        virtual bool isValid() const override {
            return true;  //return true for now
        }


        SudokuBoard operator+(const SudokuBoard& rhs){
            SudokuBoard result = *this;  // making a copy the current board
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    if (result.getValue(i, j) == 0) {//adding values that are 0
                        result.setValue(i, j, rhs.getValue(i, j));
                    }
                }
            }
            return result;
        }
        
        
        
        friend std::ostream& operator<<(std::ostream& os, const SudokuBoard& sb);
        
};

// }
ostream& operator<<(ostream& os, const SudokuBoard& sb) {
    os << "\n    ";
    for (int col = 0; col < sb.SIZE; ++col) {
        os << col + 1 << " ";
        if ((col + 1) % 3 == 0 && col != sb.SIZE - 1)
            os << "| ";
    }
    os << "\n  ";
    for (int i = 0; i < sb.SIZE + 2; ++i)
        os << "--";
    os << "\n";

    for (int i = 0; i < sb.SIZE; ++i) {
        os << i + 1 << " | ";
        for (int j = 0; j < sb.SIZE; ++j) {
            if (sb.board[i][j] == 0)
                os << ". ";
            else
                os << sb.board[i][j] << " ";

            if ((j + 1) % 3 == 0 && j != sb.SIZE - 1)
                os << "| ";
        }
        os << "\n";

        if ((i + 1) % 3 == 0 && i != sb.SIZE - 1) {
            os << "  ";
            for (int i = 0; i < sb.SIZE + 2; ++i)
                os << "--";
            os << "\n";
        }
    }
    os << endl;
    return os;
}

class SudokuGame : public SudokuBoard {
    private:
        set<int> validNumbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    public:
        SudokuGame(int size) : SudokuBoard(size) {}



        void generateBaseValues(int amount){
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(1, 9);
                for (int i = 0; i<amount; ++i){
                    //generate random coordinate
                    int row = distrib(gen)-1; 
                    int col = distrib(gen)-1;
                    //generate random value
                    int value = distrib(gen);

                    bool horOK = true, vertOk = true, noDoubles = true;
                    
                    if (getValue(row, col) != 0) {
                        i--;
                        continue;
                    }
                    if(getValue(row, col) == 0){//if position not taken
                        //check that the row doesnt have the same number
                        for(int x = 0; x<SIZE; ++x){
                            if(getValue(row, x) == value){
                                horOK = false;
                                break;
                            }
                        }
                        //check that the column doesnt have the same number
                        for(int y = 0; y<SIZE; ++y){
                            if(getValue(y, col) == value){
                                vertOk = false;
                                break;
                            }
                        }

                        //chack that 3x3 square doesnt have same number
                        int littleSquareRow = (row/3)*3;
                        int littleSquareCol = (col/3)*3;
                        //cout << littleSquareRow << " " << littleSquareCol << endl;

                        for(int y = 0; y < 3 && noDoubles; ++y){
                            for (int x = 0; x < 3; ++x){
                                if(getValue(littleSquareRow+y, littleSquareCol+x) == value) {
                                    noDoubles = false;
                                    break;
                                }
                            }
                        }

                        if(horOK && vertOk && noDoubles){
                            setValue(row, col, value);
                        }
                    }
            }
        }

        bool check3x3Square(int startRow, int startCol) const {
            set<int> seen;
            for (int y = 0; y < 3; ++y) {
                for (int x = 0; x < 3; ++x) {
                    int val = getValue(startRow + y, startCol + x);
                    if (val == 0) return false; // empty cell means incomplete
                    if (seen.count(val)) {
                        return false; // duplicate found
                    }
                    seen.insert(val);
                }
            }

            return seen == validNumbers; // make sure it contains all digits 1–9
        }

        

        bool checkComplete() const {
            bool sudokuCompleted = true;

            //check sum   (1+2+3..8+9 = 45  -> 45*9 = 405)  
            int Sum = 0;
            for (int i = 0; i < SIZE; i++){
                for (int j = 0; j < SIZE; j++){
                    Sum += getValue(j, i);
                }
            }  
            if(!(Sum == 405)){
                sudokuCompleted = false;
            }
            //check that each row has an item from set 1-9
            for(int i = 0; i<SIZE; ++i){
                set<int> rowSet;
                for (int j = 0; j < SIZE; ++j) {
                    rowSet.insert(getValue(i, j));
                }
                if (rowSet != validNumbers) {
                    sudokuCompleted = false;
                }           
            }
            for(int i = 0; i<SIZE; ++i){
                set<int> colSet;
                for (int j = 0; j < SIZE; ++j) {
                    colSet.insert(getValue(j, i));
                }
                if (colSet != validNumbers) {
                    sudokuCompleted = false;
                }           
            }
            for (int row = 0; row < 9; row += 3) {
                for (int col = 0; col < 9; col += 3) {
                    if (!check3x3Square(row, col)) {
                        sudokuCompleted = false;
                        break;
                    }
                }
            }
            return sudokuCompleted;
        }   

        //virtual void display() const override;
};





int main(){
    SetConsoleOutputCP(CP_UTF8);
    

    bool loop = true;
    SudokuGame* game = new SudokuGame(9);
    game->generateBaseValues(50);
    cout << *game;
    while (loop) {
        int ch = _getch();

        if (ch == 0 || ch == 224) {
            int key = _getch();  // Actual key code
            system("cls");
            cout << "Press arrow keys, ESC to quit...\n";
            cout << *game;
            switch (key) {
                case 72: cout << "↑\n"; break;
                case 80: cout << "↓\n"; break;
                case 75: cout << "←\n"; break;
                case 77: cout << "→\n"; break;
                default: break;
            }
            
        } else {
            if (ch == 27) { // ESC key
                cout << "Exiting...\n";
                loop = false;
            }
        }
    }
    return 0;     
}      
