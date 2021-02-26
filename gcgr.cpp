#include <bits/stdc++.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;

using namespace std;

HANDLE hOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
HWND myconsole = GetConsoleWindow();
HDC dc = GetDC(myconsole);
DWORD dwWritten;

class Point
{
public:
    int x;
    int y;
    int r,g,b;
};

int XSIZE = 1800; // x window size
int YSIZE = 1800; // y window size

int XOFF = 1000; // x offset (for window positioning)
int YOFF = 100; // y offset (for window positioning)

int K = 1;
int R = 2;

void plot (Point start)
{
    SetPixel(dc,start.x+XOFF,start.y+YOFF,RGB(start.r,start.g,start.b));
}

Point findPosition(string s, Point start, Point cornerA, Point cornerC, Point cornerG, Point cornerT)
{
    Point tempCorner;

    switch (s[0])
    {
        case 'A':
            // blue
            tempCorner.x = cornerA.x;
            tempCorner.y = cornerA.y;
            if (K==1){start.b = 255;}
            break;
        case 'C':
            // orange
            tempCorner.x = cornerC.x;
            tempCorner.y = cornerC.y;
             if (K==1){start.r = 255;start.g = 145;}
            break;
        case 'G':
            // red
            tempCorner.x = cornerG.x;
            tempCorner.y = cornerG.y;
            if (K==1){start.r = 255;}
            break;
        case 'T':
            // green
            tempCorner.x = cornerT.x;
            tempCorner.y = cornerT.y;
            if (K==1){start.g = 255;}
            break;
        default:
            break;
    }

    for (int i = 1; i < s.length(); i++)
    {
        switch (s[i])
        {
            case 'A':
                tempCorner.x = (tempCorner.x + cornerA.x)/R;
                tempCorner.y = (tempCorner.y + cornerA.y)/R;
                start.b = 255;
                break;
            case 'C':
                tempCorner.x = (tempCorner.x + cornerC.x)/R;
                tempCorner.y = (tempCorner.y + cornerC.y)/R;
                start.r = 255;
                start.g = 145;
                break;
            case 'G':
                tempCorner.x = (tempCorner.x + cornerG.x)/R;
                tempCorner.y = (tempCorner.y + cornerG.y)/R;
                start.r = 255;
                break;
            case 'T':
                tempCorner.x = (tempCorner.x + cornerT.x)/R;
                tempCorner.y = (tempCorner.y + cornerT.y)/R;
                start.g = 255;
                break;
            default:
                break;
        }


    }
    start.x = (tempCorner.x + start.x)/R;
    start.y = (tempCorner.y + start.y)/R;

    return start;
}

int main()
{
    string line;
    ifstream file (""); // .fasta file goes here

    string s = "";

    // default corner positions

    Point cornerA;
    cornerA.x = 0;
    cornerA.y = YSIZE;

    Point cornerC;
    cornerC.x = 0;
    cornerC.y = 0;

    Point cornerG;
    cornerG.x = XSIZE;
    cornerG.y = 0;

    Point cornerT;
    cornerT.x = XSIZE;
    cornerT.y = YSIZE;

    Point start = Point();
    start.x = XSIZE/2;
    start.y = YSIZE/2;

    if (file.is_open())
    {
    while (getline(file,line))
    {
        for (int i = 0; i < line.length(); i+=K)
        {
            s = line.substr(i, K);
            transform(s.begin(), s.end(), s.begin(), ::toupper); // ensuring substring is uppercase

            // reset colors
            start.r = 0;
            start.g = 0;
            start.b = 0;
            
            start = findPosition(s, start, cornerA, cornerC, cornerG, cornerT);
            plot(start);
        }
    }
    file.close();
    } else
    {
        cout << "error finding file.";
    }
}
