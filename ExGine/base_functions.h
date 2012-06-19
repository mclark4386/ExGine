#ifndef __BASE_FUNCTIONS_H__
#define __BASE_FUNCTIONS_H__

#include <cmath>
//#include <pthread.h>

#define DOT(x1, y1, z1, x2, y2, z2) ((x1*x2)+(y1*y2)+(z1*z2))
#define MAG(x, y, z) (sqrt((x*x)+(y*y)+(z*z)))
#define RECCYLI(m, x, y) ((m*((x*x)+(y*y)))/12)
#define DIST(x1, y1, z1, x2, y2, z2) (sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))+((z1-z2)*(z1-z2))))

#endif
