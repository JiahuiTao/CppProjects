#include "fractals.h"
#include <cmath>
#define PI 3.14159265

using namespace std;

const int LEAF_COLOR = 0x2e8b57;   /* Color of all leaves of recursive tree (level 1) */
const int BRANCH_COLOR = 0x8b7765; /* Color of all branches of recursive tree (level >=2) */

/**
 * Draws a Sierpinski triangle of the specified size and order, placing its
 * top-left corner at position (x, y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the Sierpinski triangle.
 * @param x - The x coordinate of the top-left corner of the triangle.
 * @param y - The y coordinate of the top-left corner of the triangle.
 * @param size - The length of one side of the triangle.
 * @param order - The order of the fractal.
 */
GPoint pointBetween(GPoint p1, GPoint p2, double fraction) {
    double deltaX = p2.getX() - p1.getX();
    double deltaY = p2.getY() - p1.getY();
    double new_x = p1.getX() + deltaX * fraction;
    double new_y = p1.getY() + deltaY * fraction;
    GPoint p(new_x, new_y);
    return p;
}

void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order) {
    if (order <= 0 || x < 0 || y < 0 || size < 0){
        cout << "Invalid input." << endl;
    }
    if (order == 1){
        GPoint top_l(x,y);
        GPoint top_r(x+size, y);
        GPoint bott(x+0.5*size, y+sqrt(3)*0.5*size);
        gw.drawLine(top_l, top_r);
        gw.drawLine(top_l, bott);
        gw.drawLine(top_r, bott);
    }
    else {
        drawSierpinskiTriangle(gw, x, y, size/2, order - 1);
        drawSierpinskiTriangle(gw, x+0.5*size, y, size/2, order - 1);
        drawSierpinskiTriangle(gw, x+0.25*size, y+sqrt(3)*0.25*size, size/2, order - 1);
    }
}

/**
 * Draws a recursive tree fractal image of the specified size and order,
 * placing the bounding box's top-left corner at position (x,y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the recursive tree.
 * @param x - The x coordinate of the top-left corner of the bounding box.
 * @param y - The y coordinate of the top-left corner of the bounding box.
 * @param size - The length of one side of the bounding box.
 * @param order - The order of the fractal.
 */
void drawBranch(GWindow& gw, double x, double y, double size, double theta, int order) {
    if (order == 0) {return;}
    else {
        if (order == 1) {gw.setColor("#2e8b57");}
        else {gw.setColor("#8b7765");}
        gw.drawPolarLine(x, y, 0.5*size, theta - 45);
        gw.drawPolarLine(x, y, 0.5*size, theta - 30);
        gw.drawPolarLine(x, y, 0.5*size, theta - 15);
        gw.drawPolarLine(x, y, 0.5*size, theta);
        gw.drawPolarLine(x, y, 0.5*size, theta + 15);
        gw.drawPolarLine(x, y, 0.5*size, theta + 30);
        gw.drawPolarLine(x, y, 0.5*size, theta + 45);
        drawBranch(gw, x+0.5*size*cos((theta - 45)*PI/180), y-0.5*size*sin((theta - 45)*PI/180), 0.5*0.5*size, theta-45, order-1);
        drawBranch(gw, x+0.5*size*cos((theta - 30)*PI/180), y-0.5*size*sin((theta - 30)*PI/180), 0.5*0.5*size, theta-30, order-1);
        drawBranch(gw, x+0.5*size*cos((theta - 15)*PI/180), y-0.5*size*sin((theta - 15)*PI/180), 0.5*0.5*size, theta-15, order-1);
        drawBranch(gw, x+0.5*size*cos(theta*PI/180), y-0.5*size*sin(theta*PI/180), 0.5*0.5*size, theta, order-1);
        drawBranch(gw, x+0.5*size*cos((theta + 15)*PI/180), y-0.5*size*sin((theta + 15)*PI/180), 0.5*0.5*size, theta+15, order-1);
        drawBranch(gw, x+0.5*size*cos((theta + 30)*PI/180), y-0.5*size*sin((theta + 30)*PI/180), 0.5*0.5*size, theta+30, order-1);
        drawBranch(gw, x+0.5*size*cos((theta + 45)*PI/180), y-0.5*size*sin((theta + 45)*PI/180), 0.5*0.5*size, theta+45, order-1);
    }
}

