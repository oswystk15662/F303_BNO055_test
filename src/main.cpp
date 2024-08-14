#include <mbed.h>
#include <BNO055.hpp>

using ThisThread::sleep_for;

BNO055 bno(PA_9, PA_10);
Timer t;

int main() {
  float degrees[3] = {0};
  float offset[3] = {0};

  t.start();
  while(t.read_ms() <= 5000){
    float data[3];
    bno.getRadians(data);

    for(int i = 0; i < 3; i++){
      offset[i] += data[i];
    }
  }

  t.stop();

  while (1) {
    bno.getDegrees(degrees);
    printf("x : %d, y : %d, z : %d\n",
            (int)(degrees[0] - offset[0] * 1),
            (int)(degrees[1] - offset[1] * 1),
            (int)(degrees[2] - offset[2] * 1));
    sleep_for(100);
  }
}