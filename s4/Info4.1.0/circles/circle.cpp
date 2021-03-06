#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;
const long double EPS = 1e-18;

struct Circle {
  int x, y, r;
};


int main() {
  fstream in;
  in.open("circles.in", fstream::in);
  int n;
  in >> n;
  vector<Circle> cir;
  Circle cur;
  for(int i = 0; i < n; i++) {
    in >> cur.x >> cur.y >> cur.r;
    cir.push_back(cur);
    in >> cur.x >> cur.y >> cur.r;
    cir.push_back(cur);
  }
  fstream out;
  out.open("circles.out", fstream::out);
  out << setiosflags(ios::fixed) << setprecision(12);
  for(int i = 0; i < n; i++) {
    if(cir[i].x == cir[i + 1].x && cir[i].y == cir[i + 1].y)
      if(cir[i].r == cir[i + 1].r) out << "I cant''t count them - too many points :(";
      else out << "There are no points!!!";
    else {
      long double r = cir[i + 1].r, a = -2 * cir[i + 1].x, b = -2 * cir[i + 1].y, c = pow(cir[i + 1].x, 2.0) + pow(cir[i + 1].y, 2.0) + pow(cir[i].r, 2.0) - pow(cir[i + 1].r, 2.0);
      long double x0 = -a * c / (a * a + b * b),  y0 = -b * c / (a * a + b * b);
      if (c * c > r * r * (a * a + b * b) + EPS)
        out << "There are no points!!!";
      else if (abs (c * c - r * r * (a * a + b * b)) < EPS) {
        out << "There are only 1 of them...." << endl;
        if(x0 < EPS) x0 = 0.0;
        if(y0 < EPS) y0 = 0.0;
        out << x0 << ' ' << y0 << '\n';
      } else {
        long double d = r * r - c * c / (a * a + b * b);
        long double mult = sqrt (d / (a * a + b * b));
        long double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        if(ax < EPS) ax = 0.0;
        if(ay < EPS) ay = 0.0;
        if(bx < EPS) bx = 0.0;
        if(by < EPS) by = 0.0;
        out << "There are only 2 of them...." << endl;
        if(ax - bx < EPS) {
          if(ay < by) out << ax << ' ' << ay << '\n' << bx << ' ' << by << '\n';
          else out << bx << ' ' << by << '\n' << ax << ' ' << ay << '\n';
        } else if(ax < bx) out << ax << ' ' << ay << '\n' << bx << ' ' << by << '\n';
        else out << bx << ' ' << by << '\n' << ax << ' ' << ay << '\n';
      }
    }
  }
  return 0;
}
