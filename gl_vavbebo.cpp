#include "gl_vavbebo.h"

GL_UTIL_BEGIN

VAVBEBO::VAVBEBO() 
    : _is_bind(false) 
{
}


VAVBEBO::~VAVBEBO() 
{ 
    release(); 
}

GL_UTIL_END