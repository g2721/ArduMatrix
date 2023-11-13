#ifndef abstractMatrix_h
#define abstractMatrix_h

class AbstractMatrix {
public:
  //virtual float operator()(int pRow, int pCol) const =0;
  virtual float& operator()(int pRow, int pCol) = 0;
  virtual AbstractMatrix* clone() = 0;
  virtual void operator=(float const rhs) = 0;

};
#endif
