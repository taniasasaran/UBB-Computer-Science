#include "ui.h"

int main()
{
    std::string filename = R"(D:\Projects\UBB-Computer-Science\Semester-2\OOP\a8-9\DoggoShelter_II\example.txt)";
    Repository repository = Repository(filename);
    Service service = Service(repository);
    UI ui = UI(service);
    ui.startUI();
}