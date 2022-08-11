#include "ui.h"
#include "teste.h"

int main()
{
    Tests tests;
    tests.TestAll();
    auto ui = UI();
    ui.startUI();
}
