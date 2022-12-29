#ifndef __CFRACT_H__
#define __CFRACT_H__

#include <iostream>

// Fraction toujours valide : b!=0
// Fraction a représentation unique : a et b premiers entre eux et b>0
class CFract
{
	int a, b;
	void Norm()
	{
		int t, _a=a, _b=b;
		while (_b!=0)
		{
		  t=_b;
		  _b=_a%_b;
		  _a=t;
		}
		_a=_a>0?_a:-_a;
		a=b>0?a/_a:-a/_a;
		b=b>0?b/_a:-b/_a;
	}
public:
	CFract(const CFract& f):a(f.a),b(f.b) {/*a=f.a; b=f.b;*/}
	//CFract() { std::cout<<"Ctor par defaut: "; Afficher(); }
	//CFract(int _a) {a=_a; b=1; std::cout<<"Ctor 1 argument: "; Afficher();}
	//CFract(int _a, int _b) {a=_a; b=_b; std::cout<<"Ctor 2 arguments: "; Afficher();}
	/*explicit*/ CFract(const int _a=0, const int _b=1) {a=_a; b=_b==0 ?1:_b; Norm();}
	~CFract(){}
  void Afficher() const { Afficher(std::cout); }
  void Afficher(std::ostream& os) const { os<<"Fraction @"<<this<<": ("<<a<<"/"<<b<<")\n"; }
	CFract& MultTo(const CFract& f) {a=a*f.a; b=b*f.b; Norm(); return *this;}
	CFract& AddTo(const CFract& f) {a=a*f.b+f.a*b; b=b*f.b; Norm(); return *this;}
	const int& GetA() const {return a;} // On aurait pu retourner une copie au lieu d'une référence constante
	const int& GetB() const {return b;}
	void SetA(const int& _a) {a=_a; Norm();}
	void SetB(const int& _b) {if(_b) {b=_b; Norm();}}
	CFract& operator *=(const CFract& f) {return MultTo(f);}
	//CFract& operator *=(const CFract& f) {return *this.MultTo(f);}
	//CFract& operator *=(const CFract& f) {return this->MultTo(f);}
	//CFract& operator *=(const CFract& f) {a=a*f.a; b=b*f.b; Norm(); return *this;}
	//CFract& operator *=(const CFract& f) {return *this=*this+f;} // NON !!
	CFract& operator +=(const CFract& f) {return AddTo(f);}
	//CFract operator +=(const CFract& f) const {return CFract(a*f.b+f.a*b,b*f.b);}
	//CFract operator +=(const CFract& f) const {CFract f2(a*f.b+f.a*b,b*f.b); return f2}
	CFract operator+(const CFract& f) const {return CFract(*this)+=f;}
	//CFract operator+(const CFract& f) const {return *this+=f;} // NON !!
	// en chantier :
	CFract& operator /=(const CFract& f) {if(f.a) {return MultTo(CFract(f.b,f.a));} else {return *this;}}
	CFract& operator -=(const CFract& f) {return AddTo(CFract(-f.a,f.b));}
	CFract operator -(const CFract& f) const {return CFract(*this)-=f;}
	CFract operator *(const CFract& f) const {return CFract(*this)*=f;}
	CFract operator /(const CFract& f) const {return CFract(*this)/=f;}
	bool operator ==(const CFract& f) const {return f.a==a && f.b==b;}
	CFract operator -() {return CFract(-a, b);} // moins unaire
	// en chantier :
	bool operator <(const CFract& f) const {CFract f2(*this-f); return f2.a<0;}
	bool operator >(const CFract& f) const {return f<*this;}
	bool operator <=(const CFract& f) const {return !(*this>f);}
	bool operator >=(const CFract& f) const {return !(*this<f);}
	CFract& operator ++() {return AddTo(1);} // pré-incrémentation
	//CFract& operator ++() {return AddTo(CFract(1));}
	//CFract& operator ++() {return *this+=1;}
	CFract operator ++(int) {CFract f(*this); AddTo(1); return f;} // post-incrémentation
	CFract& operator --() {return *this-=1;} // pré-incrémentation
	CFract operator --(int) {CFract f(*this); --*this; return f;} // post-incrémentation
	operator double() {return a/(double)b;}
	CFract& operator()(const int& _a, const int& _b) {a=_a; b=_b==0 ?1:_b; Norm(); return *this;}
};

inline std::ostream& operator<<(std::ostream& os, const CFract& f) {f.Afficher(os); return os;}

#endif //__CFRACT_H__