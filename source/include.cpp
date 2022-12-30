#pragma once 
#include<bits/stdc++.h>

using namespace std;

typedef int ll;
#define FOR(prom,a,b) for ( ll prom = (a); prom < (ll)(b); ++prom )

#define deb(x) std::cerr<<#x<<" "<<x<<std::endl;
template<typename T> ostream& operator<<(ostream& out, const vector<T> & v){for(const auto & x : v){out << x << ' ';} return out;}
template<typename T> istream& operator>>(istream& in, vector<T>&v){for(auto&x:v){in>>x;}return in;}

std::mt19937 rng;

void initRNG()
{
	rng = std::mt19937(1000);
}

int getrandInt(int lb, int ub)
{
	std::uniform_int_distribution<std::mt19937::result_type> generator(lb , ub-1);
	return generator(rng);
}