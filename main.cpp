#include <iostream>
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

// std::ostream& operator<<(std::ostream& os, const SudokuBoard& c){
//     os << c.real << " + " << c.imag << "i" << std::endl;
//     return os;
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

                    bool horOK = false, vertOk = false, noDoubles = false;
                    
                    if(validNumbers.count(getValue(row, col)) > 0){
                        i--;
                        continue;
                    }
                    if(getValue(row, col) == 0){//if position not taken
                        //check that the row doesnt have the same number
                        for(int x = 0; x<SIZE; ++x){
                            if(getValue(row, x) == value){
                              break;
                            }
                            if(x == SIZE-1){
                                horOK = true;
                            }
                        }
                        //check that the column doesnt have the same number
                        for(int y = 0; y<SIZE; ++y){
                            if(getValue(y, col) == value){
                              break;
                            }
                            if(y == SIZE-1){
                                vertOk = true;
                            }
                        }

                        //chack that 3x3 square doesnt have same number
                        int littleSquareRow = row/3;
                        int littleSquareCol = col/3;
                        //cout << littleSquareRow << " " << littleSquareCol << endl;
                        for(int y = 0; y < 3; ++y){
                            for (int x = 0; x < 3; ++x){
                                if(getValue(y, x) == value) {
                                    noDoubles = false;
                                    break;
                                }
                                else if(validNumbers.count(getValue(row, col)) > 0){
                                }
                            }
                            
                        }
                        
                        if(horOK & vertOk & noDoubles){
                            setValue(row, col, value);
                        }
                    }
            }
        }

        //bool checkComplete() const;
        //virtual void display() const override;
};





int main(){

    bool loop = true;
    while(loop){
        int a;
        cout << "\nEnter 1 to start sudoku game, 2 to exit the program: ";
        cin >> a;
        if(a == 1){
            cout << "good choice\n";
            SudokuGame* game = new SudokuGame(9);
            cout << "Initial empty board:\n";
            cout << *game;
            game->display();
            cout << "After generating base values:\n";
            cout << *game;
            delete game;
        }
        else if(a == 2){
            cout << "EXITING";
            loop = false;
        }
        else{
            cout << "EXITING";
            loop = false;
        }
    }

    return 0;
}
            