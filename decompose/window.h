
#ifndef WINDOW_H_
#define WINDOW_H_

#include <QWidget>
#include <QString>
#include <QColor>
#include <QGridLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>


class Canvas;
class CanvasWidget;
class Manager;

class Window : public QWidget
{
   Q_OBJECT

public:
   Window(Manager* _manager = 0);
   ~Window();

   void initStyles();
   void initCanvas();
   void initLayout();

public slots:
	void windowAnimate();
   void pathCalculated();

protected:
   void keyPressEvent(QKeyEvent* event);
   void keyReleaseEvent(QKeyEvent* event);
	void mouseReleaseEvent(QMouseEvent* e);

private:
   Canvas*        canvas;
   CanvasWidget*  canvasWidget;
	Manager*			manager;

   // What is currently selected to place
   // 0 = robot
   // 4 = destination
   // 1 = box 1
   // 2 = box 2
   // 3 = box 3
   int            selection;

   // The window's layout
   QGridLayout*   layout;

   // The window's title
   QString        windowTitle;

   // Qt CSS-like style sheet
   QString        controlPanelStyle;
   QString        getControlStyle(QColor widget);
};

#endif

