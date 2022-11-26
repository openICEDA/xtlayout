#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintingarea.h"
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QToolButton>
#include "drawcommand.h"
#include "rectangletool.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mUiState(NO_ACTIVE_TOOL_STATE), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mPA = new PaintingArea(this);
    setCentralWidget(mPA);
    QToolButton *rectToolButton = new QToolButton(this);
    QToolButton *selectToolButton = new QToolButton(this);
    ui->toolBar->addWidget(rectToolButton);
    ui->toolBar->addWidget(selectToolButton);
    rectToolButton->setText("Rectangle");
    rectToolButton->setShortcut(QKeySequence("R"));
    selectToolButton->setText("Select");
    connect(rectToolButton, SIGNAL(clicked()), this, SLOT(newRectangleTool()));
    qApp->installEventFilter(this);
}

void MainWindow::paintEvent(QPaintEvent *)
{
}

void MainWindow::newRectangleTool()
{
    if(nullptr == mPA->getTool())
    {
        mPA->setTool(new RectangleTool(mPA));
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    return false;
//    if(mUiState == NO_ACTIVE_TOOL_STATE)
//    {
//        if(event->type() == QEvent::KeyPress || event->type() == QEvent::MouseButtonPress)
//        {
//            if(key or button activates a tool)
//            {
//                mUiState = INTERMEDIATE_STATE;
//            }
//        }
//        return true;
//    }
//    else if(mUiState == INTERMEDIATE_STATE)
//    {
//        if(event->type() == QEvent::KeyRelease)
//        {
//            QKeyEvent *event = static_cast<QKeyEvent*>(event);
//            mPA->setTool(tool(event->key()));
//            mUiState = TOOL_ACTIVE_STATE;
//        }
//        else if(event->type() == QEvent::MouseButtonRelease)
//        {
//            QMouseEvent *event = static_cast<QMouseEvent*>(event);
//            if(event->pos() within a tool button)
//            {
//                mPA->setTool(tool(event->pos()));
//                mUiState = TOOL_ACTIVE_STATE;
//            }
//            else
//            {
//                mUiState = NO_ACTIVE_TOOL_STATE;
//            }
//        }
//        return true;
//    }
//    else if(mUiState == TOOL_ACTIVE_STATE)
//    {

//    }
//    else
//    {

//    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
//    if(nullptr != mPA->getTool())
//    {
//        mPA->getTool()->keyPressEvent(event);
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

