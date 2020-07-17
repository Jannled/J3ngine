#ifndef J3_WINDOW_H
#define J3_WINDOW_H

namespace J3
{
	typedef struct {
		unsigned int x, y;
	} Vec2D;

	class Window
	{
		public:
			Window();
			~Window();

			void setTitle(const char* title);
			void setSize(unsigned int width, unsigned int height);
			void setSize(Vec2D dimension);
	};    
}

#endif // J3_WINDOW_H