#include <iostream>
using namespace std;

double _my_cube(double x){
return x*x*x;
}

int main()
{
    int i, ctr, cub;

    cout << "\n\n Display the cube of the number:\n";
    //cout << "----------------------------------------------------------\n";
    //cout << "Input the number of terms : ";
    cin >> i;
    //for (i = 1; i <= ctr; i++) 
    //{
        cub=_my_cube(i);
        cout << "Number is : " << i << " and the cube of " << i << " is: " << cub << endl;
    //}
}

