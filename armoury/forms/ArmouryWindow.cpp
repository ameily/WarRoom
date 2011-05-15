/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  xproject <meily.adam@gmail.com>

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


#include "ArmouryWindow.h"
#include "ArmouryWindow.moc"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

ArmouryWindow::ArmouryWindow(QWidget* parent) : QMainWindow(parent),
    m_pwd(QDir::currentPath())
{
    setupUi(this);
    m_viewingFile = false;
    setWindowFilePath("No File");
    m_game = 0;
    connect(actionOpenFile, SIGNAL(triggered()), SLOT(onMenuOpenFile()));
    connect(actionQuit, SIGNAL(triggered()), SLOT(close()));
}

void ArmouryWindow::onMenuOpenFile()
{
    closeOpenFile();
    
    QString filter = "War Files (*.game *.race)";
    QString path = QFileDialog::getOpenFileName(this, "Open File",
        m_pwd, filter, &filter);
    
    if(!path.isEmpty())
    {
        QFile fp(path);
        if(!fp.open(QFile::ReadOnly))
        {
            QMessageBox::warning(this, "Error Opening File", "The file `" +
                path + "` could not be opened."
            );
            
            return;
        }
        
        QDomDocument doc;
        if(!openXml(doc, &fp))
            return;
        
        QString root = doc.documentElement().tagName();
        try
        {
            if(root == "game")
            {
                m_game = new Game(doc);
                WarPage page(*m_game);
                pageViewer->setFirstPage(page);
            }
        }
        catch(XmlParseException e)
        {
            QMessageBox::warning(this, "Parse Error", "Could not parse file " +
                fp.fileName() + ".\n[" + e.elementName() + "@" +
                QString::number(e.line()) + "]: " + e.description());
            
            closeOpenFile();
        }
        
        setWindowFilePath(fp.fileName());
        
        fp.close();
    }
}

bool ArmouryWindow::openXml(QDomDocument& doc, QFile* file)
{
    QString err;
    int line;
    if(!doc.setContent(file, &err, &line))
    {
        QMessageBox::warning(this, "Parse Error", "Could not parse file " +
            file->fileName() + "[line " + QString::number(line) + ": " +
            err + "]");
        
        return false;
    }
    
    return true;
}

void ArmouryWindow::cleanup()
{
    if(m_game)
        delete m_game;
    
    m_game = 0;
}

void ArmouryWindow::closeOpenFile()
{
    cleanup();
    m_viewingFile = false;
    pageViewer->clear();
    setWindowFilePath("No File");
}

void ArmouryWindow::setPwd(const QString& dir)
{
    m_pwd = dir;
}



ArmouryWindow::~ArmouryWindow()
{
    cleanup();
}

