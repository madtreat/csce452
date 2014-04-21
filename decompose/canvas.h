
#ifndef CANVAS_H_
#define CANVAS_H_

class Manager;

class Canvas
{
public:

   Canvas(Manager* _man);
   ~Canvas();

   void init();
	void display();
   void drawBox(int boxNum);
   void drawRobot();
   void drawDest(); 
   void drawCellNode(int row, int col);
	void drawCellBorders(int row, int col);
	void drawCells();
   
private:
   Manager* manager;
	
};

#endif

