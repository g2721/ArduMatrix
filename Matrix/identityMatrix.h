#ifndef identityMatrix_h
#define identityMatrix_h

#include "abstractMatrix.h"

template<const int rowsT>
class IdentityMatrix: public AbstractMatrix {
private:
  float dontchangeme0 = 0.0;
  float dontchangeme1 = 1.0;

public:
  //Constructor
  IdentityMatrix<rowsT>() {
  }


  // Copy constructer
  IdentityMatrix<rowsT>(const IdentityMatrix<rowsT> &rhs) {
  }

  IdentityMatrix* clone(){
    return new IdentityMatrix(*this);
  }


  //Element Access
  /*Single elements of a Matrix may be accessed like this:
      Matrix<3,3> A;
      x of type float
      x = A(2,3); //get
    */

  float& operator()(int pRow, int pCol){
      if(pRow == pCol){
        return dontchangeme1;
      }
      else{
        return dontchangeme0;
      }
  }

  void operator=(float const rhs) {
    //Error Warning: You can't override an identityMatrix
  }

};
#endif
