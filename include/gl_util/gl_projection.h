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
    Projection(float fxy, float cx, float cy, uint16_t w, uint16_t h, 
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
    Projection(float fxy, uint16_t w, uint16_t h, float z_near, float z_far);

    /**
     * @brief Set the Focal Length object.
     */
    void setFocalLength(float fxy);

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

    /**
     * @brief Return a new gl_util::Projection object which for the Near-Eye Display (NED)
     * that displays the camera images.
     * 
     * @param ocular_fov The full FOV of the NED ocular, in radians.
     * @param screen_w The width of NED screen, in pixels.
     * @param screen_h The height of NED screen, in pixels.
     * @param disp_w The width of display region (defaultly equal to screen_w).
     * @param disp_h The height of display region (defaultly equal to screen_h).
     *
     * @note When display size is set, both display width and display height should be
     * given. Besides, the given display width and height must have the same aspect-ratio
     * to the aspect-ratio of camera image.
     * If no display size is set, full screen region is considered, and the camera image 
     * is supposed to be adaptively displayed with fixed aspect-ratio.
     *
     * @return Projection
     */
    Projection adaptToNED(float ocular_fov, uint16_t screen_w, uint16_t screen_h,
                           uint16_t disp_w = 0, uint16_t disp_h = 0) const;

private:
    /** Calculate projection matrix **/
    void calcProjection();

    float _z_near;  ///< The distance of near plane
    float _z_far;   ///< The distance of far plane

    float _fxy;     ///< The focal length of camera
    float _cx;      ///< The optical aixs's x coordinate
    float _cy;      ///< The optical aixs's y coordinate
    uint16_t _w;    ///< The pixel width of camera
    uint16_t _h;    ///< The pixel height of camera

    float _A;       ///< The temporary variable A
    float _B;       ///< The temporary variable B 
    
    glm::mat4 _projection; ///< The projection matrix
};

GL_UTIL_END
#endif // GL_UTIL_PROJECTION_H_LF