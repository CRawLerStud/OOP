#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "AgentieGUI.h"
#include "MainTests.h"

int main(int argc, char *argv[])
{
    testAll();
    QApplication a(argc, argv);
    RepositorryFile repo{ "oferte.csv" };
    Validator validator;
    Repositorry wishlist;
    Service service(repo, validator, wishlist);

    AgentieGUI w{ service };

    w.showMaximized();
    return a.exec();
}
