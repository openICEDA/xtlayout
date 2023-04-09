#include "paintingarea.h"
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QDebug>
#include "tool.h"
#include "mainwindow.h"
#include "xtliterals.h"
#include "lblock.h"
#include <QFileDialog>
#include <QGuiApplication>


PaintingArea::PaintingArea(QWidget* pMainWindow)
    : QWidget{pMainWindow}, mMainWindow(static_cast<MainWindow*>(pMainWindow)), mBlock(new LBlock(this, pMainWindow->geometry().width(), pMainWindow->geometry().height()))
{
    resize(pMainWindow->geometry().width(), pMainWindow->geometry().height());
    update();
}

PaintingArea::~PaintingArea()
{
    delete mBlock;
}

void PaintingArea::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    VisualEntity* ve;
    mBlock->initVisualEntityPtr();
    while ((ve = mBlock->nextVisualEntityPtr()))
    {
        ve->draw(&painter);
    }
}

bool PaintingArea::loadFile(const QString& pFileName)
{
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    bool succeeded = mBlock->open(pFileName.toStdString().c_str());
    QGuiApplication::restoreOverrideCursor();
    return succeeded;
}

void PaintingArea::mousePressEvent(QMouseEvent* event)
{
    std::vector<Tool*>& activeTools = static_cast<MainWindow*>(mMainWindow)->getActiveTools();
    for (std::vector<Tool*>::const_iterator it = activeTools.cbegin(); it != activeTools.cend(); it++)
    {
        Tool* tool = *it;
        if (tool)
        {
            tool->mousePressEvent(event, mBlock);
        }
    }
    update();
}

void PaintingArea::mouseMoveEvent(QMouseEvent* event)
{
    std::vector<Tool*>& activeTools = static_cast<MainWindow*>(mMainWindow)->getActiveTools();
    for (std::vector<Tool*>::const_iterator it = activeTools.cbegin(); it != activeTools.cend(); it++)
    {
        Tool* tool = *it;
        if (tool)
        {
            tool->mouseMoveEvent(event, mBlock);
        }
    }
    update();
}

void PaintingArea::mouseReleaseEvent(QMouseEvent* event)
{
    std::vector<Tool*>& activeTools = static_cast<MainWindow*>(mMainWindow)->getActiveTools();
    for (std::vector<Tool*>::const_iterator it = activeTools.cbegin(); it != activeTools.cend(); it++)
    {
        Tool* tool = *it;
        if (tool)
        {
            tool->mouseReleaseEvent(event, mBlock);
        }
    }
    update();
}

bool PaintingArea::saveAs()
{
    QString curFile;
    QString fileName = QFileDialog::getSaveFileName(this, "Save As", curFile);
    if (fileName.isEmpty())
    {
        return false;
    }
    return saveFile(fileName);
}

bool PaintingArea::saveFile(const QString& pFileName)
{
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    bool succeeded = mBlock->write(pFileName.toStdString().c_str());
    QGuiApplication::restoreOverrideCursor();
    return succeeded;
}
