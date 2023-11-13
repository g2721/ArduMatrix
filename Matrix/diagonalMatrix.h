#ifndef diagonalMatrix_h
#define diagonalMatrix_h

#include "abstractMatrix.h"

template<const int rowsT>
class DiagonalMatrix: public AbstractMatrix {
  /*
      arr = 1D-array of size (rowsT)
      rowsT = number of rows and columns
    */
private:
  float arr[rowsT];
  float dontchangeme = 0.0;

public:
  //Constructer
  DiagonalMatrix() {
  }

  //Constructor (1D-Array)
  /*
      may be used to construct a matrix from a 1D-array
    */
  DiagonalMatrix<rowsT>(const float pArr[rowsT]) {
    /*
        pArr = input array (rowsT)
        rowsT = number of rows and columns in this
      */
    for (int i = 0; i < (rowsT); i++) {
      this->arr[i] = pArr[i];
    }
  }


  // Copy constructer
  DiagonalMatrix<rowsT>(const DiagonalMatrix<rowsT> &rhs) {
    /*
        this = input matrix (rowsT x rowsT)
        rhs = input matrix (rowsT x rowsT)
        rowsT = number of rows and columns in this and rhs
      */
    for (int i = 0; i < (rowsT); i++) {
      this->arr[i] = rhs.arr[i];
    }
  }

  DiagonalMatrix* clone(){
    return new DiagonalMatrix(*this);
  }


  //Element Access
  /*Single elements of a Matrix may be accessed like this:
      Matrix<3,3> A;
      x of type float
      x = A(2,3); //get
      A(2,2) = x; //set
    */
  float operator()(int pRow, int pCol) const{
    /*
        this = input matrix (rowsT x rowsT)
        rowsT = number of rows and columns in this
      */
    if(pRow == pCol){
      return this->arr[pRow-1];
    }
    else{
      return 0.0;
    }
  }

  float& operator()(int pRow, int pCol){
    /*
        this = input matrix (rowsT x rowsT)
        rowsT = number of rows and columns in this
      */
      if(pRow == pCol){
        return this->arr[pRow-1];
      }
      else{
        return dontchangeme;
      }
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
        this = input matrix (rowsT x rowsT)
        rhs = input float
        rowsT = number of rows and columns in this
      */
    for (int i = 0; i < (rowsT); i++) {
      this->arr[i] = rhs;
    }
  }

};

#endif
