#pragma once
//#include "service.h"
#include "service2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crtdbg.h"

typedef struct
{
    Service* serv;
} UI;

UI* createUI(Service* s);
void destroyUI(UI* ui);

void startUI(UI* ui);

