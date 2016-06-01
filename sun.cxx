#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>
#include <string.h>
#include <utility>

using namespace cv;

int main(int argc, char** argv )
{
  bool hay=true;
  int imgN=374;
  
  while(imgN!=722)
  {
  	  std::stringstream ss;
  	  ss<<"fotosVision/DSC00";
  	  ss<<imgN<<".JPG";
	  Mat image;
	  image = imread( ss.str(), 1 );

	  if ( !image.data )
	  {
		hay=false;
	  }
	  
	  if (hay)
	  {
	  	std::vector < std::pair<int,int> > azules(256, std::make_pair(0,0) );
	  	for (int i = 0 ; i < 256 ; i++)
	  	{
	  		azules[i].second=i;
	  	}
	  	int cont=0;
	  	MatIterator_< Vec3b > it, end;
		it = image.begin< Vec3b >( );
		end = image.end< Vec3b >( );
		for( ; it != end; ++it)
		{
		 	azules[ (*it) [0] ].first++;
		 	cont++;
		}
	    //std::sort(azules.begin(),azules.end());
	    std::stringstream ssout( "DSC00" );
  	  	ssout<<imgN<<"Hist.txt";
	    std::ofstream out(ssout.str().c_str());
	    for(int i = 0 ; i < 256 ; i++)
	    {
	    	double resp= ((double)azules[i].first/(double)cont)*100.0;
	    	out<</*azules[i].second<<";"<<azules[i].first<<";"<<*/resp<<std::endl;
	    }
	    out.close();
	  	
	  }
	  else
	  {
	  	std::cout<<ss.str()<<" no entro"<<std::endl;
	  }
	  
	  imgN++;
	  hay=true;
  }

  return( 0 );
}

