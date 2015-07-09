// =====================================================================================
//
//       Filename:  union.cc
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年01月15日 15时19分14秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include <stdio.h>
#include <stdlib.h>

enum ShapeType
{
    Rectangle = 1,
    Circle = 2,
    Square = 3
};

struct Shape
{
    enum ShapeType kind;

    union {
        struct { int width; int height; } RectangleData;
        struct { int radius; } CircleData;
        struct { int side; } SquareData;
    } ShapeData;
};



double area(struct Shape *s)
{
    double area = 0.0;

    if (s->kind == Rectangle)
    {
        int width, ht;
        width = s->ShapeData.RectangleData.width;
        ht = s->ShapeData.RectangleData.height;
        area = width * ht;
    }
    else if (s->kind == Circle)
    {
        int r = s->ShapeData.CircleData.radius;
        area = 3.1415 * r * r;
    }
    else if (s->kind == Square)
    {
        int side = s->ShapeData.SquareData.side;
        area = side * side;
    }
    else
    {
        area = -1.0;
    }

    return area;
}

int main()
{
    printf("size of struct Shape: %u\n", sizeof(struct Shape));

    struct Shape *s = (struct Shape*)malloc(sizeof(struct Shape));
    s->kind = Rectangle;
    s->ShapeData.RectangleData.width = 3;
    s->ShapeData.RectangleData.height = 4;

    printf("area: %f\n", area(s));

    free(s);

    return 0;
}
