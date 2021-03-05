//
// Created by nelly on 10/20/20.
//

#include "sample.h"
#include "initial.h"

/**************************************************
 Получение плотности, давления и скорости в точке
**************************************************/
//на входе давление по сторонам контактного разрыва, скорость контактного разрыва,характеристика,
void sample(double &pm, double &um, double &s,
            double &d, double &u, double &p, gas left, gas right)
{
    double c, cml, cmr, pml, pmr, shl, shr, sl, sr, stl, str;

    if(s <= um)
    {
        // точка слева от контактного разрыва
        if(pm <= left.p)
        {
            // левая волна разрежения
            shl = left.u - left.c;

            if(s <= shl)
            {
                // точка слева
                d = left.r;
                u = left.u;
                p = left.p;
            }
            else
            {
                cml = left.c * pow(pm/left.p,g1);
                stl = um - cml;

                if( s > stl )
                {
                    // точка слева от контактного разрыва
                    d = left.r * pow(pm/left.p,1.0/GAMMA);
                    u = um;
                    p = pm;
                }
                else
                {
                    // точка в волне разрежения
                    u = g5 * (left.c + g7*left.u + s);
                    c = g5 * (left.c + g7*(left.u-s));
                    d = left.r*pow(c/left.c,g4);
                    p = left.p*pow(c/left.c,g3);
                }
            }
        }
        else
        {
            // левая ударная волна
            pml = pm/left.p;
            sl  = left.u - left.c * sqrt(g2*pml + g1);

            if( s <= sl )
            {
                // точка слева от ударной волны
                d = left.r;
                u = left.u;
                p = left.p;
            }
            else
            {
                // точка слева от контактного разрыва
                d = left.r * (pml + g6)/(pml*g6 + 1.0);
                u = um;
                p = pm;
            }
        }
    }
    else
    {
        // точка справа от контактного разрыва
        if( pm > right.p )
        {
            // правая ударная волна
            pmr = pm/right.p;
            sr  = right.u + right.c * sqrt(g2*pmr + g1);

            if( s >= sr )
            {
                // точка справа от ударной волны
                d = right.r;
                u = right.u;
                p = right.p;
            }
            else
            {
                // точка справа от контактного разрыва
                d = right.r * (pmr + g6)/(pmr*g6 + 1.0);
                u = um;
                p = pm;
            }
        }
        else
        {
            // правая волна разрежения
            shr = right.u + right.c;

            if( s >= shr )
            {
                // точка справа от волны разрежения
                d = right.r;
                u = right.u;
                p = right.p;
            }
            else
            {
                cmr = right.c * pow(pm/right.p,g1);
                str = um + cmr;

                if( s <= str )
                {
                    // точка справа от контактного разрыва
                    d = right.r * pow(pm/right.p,1.0/GAMMA);
                    u = um;
                    p = pm;
                }
                else
                {
                    // точка в левой волне разрежения
                    u = g5 * (-right.c + g7*right.u + s);
                    c = g5 * (right.c - g7*(right.u-s));
                    d = right.r * pow(c/right.c,g4);
                    p = right.p * pow(c/right.c,g3);
                }
            }
        }
    }

}
