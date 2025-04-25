#include "../include/gl_util/gl_projection.h"


GL_UTIL_BEGIN

Projection::Projection(float fxy, float cx, float cy, uint16_t w, uint16_t h, 
                       float z_near, float z_far)
    : _z_near(z_near)
    , _z_far(z_far)
    , _fxy(fxy)
    , _cx(cx), _cy(cy)
    , _w(w), _h(h)
    , _A(0), _B(0)
    , _projection(glm::mat4(.0f)) {
    calcProjection();
}

Projection::Projection(float fxy, uint16_t w, uint16_t h, float z_near, float z_far)
    : Projection(fxy, w/2, h/2, w, h, z_near, z_far) {
}

void Projection::setFocalLength(float fxy) {
    _fxy = fxy;
    calcProjection();
}

const glm::mat4& Projection::mat4() const {
    return _projection;
}

float Projection::cvt2RealDepth(float z_buf) const {
    return _B / (_A + 2*z_buf - 1);
}

Projection Projection::adaptToNED(float ocular_fov, uint16_t screen_w, uint16_t screen_h, 
                                   uint16_t disp_w, uint16_t disp_h) const {
    float im_aspect_ratio = 1.f * _w / _h;
    if(disp_w == 0 && disp_h == 0) {
        float screen_aspect_ratio = 1.f * screen_w / screen_h;
        if (std::fabs(im_aspect_ratio - screen_aspect_ratio) > 1e-6) {
            if(im_aspect_ratio < screen_aspect_ratio) {
                disp_h = screen_h;
                disp_w = round(disp_h * im_aspect_ratio);
            }
            else {
                disp_w = screen_w;
                disp_h = round(disp_w / im_aspect_ratio);
            }
        }
        else {
            disp_w = screen_w;
            disp_h = screen_h;
        }
    }
    else if (disp_w != 0 && disp_h != 0) {
        if (std::fabs(im_aspect_ratio - 1.f*disp_w / disp_h) > 1e-6) {
            GL_UTIL_LOG("ERROR: the aspect-ratio of given displaying region (%dx%d) "
                        "is not equal to the image (%dx%d).\n", 
                        disp_w, disp_h, _w, _h);
            std::exit(EXIT_FAILURE);
        }
    }
    else {
        GL_UTIL_LOG("ERROR, both display width and display height should be set.\n");
        std::exit(EXIT_FAILURE);
    }
    GL_UTIL_LOG("NED screen: %dx%d, display region: %dx%d.\n", 
                screen_w, screen_h, disp_w, disp_h);

    float half_diag_screen = sqrtf(screen_w*screen_w + screen_h*screen_h) / 2.f;
    float half_diag_disp = sqrtf(disp_w*disp_w + disp_h*disp_h) / 2.f;
    float ned_fov = atanf(half_diag_disp / half_diag_screen * tanf(ocular_fov/2.f)) * 2.f;
    GL_UTIL_LOG("NED ocular FOV: %f, display FOV: %f rad in the given display region.\n", 
                ocular_fov, ned_fov);
    float cam_fov = 2.f*atanf(sqrtf(_w*_w + _h*_h) / 2.f / _fxy);
    float virtual_cam_fxy = disp_w / _w * _fxy;
    float ned_fxy = tan(cam_fov / 2.f) * virtual_cam_fxy / tan(ned_fov / 2.f);
printf("ned_fxy:%f\n", ned_fxy);
    return Projection(ned_fxy, disp_w, disp_h, _z_near, _z_far);
}

void Projection::calcProjection() {
    _projection[0][0] = 2.0 * _fxy / _w;
    _projection[0][2] = 1.0 - 2.0 * _cx / _w;
    _projection[1][1] = 2.0 * _fxy / _h;
    _projection[1][2] = 1.0 - 2.0 * _cy / _h;

    _A = -1.0 * (_z_far + _z_near) / (_z_far - _z_near);
    _B = -1.0 * 2.0 * _z_near * _z_far / (_z_far - _z_near);
    _projection[2][2] = _A;
    _projection[3][2] = _B;

    _projection[2][3] = -1.0;
}

GL_UTIL_END