#pragma once
#include <cliext/set>

using namespace cliext;
using namespace System;

public ref class Cancion
{

public:
    String^ nombre;
    String^ cantante;
    String^ duracion;

    static bool CompareCancion(Album a, Album b)
    {
        return a.nombre->CompareTo(b.nombre) < 0;
    }
};
