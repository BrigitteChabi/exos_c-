#include "templates.h"
#include "CFract.h"

using namespace std;

void test1()
{
	cout<<"******************** Test1 ********************\n";
	float f1=5.5f, f2=4.5f;
	double d1=2.1, d2=-15.3;
	int i1=23, i2=-5;
	cout<<MaxVal(f1, f2)<<endl;
	cout<<MaxVal(i1, i2)<<endl;
	cout<<MaxVal(d1, d2)<<endl;
	cout<<MaxVal(i1, 25)<<endl; // Deuxième version
	MaxVal(i1,i2)=55; // Le compilateur utilise la première version
	//cout<<MaxVal(f1, d2)<<endl; Le compilateur affiche une erreur car type diférent, il ne choisit pas
	cout<<MaxVal<float>(f1,d2)<<endl;
	cout<<MaxVal<double>(f1,d2)<<endl;

}

void test2()
{
	cout<<"******************** Test2 ********************\n";
	double vd1[]={6.6, -6.6, 2.5, 4.6};
	const size_t vd1_sz=sizeof(vd1)/sizeof(vd1[0]);
	ShowVect(cout, vd1, "vd1");
	ShowVect(cout, vd1, vd1_sz, "vd1");
	int vi1[]={-6, -16, 25, 46};
	const size_t vi1_sz=sizeof(vi1)/sizeof(vi1[0]);
	ShowVect(cout, vi1, "vi1");
	ShowVect(cout, vi1, vi1_sz, "vi1");
	cout<<"taille vi1 = "<<GetSize(vi1)<<", vd1 = "<<GetSize(vd1)<<endl;
	cout<<"Somme de vi1 = "<<VectSomme(vi1)<<endl;
	TestVectSomme(cout, vi1, "vi1"); TestVectSomme(cout, vd1, "vd1");

	size_t tdyn_sz=5+(rand()%5);
	int *tdyn=new int[tdyn_sz];
	for (size_t i=0; i<tdyn_sz; i++) tdyn[i]=int(i*i);
	//ShowVect(cout, tdyn, "(tdyn)"); // impossible
	ShowVect(cout, tdyn, tdyn_sz, "(tdyn)"); //ok
	//TestVectSomme(cout, tdyn, "tdyn"); // impossible, à modifier !!!
  TestVectSomme(cout, tdyn, tdyn_sz, "tdyn");
	delete[] tdyn;
}

int main()
{
	//test1();
	test2();
	return 0;
}