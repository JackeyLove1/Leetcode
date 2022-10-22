#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define N 1005
using namespace std;
 
struct Point2D //二维平面点
{
    double x,y;
    Point2D():x(0),y(0){}
    Point2D(double x,double y):x(x),y(y){}
    double Mod() const {return sqrt(x*x + y*y);}
    friend Point2D operator-(const Point2D& lh,const Point2D& rh){
        return Point2D(lh.x-rh.x, lh.y-rh.y);
    }
    friend double operator&(const Point2D& lh,const Point2D& rh){
        return lh.x*rh.y - lh.y*rh.x;
    } 
    friend std::istream& operator>>(std::istream& in, Point2D& pt){
        in>>pt.x>>pt.y;
        return in;
    }
}; 
 
struct Segment2D{
    Point2D bgn, end;
    Segment2D():bgn(),end(){}
    Segment2D(Point2D b,Point2D e):bgn(b),end(e){}
    Segment2D(double x1,double y1,double x2,double y2):bgn(x1,y1),end(x2,y2){}
    friend std::istream& operator>>(std::istream& in, Segment2D& pt){
        in>>pt.bgn>>pt.end;
        return in;
    }    
    friend std::ostream& operator<< (std::ostream& out, Segment2D& pt){
        out<<pt.bgn.x<<" "<<pt.bgn.y<<" "<<pt.end.x<<" "<<pt.end.y;
        return out;
    }
};
 
bool SegmentIntersect(const Segment2D& u, const Segment2D& v)
{
    //1.快速排斥试验,不相交返回0
    if((max(u.bgn.x,u.end.x)>=min(v.bgn.x,v.end.x))&&
       (max(v.bgn.x,v.end.x)>=min(u.bgn.x,u.end.x))&&
       (max(u.bgn.y,u.end.y)>=min(v.bgn.y,v.end.y))&&
       (max(v.bgn.y,v.end.y)>=min(u.bgn.y,u.end.y)));
    else return false;
    
    //2.跨立实验,u的两端点在v两侧，并且v的两端点在u两侧
    if((((u.bgn-v.bgn)&(v.end-v.bgn))*((v.end-v.bgn)&(u.end-v.bgn))>=0)&&
       (((v.bgn-u.bgn)&(u.end-u.bgn))*((u.end-u.bgn)&(v.end-u.bgn))>=0))
        return true;
    else return false;
}
 
Segment2D arr[N];
