#include <chrono>
#include <map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <time.h>

typedef long T;

using namespace std;

struct grupoVector
{
	T cant_vec, dim , vec_fil;
    vector<T> vec_dim;
	vector<vector<T>> grupoVectores;

	void refill(T i,T j,vector<vector<T>>& Matriz)
	{
        std::random_device rd;
        std::mt19937 gen(rd( ));
        std::uniform_int_distribution<>distrib(1, 10000);
		for (size_t i=0;i<cant_vec;i++)
        {
			Matriz[i].resize(dim);
			for (size_t j=0;j<dim;j++)
			{
				Matriz[i][j]=distrib(gen);
            }
        }
    }

	double calculo(vector<T> v1,vector<T> v2) //distancia euclidiana
	{
		T resultado=0;
		for (size_t i=0;i<v1.size();i++)
        {
			resultado=resultado+pow(v2[i]-v1[i],2);
		}
		return sqrt(resultado);
	}

    void imprimir()
	{

	    double temp,minimo,maximo;
		string dec;
	    vector<double> maximo_minimo;
        map<string,int> num;

        chrono::time_point<chrono::high_resolution_clock> start, end;
		start = chrono::high_resolution_clock::now();

		cout << "dimension: " << dim << endl;
		cout << "datos: " << cant_vec << endl;

		for (size_t i = 1; i < cant_vec; i++){
				temp=calculo(grupoVectores[i], grupoVectores[0]);
				maximo_minimo.push_back(temp);
		}
		sort(maximo_minimo.begin(),maximo_minimo.end());

		minimo=maximo_minimo[0];
		maximo=maximo_minimo[maximo_minimo.size()-1];

		for(size_t j=0;j<maximo_minimo.size();j++)
        {
			temp=(maximo_minimo[j]-minimo)/(maximo-minimo);
			dec=to_string(temp);
			dec=dec.substr(0,dec.find('.')+3);
			num[dec]++;
		}

		end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
		cout << "tiempo: " << duration.count()<< endl<<endl;

		ofstream archivotxt;
		archivotxt.open("hacergrafica"+to_string(dim)+".txt");

		for(map<string,int>::iterator it=num.begin();it!=num.end();it++)
        {
			archivotxt<<it->first+"\t"+to_string(it->second)+"\n";

		}

	}
	grupoVector(T vec_fil, vector<T> vec_dim)
	{
		this->vec_dim=vec_dim;
		this->vec_fil=vec_fil;
		cant_vec=this->vec_fil;
		for (size_t j=0; j<vec_dim.size(); j++)
        {
			dim=vec_dim[j];
			grupoVectores.resize(vec_fil);
			refill(0,j,grupoVectores);
			imprimir();
		}

	}


};


int main()
{
    vector<T> dim{ 2, 5, 10, 15, 20, 25};
	T cant_vec = 999999;
	grupoVector task(cant_vec, dim);
	return 0;
}
