#if !defined(POINT)
#define POINT
template<typename T>
struct Point
{
    T x,y;
    Point(){
        x=0;
        y=0;
    }

    Point(T x,T y){
        this->x=x;
        this->y=y;
    }
};
#endif