#include "ui.h"
#include "gui.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    std::string filename = R"(D:\Projects\UBB-Computer-Science\Semester-2\OOP\a14\LocalMovieDatabase_IV\example.txt)";
    Repository repository = Repository(filename);
    Service service = Service(repository);
    GUI* g = new GUI(service, repository);
    g->start();
    return app.exec();
}
