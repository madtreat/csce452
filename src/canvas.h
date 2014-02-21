
#ifndef CANVAS_H_
#define CANVAS_H_

class Canvas
{
public:
   static const int WIDTH  = 640;
   static const int HEIGHT = 480;
   
   //Canvas(int argc, char* argv[]);
   Canvas();
   ~Canvas();

   void init();

   static void circle(int x, int y);
   static void display();
   static void keyboard(unsigned char key, int x, int y);
   static void mouseMove(int x, int y);

private:
   
};

#endif

