#ifndef J3_WINDOW_H
#define J3_WINDOW_H

namespace J3
{
    
    class Window
    {
        public:
            Window();
            ~Window();

            void setTitle(const char* title);
            void setSize(unsigned int width, unsigned int height);
    };    
}

#endif // J3_WINDOW_H