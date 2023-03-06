#pragma once;
#ifndef SAFE_H
#define SAFE_H


#ifndef SAFE_DELETE
#define SAFE_DELETE(p){if(p){delete(p);(p)=0;}}
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p){if(p){delete[](p);(p)=0;}}
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p){if(p){(p)->Release();(p)=0;}}
#endif


#endif // SAFE_H