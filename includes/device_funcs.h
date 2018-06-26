#ifndef DEVICE_FUNCS_H_
#define DEVICE_FUNCS_H_

float sigmoid(float x){
    return 1 / (1 + __expf(x));
}

float sigmoid_prime(float x){
    float sig = sigmoid(x);
    return sig (1 - sig);
}

#endif
