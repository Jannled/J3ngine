#ifndef J3_STATICOBJECT_H
#define J3_STATICOBJECT_H

#include "Node.h"

namespace J3
{
	class StaticObject : public Node
	{
		public:
			StaticObject();
			~StaticObject();

			void render();
	};
}


#endif // J3_STATICOBJECT_H