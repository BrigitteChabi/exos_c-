#ifndef _PERMUTATION_H
#define _PERMUTATION_H

#include <iostream>
#include <vector>

inline unsigned long long Fact(unsigned long long f)
{
  if (f==0) return 1;
  unsigned long long v=Fact(f-1);
  return v*f;
}

class TPermType
{
public:
  typedef unsigned char TypeORD;
  typedef unsigned long long TypeIndex;
};

template<TPermType::TypeORD ORD> class TPerm: public TPermType
{
  TypeIndex IPerm;
  static const TypeIndex MAX_PERM;
public:
  TPerm(TypeIndex index=0):IPerm(index) {}
  TPerm(const TypeORD (&Tab)[ORD]) {IPerm=Tab2Idx(Tab);}
  const TPerm& operator= (const TPerm &p) {IPerm=p.GetIdx(); return *this;}
  const TypeIndex& GetIdx() const {return IPerm;}
  static const TypeIndex& MaxIdx() {return MAX_PERM;}
  static TypeIndex Tab2Idx(const TypeORD (&Tab)[ORD])
  {
    TypeIndex index=0;
    TypeORD Tmp[ORD];
    for (TypeORD i=0; i<ORD; i++) Tmp[i]=Tab[i];
    for (TypeORD i=0; i<ORD; i++)
    {
      index+=Tmp[i]*Fact(ORD-i-1);
      for (TypeORD j=i+1; j<ORD; j++) if (Tmp[j]>Tmp[i]) Tmp[j]--;
    }
    return index;
  }
  static void Idx2Tab(TypeIndex index, TypeORD (&Tab)[ORD])
  {
    for (TypeORD i=0; i<ORD; i++) Tab[i]=i;
    TypeORD ofs, Tmp;
    for (TypeORD i=0; i<ORD; i++)
    {
      ofs=TypeORD(index/Fact(ORD-i-1));
      Tmp=Tab[i+ofs];
      for (TypeORD j=0; j<ofs; j++) Tab[i+ofs-j]=Tab[i+ofs-j-1];
      Tab[i]=Tmp;
      index=index%Fact(ORD-i-1);
    }
  }
  void Next() {IPerm=(IPerm+1)%MAX_PERM;}
  std::ostream& Show(std::ostream& os) const {
    TypeORD Tab[ORD];
    Idx2Tab(IPerm, Tab);
    os<<"Permutation d'ordre "<<ORD<<" et d'index "<<IPerm<<" :\n{ ";
    for (TypeORD i=0; i<ORD; i++) os<<Tab[i]<<" ";
    return os<<"}\n";
  }
  const TPerm& operator ++() {Next(); return *this;} // pré-incrémentation
	TPerm operator ++(int) {TPerm p(*this); Next(); return p;} // post-incrémentation
  const TPerm& operator*= (const TPerm &p)
  {
    TypeORD Tabg[ORD], Tabd[ORD], Res[ORD];
    Idx2Tab(IPerm, Tabg); Idx2Tab(p.GetIdx(), Tabd);
    for (TypeORD i=0; i<ORD; i++) Res[i]=Tabg[Tabd[i]];
    IPerm=Tab2Idx(Res);
    return *this;
  }
  TPerm operator* (const TPerm &p) const
  {
    return TPerm(*this)*=p;
  }
};

template<TPermType::TypeORD ORD> __declspec(selectany) const TPermType::TypeIndex TPerm<ORD>::MAX_PERM=Fact(ORD);

template<TPermType::TypeORD ORD> inline std::ostream& operator<<(std::ostream& os, const TPerm<ORD>& p)
{ return p.Show(os); }

inline void ChercheRacine(const TPermType::TypeORD &N)
{
  TPerm<4> p, tmp;
  TPermType::TypeIndex s=0;
  std::cout<<"Racines d'ordre "<<N<<" de la permutation identite :\n";
  for (TPermType::TypeIndex i=0; i<p.MaxIdx(); i++)
  {
    tmp=p;
    for (TPermType::TypeORD j=0; j<N; j++) tmp*=tmp;
    if (tmp.GetIdx()==0)
    {
      std::cout<<p;
      s++;
    }
    p++;
  }
  std::cout<<s<<" racines au total\n";
}

using namespace std;

template<TPermType::TypeORD ORD> inline vector<TPermType::TypeORD> PermVect(const vector<TPermType::TypeORD> &v, const TPerm<ORD> &p)
{
  if (v.size()!=ORD) throw std::exception("Vecteur et Permutation non compatibles\n");
  TPerm<ORD>::TypeORD tmp[ORD];
  p.Idx2Tab(p.GetIdx(), tmp);
  vector<TPerm<ORD>::TypeORD> res(v);
  for (TPerm<ORD>::TypeORD i=0; i<ORD; i++) res[i]=v[tmp[i]];
  return res;
}

#endif //_PERMUTATION_H