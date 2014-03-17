
#ifndef WINDOW_H_
#define WINDOW_H_

#include <QWidget>
#include <QString>
#include <QColor>
#include <QGridLayout>
#include <QPushButton>
#include <QKeyEvent>

class RobotArm;
class Canvas;
class CanvasWidget;

class Window : public QWidget
{
   Q_OBJECT

public:
   // sizes for the control panel widgets
   static const int CONTROL_WIDTH   = 132;
   static const int JOINT_HEIGHT    = 30;

   // range for the brush
   static const int BRUSH_MIN       = 5;
   static const int BRUSH_MAX       = 40;

   Window();
   ~Window();

   void initStyles();
   void initCanvas();
   void initLayout();
   QWidget* initControlPanel();

public slots:
   void togglePaintText(bool);
   void toggleJointControlsVisible(bool);
   void toggleWorldControlsVisible(bool);

protected:
   void keyPressEvent(QKeyEvent* event);
   void keyReleaseEvent(QKeyEvent* event);

private:
   RobotArm*      arm;
   Canvas*        canvas;
   CanvasWidget*  canvasWidget;

   QString        controlPanelStyle;
   bool           painting;

   QGridLayout*   layout;
   QWidget*       controlPanel;
   QWidget*       jointControls;
   QWidget*       worldControls;

   QGridLayout*   controlLayout;
   QPushButton*   paintButton;
   QPushButton*   jointButton;
   QPushButton*   worldButton;
   
   QWidget* initJointControls();
   QWidget* initWorldControls();
   QWidget* initBrushControls();

   QString  getControlStyle(QColor widget);

   QWidget* createJointControl(int id);
   QWidget* createWorldControl(int id);
   QWidget* createBrushControl();
};

#endif

