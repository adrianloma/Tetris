//
//  Elementos.h
//  Tetris
//
//
//  Copyright (c) 2014 Adrian Lozano & Alfredo Altamirano. All rights reserved.
//

#ifndef Tetris_Elementos_h
#define Tetris_Elementos_h

struct Point {
    int x, y, z;
};

struct Color {
    float R, G, B, A;
};

//contiene la info del cuadrito
struct Cuadrito {
    Color color;
};

//contiene una lista de puntos y la info de cada cuadrito
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
};

class Tetris {
private:
    Cuadrito matriz[10][20][10];
    bool ocupado[10][20][10];
public:
    bool estaOcupado(Pieza &pieza) {
        for(int i = 0; i < pieza.posiciones.size(); i++)
            if(ocupado[pieza.posiciones[i].x][pieza.posiciones[i].y][pieza.posiciones[i].z])
                return true;
        return false;
    }
    void insertar(Pieza &pieza) {
        for(int i = 0; i < pieza.cuadritos.size(); i++)
            matriz[pieza.posiciones[i].x][pieza.posiciones[i].y][pieza.posiciones[i].z] = pieza.cuadritos[i];
    }
    void quitar(Pieza &pieza) {
        for(int i = 0; i < pieza.posiciones.size(); i++)
            ocupado[pieza.posiciones[i].x][pieza.posiciones[i].y][pieza.posiciones[i].z] = false;
    }
    bool nivelCompleto(int nivel) {
        for(int x = 0; x < 10; x++)
            for(int z = 0; z < 10; z++)
                if(!ocupado[x][nivel][z])
                    return false;
        return true;
    }
    void checarCompletos() {
        for(int i = 0; i < 20; i++) {
            if(nivelCompleto(i)) {
                //TODO mover todo lo que este arriba de i un nivel abajo
            }
            i--;
        }
    }
};

#endif
