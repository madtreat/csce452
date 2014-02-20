
#ifndef CANVAS_H_
#define CANVAS_H_

class Canvas
{
public:
   static const int WIDTH  = 1200;
   static const int HEIGHT = 600;
   
   Canvas(int argc, char* argv[]);
   ~Canvas();

   static void circle(int x, int y);
   static void display();
   static void keyboard(unsigned char key, int x, int y);
   void init();
   static void mouseMove(int x, int y);

private:
   
};

#endif

