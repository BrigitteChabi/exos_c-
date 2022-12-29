#ifndef _TEMPLATES_H
#define _TEMPLATES_H

#include <iostream>
#include <iomanip>
#include <typeinfo.h>

// existance de :
// Ctor de copie public
// bool operator > (const TObj&, const TObj&)
//template<typename TObj> inline TObj MaxVal(TObj o1, TObj o2)
//{
//	return o1 > o2 ? o1 : o2;
//}

// existance de :
// bool operator > (const TObj&, const TObj&)
template<typename TObj> inline TObj& MaxVal(TObj& o1, TObj& o2)
{

	return o1 > o2 ? o1 : o2;
}
template<typename TObj> inline const TObj& MaxVal(const TObj& o1, const TObj& o2)
{
	return o1 > o2 ? o1 : o2;
}

template<typename TObj > inline void ShowVect(std::ostream& os, const TObj * tab, size_t size,
                                              const char* name)
{
	os<<"Tableau "<<name<<" de "<<size<<" elements de type "<<typeid(TObj).name()<<"\n ";
	for (size_t i=0; i<size-1; i++) os<<tab[i]<<", ";
	os<<tab[size-1]<<"\n";
}

// Pour être sûr que la fonction garde le paramètre TObj en tant que tableau et pas en tant que pointeur
// Mais ne marche pas pour les types dynamique
template<typename TObj , const size_t SZ> inline void ShowVect(std::ostream& os,
                                                               const TObj (&tab)[SZ],
                                                               const char* name)
{
	os<<"Tableau "<<name<<" de "<<SZ<<" elements de type "<<typeid(TObj).name()<<"\n ";
	for (size_t i=0; i<SZ-1; i++) os<<tab[i]<<", ";
	os<<tab[SZ-1]<<"\n";
}

template<typename TObj , const size_t SZ> inline const size_t GetSize(const TObj (&tab)[SZ])
{
	return SZ;
}

template<typename TObj, const size_t SZ> inline TObj VectSomme(const TObj (&tab)[SZ])
{
	TObj s(tab[0]);
	for (size_t i=1; i<SZ; i++) s+=tab[i];
	
	
	return s;
}
template<typename TObj> inline TObj VectSomme(const TObj* tab, size_t size)
{
	TObj s(tab[0]);
	for (size_t i=1; i<size; i++) s+=tab[i];
	return s;
}

template<typename TObj, const size_t SZ> inline void TestVectSomme(std::ostream& os,
                                                                   const TObj (&tab)[SZ],
                                                                   const char* name)
{
	os<<"Somme du tableau "<<name<<" = "<<VectSomme(tab)<<endl;
}

template<typename TObj> inline void TestVectSomme(std::ostream& os, const TObj* tab,
                                                  size_t size, const char* name)
{
	os<<"Somme du tableau "<<name<<" = "<<VectSomme(tab, size)<<endl;
}

#endif //_TEMPLATES_H