void drawTree(GWindow& gw, double x, double y, double size, int order) {
    if (order < 0 || x < 0 || y < 0 || size < 0) {
        cout << "Invalid input: negative input." << endl;
    }
    else if (order == 0) {
        return;
    }
    else {
        gw.drawPolarLine(x+0.5*size, y+size, 0.5*size, 90);
        drawBranch(gw, x+0.5*size, y+0.5*size, 0.5*size, 90, order - 1);
    }
}


/**
 * Draws a Mandelbrot Set in the graphical window give, with maxIterations
 * (size in GUI) and in a given color (zero for palette)
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the Mandelbrot set.
 * @param minX - left-most column of grid
 * @param incX - increment value of columns of grid
 * @param minY - top-most row of grid
 * @param incY - increment value of rows of grid
 * @param maxIterations - The maximum number of iterations to run recursive step
 * @param color - The color of the fractal; zero if palette is to be used
 */
void mandelbrotSet(GWindow& gw, double minX, double incX,
                   double minY, double incY, int maxIterations, int color) {
    Vector<int> palette = setPalette();

    int width = gw.getCanvasWidth();
    int height = gw.getCanvasHeight();
    GBufferedImage image(width,height,0xffffff);
    gw.add(&image);
    Grid<int> pixels = image.toGrid(); // Convert image to grid

    for (int r  = 0; r < pixels.numRows(); r++){
        for (int c = 0; c < pixels.numCols(); c++) {
            Complex coord = Complex(minX + incX * r, minY + incY * c);
            int numIters = mandelbrotSetIterations(coord, maxIterations);
            if (color != 0 && numIters == maxIterations) {pixels[r][c] = color;}
            else if (color == 0) {pixels[r][c] = palette[numIters % palette.size()];}
        }
    }
    image.fromGrid(pixels); // Converts and puts the grid back into the image
}

/**
 * Runs the Mandelbrot Set recursive formula on complex number c a maximum
 * of maxIterations times.
 *
 * This will be called by you. Think about how this fits with the other two functions.
 *
 * @param c - Complex number to use for recursive formula.
 * @param maxIterations - The maximum number of iterations to run recursive step
 * @return number of iterations needed to determine if c is unbounded
 */
int mandelbrotSetIterations(Complex c, int maxIterations) {
    int remainingIterations = mandelbrotSetIterations(Complex(0,0), c, maxIterations);
    return maxIterations - remainingIterations;
}
/**
 * An iteration of the Mandelbrot Set recursive formula with given values z and c, to
 * run for a maximum of maxIterations.
 *
 * This will be called by you. Think about how this fits with the other two functions.
 *
 * @param z - Complex number for a given number of iterations
 * @param c - Complex number to use for recursive formula.
 * @param remainingIterations - The remaining number of iterations to run recursive step
 * @return number of iterations needed to determine if c is unbounded
 */
int mandelbrotSetIterations(Complex z, Complex c, int remainingIterations) {
    if (remainingIterations == 0 || z.abs() > 4) {return remainingIterations;} //remainingIterations > 0, c is unbounded
    else {
        z = z * z + c;
        remainingIterations = mandelbrotSetIterations(z, c, remainingIterations-1);
    }
}

// Helper function to set the palette
Vector<int> setPalette() {
    Vector<int> colors;

    // Feel free to replace with any palette.
    // You can find palettes at:
    // http://www.colourlovers.com/palettes

    // Example palettes:
    // http://www.colourlovers.com/palette/4480793/in_the_middle
    // string colorSt = "#A0B965,#908F84,#BF3C43,#9D8E70,#C9BE91,#A0B965,#908F84,#BF3C43";

    // http://www.colourlovers.com/palette/4480786/Classy_Glass
    // string colorSt = "#9AB0E9,#C47624,#25269A,#B72202,#00002E,#9AB0E9,#C47624,#25269A";

    // The following is the "Hope" palette:
    // http://www.colourlovers.com/palette/524048/Hope
    string colorSt =  "#04182B,#5A8C8C,#F2D99D,#738585,#AB1111,#04182B,#5A8C8C,#F2D99D";
    Vector<string> colorsStrVec = stringSplit(colorSt,",");
    for (string color : colorsStrVec) {
        colors.add(convertColorToRGB(trim(color)));
    }
    return colors;
}
