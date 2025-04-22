/** -------------------------------------------------------------------
 *																		
 *   				        OpenGL Utilities 					
 *																		
 * @file 		gl_camera.h 
 * 
 * @brief 		A manager for the GL camera
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
 * --------------------------------------------------------------------
 * Change History:                        
 * 
 * 2022.4.29 Refactor the codes.
 * * --------------------------------------------------------------------
 * References:
 * https://learnopengl-cn.github.io/01%20Getting%20started/09%20Camera/
 * -------------------------------------------------------------------*/
#ifndef GL_UTIL_CAMERA_H_LF
#define GL_UTIL_CAMERA_H_LF
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "gl_util_ns.h"

GL_UTIL_BEGIN

// Default camera values
const float YAW         = -90.0f;   // rotate by y-axis
const float PITCH       = 0.0f;     // rotate by x-axis
const float SPEED       = 2.5f;
const float SENSITIVITY = 0.1;
const float ZOOM        = 45.0f;

/**
 * @brief An abstract camera class that processes input and calculates the 
 * corresponding Euler Angles, Vectors and Matrices for using in OpenGL.
 * Note, the z-axis of the GL camera is oriented from screen to you.
 */
class Camera
{
public:
    /** 
     * @brief Defines several possible options for camera movement. Used as 
     * abstraction to stay away from window-system specific input methods
     */
    enum Movement
    {
        MOVE_FORWARD,
        MOVE_BACKWARD,
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN
    };


    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
        : _front(glm::vec3(0.0f, 0.0f, -1.0f))
        , _move_speed(SPEED)
        , _mouse_sensitivity(SENSITIVITY)
        , _fov(ZOOM)
    {
        _position = position;
        _world_up = up;
        _yaw = yaw;
        _pitch = pitch;
        updateCameraVectors();
    }

    /**
     * @brief Get the View Matrix calculated by Euler Angles
     * 
     * @return glm::mat4 
     */
    glm::mat4 getViewMatrix() const
    {
        return glm::lookAt(_position, _position + _front, _up);
    }

    void processKeyboard(Movement direction, float delta_time)
    {
        float velocity = _move_speed * delta_time;
        switch (direction)
        {
        case MOVE_FORWARD:
            _position += _front * velocity;
            break;
        case MOVE_BACKWARD:
            _position -= _front * velocity;
            break;
        case MOVE_LEFT:
            _position -= _right * velocity;
            break;
        case MOVE_RIGHT:
            _position += _right * velocity;
            break;
        case MOVE_UP:
            _position += _up * velocity;
            break;
        case MOVE_DOWN:
            _position -= _up * velocity;
            break;
        default:
            break;
        }
    }

    void processMouseMovement(float x_offset, float y_offset, GLboolean constrain_pitch = true)
    {
        x_offset *= _mouse_sensitivity;
        y_offset *= _mouse_sensitivity;

        _yaw += x_offset;
        _pitch += y_offset;

        if(constrain_pitch){
            if(_pitch > 89.0f) _pitch = 89.0f;
            if(_pitch < -89.0f) _pitch = -89.0f;
        }
        updateCameraVectors();
    }

    void processMouseScroll(float y_offset)
    {
        _fov -= static_cast<float>(y_offset);
        if(_fov < 1.0f) _fov = 1.0f;
        if(_fov > 45.0f) _fov = 45.0f;
    }

    float getFOV() const
    {
        return _fov;
    }

    const glm::vec3& getPosition() const
    {
        return _position;
    }

    
private:
    void updateCameraVectors()
    {
        // Calculate the new front vector
        glm::vec3 front;
        front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        front.y = sin(glm::radians(_pitch));
        front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        _front = glm::normalize(front);
        // Update right and up
        _right = glm::normalize(glm::cross(_front, _world_up));
        _up = glm::normalize(glm::cross(_right, _front));
    }

    // Camera attributes
    glm::vec3 _position;  //!< The position of camera w.r.t {W}
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;
    glm::vec3 _world_up;
    // Euler angles
    float _yaw;
    float _pitch;
    // Camera options
    float _move_speed;
    float _mouse_sensitivity;
    float _fov;
};

/* ------------------------------------------------------------------- */
/*                         Camera Implementation                       */
/* ------------------------------------------------------------------- */



GL_UTIL_END
#endif // GL_UTIL_CAMERA_H_LF