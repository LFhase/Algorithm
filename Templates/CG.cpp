#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <stack>
#include <bitset>

using namespace std;

#define FSIO  ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define DEBUG(a)   cout<<"DEBUG: "<<(a)<<endl;
#define ll long long
#define pb push_back

const int MAXN = 1505;
const int MOD = 998244353;
const int INF = 1e9+7;

int _;

using namespace std;


const double CGINF = 1e20;
const double EPS = 1e-8;
const double PI = acos(-1.0);

int sgn(double x)
{
    if(fabs(x) < EPS) return 0;
    if(x < 0) return -1;
    return 1;
}

struct Point{
    double x, y;
    Point(){};
    Point(double _x, double _y): x(_x), y(_y){}

    void read(){
        scanf("%lf%lf",&x,&y);
    }

    void output(){
        printf("%.2f %.2f\n",x,y);
    }

    bool operator == (Point& b) const{
        return (sgn(x-b.x) == 0) && (sgn(y-b.y) == 0);
    }

    bool operator < (Point& b) const{
        return sgn(x-b.x)==0?sgn(y-b.y)<0:x<b.x;
    }

    Point operator + (Point b) const{
        return Point(x+b.x, y+b.y);
    }

    Point operator - (const Point& b) const{
        return Point(x-b.x, y-b.y);
    }
    // cross product
    double operator ^ (const Point& b) const{
        return x*b.y - y*b.x;
    }
    // point prodct
    double operator * (const Point& b) const{
        return x*b.x + y*b.y;
    }

    double len(){
        return hypot(x, y);
    }

    double len2(){
        return x*x + y*y;
    }

    double dis(Point & b){
        return hypot(x-b.x, y-b.y);
    }



    double dis2(Point & b){
        return (x-b.x)*(x-b.x)+(y-b.y)*(y-b.y);
    }

    Point operator * (const double& k) const{
        return Point(x*k, y*k);
    }

    Point operator / (const double& k) const{
        return Point(x/k, y/k);
    }
    // get the rad of ∠aOb
    double rad(Point a, Point b){
        Point p = *this;
        return fabs(atan2(fabs((a-p)^(b-p)), (a-p)*(b-p)));
    }
    // change into a vector with len r
    Point trunc(double r){
        double l = len();
        if(!sgn(l)) return *this;
        r /= l;
        return Point(x*r,y*r);
    }

    // rotate 90 counter-clockwise
    Point cc_rotate(){
        return Point(-y, x);
    }
    // rotate 90 clockwise
    Point c_rotate(){
        return Point(y, -x);
    }

    // counter-clock rotate angle around p
    Point rotate(Point p, double angle){
        Point v = (*this)-p;
        double c = cos(angle), s = sin(angle);
        return Point(p.x+v.x*c-v.y*s, p.y+v.x*s+v.y*c);
    }
};

struct Line{
    Point s, e;
    Line(){}
    Line(Point _s, Point _e): s(_s), e(_e){}
    Line(double x1, double y1, double x2, double y2){
        s = Point(x1,y1);
        e = Point(x2,y2);
    }

    Line(Point p, double angle){
        s = p;
        if(sgn(angle - PI/2) == 0){
            e = (s + Point(1,0));
        }else{
            e = (s + Point(1, tan(angle)));
        }
    }

    Line(double a, double b, double c){
        if(sgn(a)==0){
            s = Point(0,-c/b);
            e = Point(1,-c/b);
        }
        else if(sgn(b)==0){
            s = Point(-c/a,0);
            e = Point(-c/a,1);
        }else{
            s = Point(0,c/b);
            e = Point(1,(-c-a)/b);
        }
    }

    void read(){
        s.read();
        e.read();
    }
    void output(){
        s.output();
        e.output();
    }

    bool operator == (Line& v) const{
        return (s == v.s)&&(e == v.e);
    }

    double length(){
        return s.dis(e);
    }

    double angle(){
        double k = atan2(e.y-s.y,e.x-s.x);
        if(sgn(k)<0)    k+=PI;
        if(sgn(k-PI)==0)    k-=PI;
        return k;
    }



    // 1 left, 2 right, 3 on line
    int relation(Point p){
        int c = sgn((p-s)^(e-s));
        if(c < 0) return 1;
        else if(c > 0) return 2;
        return 3;
    }

