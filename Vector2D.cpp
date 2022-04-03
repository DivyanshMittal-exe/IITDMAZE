#include "Vector2D.h"

Vector2D::Vector2D()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2D::Vector2D(int xpos, int ypos){
    x = xpos;
    y = ypos;
}

    Vector2D& operator+(Vector2D& v1,const Vector2D& v2){
        v1.x = v1.x + v2.x;
        v1.y = v1.y + v2.y;
        return v1;
    }
    Vector2D& operator-(Vector2D& v1,const Vector2D& v2){
        v1.x = v1.x - v2.x;
        v1.y = v1.y - v2.y;

        return v1;
    }
    Vector2D& operator*(Vector2D& v1,const Vector2D& v2){
        v1.x = v1.x * v2.x;
        v1.y = v1.y * v2.y;

        return v1;
    }
    Vector2D& operator/(Vector2D& v1,const Vector2D& v2){
        v1.x = v1.x / v2.x;
        v1.y = v1.y / v2.y;
        return v1;
    }
    Vector2D& Vector2D::operator+=(const Vector2D& v){
        this->x = this->x + v.x;
        this->y = this->y + v.y;
        return *this;
    }
    Vector2D& Vector2D::operator-=(const Vector2D& v){
        this->x = this->x - v.x;
        this->y = this->y - v.y;
        return *this;
    }
    Vector2D& Vector2D::operator*=(const Vector2D& v){
        this->x = this->x * v.x;
        this->y = this->y * v.y;
        return *this;
    }
    Vector2D& Vector2D::operator/=(const Vector2D& v){
        this->x = this->x / v.x;
        this->y = this->y / v.y;
        return *this;
    }