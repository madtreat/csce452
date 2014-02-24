
#ifndef WINDOW_H_
#define WINDOW_H_

#include <QWidget>
#include <QString>
#include <QColor>

class Canvas;
class CanvasWidget;

class Window : public QWidget
{
   Q_OBJECT

public:
   Window();
   ~Window();

private:
   Canvas* canvas;
   CanvasWidget* canvasWidget;
   
   QString getControlStyle(QColor widget);
};

#endif