    // to judge if the point is on the segment
    bool point_onseg(Point p){
        return sgn((p-s)^(e-s))==0&&sgn((p-s)*(p-e))<=0;
    }

    bool parrallel(Line v){
        return sgn((e-s)^(v.e-v.s))==0;
    }

    // 2: intersect more than 1 point
    // 1: intersect on 1 point
    // 0: miss
    int seg_cross_seg(Line v){
        int d1 = sgn((e-s)^(v.s-s));
        int d2 = sgn((e-s)^(v.e-s));
        int d3 = sgn((v.e-v.s)^(s-v.s));
        int d4 = sgn((v.e-v.s)^(e-v.s));

        if((d1^d2) == -2 && ((d3^d4) == -2)) return 2;
        return (d1==0 && sgn((v.s-s)*(v.s-e)) <= 0) ||
            (d2 == 0 && sgn((v.e-s)*(v.e-e)) <= 0) ||
            (d3 == 0 && sgn((s-v.s)*(s-v.e)) <= 0) ||
            (d4 == 0 && sgn((e-v.s)*(e-v.e)) <= 0);
    }

    int line_cross_seg(Line v){
        int d1 = sgn((e-s)^(v.s-s));
        int d2 = sgn((e-s)^(v.e-s));
        if((d1^d2)==-2) return 2;
        return (d1==0||d2==0);
    }

    int line_cross_line(Line v){
        if(parrallel(v)){
            return v.relation(s) == 3;
        }
        return 2;
    }

    // get cross point
    Point cross_point(Line v){
        double a1 = (v.e-v.s)^(s-v.s);
        double a2 = (v.e-v.s)^(e-v.s);
        return Point((s.x*a2-e.x*a1)/(a2-a1), (s.y*a2-e.y*a1)/(a2-a1));
    }

    double dis_p2l(Point p){
        return fabs((p-s)^(e-s))/length();
    }

    double dis_p2seg(Point p){
        if(sgn((p-s)*(e-s))<0||sgn((p-e)*(s-e))<0)
            return min(p.dis(s),p.dis(e));
        return dis_p2l(p);
    }

    double dis_seg2seg(Line v){
        return min(min(dis_p2seg(v.s),dis_p2seg(v.e)),
                   min(v.dis_p2seg(s),v.dis_p2seg(e)));
    }

    Point lineprog(Point p){
        return s+(((e-s)*((e-s)*(p-s)))/((e-s).len2()));
    }

    Point symmetry_point(Point p){
        Point q = lineprog(p);
        return Point(2*q.x-p.x,2*q.y-p.y);
    }
};

struct circle
{
    Point p;
    double r;
    circle() {}
    circle(Point _p, double _r)
    {
        p = _p;
        r = _r;
    }
    circle(double x, double y, double _r)
    {
        p = Point(x, y);
        r = _r;
    }

    // circle inside traingle
    circle(Point a, Point b, Point c)
    {
        Line u = Line((a + b) / 2, ((a + b) / 2) + ((b-a).cc_rotate()));
        Line v = Line((b + c) / 2, ((b + c) / 2) + ((c-b).cc_rotate()));
        p = u.cross_point(v);
        r = p.dis(a);
    }

    // circle outside traingle
    circle(Point a, Point b, Point c, bool t)
    {
        Line u, v;
        double m = atan2(b.y-a.y, b.x-a.x), n = atan2(c.y-a.y, c.x-a.x);
        u.s = a;
        u.e = u.s + Point(cos((n + m) / 2), sin((n + m) / 2));
        v.s = b;
        m = atan2(a.y-b.y, a.x-b.x), n = atan2(c.y-b.y, c.x-b.x);
        v.e = v.s + Point(cos((n + m) / 2), sin((n + m) / 2));
        p = u.cross_point(v);
        r = Line(a, b).dis_p2seg(p);
    }

    void read()
    {
        p.read();
        scanf("%lf", &r);
    }

    void output()
    {
        printf("%.2f%.2f%.2f\n", p.x, p.y, r);
    }

    bool operator==(circle v)
    {
        return (p == v.p) && sgn(r-v.r) == 0;
    }
    bool operator<(circle v) const
    {
        return ((p < v.p) || ((p == v.p) && sgn(r-v.r) < 0));
    }

    double get_area()
    {
        return PI * r * r;
    }

