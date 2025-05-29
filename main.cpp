#include <iostream>
#include <conio.h>  // for _getch()
#include <windows.h>
#include "global_cursor.h"
#include <set>
#include <random>
using namespace std;
Cursor globalCursor = Cursor();
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
        SudokuBoard operator+(const SudokuBoard& rhs) const;
    };
    class SudokuGame : public SudokuBoard {
        private:
            set<int> validNumbers;
            int attempts;
            string difficulty;
        public:
            SudokuGame(int size = 9, string level = "easy");
        
            void start();
            void play();
            void saveGame(const string& filename) const;
            void loadGame(const string& filename);
            void giveHint();
            bool checkComplete() const;
        
            virtual void display() const override;
        };
            