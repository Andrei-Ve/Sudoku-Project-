#include <iostream>
#include <set>

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
        SudokuBoard(int size = 9) : SIZE(size){};
        SudokuBoard(const SudokuBoard& other); // Copy constructor
        virtual ~SudokuBoard();
    
        void setValue(int row, int col, int value);
        int getValue(int row, int col) const;

        virtual void display() const override;
        virtual bool isValid() const override;

        friend std::ostream& operator<<(std::ostream& os, const SudokuBoard& sb);
        SudokuBoard operator+(const SudokuBoard& rhs) const;
    };

// std::ostream& operator<<(std::ostream& os, const SudokuBoard& c){
//     os << c.real << " + " << c.imag << "i" << std::endl;
//     return os;
// }

class SudokuGame : public SudokuBoard {
    private:
        set<int> validNumbers;
    public:
        SudokuGame(int size = 9);

        void start();
        void play();
        bool checkComplete() const;
        virtual void display() const override;
        
    };

/*
#include <random>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(1, 9);
int random_number = distrib(gen);
std::cout << "Random number between 1 and 9: " << random_number << std::endl;
*/

int main(){

    bool loop = true;
    while(loop){
        int a;
        cout << "\nEnter 1 to start sudoku game, 2 to exit the program: ";
        cin >> a;
        if(a == 1){
            cout << "good choice";
            GameComponent* game = new SudokuGame();
            game->display();

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
            