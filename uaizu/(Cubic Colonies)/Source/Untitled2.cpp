#include <stdio.h>
#include <math.h>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

struct point{
  int x, y, z;
  point(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
  bool operator< (const point& rhs) const {
    return false;
  }
};

const int dv = 18;
const int sd = 420;

int b[5][5][5];
int dvs[dv + 1] = {0, 60, 70, 84, 105, 120, 140, 168, 180, 210, 240, 252, 280, 300, 315, 336, 350, 360};
int rot[dv * 4 + 1][2];

int xtov[dv * 3 + 1];

vector<point> ed[dv * 3 + 1][dv * 3 + 1][dv * 3 + 1];
priority_queue< pair<double, point> > pq;
bool vis[dv * 3 + 1][dv * 3 + 1][dv * 3 + 1];

double dist(int xa, int ya, int za, int xb, int yb, int zb){
  int dx = xa - xb, dy = ya - yb, dz = za - zb;
  double d = sqrt(dx * dx + dy * dy + dz * dz);
  return d;
}

int main(){
  int i, j, k;
  for(i = 0; i <= dv * 3 + 1; i++){
    if(i < dv) xtov[i] = dvs[i];
    else xtov[i] = xtov[i - dv] + sd;
  }
  for(i = 0; i < dv; i++){
    rot[i][0] = i;
    rot[i][1] = 0;
    rot[dv + i][0] = dv;
    rot[dv + i][1] = i;
    rot[2 * dv + i][0] = dv - i;
    rot[2 * dv + i][1] = dv;
    rot[3 * dv + i][0] = 0;
    rot[3 * dv + i][1] = dv - i;
  }

  for(;;){
    int x1, y1, z1;
    int x2, y2, z2;
    scanf("%d%d%d", &x1, &y1, &z1);
    scanf("%d%d%d", &x2, &y2, &z2);
    if(x1 == 0 && y1 == 0 && z1 == 0
        && x2 == 0 && y2 == 0 && z2 == 0) break;

    for(i = 0; i <= 3 * dv; i++){
      for(j = 0; j <= 3 * dv; j++){
        for(k = 0; k <= 3 * dv; k++){
          ed[i][j][k].clear();
          vis[i][j][k] = false;
        }
      }
    }
    while(!pq.empty()) pq.pop();

    char tmp[5];
    for(i = 0; i < 3; i++){
      for(j = 0; j < 3; j++){
        scanf("%s", tmp);
        for(k = 0; k < 3; k++){
          b[k][j][i] = (tmp[k] == '#');
        }
      }
    }

    for(i = 0; i <= 3; i++){
      for(j = 0; j <= 3; j++){
        for(k = 0; k <= 3; k++){
          // (i, j, k) (i + 1, j, k) (i, j + 1, k) (i + 1, j + 1, k)
          // square (i, j, k - 1), (i, j, k)
          if(i < 3 && j < 3 && (k == 0 ? 0 : b[i][j][k - 1]) + b[i][j][k] == 1){
            for(int l0 = 0; l0 < 4 * dv; l0++){
              for(int l1 = l0 + 1; l1 < 4 * dv; l1++){
                // (i * dv + rot[l][0], j * dv + rot[l][1], k * dv)
                int nx0 = i * dv + rot[l0][0], ny0 = j * dv + rot[l0][1], nz0 = k * dv;
                int nx1 = i * dv + rot[l1][0], ny1 = j * dv + rot[l1][1], nz1 = k * dv;
                ed[nx0][ny0][nz0].push_back(point(nx1, ny1, nz1));
                ed[nx1][ny1][nz1].push_back(point(nx0, ny0, nz0));
              }
            }
          }
          // (i, j, k) (i + 1, j, k) (i, j, k + 1) (i + 1, j, k + 1)
          // square (i, j - 1, k), (i, j, k)
          if(i < 3 && k < 3 && (j == 0 ? 0 : b[i][j - 1][k]) + b[i][j][k] == 1){
            for(int l0 = 0; l0 < 4 * dv; l0++){
              for(int l1 = l0 + 1; l1 < 4 * dv; l1++){
                // (i * dv + rot[l][0], j * dv, k * dv + rot[l][1])
                int nx0 = i * dv + rot[l0][0], ny0 = j * dv, nz0 = k * dv + rot[l0][1];
                int nx1 = i * dv + rot[l1][0], ny1 = j * dv, nz1 = k * dv + rot[l1][1];
                ed[nx0][ny0][nz0].push_back(point(nx1, ny1, nz1));
                ed[nx1][ny1][nz1].push_back(point(nx0, ny0, nz0));
              }
            }
          }
          // (i, j, k) (i, j + 1, k) (i, j, k + 1) (i, j + 1, k + 1)
          // square (i - 1, j, k), (i, j, k)
          if(j < 3 && k < 3 && (i == 0 ? 0 : b[i - 1][j][k]) + b[i][j][k] == 1){
            for(int l0 = 0; l0 < 4 * dv; l0++){
              for(int l1 = l0 + 1; l1 < 4 * dv; l1++){
                // (i * dv, j * dv + rot[l][0], k * dv + rot[l][1])
                int nx0 = i * dv, ny0 = j * dv + rot[l0][0], nz0 = k * dv + rot[l0][1];
                int nx1 = i * dv, ny1 = j * dv + rot[l1][0], nz1 = k * dv + rot[l1][1];
                ed[nx0][ny0][nz0].push_back(point(nx1, ny1, nz1));
                ed[nx1][ny1][nz1].push_back(point(nx0, ny0, nz0));
              }
            }
          }
        }
      }
    }

    pq.push(make_pair(0.0, point(x1 * dv, y1 * dv, z1 * dv)));
    double ans = 0.0;

    while(!pq.empty()){
      double nd = pq.top().first;
      int nx = pq.top().second.x, ny = pq.top().second.y, nz = pq.top().second.z;
      pq.pop();

      if(vis[nx][ny][nz]) continue;
      vis[nx][ny][nz] = true;

      if(nx == x2 * dv && ny == y2 * dv && nz == z2 * dv){
        ans = nd;
        break;
      }

      for(point pp : ed[nx][ny][nz]){
        if(!vis[pp.x][pp.y][pp.z]){
          pq.push(make_pair(nd - dist(xtov[nx], xtov[ny], xtov[nz], xtov[pp.x], xtov[pp.y], xtov[pp.z]), pp));
        }
      }
    }
    printf("%.20lf\n", -ans / sd);
  }
  return 0;
}
