#include <bits/stdc++.h>
using namespace std;
struct Widget {
  string name;
  long long width, height;
  Widget(const string& name, long long width, long long height)
    : name(name), width(width), height(height) {}
  ~Widget() {}
  virtual void calculateSize() {}
};
struct Box: public Widget {
  int spacing, border;
  vector<Widget*> children;
  Box(const string& name):Widget(name, 0, 0), spacing(0), border(0) {}
};
struct HBox : public Box {
  HBox(const string& name):Box(name) {}
  virtual void calculateSize()
  {
      
    if(children.empty()) {
      width = 0;
      height = 0;
      return;
    }
    if(width == 0 && height == 0) {
      for(vector<Widget*>::iterator i = children.begin(); i != children.end(); ++i) {
        (*i)->calculateSize();
        width += (*i)->width;
        height = max(height, (*i)->height);
      }
      width += (children.size()-1)*spacing+2*border;
      height += 2*border;
    }
  }
};
struct VBox : public Box {
  VBox(const string& name):Box(name) {}
  virtual void calculateSize()
  {
    if(children.empty()) {
      width = 0;
      height = 0;
      return;
    }
    if(width == 0 && height == 0) {
      for(vector<Widget*>::iterator i = children.begin(); i != children.end(); ++i) {
        (*i)->calculateSize();
        width = max(width, (*i)->width);
        height += (*i)->height;
      }
      height += (children.size()-1)*spacing+2*border;
      width += 2*border;
    }
  }
};

int main()
{
    
  int n;
  cin >> n;
  map<string, Widget*> map;
  for(int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    if(s == "Widget") {
      cin >> s;
      auto lparen = s.find("(");
      string name = s.substr(0, lparen);
      auto comma = s.find(",", lparen+1);
      auto rparen = s.find(")", comma+1);
      int width = strtol(s.substr(lparen+1, comma-lparen-1).c_str(), 0, 10);
      int height = strtol(s.substr(comma+1, rparen-comma-1).c_str(), 0, 10);
      map[name] = new Widget(name, width, height);
    } else if(s == "VBox") {
      cin >> s;
      map[s] = new VBox(s);
    } else if(s == "HBox") {
      cin >> s;
      map[s] = new HBox(s);
    } else {
      auto dot = s.find(".");
      auto lparen = s.find("(", dot+1);
      auto rparen = s.find(")", lparen+1);
      string name = s.substr(0, dot);
      string method = s.substr(dot+1, lparen-dot-1);
      if(method == "pack") {
        string child = s.substr(lparen+1, rparen-lparen-1);
        static_cast<Box*>(map[name])->children.push_back(map[child]);
      } else if(method == "set_border") {
        int border = strtol(s.substr(lparen+1, rparen-lparen-1).c_str(), 0, 10);
        static_cast<Box*>(map[name])->border = border;
      } else if(method == "set_spacing") {
        int spacing = strtol(s.substr(lparen+1, rparen-lparen-1).c_str(), 0, 10);
        static_cast<Box*>(map[name])->spacing = spacing;
      }
    }
  }
  for(std::map<string, Widget*>::iterator i = map.begin(); i != map.end(); ++i) {
    Widget* widget = (*i).second;
    widget->calculateSize();
    cout << widget->name << " " << widget->width << " " << widget->height << endl;
  }
} 