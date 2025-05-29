#pragma once
class Cursor{
    private:
        int x = 4;
        int y = 4;
    public:
        Cursor(){}
        int getX() const {return x;}

        int getY() const {return y;}

        void moveLeft(){
            if(x > 0){
                x--;
            }
        }
        void moveRight(){
            if(x < 8){
                x++;
            }
        }
        void moveUp(){
            if(y > 0){
                y--;
            }
        }
        void moveDown(){
            if(y < 8){
                y++;
            }
        }
};