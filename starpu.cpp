//
// Created by nelly on 10/20/20.
//

#include "initial.h"
#include "starpu.h"

/**************************************************
		Решение для одной из частей
**************************************************/
void prefun(double &f, double &fd, double &p,
            double &dk, double &pk, double &ck)
{
    double ak, bk, pratio, qrt;

    if(p <= pk)
    {
        // волна разрежения
        pratio = p/pk;
        f	   = g4*ck*(pow(pratio,g1) - 1.0);
        fd     = (1.0/(dk*ck))*pow(pratio,-g2);

    }
    else
    {
        // ударная волна
        ak  = g5/dk;
        bk  = g6*pk;
        qrt = sqrt(ak/(bk + p));
        f   = (p - pk)*qrt;
        fd  = (1.0 - 0.5*(p - pk)/(bk + p)) * qrt;
    }

}

/**************************************************
		Вычисление начального приближения
**************************************************/
double guessp(gas left, gas right)
{
    double	cup, gel, ger,
            pmax, pmin, ppv, pq, pm,
            ptl, ptr,
            qmax, quser, um;

    /*** Вычисление приближения давления из PVRS решения Римана ***/
    quser = 2.0;
    cup = 0.25 * (left.r + right.r) * (left.c + right.c);
    ppv = 0.5 * (left.p + right.p) + 0.5 * (left.u - right.u) * cup;
    ppv = ppv > 0.0 ? ppv : 0.0;
    pmin = left.p > right.p ? right.p : left.p;
    pmax = left.p > right.p ? left.p : right.p;
    qmax = pmax/pmin;

    if( qmax<=quser && pmin<=ppv && ppv<=pmax )
    {
        pm = ppv;
    }
    else
    {
        if(ppv < pmin)
        {
            // две волны разрежения
            pq  = pow(left.p/right.p,g1);
            um  = (pq*left.u/left.c + right.u/right.c + g4*(pq - 1.0))/(pq/left.c + 1.0/right.c);
            ptl = 1.0 + g7*(left.u - um)/left.c;
            ptr = 1.0 + g7*(um - right.u)/right.c;
            pm  = 0.5*(left.p*pow(ptl,g3) + right.p*pow(ptr,g3));
        }
        else
        {
            // две ударных волны
            gel = sqrt((g5/left.r)/(g6*left.p + ppv));
            ger = sqrt((g5/left.r)/(g6*right.p + ppv));
            pm  = (gel*left.p + ger*right.p - (right.u - left.u))/(gel + ger);
        }

    }
    return pm;
}

/**************************************************
Определение давления и скорости контактного разрыва
**************************************************/
void starpu(double &p, double &u, gas left, gas right)
{
    int i;

    double pstart,	// начальное приближение давления
    pold,	// предыдущее приближение давления
    udiff,	// разность скоростей
    change;	// разность давлений

    double	fl, fld, // функции давления
    fr, frd;

    /*** Вычисление начального приближения ***/
    pstart = guessp(left, right);

    /*** Предыдущее приближение ***/
    pold = pstart;

    /*** Разность скоростей ***/
    udiff = right.u - left.u;

    /*** Метод Ньютона для определения давления ***/

    // разность между разными приближениями давлений
    change = 10.0 * EPS;

    for(i=0 ; i<MAX_ITER && change>EPS ; i++)
    {
        // решение для левой части
        prefun(fl,fld,pold,left.r,left.p,left.c);

        // решение для правой части
        prefun(fr,frd,pold,right.r,right.p,right.c);

        // очередное приближение давления
        p = pold - (fl + fr + udiff) / (fld + frd);

        // разность между разными приближениями давлений
        change = 2.0 * fabs((p-pold)/(p+pold));

        // если давление отрицательное, до обнуляем его
        if(p < 0.0) p =0.0;

        pold = p;
    }

    // определение скорости
    u = 0.5 * (left.u + right.u + fr - fl);
}
