#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
 char* imageName = argv[1];

 Mat image;
 image = imread( imageName, 0 );

 if( argc != 2 || !image.data )
 {
   printf( " No image data \n " );
   return -1;
 }

 
 
 Mat mfilter_image;
 threshold ( image, mfilter_image, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU );
 imwrite( "Otsu_Image.jpg", mfilter_image );

 Mat element = getStructuringElement( MORPH_RECT, Size( 5, 5), Point( 3,3 ) );
 Mat openclose_image;
 
 /// Apply the specified morphology operation
  morphologyEx( mfilter_image, openclose_image, MORPH_OPEN, element );
  morphologyEx( openclose_image, openclose_image, MORPH_CLOSE, element );
  imwrite( "OpenClose_Image.jpg", openclose_image );
 

 //namedWindow( imageName, CV_WINDOW_AUTOSIZE );
 //namedWindow( "MedFilter image", CV_WINDOW_AUTOSIZE );

 //imshow( imageName, image );
 //imshow( "MedFilter image", mfilter_image );

 waitKey(0);

 return 0;
}
