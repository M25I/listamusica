#pragma once
#include <cliext/set>
#include <vector>
#include "Cancion.h"

using namespace cliext;
using namespace System;
using namespace System::Collections;

public ref class Album
{

public:
    String^ nombre;
    set<Cancion>^ canciones;

    static bool CompareAlbums(Album a, Album b)
    {
        return a.nombre->CompareTo(b.nombre) < 0;
    }
};

