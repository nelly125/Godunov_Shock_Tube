//
// Created by nelly on 10/20/20.
//

#ifndef GODUNOV_SHOCK_TUBE_STARPU_H
#define GODUNOV_SHOCK_TUBE_STARPU_H

#include <cmath>
#include "gas.h"

double guessp(gas left, gas right);
void starpu(double &p, double &u, gas left, gas right);
void prefun(double &f, double &fd, double &p,
            double &dk, double &pk, double &ck);


#endif //GODUNOV_SHOCK_TUBE_STARPU_H
