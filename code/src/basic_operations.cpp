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


#include "../header/basic_operations.hpp"

int init_pic(int argc, char* argv[], std::string & strpicName, Mat & myPic) {
  if(argc != 2) {
    std::cout<<"Missing picture name"<<std::endl;
    return -1;
  }

  myPic= imread( argv[1], CV_LOAD_IMAGE_UNCHANGED);

  if( myPic.empty())  {
    std::cout<<"Error opening picture file "<<argv[1]<<std::endl;
    return -1;
  }

  char chpicName[CHL];
  strcpy(chpicName, argv[1]);
  std::string picName(chpicName);
  strpicName= picName;

  int n= strpicName.find("Pictures/");
  strpicName.erase(strpicName.begin(), strpicName.begin() + n+9);

  return 0;
}

int init_pic(int argc, char* argv[], std::vector<std::string> & strpicName, std::vector<Mat> & myPic) {

  static int n_pic=0;

  myPic.reserve(argc-1);

  for(int i=1; i<argc; ++i)
  {
    ++n_pic;

    if(argc < n_pic+1) {
      std::cout<<"Missing picture name"<<std::endl;
      return -1;
    }

    myPic[i-1]= imread( argv[n_pic], CV_LOAD_IMAGE_UNCHANGED);

    if( myPic[i-1].empty())  {
      std::cout<<"Error opening picture file "<<argv[n_pic]<<std::endl;
      return -1;
    }

    char chpicName[CHL];
    strcpy(chpicName, argv[n_pic]);
    std::string picName(chpicName);

    int n= picName.find("Pictures/");
    picName.erase(picName.begin(), picName.begin() + n+9);
    strpicName.push_back(picName);

    show_pic(myPic[i-1], strpicName[i-1]);
  }

  return 0;
}

void print_info(const Mat & myPic, const std::string & picName ) {

  std::cout << "OpenCV version: " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << std::endl;
  // std::cout << "OpenCV: " << getBuildInformation();

  std::cout<<std::endl;
  std::cout<< "Name:\t\t"    << picName          <<std::endl;
  std::cout<< "Rows:\t\t"    << myPic.rows       <<std::endl;
  std::cout<< "Columns:\t"   << myPic.cols       <<std::endl;
  std::cout<< "Channels:\t"  << myPic.channels() <<std::endl;
  std::cout<< "Type:\t\t";

  if     (myPic.type() == CV_8UC1)  std::cout << "CV_8UC1"  << std::endl;
  else if(myPic.type() == CV_8UC3)  std::cout << "CV_8UC3"  << std::endl;
  else if(myPic.type() == CV_32FC1) std::cout << "CV_32FC1" << std::endl;
  else if(myPic.type() == CV_32FC3) std::cout << "CV_32FC3" << std::endl;
  else std::cout << "Unknown" << std::endl;
  std::cout<<"Depth:\t\t"<< myPic.depth();

  std::cout<<std::endl;
}


void show_pic(const Mat & myPic)  {
    std::cout<<"ss"<<std::endl;
  std::string name(stringify(myPic));
  namedWindow(name, WINDOW_AUTOSIZE);
  imshow(name, myPic);
}

// void show_pic(const Mat & myPic, bool save)  {     // string in void show_pic(const Mat & myPic, std::string name) is interpreted as bool
//     std::cout<<"ssff"<<std::endl;
//   show_pic(myPic);
//   if(save==true)
//     save_pic(myPic);
// }

void show_pic(const Mat & myPic, std::string name) {
  namedWindow(name, WINDOW_AUTOSIZE);
  imshow(name, myPic);
}

void show_pic(const Mat & myPic, std::string name, bool save) {
  namedWindow(name, WINDOW_AUTOSIZE);
  imshow(name, myPic);
  if(save==true)
    save_pic(myPic, name);
}

void save_pic(const Mat& Pic) {
  std::string newName(stringify(Pic));
  newName += ".jpg";  // Fundamental to add the extension
  imwrite(newName, Pic);
}


void save_pic(const Mat& Pic, std::string str) {
  std::string newName(stringify(Pic));
  newName += "_" + str + ".jpg";  // Fundamental to add the extension
  imwrite(newName, Pic);
}
