#include "../include/gl_util/gl_projection.h"

GL_UTIL_BEGIN

Projection::Projection(float fxy, float cx, float cy, float w, float h, float z_near, float z_far)
    : _z_near(z_near)
    , _z_far(z_far)
    , _fxy(fxy)
    , _cx(cx), _cy(cy)
    , _w(w), _h(h)
    , _A(0), _B(0)
    , _projection(glm::mat4(.0f))
{
    calcProjection();
}


void Projection::calcProjection()
{
    _projection[0][0] = 2 * _fxy / _w;
    _projection[0][2] = 1 - 2 * _cx / _w;
    _projection[1][1] = 2 * _fxy / _h;
    _projection[1][2] = 1 - 2 * _cy / _h;

    _A = -1 * (_z_far + _z_near) / (_z_far - _z_near);
    _B = -1 * 2 * _z_near * _z_far / (_z_far - _z_near);
    _projection[2][2] = _A;
    _projection[3][2] = _B;

    _projection[2][3] = -1;
}


const glm::mat4& Projection::mat4() const
{
    return _projection;
}


float Projection::cvt2RealDepth(float z_buf) const
{
    return _B / (_A + 2*z_buf - 1);
}

GL_UTIL_END