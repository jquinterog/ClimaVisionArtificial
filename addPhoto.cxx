#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>
#include <string.h>
#include <utility>

using namespace cv;

int main(int argc, char** argv )
{
  if (argc!=2)
  {
  	  std::cout<<"Numero de argumentos invalido"<<std::endl;
  	  std::cout<<"Uso: ./addPhoto <path_de_imagen>"<<std::endl;
  	  return -1;
  }
  
  Mat image;
  image = imread( argv[1], 1 );

  if ( !image.data )
  {
		std::cout<<"Error al abrir la imagen"<<std::endl;
		return -1;
  }

	std::vector < int > azules(256, 0 );
	int cont=0;
	MatIterator_< Vec3b > it, end;
	it = image.begin< Vec3b >( );
	end = image.end< Vec3b >( );
	for( ; it != end; ++it)
	{
	 	azules[ (*it) [0] ]++;
	 	cont++;
	}
	std::stringstream ss(argv[1]);
	std::string aux;
	getline (ss,aux,'.');
	std::stringstream ssout;
	ssout<<aux<<"Hist.txt";
	std::ofstream out(ssout.str().c_str());
	for(int i = 0 ; i < 256 ; i++)
	{
		double resp= ((double)azules[i]/(double)cont)*100.0;
		out<<resp<<std::endl;
	}
	out.close();

  return( 0 );
}

