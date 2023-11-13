#ifndef rectangularMatrix_h
#define rectangularMatrix_h


#include "abstractMatrix.h"


template<const int rowsT, const int colsT = 1>
class RectangularMatrix: public AbstractMatrix {
  /*
      arr = 1D-array of size (rowsT*cols)
      rowsT = number of rows
      colsT = number of columns
    */
private:
  float arr[rowsT * colsT];

public:
  //Constructer
  RectangularMatrix() {
  }

  //Constructor (2D-Array)
  /*
       may be used to construct a matrix from a 2D-array
    */
  RectangularMatrix<rowsT, colsT>(const float pArr[rowsT][colsT]) {
    /*
        pArr = input array (rowsT x colsT)
        rowsT = number of rows in this and pArr
        colsT = number of columns in this and pArr
      */
    for (int i = 0; i < rowsT; i++) {
      for (int j = 0; j < colsT; j++) {
        this->arr[i * colsT + j] = pArr[i][j];
      }
    }
  }

  //Constructor (1D-Array)
  /*
       may be used to construct a matrix from a 1D-array
    */
  RectangularMatrix<rowsT, colsT>(const float pArr[rowsT*colsT]) {
    /*
        pArr = input array (rowsT x colsT)
        rowsT = number of rows in this and pArr
        colsT = number of columns in this and pArr
      */
    for (int i = 0; i < rowsT*colsT; i++) {
      this->arr[i] = pArr[i];
    }
  }

  // Copy constructer
  RectangularMatrix<rowsT, colsT>(const RectangularMatrix<rowsT, colsT> &rhs) {
    /*
        this = input matrix (rowsT x colsT)
        rhs = input matrix (rowsT x colsT)
        rowsT = number of rows in this and rhs
        colsT = number of columns in this and rhs
      */
    for (int i = 0; i < (rowsT * colsT); i++) {
      this->arr[i] = rhs.arr[i];
    }
  }

  AbstractMatrix* clone(){
    return new RectangularMatrix(*this);
  }


  //Element Access
  /*Single elements of a Matrix may be accessed like this:
      Matrix<3,3> A;
      x of type float
      x = A(2,3); //get
      A(2,1) = x; //set
    */
  float operator()(int pRow, int pCol = 1) const{
    /*
        this = input matrix (rowsT x colsT)
        rowsT = number of rows in this
        colsT = number of columns in this
      */
    return this->arr[(pRow-1) * colsT + (pCol-1)];
  }

  float& operator()(int pRow, int pCol = 1){
    /*
        this = input matrix (rowsT x colsT)
        rowsT = number of rows in this
        colsT = number of columns in this
      */
    return this->arr[(pRow-1) * colsT + (pCol-1)];
  }





  //Assignemt with single float value
  /*
       gives an easy way of filling the complete matrix with one value
       may be used to initialize a matrix, for exampe with '0':
       Matrix<1,3> A;
       A=0; //--> A=[0,0,0]
    */
  void operator=(float const rhs) {
    /*
        this = input matrix (rowsT x colsT)
        rhs = input float
        rowsT = number of rows in this
        colsT = number of columns in this
      */
    for (int i = 0; i < (rowsT * colsT); i++) {
      this->arr[i] = rhs;
    }
  }


};
#endif
