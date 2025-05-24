#include <iostream>
#include <fstream>
#include <array>
#include <set>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>
using namespace std;

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
        SudokuBoard(int size = 9);
        SudokuBoard(const SudokuBoard& other); // Copy constructor
        virtual ~SudokuBoard();
    
        void setValue(int row, int col, int value);
        int getValue(int row, int col) const;
    
        virtual void display() const override;
        virtual bool isValid() const override;
    
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
            