#ifndef BONE_HPP
#define BONE_HPP

#include <glm/glm.hpp>

using namespace glm;

class Bone {
    public:
        mat4 transformation;
        mat4 transformation_inverse;
        
        Bone();
        Bone(mat4 transformation);
        Bone(mat4 transformation, mat4 transformation_inverse);
        ~Bone();
};

#endif // BONE_HPP
