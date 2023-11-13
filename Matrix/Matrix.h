#ifndef Matrix_h
#define Matrix_h

#include <abstractMatrix.h>
#include <diagonalMatrix.h>
#include <rectangularMatrix.h>
#include <identityMatrix.h>


enum matrixType {rectangular, diagonal, identity};


template<const int rowsT, const int colsT>
class Matrix {

public:
  AbstractMatrix* data = NULL;


Matrix(const matrixType t = rectangular){
  switch(t){
    case rectangular: data = new RectangularMatrix<rowsT,colsT>(); break;
    case diagonal: data = new DiagonalMatrix<rowsT>(); break;
    case identity: data = new IdentityMatrix<rowsT>(); break;
  }
}

Matrix<rowsT, colsT>(const float pArr[rowsT][colsT]){
  data = new RectangularMatrix<rowsT,colsT>(pArr);
}

Matrix<rowsT, colsT>(const float pArr[rowsT], const matrixType t = diagonal){
  switch(t){
  case diagonal: data = new DiagonalMatrix<rowsT>(pArr); break;
  case rectangular: data = new RectangularMatrix<rowsT,colsT>(pArr); break;
  }
}



// Copy constructer
Matrix<rowsT, colsT>(const Matrix<rowsT, colsT> &rhs) {
data = rhs.data->clone();
}


~Matrix(){
  if (data){delete data; data = NULL;}
}


Matrix<rowsT, colsT>& operator=(Matrix<rowsT, colsT> const &rhs) {
  /*
      this = input matrix (rowsT x colsT)
      rhs = input matrix (rowsT x colsT)
      rowsT = number of rows in this and rhs
      colsT = number of columns in this and rhs
    */

  if (this == &rhs){
      return *this;
  }

  if (data){delete data;}
  data = rhs.data->clone();

  return *this;
}



//Assignemt with single float value
/*
     gives an easy way of filling the complete matrix with one value
     may be used to initialize a matrix, for exampe with '0':
     Matrix<1,3> A;
     A=0; //--> A=[0,0,0]
  */
void operator=(float const rhs) {
    *data = rhs;
}


//Element Access
/*Single elements of a Matrix may be accessed like this:
    Matrix<3,3> A;
    x of type float
    x = A(2,3); //get
    A(2,1) = x; //set
  */
float operator()(int pRow, int pCol = 1) const{

  return (*data)(pRow,pCol);
}

float& operator()(int pRow, int pCol = 1){

  return (*data)(pRow,pCol);
}



  //Addition
  Matrix<rowsT, colsT> operator+(Matrix<rowsT, colsT>const &rhs) const{
    /*
        this = input matrix (rowsT x colsT)
        rhs = input matrix (rowsT x colsT)
        ret = output matrix = (this + rhs) (rowsT x colsT)
        rowsT = number of rows in this and rhs
        colsT = number of columns in this and rhs
      */
    Matrix<rowsT, colsT> ret;
    ret = 0;
    for (int i = 1; i <= rowsT; ++i) {
      for (int j = 1; j <= colsT; ++j) {
        ret(i,j)= (*this)(i,j) + rhs(i,j);
      }
    }
    return ret;
  }



  //Subtraction
  Matrix<rowsT, colsT> operator-(Matrix<rowsT, colsT> const &rhs) const {
    /*
        this = input matrix (rowsT x colsT)
        rhs = input matrix (rowsT x colsT)
        ret = output matrix = (this - rhs) (rowsT x colsT)
        rowsT = number of rows in this and rhs
        colsT = number of columns in this and rhs
      */
    Matrix<rowsT, colsT> ret;
    for (int i = 1; i <= rowsT; ++i) {
      for (int j = 1; j <= colsT; ++j) {
        ret(i,j)= (*this)(i,j) - rhs(i,j);
      }
    }
    return ret;
  }


  //Addition assignment
  Matrix<rowsT, colsT>& operator+=(Matrix<rowsT, colsT> const &rhs) {
    /*
        this = input and output matrix = (this += rhs) (rowsT x colsT)
        rhs = input matrix (rowsT x colsT)
        rowsT = number of rows in this and rhs
        colsT = number of columns in this and rhs
      */
    for (int i = 1; i <= rowsT; i++) {
      for (int j = 1; j <= colsT; j++) {
        (*this)(i,j) += rhs(i,j);
      }
    }
    return *this;
  }


  //Subtraction assignment
  Matrix<rowsT, colsT>& operator-=(Matrix<rowsT, colsT> const &rhs) {
    /*
        this = input and output matrix = (this -= rhs) (rowsT x colsT)
        rhs = input matrix (rowsT x colsT)
        rowsT = number of rows in this and rhs
        colsT = number of columns in this and rhs
      */
    for (int i = 1; i <= rowsT; i++) {
      for (int j = 1; j <= colsT; j++) {
        (*this)(i,j) -= rhs(i,j);
      }
    }
    return *this;
  }


