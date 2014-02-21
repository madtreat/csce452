
#ifndef WINDOW_H_
#define WINDOW_H_

#include <QWidget>

class Canvas;

class Window : public QWidget
{
   Q_OBJECT

public:
   Window();
   ~Window();

private:
   Canvas* canvas;

};

#endif

