#ifndef NODE_H
#define NODE_H

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/quaternion.hpp"
#include "lib/glm/gtx/quaternion.hpp"

class Node 
{
    public:
        Node(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
        Node(glm::vec3 pos, glm::quat rot, glm::vec3 scale);
        virtual ~Node();

        glm::vec3* getPosition();

        void setPosition(float x, float y, float z);
		void setPosition(glm::vec3 pos);
		void setEulerRotation(float x, float y, float z);
		void setEulerRotation(glm::vec3 rot);

    protected:
        glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
		glm::quat rotation = glm::quat(glm::vec3(0.0, 0.0, 0.0));
		glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
};

#endif