
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
   // sizes for the control panel widgets
   static const int JOINT_HEIGHT    = 30;
   static const int COMBO_WIDTH     = 80;

   // range for the brush
   static const int BRUSH_MIN       = 5;
   static const int BRUSH_MAX       = 40;

   Window(Manager* _manager = 0);
   ~Window();

   void initStyles();
   void initCanvas();
   void initLayout();
   QWidget* initControlPanel();

public slots:
	void windowAnimate();
   void updateCarBox();
   void updateLightBox();
	
   void carSelected(int index);
   void lightSelected(int index);
   void setCheckBoxText(int);

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
   QCheckBox*     directBox;
   QSpinBox*      carSpinX;
   QSpinBox*      carSpinY;
   QSpinBox*      lightSpinX;
   QSpinBox*      lightSpinY;

   QComboBox*     carComboBox;
   QComboBox*     lightComboBox;

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

