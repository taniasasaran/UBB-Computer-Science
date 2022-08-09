#include "ui.h"
#include "gui.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    std::string filename = R"(C:\Users\TANIA\CLionProjects\GitHub\a14-taniasasaran\example.txt)";
    Repository repository = Repository(filename);
    Service service = Service(repository);
    GUI* g = new GUI(service, repository);
    g->start();
    return app.exec();
}