    double get_circumference()
    {
        return 2 * PI * r;
    }

    // 0: out of the circle
    // 1: on the circle
    // 2: inside
    int relation_point(Point b)
    {
        double dst = b.dis(p);
        if (sgn(dst-r) < 0)
            return 2;
        else if (sgn(dst-r) == 0)
            return 1;
        return 0;
    }


    int relation_seg(Line v)
    {
        double dst = v.dis_p2seg(p);
        if (sgn(dst-r) < 0)
            return 2;
        else if (sgn(dst-r) == 0)
            return 1;
        return 0;
    }

    int relation_line(Line v)
    {
        double dst = v.dis_p2l(p);
        if (sgn(dst-r) < 0)
            return 2;
        else if (sgn(dst-r) == 0)
            return 1;
        return 0;
    }


    int relation_circle(circle v)
    {
        double d = p.dis(v.p);
        if (sgn(d-r-v.r) > 0)
            return 5;
        if (sgn(d-r-v.r) == 0)
            return 4;
        double l = fabs(r-v.r);
        if (sgn(d-r-v.r) < 0 && sgn(d-l) > 0)
            return 3;
        if (sgn(d-l) == 0)
            return 2;
        if (sgn(d-l) < 0)
            return 1;
    }


    int cross_point(circle v, Point &p1, Point &p2)
    {
        int rel = relation_circle(v);
        if (rel == 1 || rel == 5)
            return 0;
        double d = p.dis(v.p);
        double l = (d * d + r * r-v.r * v.r) / (2 * d);
        double h = sqrt(r * r-l * l);
        Point tmp = p + (v.p-p).trunc(l);
        p1 = tmp + ((v.p-p).cc_rotate().trunc(h));
        p2 = tmp + ((v.p-p).c_rotate().trunc(h));
        if (rel == 2 || rel == 4)
            return 1;
        return 2;
    }


    int cross_point(Line v, Point &p1, Point &p2)
    {
        if (!(*this).relation_line(v))
            return 0;
        Point a = v.lineprog(p);
        double d = v.dis_p2l(p);
        d = sqrt(r * r-d * d);
        if (sgn(d) == 0)
        {
            p1 = a;
            p2 = a;
            return 1;
        }
        p1 = a + (v.e-v.s).trunc(d);
        p2 = a - (v.e-v.s).trunc(d);
        return 2;
    }


    int ger_circle(Point a, Point b, double r1, circle &c1, circle &c2)
    {
        circle x(a, r1), y(b, r1);
        int t = x.cross_point(y, c1.p, c2.p);
        if (!t)
            return 0;
        c1.r = c2.r = r;
        return t;
    }


    int get_circle(Line u, Point q, double r1, circle &c1, circle &c2)
    {
        double dis = u.dis_p2l(q);
        if (sgn(dis-r1 * 2) > 0)
            return 0;
        if (sgn(dis) == 0)
        {
            c1.p = q + ((u.e-u.s).cc_rotate().trunc(r1));
            c2.p = q + ((u.e-u.s).c_rotate().trunc(r1));
            c1.r = c2.r = r1;
            return 2;
        }
        Line u1 = Line((u.s + (u.e-u.s).cc_rotate().trunc(r1)), (u.e + (u.e-u.s).cc_rotate().trunc(r1)));
        Line u2 = Line((u.s + (u.e-u.s).c_rotate().trunc(r1)), (u.e + (u.e-u.s).c_rotate().trunc(r1)));
        circle cc = circle(q, r1);
        Point p1, p2;
        if (!cc.cross_point(u1, p1, p2))
            cc.cross_point(u2, p1, p2);
        c1 = circle(p1, r1);
        if (p1 == p2)
        {
            c2 = c1;
            return 1;
        }
        c2 = circle(p2, r1);
        return 2;
    }


    int get_circle(Line u, Line v, double r1, circle &c1, circle &c2, circle &c3, circle &c4)
    {
        if (u.parrallel(v))  return 0;
        Line u1 = Line(u.s + (u.e-u.s).cc_rotate().trunc(r1), u.e + (u.e-u.s).cc_rotate().trunc(r1));
        Line u2 = Line(u.s + (u.e-u.s).c_rotate().trunc(r1), u.e + (u.e-u.s).c_rotate().trunc(r1));
        Line v1 = Line(v.s + (v.e-v.s).cc_rotate().trunc(r1), v.e + (v.e-v.s).cc_rotate().trunc(r1));
        Line v2 = Line(v.s + (v.e-v.s).c_rotate().trunc(r1), v.e + (v.e-v.s).c_rotate().trunc(r1));
        c1.r = c2.r = c3.r = c4.r = r1;
        c1.p = u1.cross_point(v1);
        c2.p = u1.cross_point(v2);
        c3.p = u2.cross_point(v1);
        c4.p = u2.cross_point(v2);
        return 4;
    }

