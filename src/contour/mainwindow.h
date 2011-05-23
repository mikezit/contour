#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>

class ContourFrame;

class MainWindow : public QMainWindow
{
   Q_OBJECT

public :
     MainWindow( QWidget * parent = 0, Qt::WindowFlags flags = 0 );

     ~MainWindow();

public slots:

     void about();
private:
     void keyPressEvent(QKeyEvent* event);
     void createActions();
     void createMenus();
     ContourFrame *frame;
     QMenu *fileMenu;
     QMenu *editMenu;
     QMenu *optionMenu;
     QMenu *helpMenu;

     QAction *openGridAction;
     QAction *openScatterAction;
     QAction *showGridAction;
     QAction *showPointAction;
     QAction *fillColorAction;
     QAction *exitAction;
     QAction *separatorAction;
     QAction *randAction;
     QAction *randSetAction;
     QAction *saveRandDataAction;
     QAction *saveGridDataAction;
     QAction *traceValueAction;
     QAction *colorEditAction;
     QAction *aboutAction;
};

#endif
