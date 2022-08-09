#include "main.h"

int main()
{
    test_all();
    Repository* repository = createRepo();
    Service* service = createService(repository);
    populateRepo(service);
    UI* ui = createUI(service);
    startUI(ui);
    destroyUI(ui);

    _CrtDumpMemoryLeaks();
    return 0;
}