    //同时与不相交圆 cx,cy 相切，半径为 r1 的圆
    //测试：UVA12304
    int getcircle(circle cx,circle cy,double r1,circle &c1,circle &c2){
        circle x(cx.p,r1+cx.r), y(cy.p,r1+cy.r);
        int t = x.cross_point(y,c1.p,c2.p);
        if(!t)  return 0;
        c1.r = c2.r = r1;
        return t;
    }

    //过一点作圆的切线 (先判断点和圆的关系)
    //测试：UVA12304
    int tangent_line(Point q, Line &u, Line &v)
    {
        int x = relation_point(q);
        if (x == 2)
            return 0;
        if (x == 1)
        {
            u = Line(q, q + (q-p).cc_rotate());
            v = u;
            return 1;
        }
        double d = p.dis(q);
        double l = r * r / d;
        double h = sqrt(r * r-l * l);
        u = Line(q, p + ((q-p).trunc(l) + (q-p).cc_rotate().trunc(h)));
        v = Line(q, p + ((q-p).trunc(l) + (q-p).c_rotate().trunc(h)));
        return 2;
    }


    double area_c2c(circle v)
    {
        int rel = relation_circle(v);
        if (rel >= 4)
            return 0.0;
        if (rel <= 2)
            return min(get_area(), v.get_area());
        double d = p.dis(v.p);
        double hf = (r + v.r + d) / 2.0;
        double ss = 2 * sqrt(hf * (hf-r) * (hf-v.r) * (hf-d));
        double a1 = acos((r * r + d * d-v.r * v.r) / (2.0 * r * d));
        a1 = a1 * r * r;
        double a2 = acos((v.r * v.r + d * d-r * r) / (2.0 * v.r * d));
        a2 = a2 * v.r * v.r;
        return a1 + a2-ss;
    }


    double area_c2t(Point a, Point b)
    {
        if (sgn((p-a) ^ (p-b)) == 0)
            return 0.0;
        Point q[5];
        int len = 0;
        q[len++] = a;
        Line l(a, b);
        Point p1, p2;
        if (cross_point(l, q[1], q[2]) == 2)
        {
            if (sgn((a-q[1]) * (b-q[1])) < 0)
                q[len++] = q[1];
            if (sgn((a-q[2]) * (b-q[2])) < 0)
                q[len++] = q[2];
        }
        q[len++] = b;
        if (len == 4 && sgn((q[0]-q[1]) * (q[2]-q[1])) > 0)
            swap(q[1], q[2]);
        double res = 0;
        for (int i = 0; i < len-1; i++)
        {
            if (relation_point(q[i]) == 0 || relation_point(q[i + 1]) == 0)
            {
                double arg = p.rad(q[i], q[i + 1]);
                res += r * r * arg / 2.0;
            }
            else
            {
                res += fabs((q[i]-p) ^ (q[i + 1]-p)) / 2.0;
            }
        }
        return res;
    }
};



bool operator<(const Point& a, const Point& b)
{
    return sgn(a.x-b.x)==0?sgn(a.y-b.y)<0:a.x<b.x;
}

