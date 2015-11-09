#include <vector>

using namespace std;

void drawLineDDA(int x1, int y1, int x2, int y2,  vector< vector<char> > &space);
void drawLineBresenham(int x1, int y1, int x2, int y2,  vector< vector<char> > &space);
void drawPixel(int x, int y, vector< vector<char> > &space);
void plotSpace(size_t height, size_t width, vector< vector<char> > &space);