#include "ui.h"
#include "crtdbg.h"
#include "tests.h"

int main()
{
    Repository* repository  = createRepo();
    Service* service = createService(repository);
    populateRepo(service);
    UI* ui = createUI(service);
    test_all();

    startUI(ui);
    destroyUI(ui);

    _CrtDumpMemoryLeaks();
    return 0;
}

