#ifndef VECTOR2D_H
#define VECTOR2D_H

#pragma once

class Vector2D
{
    public:
    float x;
    float y;

    Vector2D();
    Vector2D(int x, int y);

    friend Vector2D& operator+(Vector2D& v1,const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1,const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1,const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1,const Vector2D& v2);
    Vector2D& operator+=(const Vector2D& v);
    Vector2D& operator-=(const Vector2D& v);
    Vector2D& operator*=(const Vector2D& v);
    Vector2D& operator/=(const Vector2D& v);
    Vector2D& operator*(const int& i);
    Vector2D& reset();

};

#endif