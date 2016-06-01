#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>

using namespace cv;

int main(int argc, char** argv )
{
	if (argc!=2)
	{
		std::cout<<"Numero de argumentos invalido"<<std::endl;
		std::cout<<"Uso: ./test <path_de_imagen>"<<std::endl;
		return -1;
	}
	Mat image;
	image= imread(argv[1], 1 );
	if (!image.data)
	{
		std::cout<<"Error al abrir la imagen"<<std::endl;
		return -1;
	}
	std::vector <int> azules(256,0);
	int cont=0;
	MatIterator_< Vec3b > it, end;
	it = image.begin< Vec3b >( );
	end = image.end< Vec3b >( );
	for( ; it != end; ++it)
	{
	 	azules[ (*it) [0] ]++;
	 	cont++;
	}
	std::vector <double> porc(256,0.0);
	for (int i = 0 ; i < 256 ; i++)
	{
		porc[i]=((double)azules[i]/(double)cont)*100.0;
	}
	std::set <double> difNotRain;
	std::set <double> difRain;
	double promN=0.0;
	double promR=0.0;
	int N=0;
	int R=0;
	
	FILE *fp;
	char path[1035];

	fp = popen("/bin/ls rain/", "r");
	if (fp == NULL)
	{
		std::cout<<"No se pudo abrir la carpeta \"rain\""<<std::endl;
		exit(1);
	}
	while (fgets(path, sizeof(path)-1, fp) != NULL) 
	{
		std::stringstream ss;
		path[strlen(path)-1]='\0';
		ss<<"rain/"<<path;
		//std::cout<<ss.str()<<std::endl;
		std::ifstream input(ss.str().c_str());
		double dif=0.0;
		double a;
		for (int i = 0 ; i < 256 ; i++)
		{
			input>>a;
			dif+=fabs(a-porc[i]);
			promR+=fabs(a-porc[i]);
		}
		difRain.insert(dif);
		R++;
	}
	pclose(fp);

	fp = popen("/bin/ls notrain/", "r");
	if (fp == NULL)
	{
		std::cout<<"No se pudo abrir la carpeta \"notrain\""<<std::endl;
		exit(1);
	}
	while (fgets(path, sizeof(path)-1, fp) != NULL) 
	{
		std::stringstream ss;
		path[strlen(path)-1]='\0';
		ss<<"notrain/"<<path;
		//std::cout<<ss.str()<<std::endl;
		std::ifstream input(ss.str().c_str());
		double dif=0;
		double a;
		for (int i = 0 ; i < 256 ; i++)
		{
			input>>a;
			dif+=fabs(a-porc[i]);
			promN+=fabs(a-porc[i]);
		}
		difNotRain.insert(dif);
		N++;
	}
	pclose(fp);
	
	double llueve=*(difRain.begin())+*(difRain.rbegin());
	double nollueve=*(difNotRain.begin())+*(difNotRain.rbegin());
	promN=promN/(double)N;
	promR=promR/(double)R;
	//IMPRIMIR RESULTADOS
	std::cout<<"Porcentaje de lluvia: "<<(nollueve/llueve)*50.0<<"%"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Porcentaje de lluvia: "<<(promN/promR)*50.0<<"%"<<std::endl;
	//std::cout<<"Porcentaje de lluvia: "<<promN-promR+50.0<<"%"<<std::endl;
	std::cout<<std::endl;
	
	return 0;
}


