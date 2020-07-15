#ifndef J3_STATICOBJECT_H
#define J3_STATICOBJECT_H

#include "SceneObject.h"

namespace J3
{
	class StaticObject : public SceneObject
	{
		public:
			StaticObject();
			~StaticObject();

			void render();
	};
}


#endif // J3_STATICOBJECT_H