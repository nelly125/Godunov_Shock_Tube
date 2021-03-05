//
// Created by nelly on 10/20/20.
//

#ifndef GODUNOV_SHOCK_TUBE_INITIAL_H
#define GODUNOV_SHOCK_TUBE_INITIAL_H

#define EPS		1.0e-10	// точность решения нелинейного уравнения
#define MAX_ITER	20	// количество итераций для решения нелинейного уравнения
#define CFL		0.4	// число Куранта

/***** Константы из показателя адиабаты *****/
const double	GAMMA = 1.4,
        g1 = (GAMMA - 1.0)/(2.0*GAMMA),
        g2 = (GAMMA + 1.0)/(2.0*GAMMA),
        g3 = 2.0*GAMMA/(GAMMA - 1.0),
        g4 = 2.0/(GAMMA - 1.0),
        g5 = 2.0/(GAMMA + 1.0),
        g6 = (GAMMA - 1.0)/(GAMMA + 1.0),
        g7 = (GAMMA - 1.0)/2.0,
        g8 = GAMMA - 1.0;


#endif //GODUNOV_SHOCK_TUBE_INITIAL_H
