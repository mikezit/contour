#include "mainwindow.h"
#include "contourframe.h"
#include "ui_contourframe.h"
#include "dialog/helpdialog.h"
#include <QMenuBar>
#include <QDialog>

MainWindow::MainWindow(QWidget * parent/* = 0*/, Qt::WindowFlags flags/* = 0*/ )
     :QMainWindow()
{
    setWindowTitle(tr("Jian's Contour"));

    frame = new ContourFrame;
    frame->randContour();
    setCentralWidget(frame);
    createActions();
    createMenus();
    resize(1000,1000);
}

MainWindow::~MainWindow()
{

}
void MainWindow::createActions()
{
     openGridAction = new QAction(tr("Open Grid"),this);
     openGridAction->setShortcut(tr("open grid data file."));
     connect(openGridAction,SIGNAL(triggered()),frame,SLOT(importGridFile()));

     openScatterAction = new QAction(tr("Open Scatter"),this);
     openScatterAction->setShortcut(tr("open scatter data file."));
     connect(openScatterAction,SIGNAL(triggered()),frame,SLOT(importScatterFile()));

     exitAction = new QAction(tr("Exit"),this);
     connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

     showGridAction = new QAction(tr("&Show Grid"), this); 
     showGridAction->setCheckable(true); 
     showGridAction->setChecked(true); 
     showGridAction->setStatusTip(tr("Show or hide the spreadsheet's grid")); 
     connect(showGridAction, SIGNAL(toggled(bool)),frame, SLOT(setGrid(bool)));

     showPointAction = new QAction(tr("&Show Point"), this); 
     showPointAction->setCheckable(true); 
     showPointAction->setChecked(false); 
     showPointAction->setStatusTip(tr("Show or hide the spreadsheet's point")); 
     connect(showPointAction, SIGNAL(toggled(bool)),frame, SLOT(setPointShow(bool)));

     fillColorAction = new QAction(tr("&Fill Color"), this); 
     fillColorAction->setCheckable(true); 
     fillColorAction->setChecked(true); 
     connect(fillColorAction, SIGNAL(toggled(bool)),frame, SLOT(setFillColor(bool))) ;

     colorEditAction = new QAction(tr("Edit Color"),this);
     connect(colorEditAction, SIGNAL(triggered()),frame, SLOT(editColorMap())) ;

     traceValueAction = new QAction(tr("Set Trace"),this);
     connect(traceValueAction,SIGNAL(triggered()),frame,SLOT(setTraceValue()));

     randAction = new QAction(tr("Rand"),this);
     connect(randAction, SIGNAL(triggered()),frame, SLOT(randContour()));

     randSetAction = new QAction(tr("Set"),this);
     connect(randSetAction,SIGNAL(triggered()),frame,SLOT(setRandInfo()));

     saveRandDataAction = new QAction(tr("Save rand data"),this);
     connect(saveRandDataAction,SIGNAL(triggered()),frame,SLOT(saveRandData()));

     saveGridDataAction = new QAction(tr("Save grid"),this);
     connect(saveGridDataAction,SIGNAL(triggered()),frame,SLOT(saveGridData()));

     aboutAction = new QAction(tr("about"),this);
     connect(aboutAction,SIGNAL(triggered()),this,SLOT(about()));
}


void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File")); 
    fileMenu->addAction(openGridAction); 
    fileMenu->addAction(openScatterAction); 
    fileMenu->addAction(saveRandDataAction); 
    fileMenu->addAction(saveGridDataAction); 
    separatorAction = fileMenu->addSeparator(); 
    fileMenu->addSeparator(); 
    fileMenu->addAction(exitAction); 

    editMenu = menuBar()->addMenu(tr("&Edit"));     
    editMenu->addAction(traceValueAction);

    optionMenu = menuBar()->addMenu(tr("&Options"));   
    optionMenu->addAction(showGridAction);
    optionMenu->addAction(showPointAction);
    optionMenu->addAction(fillColorAction);
    QMenu* randMenu = optionMenu->addMenu("rand");
    randMenu->addAction(randAction);
    randMenu->addAction(randSetAction);
    optionMenu->addAction(colorEditAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);   
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
     QMainWindow::keyPressEvent(event);
     int key = event->key();

     if(key == Qt::Key_F5){
	  frame->_isRand = true;
	  frame->randContour();
     }
     else if(key == Qt::Key_F){
	  frame->setFillColor(!frame->_fillColor);
	  fillColorAction->setChecked(frame->_fillColor); 
     }
     else if(key == Qt::Key_G){
	  frame->setGrid(!frame->_showGrid);
	  showGridAction->setChecked(frame->_showGrid); 
     }
     else if(key == Qt::Key_P){
	  frame->setPointShow(!frame->_showPoint);
     }
}

void MainWindow::about()
{
     HelpDialog dialog;
     dialog.exec();
}

