#include "ui.h"
//#include "crtdbg.h"

int main()
{
    Repository* repository  = createRepo();
    Service* service = createService(repository);
    populateRepo(service);
    UI* ui = createUI(service);

    startUI(ui);
    destroyUI(ui);

//    _CrtDumpMemoryLeaks();
    return 0;
}