  //Multiplication
  template<const int pCT>
  Matrix<rowsT, pCT> operator*(Matrix<colsT, pCT> const &rhs) const {
    /*
        this = input matrix (rowsT x colsT)
        rhs = input matrix (colsT x pCT)
        ret = output matrix = (this * rhs) (rowsT x pCT)
        rowsT = number of rows in this
        colsT = number of columns in this = number of rows in rhs
        pCT = number of columns in rhs
      */
    Matrix<rowsT, pCT> ret;
    for (int i = 1; i <= rowsT; i++){
      for (int j = 1; j <= pCT; j++) {
        ret(i,j) = 0;
        for (int k = 1; k <= colsT; k++){
          ret(i,j) += (*this)(i,k) * rhs(k,j);
        }
      }
    }
    return ret;
  }


  //Transpose
  Matrix<colsT, rowsT> operator~() const {
    /*
        this = input matrix (rowsT x colsT)
        ret = output matrix = (Transpose of this) (colsT x rowsT)
        rowsT = number of rows in this
        colsT = number of columns in this
      */
    Matrix<colsT, rowsT> ret;
    for (int i = 1; i <= rowsT; i++)
      for (int j = 1; j <= colsT; j++)
        ret(j,i) = (*this)(i,j);
    return ret;
  }


  //Inversion
  Matrix<rowsT, rowsT> operator!() const {
    /*
        This function inverts a matrix based on the Gauss Jordan method.
        Specifically, it uses partial pivoting to improve numeric stability.
        The algorithm is drawn from those presented in
        NUMERICAL RECIPES: The Art of Scientific Computing.
      */

    /*
        this = input matrix (rowsT x rowsT)
        ret = result matrix (rowsT x rowsT)
        rowsT = number of rows = number of columns in this
      */

    int pivrow = 0;      // keeps track of current pivot row
    int k, i, j;         // k: overall index along diagonal; i: row index; j: col index
    int pivrows[rowsT];  // keeps track of rows swaps to undo at end
    float tmp;           // used for finding max value and making column swaps

    Matrix<rowsT, rowsT> ret;
    ret = *this;

    for (k = 1; k <= rowsT; k++) {
      //find pivot row, the row with biggest entry in current column
      tmp = 0;

      for (i = k; i <= rowsT; i++) {
        if (abs(ret(i,k)) >= tmp)  // 'Avoid using other functions inside abs()?'
        {
          tmp = abs(ret(i,k));
          pivrow = i;
        }
      }

      // check for singular matrix
      if (ret(pivrow,k) == 0.0f) {
        Serial.println("Inversion failed due to singular matrix");

        //ToDo error handling
        //return 0;
      }

      //Execute pivot (row swap) if needed
      if (pivrow != k) {
        // swap row k with pivrow
        for (j = 1; j <= rowsT; j++) {
          tmp = ret(k,j);
          ret(k,j) = ret(pivrow,j);
          ret(pivrow,j) = tmp;
        }
      }



      pivrows[k-1] = pivrow;  // record row swap (even if no swap happened)


      tmp = 1.0f / ret(k,k);  // invert pivot element
      ret(k,k) = 1.0f;        // This element of input matrix becomes result matrix

      // Perform row reduction (divide every element by pivot)
      for (j = 1; j <= rowsT; j++) {
        ret(k,j) = ret(k,j) * tmp;
      }



      // Now eliminate all other entries in this column
      for (i = 1; i <= rowsT; i++) {
        if (i != k) {
          tmp = ret(i,k);
          ret(i,k) = 0.0f;  // The other place where in matrix becomes result mat
          for (j = 1; j <= rowsT; j++) {
            ret(i,j) -=  ret(k,j) * tmp;
          }
        }
      }
    }

    // Done, now need to undo pivot row swaps by doing column swaps in reverse order

    for (k = rowsT -1; k >= 0; k--) {
      if (pivrows[k] != k+1) {
        for (i = 1; i <= rowsT; i++) {
          tmp = ret(i,k+1);
          ret(i,k+1) = ret(i,pivrows[k]);
          ret(i,pivrows[k]) = tmp;
        }
      }
    }

    return ret;
  }


  //Print
  /*
       Prints a matrix via Serial
       Uses spaces to separate numbers under assumption printed float width won't cause problems
    */
  void print() const {
    /*
        this = input matrix (rowsT x colsT)
        rowsT = number of rows in this
        colsT = number of columns in this
      */
    for (int i = 1; i <= rowsT; ++i) {
      for (int j = 1; j <= colsT; ++j) {
        Serial.print((*this)(i,j), 10);
        Serial.print("        ");
      }
      Serial.println();
    }
  }


};

#endif
