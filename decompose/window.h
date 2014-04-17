
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

protected:
   void keyPressEvent(QKeyEvent* event);
   void keyReleaseEvent(QKeyEvent* event);

private:
   Canvas*        canvas;
   CanvasWidget*  canvasWidget;
	Manager*			manager;

   // Qt CSS-like style sheet
   QString        controlPanelStyle;

   // The window's layout
   QGridLayout*   layout;

   QString  getControlStyle(QColor widget);
};

#endif

