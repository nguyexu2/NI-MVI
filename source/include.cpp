#pragma once 
#include<bits/stdc++.h>

using namespace std;

typedef int ll;
#define FOR(prom,a,b) for ( ll prom = (a); prom < (ll)(b); ++prom )

#define deb(x) std::cerr<<#x<<" "<<x<<std::endl;
template<typename T> ostream& operator<<(ostream& out, const vector<T> & v){for(const auto & x : v){out << x << ' ';} return out;}
template<typename T> istream& operator>>(istream& in, vector<T>&v){for(auto&x:v){in>>x;}return in;}
