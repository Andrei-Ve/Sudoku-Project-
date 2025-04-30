#include <iostream> // Lab2E4
#include <cmath>
using namespace std;
int num;
int main()
{
    while(true){
             cout <<"Enter number to square: ";
cin >> num; // get input from user


 if(num==0){
continue;
}else if(num <0){
break;
}
else{
    cout << sqrt(num)<<"\n";
}
    }




    return 0;
}
