/*
 * Author:      Eduardo Cáceres de la Calle
 * Subject:     Visión Artificial
 * Degree:      Industrial Electronics and Automatic Control Engineering
 * University:  Universidad de Valladolid (UVa) - EII
 *
 * Code written in 2017, during my first contact with OpenCV.
 * Uploaded for educational purposes only.
 *
 */


#include "../header_files/basic_operations.hpp"

int init_pic(int argc, char* argv[], string & strpicName, Mat & myPic) {
  if(argc != 2) {
    cout<<"Missing picture name"<<endl;
    return -1;
  }

  myPic= imread( argv[1], CV_LOAD_IMAGE_UNCHANGED);

  if( myPic.empty())  {
    cout<<"Error opening picture file "<<argv[1]<<endl;
    return -1;
  }

  char chpicName[CHL];
  strcpy(chpicName, argv[1]);
  string picName(chpicName);
  strpicName= picName;

  int n= strpicName.find("Pictures/");
  strpicName.erase(strpicName.begin(), strpicName.begin() + n+9);

  return 0;
}

void print_info(const Mat & myPic, const string & picName ) {
  cout<<endl;
  cout<< "Name:\t\t"    << picName          <<endl;
  cout<< "Rows:\t\t"    << myPic.rows       <<endl;
  cout<< "Columns:\t"   << myPic.cols       <<endl;
  cout<< "Channels:\t"  << myPic.channels() <<endl;
  cout<< "Type:\t\t";

  if     (myPic.type() == CV_8UC1)  cout << "CV_8UC1"  << endl;
  else if(myPic.type() == CV_8UC3)  cout << "CV_8UC3"  << endl;
  else if(myPic.type() == CV_32FC1) cout << "CV_32FC1" << endl;
  else if(myPic.type() == CV_32FC3) cout << "CV_32FC3" << endl;
  else cout << "Unknown" << endl;
  cout<<"Depth:\t\t"<< myPic.depth();

  cout<<endl;
}
