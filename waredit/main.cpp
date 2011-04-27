/*
    This file is part of the War Edit application (waredit)
    Url: https://github.com/ameily/WarRoom
    Copyright (C) 2011  Adam Meily <meily.adam@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "forms/WarEditWindow.h"
#include <QMainWindow>
#include <QApplication>
#include <QDesktopServices>
#include <QMessageBox>
#include <TextFormatter.h>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("War Edit");
    WarEditWindow window;
    
    QString docs = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation);
    QDir dir(docs);
    QString warDir = "War Library";
    if(!dir.exists(warDir))
    {
        int status = QMessageBox::question(&window, "Create Directory?",
            "This directory " + dir.filePath(warDir) +
            " does not exist. Create the directory?",
            QMessageBox::No | QMessageBox::Yes, QMessageBox::No);
        
        if(status == QMessageBox::Yes)
        {
            if(!dir.mkdir(warDir))
            {
                QMessageBox::information(&window, "Error",
                    "Could not create the directory " + dir.filePath(warDir) +
                    ".");
            }
        }
    }
    
    if(dir.exists(warDir))
        dir.cd(warDir);
    
    window.setPwd(dir.absolutePath());
    
    window.show();
    int status = app.exec();
    TextFormatter::destroy();
    
    return status;
}