//
// Created by Jack Armstrong on 3/26/19.
//

#include "raycast.h"

Intersection world_hit(float startX,float startY,float startZ,float dirX,float dirY,float dirZ,int range){
    float endX=startX+dirX*range;
    float endY=startY+dirY*range;
    float endZ=startZ+dirZ*range;

    const float x1=startX;
    const float y1=startY;
    const float z1=startZ;

    const float x2=endX;
    const float y2=endY;
    const float z2=endZ;

    int i= (int) floor(x1);
    int j= (int) floor(y1);
    int k= (int) floor(z1);

    const int di=x2<x1?-1:1;
    const int dj=y2<y1?-1:1;
    const int dk=z2<z1?-1:1;

    const float dx=1.0f/fabsf(x2-x1);
    const float dy=1.0f/fabsf(y2-y1);
    const float dz=1.0f/fabsf(z2-z1);

    const float minx= floorf(x1), maxx= minx + 1;
    const float miny= floorf(y1), maxy= miny + 1;
    const float minz= floorf(z1), maxz= minz + 1;

    float tx=((x1>x2)?x1-minx:maxx-x1)*dx;
    float ty=((y1>y2)?y1-miny:maxy-y1)*dy;
    float tz=((z1>z2)?z1-minz:maxz-z1)*dz;

    int nx=0;
    int ny=0;
    int nz=0;

    for(int num=0;num<range;num++){
//        traverse(i,j,k);
        if(world_get(i,j,k)!=0){
            Intersection intersection;
            intersection.x=i;
            intersection.y=j;
            intersection.z=k;
            intersection.nx=nx;
            intersection.ny=ny;
            intersection.nz=nz;
            intersection.hit=true;
            return intersection;
        }

        if(tx<=ty&&tx<=tz){
            tx+=dx;
            i+=di;
            nx=-(int)roundf(di);
            ny=0;
            nz=0;
        }else if(ty<=tz){
            ty+=dy;
            j+=dj;
            nx=0;
            ny=-(int) roundf(dj);
            nz=0;
        }else{
            tz+=dz;
            k+=dk;
            nx=0;
            ny=0;
            nz=-(int) roundf(dk);
        }
    }

    Intersection intersection;
    intersection.hit=false;

    return intersection;
}