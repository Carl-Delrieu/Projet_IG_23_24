#include "bone.hpp"

using namespace glm;

Bone::Bone() {
    transformation = mat4(1.0f);
    transformation_inverse = mat4(1.0f);
}

Bone::Bone(mat4 transformation): transformation(transformation) {
    transformation_inverse = mat4(1.0f);
}

Bone::Bone(mat4 transformation, mat4 transformation_inverse): transformation(transformation), transformation_inverse(transformation_inverse) {}
    
Bone::~Bone() {}
