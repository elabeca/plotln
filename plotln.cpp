#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <regex>
#include <algorithm>
#include "plotln.h"

using namespace std;

const string seperator = "-------------------";

int main(int argc, char** argv) {

    size_t height = 10, width = 20;

    string input = "";
    cout << "Please enter your lines coordinates (i.e. (x,y) – (x,y), (x,y) – (x,y), ...)" << endl;
    cout << "whilst ensuring not to exceed the following boundaries:  x = [1 to 19] and y = [1 to 9]:" << endl;
    getline(cin, input);

    // Regex pattern matching on line coordinates irrespective of space or tabs
    regex line_regex("(\\s*\\(\\s*[0-1]?[0-9]\\s*\\,\\s*[0-9]\\s*\\))\\s*-\\s*(\\s*\\(\\s*[0-1]?\\s*[0-9]\\s*\\,\\s*[0-9]\\s*\\))+");
    auto p_begin = sregex_iterator(input.begin(), input.end(), line_regex);
    auto p_end = sregex_iterator();

    int match_count = distance(p_begin, p_end);
    if (match_count == 0) {
        cout << "Oops! seems you're missing at least one line coordinates!" << endl;
        cout << "Please try again with the following format: (3,4)-(9,19),etc." << endl;
        cout << "whilst ensuring not to exceed the following boundaries:  x = [0 to 19] and y = [0 to 9]" << endl;
        exit(-1);
    }

    string *coordinates = new string[match_count];

    int i = 0;
    for (sregex_iterator it_p = p_begin; it_p != p_end; ++it_p, i++) {
        smatch match = *it_p;
        string found = match.str();
        coordinates[i] = found;
    }

    vector< vector<char> > space1(height, vector<char>(width));
    vector< vector<char> > space2(height, vector<char>(width));

    regex digits("(\\d+)");
    for (int c = 0; c < i; c++) {
        string str = coordinates[c];
        auto d_begin = sregex_iterator(str.begin(), str.end(), digits);
        auto d_end = sregex_iterator();

        sregex_iterator it_d = d_begin;
        smatch match_x1 = *it_d;
        int x1 = stoi(match_x1.str());
        
        ++it_d;
        smatch match_y1 = *it_d;
        int y1 = stoi(match_y1.str());
        
        ++it_d;
        smatch match_x2 = *it_d;
        int x2 = stoi(match_x2.str());
        
        ++it_d;
        smatch match_y2 = *it_d;
        int y2 = stoi(match_y2.str());

        drawLineBresenham(x1, y1, x2, y2, space1);
        drawLineDDA(x1, y1, x2, y2, space2);
    }

    cout << endl << seperator << endl << "Bresenham:" << endl << endl; 
    plotSpace(height, width, space1);

    cout << endl << seperator << endl << "Digital Differential Analyser:" << endl << endl; 
    plotSpace(height, width, space2);
    
    cout << seperator << endl << endl; 
}

void drawPixel(int x, int y, vector< vector<char> > &space) {
    space[y][x] = 'X';
}

void plotSpace(size_t height, size_t width, vector< vector<char> > &space) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cout << ((space[y][x] == 0) ? ' ' : 'X');
        }
        cout << endl;
    }
}

void drawLineDDA(int x1, int y1, int x2, int y2,  vector< vector<char> > &space) {
    int dx = (x2 - x1);
    int dy = (y2 - y1);
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    double x_inc = (dx * 1.0 / steps);
    double y_inc = (dy * 1.0 / steps);
 
    double x = x1, y = y1;
    for (int i = 0; i <= steps; i++) {
        drawPixel(x, y, space);
        y += y_inc;
        x += x_inc;
    }
}

void drawLineBresenham(int x1, int y1, int x2, int y2,  vector< vector<char> > &space) {
    bool steep = (abs(y2 - y1) > abs(x2 - x1));
    if (steep) {
        swap(x1, y1);
        swap(x2, y2);
    }

    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = abs(y2 - y1);

    float error = dx / 2.0f;
    int ystep = (y1 < y2) ? 1 : -1;
    int y = y1;

    for (int x = x1; x < x2; x++)
    {
        if (steep) {
            drawPixel(y, x, space); 
        } else {
            drawPixel(x, y, space); 
        }

        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}