#ifndef J3_CAMERA_H
#define J3_CAMERA_H

#include "Node.h"

namespace J3
{
	class Camera : public Node
	{
		public:
			Camera(unsigned int widht, unsigned int height);
			~Camera();
	};
}


#endif // J3_CAMERA_H