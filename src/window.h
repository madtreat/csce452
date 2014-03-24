
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

class RobotArm;
class Canvas;
class CanvasWidget;

enum AppType {
   NOCONN = 0,
   SERVER = 1,
   CLIENT = 2
};

struct ConnectionInfo {
   AppType        type;    // type of connection
   QHostAddress   host;    // host address
   quint16        port;    // port number of server
   int            delay;   // time delay in seconds for connected applications
};

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

   Window(ConnectionInfo _info);
   ~Window();

   // connection functions
   bool startServer();     // for servers
   bool connectToServer(); // for clients
   void processMessageFromClient(QString msg); // parse and execute
   void processMessageFromServer(QString msg); // parse and execute

   void initStyles();
   void initCanvas();
   void initLayout();
   QWidget* initControlPanel();

public slots:
   void connectClient();
   void disconnectClient();
   void readMessage();
   void sendMessage(QString);
   void notifyClient();// create message: server -> client
   void notifyServer(QString name, int val);// create message: client -> server

   // notifyServer() helper functions/slots
   // These are for client to send the appropriate command to the server
   void changeJoint1(int);
   void changeJoint2(int);
   void changeJoint3(int);
   void changeBrushX(int);
   void changeBrushY(int);
   void changeBrushSize(int);
   void changePainting(bool);

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
   RobotArm*      arm;
   Canvas*        canvas;
   CanvasWidget*  canvasWidget;

   ConnectionInfo conn;
   QTcpSocket*    socket; // used by clients and servers - the client's connection
   QTcpServer*    server; // used by server only

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

