#include <cv.h>
#include <highgui.h>

using namespace cv;

int main( int argc, char** argv )
{
 char* imageName = argv[1];

 Mat image;
 image = imread( imageName, 1 );

 if( argc != 2 || !image.data )
 {
   printf( " No image data \n " );
   return -1;
 }

 Mat gray_image;
 Mat filter_image;
 Mat equal_image;
 cvtColor( image, gray_image, CV_BGR2GRAY );
 imwrite( "Gray_Image.jpg", gray_image );
 /// Apply Histogram Equalization
 equalizeHist( gray_image, equal_image );
 imwrite( "Equalized.jpg", equal_image );
 medianBlur(equal_image, filter_image, 25);
 imwrite( "Filter_Image.jpg", filter_image );
 
 Mat otsu_image;
 threshold ( filter_image, otsu_image, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU );
 imwrite( "Otsu_Image.jpg", otsu_image );

 Mat element = getStructuringElement( MORPH_RECT, Size( 5, 5), Point( 3,3 ) );
 Mat openclose_image;
 
 /// Apply the specified morphology operation
  morphologyEx( otsu_image, openclose_image, MORPH_OPEN, element );
  morphologyEx( openclose_image, openclose_image, MORPH_CLOSE, element );
  imwrite( "OpenClose_Image.jpg", openclose_image );
 

 /*namedWindow( imageName, CV_WINDOW_AUTOSIZE );
 namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

 imshow( imageName, image );
 imshow( "Gray image", gray_image );
*/
 waitKey(0);

 return 0;
}
