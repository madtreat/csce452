
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
class Manager;

class Window : public QWidget
{
   Q_OBJECT

public:
   // sizes for the control panel widgets
   static const int JOINT_HEIGHT    = 30;
   static const int COMBO_WIDTH     = 80;

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
   
   void carSelected(int index);
   void lightSelected(int index);

   void createCarClicked();
   void deleteCarClicked();
   void createLightClicked();
   void deleteLightClicked();

protected:
   void keyPressEvent(QKeyEvent* event);
   void keyReleaseEvent(QKeyEvent* event);

private:
   Canvas*        canvas;
   CanvasWidget*  canvasWidget;
	Manager*			manager;

   // Qt CSS-like style sheet
   QString        controlPanelStyle;

   QGridLayout*   layout;
   QWidget*       controlPanel;

   QGridLayout*   controlLayout;
   QPushButton*   createCarButton;
   QPushButton*   deleteCarButton;
   QPushButton*   createLightButton;
   QPushButton*   deleteLightButton;

   // for number keys switching between joints and keeping all values up to date
   // private functions
   static int     jointToNum(QString name);
   static QString numToJoint(int     num);

   QString  getControlStyle(QColor widget);

   QWidget* createJointControl(int id);
   QWidget* createWorldControl(int id);
   QWidget* createBrushControl();

   QWidget* initCarControls();
   QWidget* initLightControls();
};

#endif

