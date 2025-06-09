#include <cmath>
#include "ModelView.hpp"


namespace Engine {
    Eigen::Matrix4f GetModelIViewMatrix(void) {
        // TODO Complete the matrix
        // rotation 
        
        Eigen::Matrix4f modelViewMatrix;
        modelViewMatrix << 1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1;
        return modelViewMatrix;
    }
    Eigen::Vector4f ModelView(Eigen::Vector4f Vec) {
        return Vec.transpose() * ModelViewMatrix;
    }
    void SetModelViewMatrix(void) {
        ModelViewMatrix = GetModelIViewMatrix();
    }
}