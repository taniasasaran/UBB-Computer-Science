#include "ui.h"
#include "teste.h"

int main()
{
    auto ui = UI();
    ui.startUI();
    Tests tests;
    tests.TestAll();
}