struct polygon{
    int n;
    Point p[MAXN];
    Line l[MAXN];
    void read_point(int _n){
        n = _n;
        for(int i = 0;i < n;i++)
            p[i].read();
    }
    void add_point(Point q){
        p[n++] = q;
    }
    void add_point(double x1, double y1){
        p[n++] = Point(x1,y1);
    }
    void get_line(){
        for(int i=0;i<n;++i)
            l[i] = Line(p[i],p[(i+1)%n]);
    }
    struct cmp{
        Point p;
        cmp(const Point& p0)    {p=p0;}
        bool operator()(const Point &aa,const Point &bb){
             Point a = aa, b = bb;
             int d = sgn((a-p)^(b-p));
             if(d == 0) return sgn(a.dis(p)-b.dis(p)) < 0;
             return d > 0;
        }
    };
    void norm(){
        Point mi = p[0];
        for(int i = 1;i < n;i++)
            mi = min(mi,p[i]);
        sort(p,p+n,cmp(mi));
    }
    polygon get_convex(){
        polygon convex;
        sort(p,p+n);
        convex.n = n;
        for(int i=0;i<min(n,2);++i)   convex.p[i]=p[i];
        if(convex.n == 2 && (convex.p[1] == convex.p[0]))   convex.n--;
        if(n <= 2)  return convex;
        int &top = convex.n;
        top = 1;
        for(int i = 2;i < n;i++)
        {
            while(top&&sgn((convex.p[top]-p[i])^(convex.p[top-1]-p[i]))>=0)
                top--;
            convex.p[++top] = p[i];
        }
        int temp = top;
        convex.p[++top] = p[n-2];
        for(int i=n-3;i>=0;--i)
        {
            while(top!=temp&&sgn((convex.p[top]-p[i])^(convex.p[top-1]-p[i]))>=0)
                top--;
            convex.p[++top] = p[i];
        }
        if(convex.n==2&&(convex.p[0]==convex.p[1])) convex.n--;
        convex.norm();
        return convex;
    }
    // may some problems
    polygon gramham(){
        norm();
        polygon convex;
        int& top = convex.n;
        top = 0;
        if(n==1){
            top = 1;
            convex.p[0] = p[0];
            return convex;
        }
        else if(n==2){
            top = 2;
            convex.p[0] = p[0];
            convex.p[1] = p[1];
            if(convex.p[0]==convex.p[1])    top--;
            return convex;
        }
        top = 2;
        convex.p[0] = p[0];
        convex.p[1] = p[1];
        for(int i=2;i<n;++i)
        {
            while(top>1&&sgn((convex.p[top-1]-convex.p[top-2])^(convex.p[i]-convex.p[top-2]))<=0)
                top--;
            convex.p[top++] = p[i];
        }
        if(convex.n==2&&(convex.p[0]==convex.p[1])) convex.n--;
        return convex;
    }
    double get_circumference(){
        double sum = 0;
        for(int i=0;i<n;++i)
            sum+=p[i].dis(p[(i+1)%n]);
        return sum;
    }
    void output(){
        for(int i=0;i<n;++i)
            p[i].output();
    }
    bool isconvex(){
        bool s[2];
        memset(s,0,sizeof(s));
        for(int i=0;i<n;++i)
        {
            int j = (i+1)%n;
            int k = (j+1)%n;
            s[sgn((p[j]-p[i])^(p[k]-p[i]))+1] = 1;
            if(s[0]&&s[2])  return 0;
        }
        return 1;
    }
    double get_area(){
        double sum = 0;
        for(int i=0;i<n;++i)
        {
            sum += (p[i]^p[(i+1)%n]);
        }
        return fabs(sum)/2.0;
    }
    // 3: on a point
    // 2: on a seg
    // 1: in the polygon
    // 0: out of the polygon
    int relation_point(Point q){
        for(int i=0;i<n;++i)
            if(p[i]==q) return 3;
        get_line();
        for(int i=0;i<n;++i)
            if(l[i].point_onseg(q)) return 2;
        int cnt = 0;
        for(int i=0;i<n;++i)
        {
            int j = (i+1)%n;
            int k = sgn((q-p[j])^(p[i]-p[j]));
            int u = sgn(p[i].y-q.y);
            int v = sgn(p[j].y-q.y);
            if(k>0&&u<0&&v>=0)  cnt++;
            if(k<0&&v<0&&u>=0)  cnt--;
        }
        return (cnt!=0);
    }

    // get the furthest pair using rotating calipers
    double furthest_pair(){
        double ans = 0;
        for(int i=0, j=1;i<n;++i)
        {
            while(fabs((p[i]-p[(i+1)%n])^(p[i]-p[(j+1)%n]))>
                  fabs((p[i]-p[(i+1)%n])^(p[i]-p[j])))
                    j = (j+1)%n;
            ans = max(ans,p[i].dis2(p[j]));
        }
        return ans;
    }
    // get the area of largest triangle using rotating calipers
    double largest_triangle(){
        double ans = 0;
        for(int i=0;i<n;++i)
        {
            int j =(i+1)%n;
            int k =(j+1)%n;
            while(j!=i&&k!=i)
            {
                ans = max(ans,(p[i]-p[k])^(p[j]-p[k]));
                while(((p[i]-p[j])^(p[(k+1)%n]-p[k]))<0)
                    k = (k+1)%n;
                j = (j+1)%n;
            }
        }
        return ans;
    }

