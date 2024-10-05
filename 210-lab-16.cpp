#include <iostream>
#include <iomanip>
using namespace std;

const int W15 = 15;

//color object
class Color {
    private:
        int red;
        int green;
        int blue;

//creating print function
public:
    Color() : red(0), green(0), blue(0) {}
    Color(int r, int g, int b) : red(r), green(g), blue(b) {}
    
    // getters and setters with check for bounds on color parameters
    void setRed(int r)              { if(r >= 0 && r <= 225) red = r; else red = 0;}
    void setGreen (int g)           {if(g >= 0 && g <= 225) green = g; else green = 0;}
    void setBlue (int b)            {if(b >= 0 && b <= 225) blue = b; else blue = 0;}
    int getRed()                    {return red;}
    int getGreen()                  {return green;}
    int getBlue()                   {return blue;}
    void print() {
        cout << setw(W15) << "Red: " << red << endl;
        cout << setw(W15) << "Green: " << green << endl;
        cout << setw(W15) << "Blue: " << blue << endl;
        cout << setw(W15) << "Color(" << red << ", " << green << ", " << blue << ")\n";
    }
};

//displaying print function
int main(){
    Color color1(255, 0, 0);
    Color color2;
    color2.setRed(128);
    color2.setGreen(3);
    color2.setBlue(250);
    Color color3;
    color3.setRed(300); //invalid value to check if statement (should be 0)
    color3.setGreen(-10); //invalid value to check if statement (should be 0)
    color3.setBlue(120);
    color1.print();
    color2.print();
    color3.print();
    return 0;
}