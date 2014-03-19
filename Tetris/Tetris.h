#ifndef Marzo_19_Tetris_h
#define Marzo_19_Tetris_h

#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y, z;
    Point(int x, int y, int z) : x(x), y(y), z(z) { }
};

struct Color {
    float R, G, B, A;
    Color(float R, float G, float B, float A) : R(R), G(G), B(B), A(A) { }
    Color() : R(1), G(1), B(1), A(1) { }
};

class Cuadrito {
private:
    Color color;
public:
    Cuadrito(Color color) : color(color) { }
    Cuadrito() { }
    void dibuja(float width) {
        glColor4f(color.R, color.G, color.B, color.A);
        glTranslatef(width / 2, width / 2, width / 2);
        glutSolidCube(width);
    }
};

class Pieza {
public:
    vector<Cuadrito> cuadritos;
    vector<Point> posiciones;
    void mover(int x, int y, int z) {
        for(int i = 0; i < posiciones.size(); i++) {
            posiciones[i].x += x;
            posiciones[i].y += y;
            posiciones[i].z += z;
        }
    }
    void rotateCW(bool x, bool y, bool z)
    {
        //TODO
    }
    void rotateCCW(bool x, bool y, bool z)
    {
        //TODO
    }
};

#define MAX_LENGTH 25

class Tetris {
private:
    Cuadrito matriz[MAX_LENGTH][MAX_LENGTH][MAX_LENGTH];
    bool ocupado[MAX_LENGTH][MAX_LENGTH][MAX_LENGTH];
    int width, height, depth;
    float unitWidth;
public:
    Tetris(int width, int height, int depth, float unitWidth) : width(width), height(height), depth(depth), unitWidth(unitWidth)
    {
        for(int x = 0; x < width; x++)
            for(int y = 0; y < height; y++)
                for(int z = 0; z < depth; z++)
                    ocupado[x][y][z] = false;
    }
    bool estaOcupado(Pieza &pieza) {
        for(int i = 0; i < pieza.posiciones.size(); i++)
            if(ocupado[pieza.posiciones[i].x][pieza.posiciones[i].y][pieza.posiciones[i].z])
                return true;
        return false;
    }
    void insertar(Pieza &pieza) {
        for(int i = 0; i < pieza.cuadritos.size(); i++) {
            matriz[pieza.posiciones[i].x][pieza.posiciones[i].y][pieza.posiciones[i].z] = pieza.cuadritos[i];
            ocupado[pieza.posiciones[i].x][pieza.posiciones[i].y][pieza.posiciones[i].z] = true;
        }
    }
    void quitar(Pieza &pieza) {
        for(int i = 0; i < pieza.posiciones.size(); i++)
            ocupado[pieza.posiciones[i].x][pieza.posiciones[i].y][pieza.posiciones[i].z] = false;
    }
    bool nivelCompleto(int nivel) {
        for(int x = 0; x < width; x++)
            for(int z = 0; z < depth; z++)
                if(!ocupado[x][nivel][z])
                    return false;
        return true;
    }
    void checarCompletos() {
        for(int i = 0; i < height; i++) {
            if(nivelCompleto(i)) {
                for(int j = i; j < height; j++) {
                    for(int x = 0; x < width; x++) {
                        for(int z = 0; z < depth; z++) {
                            if(j != height) {
                                matriz[x][j][z] = matriz[x][j+1][z];
                                ocupado[x][j][z] = ocupado[x][j+1][z];
                            } else {
                                matriz[x][j][z] = Cuadrito();
                                ocupado[x][j][z] = false;
                            }
                        }
                    }
                }
            }
            i--;
        }
    }
    void dibuja() {
        glColor3f(1, 1, 1);
        glutWireCube(unitWidth * width);
        glPushMatrix();
        glTranslatef(-unitWidth * width / 2, -unitWidth * width / 2, -unitWidth * width / 2);
        for(int x = 0; x < width; x++)
            for(int y = 0; y < height; y++)
                for(int z = 0; z < depth; z++)
                    if(ocupado[x][y][z]) {
                        glPushMatrix();
                        glTranslatef(x * unitWidth, y * unitWidth, z * unitWidth);
                        matriz[x][y][z].dibuja(unitWidth);
                        glPopMatrix();
                    }
        glPopMatrix();
    }
};

#endif