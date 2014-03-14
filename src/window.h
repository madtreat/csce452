
#ifndef WINDOW_H_
#define WINDOW_H_

#include <QWidget>
#include <QString>
#include <QColor>
#include <QGridLayout>
#include <QPushButton>

class RobotArm;
class Canvas;
class CanvasWidget;

class Window : public QWidget
{
   Q_OBJECT

public:
   // sizes for the control panel widgets
   static const int CONTROL_WIDTH = 200;
   static const int JOINT_HEIGHT  = 30;

   Window();
   ~Window();

   void initStyles();
   void initCanvas();
   void initLayout();
   void initControlPanel();

public slots:
   void togglePaintText(bool);

private:
   RobotArm*      arm;
   Canvas*        canvas;
   CanvasWidget*  canvasWidget;

   QString        controlPanelStyle;

   QGridLayout*   layout;
   QWidget*       controlPanel;
   QVBoxLayout*   controlLayout;
   QPushButton*   paintButton;
   
   void initJointControls();
   void initWorldControls();
   void initBrushControls();

   QString  getControlStyle(QColor widget);

   QWidget* createJointControl(int id, QColor color);
   QWidget* createWorldControl(int id, QColor color);
   QWidget* createBrushControl();
};

#endif

