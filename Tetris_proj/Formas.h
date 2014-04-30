#ifndef Tetris_proj_Formas_h
#define Tetris_proj_Formas_h

#define TETRIS_SHAPE_FREDDY     0
#define TETRIS_SHAPE_L          1
#define TETRIS_SHAPE_T          2
#define TETRIS_SHAPE_SQUARE     3
#define TETRIS_SHAPE_STICK      4
#define TETRIS_SHAPE_MINISQUARE 5
#define TETRIS_SHAPE_HUGESQUARE 6



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
    Pieza(){}
    Pieza(int shape, int height, int width, int depth)
    {
        switch (shape) {
            case TETRIS_SHAPE_FREDDY:
                posiciones.push_back(Point(width/2, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 0, 1, 1)));
                posiciones.push_back(Point(width/2-1, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 1, 0, 1)));
                posiciones.push_back(Point(width/2+1, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(0, 1, 1, 1)));
                posiciones.push_back(Point(width/2, height, depth/2-1));
                cuadritos.push_back(Cuadrito(Color(0, 0, 1, 1)));
                posiciones.push_back(Point(width/2, height, depth/2+1));
                cuadritos.push_back(Cuadrito(Color(0, 1, 0, 1)));
                posiciones.push_back(Point(width/2, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 0, 1, 1)));
                break;
                
            case TETRIS_SHAPE_L:
                posiciones.push_back(Point(width/2, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 0, 1, 1)));
                posiciones.push_back(Point(width/2-1, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 1, 0, 1)));
                posiciones.push_back(Point(width/2+1, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 1, 0, 1)));
                posiciones.push_back(Point(width/2+1, height, depth/2+1));
                cuadritos.push_back(Cuadrito(Color(0, 0, 1, 1)));
                break;
                
            case TETRIS_SHAPE_T:
                posiciones.push_back(Point(width/2, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 0, 1, 1)));
                posiciones.push_back(Point(width/2-1, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 1, 0, 1)));
                posiciones.push_back(Point(width/2+1, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 1, 0, 1)));
                posiciones.push_back(Point(width/2, height, depth/2+1));
                cuadritos.push_back(Cuadrito(Color(0, 1, 0, 1)));
                break;
            
            //case TETRIS_SHAPE_STICK:
            case TETRIS_SHAPE_SQUARE:
                posiciones.push_back(Point(width/2, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 0, 1, 1)));
                posiciones.push_back(Point(width/2-1, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 1, 0, 1)));
                posiciones.push_back(Point(width/2-1, height, depth/2+1));
                cuadritos.push_back(Cuadrito(Color(1, 1, 0, 1)));
                posiciones.push_back(Point(width/2, height, depth/2+1));
                cuadritos.push_back(Cuadrito(Color(0, 1, 1, 1)));
                break;
                
            case TETRIS_SHAPE_STICK:
                posiciones.push_back(Point(width/2-1, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 1, 0, 1)));
                posiciones.push_back(Point(width/2, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 0, 1, 1)));
                posiciones.push_back(Point(width/2-2, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 1, 0, 1)));
                if (depth > 5)
                {
                    posiciones.push_back(Point(width/2-3, height, depth/2));
                    cuadritos.push_back(Cuadrito(Color(1, 1, 1 , 1)));
                }
                break;
                
            case TETRIS_SHAPE_MINISQUARE:
                posiciones.push_back(Point(width/2, height, depth/2));
                cuadritos.push_back(Cuadrito(Color(1, 1 , 1, 1)));
                break;
                

                
            default:
                break;
        }

        
        

    }
    void mover(int x, int y, int z) {
        for(int i = 0; i < posiciones.size(); i++) {
            posiciones[i].x += x;
            posiciones[i].y += y;
            posiciones[i].z += z;
        }
    }
    void rotateCW()
    {
        int offset_x=posiciones[0].x;
        int offset_z=posiciones[0].z;
        
        for (int i=1; i < posiciones.size() ; i++) {
            int tempx= posiciones[i].x - offset_x;
            int tempz= posiciones[i].z - offset_z;
            
            posiciones[i].x= tempz + offset_x;
            posiciones[i].z= tempx*-1 + offset_z;
        }
        
    }
    void rotateCCW()
    {
        int offset_x=posiciones[0].x;
        int offset_z=posiciones[0].z;
        
        for (int i=1; i < posiciones.size() ; i++) {
            int tempx= posiciones[i].x - offset_x;
            int tempz= posiciones[i].z - offset_z;
            
            posiciones[i].x= tempz*-1 + offset_x;
            posiciones[i].z= tempx + offset_z;
        }
    }
    
    void barrelCW()
    {
        int offset_x=posiciones[0].x;
        int offset_y=posiciones[0].y;
        
        for (int i=1; i < posiciones.size() ; i++) {
            int tempx= posiciones[i].x - offset_x;
            int tempy= posiciones[i].y - offset_y;
            
            posiciones[i].x= tempy + offset_x;
            posiciones[i].y= tempx*-1 + offset_y;
        }
        
    }
    
    void barrelCCW()
    {
        int offset_x=posiciones[0].x;
        int offset_y=posiciones[0].y;
        
        for (int i=1; i < posiciones.size() ; i++) {
            int tempx= posiciones[i].x - offset_x;
            int tempy= posiciones[i].y - offset_y;
            
            posiciones[i].x= tempy*-1 + offset_x;
            posiciones[i].y= tempx + offset_y;
        }
        
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
    
    int getHeight(){ return height;}
    int getWidth() { return width; }
    int getDepth() { return depth; }
    int getUnitWidth() {return unitWidth;}
    
    bool estaOcupado(Pieza &pieza) {
        for(int i = 0; i < pieza.posiciones.size(); i++){

            if (pieza.posiciones[i].x < 0       ||
                pieza.posiciones[i].x >= width   ||
                pieza.posiciones[i].y < 0        ||
                pieza.posiciones[i].y >= height  ||
                pieza.posiciones[i].z < 0       ||
                pieza.posiciones[i].z >= depth ) {
                return true;
            }
            if(ocupado[pieza.posiciones[i].x][pieza.posiciones[i].y][pieza.posiciones[i].z])
                return true;
        }
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
        for(int x = 0; x < width; x++){
            for(int z = 0; z < depth; z++){
                if(!ocupado[x][nivel][z]){
                    return false;
                }
            }
        }
        
        return true;
    }
    
    int checarCompletos() {
        int ret = 0;
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
                ret++;
                i--;
            }
            
        }
        return ret;
    }
    void dibuja() {
        glColor3f(0, 0, 0);
        
        glPushMatrix();
        GLfloat ambient1[ ] = {0.2, 0.2, 0.2, 1.0};
        GLfloat diffuse1[ ] = {0.3, 0.3, 0.3,  1.0  };
        GLfloat specular1[ ] = {0.5, 0.5, 0.5, 1.0};
        
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
        
        glPushMatrix();
        glScaled(1, ((double) height)/ ((double) width), 1);
        glutWireCube(unitWidth * width);
        glPopMatrix();
        

        
        glPushMatrix();
        glTranslatef(0, -height/8, 0);
        glScaled(1, unitWidth/4, 1);
        glutSolidCube(unitWidth * width);
        glPopMatrix();
        

//
//        GLfloat shine = 100.0;
//        
//        

//
//        glMaterialf(GL_FRONT, GL_SHININESS, shine);
        
        
        
        GLfloat specular[ ] = {0.2, 0.2, 0.2, 1.0};
        GLfloat shine = 10.0;
        
        glTranslatef(-unitWidth * width / 2, -unitWidth * height / 2, -unitWidth * depth / 2);
        //////
        glPushMatrix();
        
        //glTranslatef(unitWidth / 2, unitWidth / 2, unitWidth / 2);
//        GLfloat globalAmbient[ ] = { 0.4, 0.0, 0.0, 1.0 };
//        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
        
        GLfloat light1_ambient[] = {0.8, 0.8, 0.8, 1.0}; /* soft white */
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
        glPushMatrix();
        glTranslatef(-.6, 10.0, .1);
        GLfloat light2_ambient[] = {1.0,1.0,1.0, 1.0}; /*  white */
        glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
        glPopMatrix();
        
        GLfloat lmodel_ambient[] ={0.2, 0.2, 0.2, 1.0};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
        GLfloat local_view[] ={0.0};
        glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
        
        
        GLfloat position[] = {
            static_cast<GLfloat>(width*unitWidth/2),
            static_cast<GLfloat>(getHeight()*unitWidth+unitWidth),
            static_cast<GLfloat>(depth*unitWidth/2), 1.0};

        GLfloat lightIntensity[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glLightfv(GL_LIGHT0, GL_DIFFUSE,lightIntensity);
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        GLfloat direction[ ] = {(GLfloat)(getWidth()*getUnitWidth()/2.0),
            0.0,
            (GLfloat)(getWidth()*getUnitWidth()/2.0)};
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
        GLfloat thetaLight = 45.0;
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, thetaLight);
        glPopMatrix();
        ////////////
        for(int x = 0; x < width; x++)
            for(int y = 0; y < height; y++)
                for(int z = 0; z < depth; z++)
                    if(ocupado[x][y][z]) {
                        glPushMatrix();
                        glTranslatef(x * unitWidth, y * unitWidth, z * unitWidth);
                        
                        GLfloat diffuse[ ] = {1.0f / height * y,
                                            1.0f / height * x,
                                            1.0f / height * y,
                                            1.0  };
//                        GLfloat specular[ ] = {1.0f / height * y /2 ,
//                                            1.0f / height * x /2,
//                                            1.0f / height * y /2,
//                                            1.0};
                        GLfloat ambient[ ] = {1.0f / height * y /2 ,
                                            1.0f / height * x /2,
                                            1.0f / height * y /2,
                                            1.0};
                        
                        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
                        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
                        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
                        
                        glMaterialf(GL_FRONT, GL_SHININESS, shine);

                        //glColor3f(.5, .5, .5);
                        glTranslatef(unitWidth / 2, unitWidth / 2, unitWidth / 2);
                        //glNormal3f(1,1,1);
                        glutSolidCube(unitWidth);
                        //matriz[x][y][z].dibuja(unitWidth);
                        glPopMatrix();
                    }
        glPopMatrix();
    }
    
};












#endif

