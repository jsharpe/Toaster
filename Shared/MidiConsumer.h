#ifndef MIDICONSUMER_H
#define MIDICONSUMER_H

#include "Commons.h"

class IMidiConsumer {
public:
  virtual void consume(const ByteArray &msg) = 0;
  virtual unsigned char getStatusByte() = 0;
};

#endif // MIDICONSUMER_H
