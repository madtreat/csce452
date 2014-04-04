
#ifndef WINDOW_H_
#define WINDOW_H_

#include <QWidget>
#include <QString>
#include <QColor>
#include <QGridLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QSpinBox>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

#include "myQSpinBox.h"

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
   // other usefull helper functions/slots
   void togglePaintText(bool);
   void toggleJointControlsVisible(bool);
   void toggleWorldControlsVisible(bool);
   void updateBrushPos();
   void updateJointPos();

protected:
   void keyPressEvent(QKeyEvent* event);
   void keyReleaseEvent(QKeyEvent* event);

private:
   Canvas*        canvas;
   CanvasWidget*  canvasWidget;

   // Qt CSS-like style sheet
   QString        controlPanelStyle;

   QGridLayout*   layout;
   QWidget*       controlPanel;
   QWidget*       jointControls;
   QWidget*       worldControls;

   QGridLayout*   controlLayout;
   QPushButton*   paintButton;
   QPushButton*   jointButton;
   QPushButton*   worldButton;

   // for number keys switching between joints and keeping all values up to date
   // private functions
   static int     jointToNum(QString name);
   static QString numToJoint(int     num);

   myQSpinBox*      joint1Spin;
   myQSpinBox*      joint2Spin;
   myQSpinBox*      joint3Spin;
   myQSpinBox*      brushSpinX;
   myQSpinBox*      brushSpinY;
   myQSpinBox*      brushSizeSpin;
   
   QWidget* initJointControls();
   QWidget* initWorldControls();
   QWidget* initBrushControls();

   QString  getControlStyle(QColor widget);

   QWidget* createJointControl(int id);
   QWidget* createWorldControl(int id);
   QWidget* createBrushControl();
};

#endif

