#pragma once
#include <vector>
#include "Cancion.h"

using namespace System;
using namespace System::Collections::Generic;

public ref class Album
{

public:
    String^ nombre;
    List<Cancion^>^ canciones;

};

