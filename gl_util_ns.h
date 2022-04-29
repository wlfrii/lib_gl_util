#ifndef GL_UTIL_NS_H_LF
#define GL_UTIL_NS_H_LF

#define GL_UTIL_BEGIN namespace gl_util{
#define GL_UTIL_END }

#define GL_LOG(fmt, ...) \
    printf("[%s][%s][%d] " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#endif // GL_WARPPER_NS_H_LF