    double area_circle(circle c){
        double ans = 0;
        for(int i=0;i<n;++i)
        {
            int j =(i+1)%n;
            if(sgn((p[j]-c.p)^(p[i]-c.p))>=0)
                ans += c.area_c2t(p[i],p[j]);
            else    ans -= c.area_c2t(p[i],p[j]);
        }
        return fabs(ans);
    }
};

struct halfplane:public Line{
    double angle;
    halfplane(){}
    halfplane(Point _s, Point _e){
        s = _s;
        e = _e;
    }
    halfplane(Line v){
        s = v.s;
        e = v.e;
    }
    void calangle(){
        angle = atan2(e.y-s.y,e.x-s.x);
    }
    bool operator<(const halfplane& b)const{
        return angle<b.angle;
    }
};

struct halfplanes{
    int n;
    halfplane hp[MAXN];
    Point p[MAXN];
    int que[MAXN];
    int st, ed;
    // add edge in reversed order
    void push(halfplane tmp){
        hp[n++] = tmp;
    }
    void unique(){
        int m = 1;
        for(int i=1;i<n;++i)
        {
            if(sgn(hp[i].angle-hp[i-1].angle)!=0)   hp[m++]=hp[i];
            else if(sgn((hp[m-1].e-hp[m-1].s)^(hp[i].s-hp[m-1].s))>0)
                hp[m-1] = hp[i];
        }
        n = m;
    }

    bool halfplaneinsert(){
        for(int i = 0;i < n;i++)hp[i].calangle();
        sort(hp,hp+n);
        unique();
        que[st=0] = 0;
        que[ed=1] = 1;
        p[1] = hp[0].cross_point(hp[1]);
        for(int i = 2;i < n;i++)
        {
            while(st<ed && sgn((hp[i].e-hp[i].s)^(p[ed]-hp[i].s))<0)
                ed--;
            while(st<ed && sgn((hp[i].e-hp[i].s)^(p[st+1]-hp[i].s))<0)
                st++;
            que[++ed] = i;
            if(hp[i].parrallel(hp[que[ed-1]]))  return 0;
            p[ed] = hp[i].cross_point(hp[que[ed-1]]);
        }
        while(st<ed && sgn((hp[que[st]].e-hp[que[st]].s)^(p[ed]-hp[que[st]].s))<0)
            ed--;
        while(st<ed && sgn((hp[que[ed]].e-hp[que[ed]].s)^(p[st+1]-hp[que[ed]].s))<0)
            st++;
        if(st+1>=ed)    return 0;
        return 1;
    }

    void get_convex(polygon& con){
        p[st] = hp[que[st]].cross_point(hp[que[ed]]);
        con.n = ed-st+1;
        for(int j=st,i=0;j<=ed;++j,++i)
            con.p[i] = p[j];
    }
};



// 3-D CG
const double CGINF = 1e20;
const double EPS = 1e-8;
const double PI = acos(-1.0);

int sgn(double x)
{
    if(fabs(x) < EPS) return 0;
    if(x < 0) return -1;
    return 1;
}


struct Point3
{
    double x, y, z;
    Point3(double _x = 0, double _y = 0, double _z = 0){
        x = _x;
        y = _y;
        z = _z;
    }
    void read(){
        scanf("%lf%lf%lf", &x, &y, &z);
    }
    bool operator==(const Point3 &b) const{
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0 && sgn(z - b.z) == 0;
    }
    double len(){
        return sqrt(x * x + y * y + z * z);
    }
    double len2(){
        return x * x + y * y + z * z;
    }
    double distance(const Point3 &b) const{
        return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) + (z - b.z) * (z - b.z));
    }
    Point3 operator-(const Point3 &b) const{
        return Point3(x - b.x, y - b.y, z - b.z);
    }
    Point3 operator+(const Point3 &b) const{
        return Point3(x + b.x, y + b.y, z + b.z);
    }
    Point3 operator*(const double &k) const{
        return Point3(x * k, y * k, z * k);
    }
    Point3 operator/(const double &k) const{
        return Point3(x / k, y / k, z / k);
    }
    double operator*(const Point3 &b) const{
        return x * b.x + y * b.y + z * b.z;
    }
    Point3 operator^(const Point3 &b) const{
        return Point3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
};


