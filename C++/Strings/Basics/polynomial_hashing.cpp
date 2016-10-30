#include <bits/stdc++.h>
using namespace std ;
class PolynomialHashing { // uses natural mod 2^64 , assumr 0 based indexing everywhere
  public:
    string s;
    long long * fHash, * rHash, * parr;
    long long prime;
    char offset = 0;
    
    PolynomialHashing(string str, long long pri = 257) : s(str), prime(pri) { // declare two instances with different primes as base to be more certain of not falling for anti hash cases
      fHash = new long long[s.size()], rHash = new  long long[s.size()], parr = new  long long[s.size()];
      fHash[0] = s[0] - offset + 1;
      parr[0] = 1;
      rHash[s.size() - 1] = s[s.size() - 1] - offset + 1;
      for(int i = 1; i < s.size(); i++) { // O(n)
        fHash[i] = fHash[i - 1] * prime + s[i] - offset + 1;
        parr[i] = parr[i - 1] * prime;
        rHash[s.size() - 1 - i] = rHash[s.size() - i] * prime + s[s.size() - i - 1] - offset + 1;
      }
    }

    long long getFrontHash (long long l, long long r) { // front hash of subtring from (l,r)
      if(l == 0) return fHash[r];
      if(l > r) return 0;
      return fHash[r] - fHash[l - 1] * parr[r - l + 1];
    }

    long long getReverseHash(long long l, long long r) { // reverse hash of substring from (l,r)
      if(r == s.size() - 1) return rHash[l];
      if(l > r) return 0;
      return rHash[l] - rHash[r + 1] * parr[r - l + 1];
    }
};
int main(){
  string s = "akshitchopra" ;
  PolynomialHashing ph(s,31) ;
  cout << ph.getFrontHash(0,4) << endl ;
  return 0 ;
}