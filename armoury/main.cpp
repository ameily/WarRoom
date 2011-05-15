

#include "forms/ArmouryWindow.h"
#include <QApplication>
#include <QDesktopServices>
#include <QDir>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("Armoury");
    ArmouryWindow window;
    
    QString docs = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation);
    QDir dir(docs);
    QString warDir = "War Library";
    if(dir.exists(warDir))
        dir.cd(warDir);
    
    window.setPwd(dir.absolutePath());
    
    window.show();
    return app.exec();
}