struct CH3D
{
    struct face{
        int a, b, c;
        bool ok;
    };
    int n;
    Point3 P[MAXN];
    int num;
    face F[MAXN<<3];
    int g[MAXN][MAXN];

    Point3 cross(const Point3 &a, const Point3 &b, const Point3 &c){
        return (b - a) ^ (c - a);
    }

    double area(Point3 a, Point3 b, Point3 c){
        return ((b - a) ^ (c - a)).len();
    }

    double volume(Point3 a, Point3 b, Point3 c, Point3 d){
        return ((b - a) ^ (c - a)) * (d - a);
    }

    double dblcmp(Point3 &p, face &f){
        Point3 p1 = P[f.b] - P[f.a];
        Point3 p2 = P[f.c] - P[f.a];
        Point3 p3 = p - P[f.a];
        return (p1 ^ p2) * p3;
    }
    void deal(int p, int a, int b){
        int f = g[a][b];
        face add;
        if (F[f].ok)
        {
            if (dblcmp(P[p], F[f]) > EPS)   dfs(p, f);
            else
            {
                add.a = b;
                add.b = a;
                add.c = p;
                add.ok = true;
                g[p][b] = g[a][p] = g[b][a] = num;
                F[num++] = add;
            }
        }
    }

    void dfs(int p, int now){
        F[now].ok = false;
        deal(p, F[now].b, F[now].a);
        deal(p, F[now].c, F[now].b);
        deal(p, F[now].a, F[now].c);
    }
    bool same(int s, int t){
        Point3 &a = P[F[s].a];
        Point3 &b = P[F[s].b];
        Point3 &c = P[F[s].c];
        return fabs(volume(a, b, c, P[F[t].a])) < EPS &&
               fabs(volume(a, b, c, P[F[t].b])) < EPS &&
               fabs(volume(a, b, c, P[F[t].c])) < EPS;
    }

    void create(){
        num = 0;
        face add;

        bool flag = true;
        for (int i = 1; i < n; i++)
        {
            if (!(P[0] == P[i]))
            {
                swap(P[1], P[i]);
                flag = false;
                break;
            }
        }
        if (flag)   return;
        flag = true;
        for (int i = 2; i < n; i++)
        {
            if (((P[1] - P[0]) ^ (P[i] - P[0])).len() > EPS)
            {
                swap(P[2], P[i]);
                flag = false;
                break;
            }
        }
        if (flag)
            return;
        flag = true;
        for (int i = 3; i < n; i++)
            if (fabs(((P[1] - P[0]) ^ (P[2] - P[0])) * (P[i] - P[0])) > EPS)
            {
                swap(P[3], P[i]);
                flag = false;
                break;
            }
        if (flag)   return;

        for (int i = 0; i < 4; i++)
        {
            add.a = (i + 1) % 4;
            add.b = (i + 2) % 4;
            add.c = (i + 3) % 4;
            add.ok = true;
            if (dblcmp(P[i], add) > 0)
                swap(add.b, add.c);
            g[add.a][add.b] = g[add.b][add.c] = g[add.c][add.a] = num;
            F[num++] = add;
        }
        for (int i = 4; i < n; i++)
            for (int j = 0; j < num; j++)
                if (F[j].ok && dblcmp(P[i], F[j]) > EPS)
                {
                    dfs(i, j);
                    break;
                }
        int tmp = num;
        num = 0;
        for (int i = 0; i < tmp; i++)
            if (F[i].ok)
                F[num++] = F[i];
    }

    double area(){
        double res = 0;
        if (n == 3)
        {
            Point3 p = cross(P[0], P[1], P[2]);
            return p.len() / 2;
        }
        for (int i = 0; i < num; i++)
            res += area(P[F[i].a], P[F[i].b], P[F[i].c]);
        return res / 2.0;
    }
    double volume(){
        double res = 0;
        Point3 tmp = Point3(0, 0, 0);
        for (int i = 0; i < num; i++)
            res += volume(tmp, P[F[i].a], P[F[i].b], P[F[i].c]);
        return fabs(res / 6);
    }

