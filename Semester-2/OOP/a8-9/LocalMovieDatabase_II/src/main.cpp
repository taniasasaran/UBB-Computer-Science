//
// Created by TANIA on 3/19/2022.
//

#include "ui.h"

int main()
{
    std::string filename = R"(C:\Users\TANIA\CLionProjects\GitHub\a8-9-taniasasaran\example.txt)";
    Repository repository = Repository(filename);
    Service service = Service(repository);
    UI ui = UI(service);
    ui.startUI();
}
