/** -------------------------------------------------------------------------------------
 *																		
 *   				                 OpenGL Utilities 					
 *																		
 * @file 		gl_projection.h 
 * 
 * @brief 		A manager for construct projection matrix.
 * 
 * @author		Longfei Wang
 * 
 * @version		2.0.0
 * 
 * @date		2021/10/08
 * 
 * @license		MIT
 * 
 * Copyright (C) 2021-Now Longfei Wang.
 * 
 * --------------------------------------------------------------------------------------
 * Change History:                        
 * 
 * ------------------------------------------------------------------------------------*/
#ifndef GL_UTIL_PROJECTION_H_LF
#define GL_UTIL_PROJECTION_H_LF
#include <glm/glm.hpp>
#include "gl_util_ns.h"

GL_UTIL_BEGIN

/**
 * @brief Construct the projection matrix for OpenGL. 
 * The OpenGL projection matrix is consist of clipping and NDC transform. 
 */
class Projection {
public:
    /**
     * @brief Construct a new Projection object.
     * 
     * @param fxy  The focal length of camera. For binocular, this value should be the 
     * stereo-rectified focal length value.
     * @param cx  The x coordinta of camera optical axis
     * @param cy  The y coordinta of camera optical axis
     * @param w  The pixel width of camera
     * @param h  The pixel height of camera 
     * @param z_near  The near plane distance
     * @param z_far  The far plane distance
     */
    Projection(float fxy, float cx, float cy, float w, float h, 
               float z_near, float z_far);

    /**
     * @brief Construct a new Projection object.
     * 
     * @param fxy The focal length of camera. For binocular, this value should be the 
     * stereo-rectified focal length value.
     * @param w  The pixel width of camera.
     * @param h  The pixel height of camera.
     * @param z_near  The near plane distance.
     * @param z_far  The far plane distance.
     * 
     * @note The (cx, cy) of a camera will replaced assumed as (w/2, h/2), the center 
     * of the image, when calling this constructor.
     */
    Projection(float fxy, float w, float h, float z_near, float z_far);

    /**
     * @brief Return the projection matrix based on the setting as in 
     * constructor.
     * 
     * @return The 4x4 projection matrix.
     */
    const glm::mat4& mat4() const;

    /**
     * @brief  Convert depth buffer read from GL_DEPTH_COMPONENT to real depth 
     * w.r.t camera frame.
     * 
     * @param[in] z_buf  The depth value from depth buffer
     * @return The depth value w.r.t camera frame
     */
    float cvt2RealDepth(float z_buf) const;

private:
    /** Calculate projection matrix **/
    void calcProjection();

    float _z_near;  ///< The distance of near plane
    float _z_far;   ///< The distance of far plane

    float _fxy;     ///< The focal length of camera
    float _cx;      ///< The optical aixs's x coordinate
    float _cy;      ///< The optical aixs's y coordinate
    float _w;       ///< The pixel width of camera
    float _h;       ///< The pixel height of camera

    float _A;       ///< The temporary variable A
    float _B;       ///< The temporary variable B 
    
    glm::mat4 _projection; ///< The projection matrix
};

GL_UTIL_END
#endif // GL_UTIL_PROJECTION_H_LF