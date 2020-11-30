#pragma once
#include "OfficeDesk.h"

//class interface of "graphAPI": receive data from framelistener and send to OpenGL
class graphAPI
{
public:
    //read data of MVX file and save to public variables
    void readMvx(OfficeDesk* InputDesk);

    //send data to OpenGL and paint
    void paint(OfficeDesk* target, float* vertex, unsigned char* color, float* normal, int vertex_count, int color_count, int normal_count);

public:
    float* m_vertex = nullptr;                  // vertex pos buffer
    unsigned char* m_color = nullptr;           // vertex color buffer
    float* m_normal = nullptr;                  // vertex normal buffer

    int m_vertex_count = 0;
    int m_color_count = 0;
    int m_normal_count = 0;
};



