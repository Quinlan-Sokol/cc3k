# ifndef _POINT_H_
# define _POINT_H_
#include <cmath>

class Point{
    int x;
    int y;
public:
    Point() noexcept: x{0}, y{0} {}
    Point(int x, int y) noexcept: x{x}, y{y} {}
    
    int getX() const{
        return x;
    }
    
    int getY() const{
        return y;
    }
    
    // calculates eulerian distance
    float distance(Point p){
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }
    
    Point operator+(const Point& p){
        return {x + p.x, y + p.y};
    }
    
    bool operator==(const Point& rhs) const{
        return (x == rhs.x) && (y == rhs.y);
    }
    
    bool operator<(const Point& rhs) const{
        return x < rhs.x;
    }
};

#endif