    // the no of triangles in the surface
    int triangle(){
        return num;
    }
    // the no of polygons in the surface
    int polygon(){
        int res = 0;
        for (int i = 0; i < num; i++)
        {
            bool flag = true;
            for (int j = 0; j < i; j++)
                if (same(i, j))
                {
                    flag = 0;
                    break;
                }
            res += flag;
        }
        return res;
    }

    Point3 barycenter(){
        Point3 ans = Point3(0, 0, 0);
        Point3 o = Point3(0, 0, 0);
        double all = 0;
        for (int i = 0; i < num; i++)
        {
            double vol = volume(o, P[F[i].a], P[F[i].b], P[F[i].c]);
            ans = ans + (((o + P[F[i].a] + P[F[i].b] + P[F[i].c]) / 4.0) * vol);
            all += vol;
        }
        ans = ans / all;
        return ans;
    }

    double dis_p2face(Point3 p, int i){
        double tmp1 = fabs(volume(P[F[i].a], P[F[i].b], P[F[i].c], p));
        double tmp2 = ((P[F[i].b] - P[F[i].a]) ^ (P[F[i].c] - P[F[i].a])).len();
        return tmp1 / tmp2;
    }
};

CH3D hull;

int main()
{
    int N;
    while(scanf("%d",&N)!=EOF)
    {
        hull.n = N;
        for(int i=0; i<N; ++i)    hull.P[i].read();
        hull.create();
        printf("%d\n", hull.polygon());
    }
    return 0;
}



// 最小圆覆盖 POJ1981
const double CGINF = 1e20;
const double EPS = 1e-8;
const double PI = acos(-1.0);

int sgn(double x)
{
    if(fabs(x) < EPS) return 0;
    if(x < 0) return -1;
    return 1;
}

struct Point{
    double x, y;
    Point(){};
    Point(double _x, double _y): x(_x), y(_y){}

    void read(){
        scanf("%lf%lf",&x,&y);
    }

    void output(){
        printf("%.2f %.2f\n",x,y);
    }

    bool operator == (Point& b) const{
        return (sgn(x-b.x) == 0) && (sgn(y-b.y) == 0);
    }

    bool operator < (Point& b) const{
        return sgn(x-b.x)==0?sgn(y-b.y)<0:x<b.x;
    }

    Point operator + (Point b) const{
        return Point(x+b.x, y+b.y);
    }

    Point operator - (const Point& b) const{
        return Point(x-b.x, y-b.y);
    }
    // cross product
    double operator ^ (const Point& b) const{
        return x*b.y - y*b.x;
    }
    // point prodct
    double operator * (const Point& b) const{
        return x*b.x + y*b.y;
    }

    double len(){
        return hypot(x, y);
    }

    double len2(){
        return x*x + y*y;
    }

    double dis(Point & b){
        return hypot(x-b.x, y-b.y);
    }
};


struct PolarAngle
{
	double angle;
	bool flag;
} pa[MAXN];

bool operator<(const PolarAngle &a, const PolarAngle &other)
{
    return a.angle < other.angle;
}

Point pp[MAXN];
int N;


int solve(double r)
{
    int res = 1;
    REP(i,1,N)
    {
        int m = 0;
        double dd;
        REP(j,1,N)
        {
            dd=pp[i].dis(pp[j]);
            if(i!=j&&dd<=2.0*r)
            {
                double phi = acos(dd/(2.0*r));
                double theta = atan2(pp[j].y-pp[i].y,pp[j].x-pp[i].x);
                if(theta<0) theta+=2*PI;
                pa[++m].angle = theta - phi+2*PI;
                pa[m].flag = 1;
                pa[++m].angle = theta + phi+2*PI;
                pa[m].flag = 0;
            }
        }
        sort(pa+1,pa+m+1);
        for(int sum=1,j=1;j<=m;++j)
        {
            if(pa[j].flag)  ++sum;
            else    --sum;
            res = max(res,sum);
        }
    }
    return res;
}

int main()
{
    //freopen("test.in","r",stdin);
    //freopen("test.in","w+",stdout);
    while(scanf("%d",&N)!=EOF&&N)
    {
        REP(i,1,N)  pp[i].read();
        printf("%d\n",solve(1.0));
    }
    return 0;
}



