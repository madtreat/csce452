
#ifndef CANVAS_H_
#define CANVAS_H_

class Canvas
{
public:
   static const int WIDTH  = 640;
   static const int HEIGHT = 480;
   
   Canvas();
   ~Canvas();

   void init();

   static void circle(int x, int y);
   static void display();

private:
   
};

#endif

