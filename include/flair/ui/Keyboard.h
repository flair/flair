#ifndef flair_ui_Keyboard_h
#define flair_ui_Keyboard_h

namespace flair {
  namespace ui {

     class Keyboard
     {
     public:
        
        // KeyCodes
        enum {
           LEFT = 37,
           UP = 38,
           RIGHT = 39,
           DOWN = 40,
           
           A = 65,
           B = 66,
           C = 67,
           D = 68,
           E = 69,
           F = 70,
           G = 71,
           H = 72,
           I = 73,
           J = 74,
           K = 75,
           L = 76,
           M = 77,
           N = 78,
           O = 79,
           P = 80,
           Q = 81,
           R = 82,
           S = 83,
           T = 84,
           U = 85,
           V = 86,
           W = 87,
           X = 88,
           Y = 89,
           Z = 90,
           
           _KEY_COUNT // Internal for sizing the key array
        };
      
     // Properties
     public:
        static bool capsLock();
        
        static bool hasVirtualKeyboard();
        
        static bool numLock();
        
        static int physicalKeyboardType();
        
     private:
        Keyboard();

     };

  }
}
#endif
