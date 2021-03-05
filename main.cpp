#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "initial.h"
#include "sample.h"
#include "starpu.h"
#include <string>
#include "gas.h"

using namespace std;

#define sgn(x) x>0 ? 1 : -1
#define min(x, y) x<y ? x : y
#define abs(x) x>0 ? x : -x

double minmod(double x, double y)
{
  if (x * y > 0) {
//    cout << x << " " << y << endl;
      double f = sgn(x) * min (fabs(x), fabs(y));
//      cout << (min (abs(x), abs(y))) << "про" << endl;
      return (sgn(x) * min (fabs(x), fabs(y)));
  }
  else
      return 0;
};

int main()
{
/***** Параметры ударной трубы для соседних ячеек *****/
// Параметры слева
    gas left;
// Параметры справа
    gas right;

    char string[128];	// строка в файле конфигурации ударной трубы

    double	diaph,	// позиция разделителя
            len,	// размер области [0;len]
            time,	// время распада разрыва
            pm,		// давление по сторонам контактного разрыва
            um,		// скорость контактного разрыва
            dx,		// шаг по пространству
            xpos,	// текущая точка области
            ds,		// плотность в точке области
            ps,		// давление в точке области
            us,		// скорость в точке области
            s;		// характеристика

    double
            ctime,		// текущее времы
            tau,		// переменный шаг по времени
            umax,		// максимальная скорость плюс скорость звука
            u1,u2,u3;	// вспомогательные переменные скорости

    int numcells;	// количество ячеек
    int i, j=0;			// номер ячейки


    ifstream fin("shock_tube.dat");
    ofstream fout("output.txt"),
            fpressure("/home/nelly/CLionProjects/Godunov_Shock_Tube/Results/1000pointsP.txt"),
            fdensity("/home/nelly/CLionProjects/Godunov_Shock_Tube/Results/1000pointsR.txt"),
            fvelocity("/home/nelly/CLionProjects/Godunov_Shock_Tube/Results/1000pointsU.txt"),
            sound("/home/nelly/CLionProjects/Godunov_Shock_Tube/Results/sound.txt"),
            entropy("/home/nelly/CLionProjects/Godunov_Shock_Tube/Results/entropy.txt"),
            result100("/home/nelly/CLionProjects/Godunov_Shock_Tube/Results/test1.txt"),
//            result100("/home/nelly/CLionProjects/Godunov_Shock_Tube/Results/Godunov_result50.txt"),
            data("/home/nelly/CLionProjects/Godunov_Shock_Tube/Results/input_data.txt");
    double
            *R,		// плотность
            *P,		// давление
            *U,		// скорость
            *RU,		// импульс
            *RE;		// полная энергия

    double *FR,		// поток плотности
            *FRU,	// поток импульса
            *FRE;	// поток полной энергии

    /*** задание параметров трубы ***/
    // размер трубы [0;len]
    fin >> len;
    // позиция разделителя
    fin >> diaph;
    // время распада разрыва
    fin >> time;
    // параметры слева
    fin >> left.r; //плотность
    fin >> left.u; //скорость
    fin >> left.p; //давление

    left.c	= sqrt(GAMMA*left.p/left.r); //скорость звука

    // параметры справа
    fin >> right.r; //плотность
    fin >> right.u; //скорость
    fin >> right.p; //давление

    right.c	= sqrt(GAMMA*right.p/right.r);

    // количество ячеек
    fin >> numcells;

    data << setw(15) << "Пространство" << setw(15) << len << endl;
    data << setw(15) << "Разделитель" << setw(15) << diaph << endl;
    data << setw(15) << "Время" << setw(15) << time << endl;
    data << "Плотность" << endl << "Скорость" << endl << "Давление" << endl;
    data  << setw(20) << left.r << "|" << setw(20) << right.r << "|" << endl;
    data  << setw(20) << left.u << "|" << setw(20) << right.u << "|" << endl;
    data  << setw(20) << left.p << "|" << setw(20) << right.p << "|" << endl;

    /********************************/

    /*** Выделение памяти для массивов ***/
    R   = new double[numcells];
    P   = new double[numcells];
    U   = new double[numcells];
    RU  = new double[numcells];
    RE  = new double[numcells];
    FR  = new double[numcells-1];
    FRU = new double[numcells-1];
    FRE = new double[numcells-1];
    /*************************************/

    /*** Определение шага (размера ячейки) ***/
    dx = len/double(numcells);
    /*****************************************/

    /*** Инициализация начальных данных ***/
    for(i=0 ; i<numcells ; i++)
    {
        xpos = i*dx + 0.5*dx;
        if(xpos <= diaph)
        {
            R[i]  = left.r;
            P[i]  = left.p;
            U[i]  = left.u;
            RU[i] = left.r * left.u;
            RE[i] = left.p/g8 + 0.5 * left.r*left.u*left.u;
        }
        else
        {
            R[i]  = right.r;
            P[i]  = right.p;
            U[i]  = right.u;
            RU[i] = right.r * right.u;
            RE[i] = right.p/g8 + 0.5 * right.r*right.u*right.u;
        }
    }
    /**************************************/

/***** Вычислительный цикл метода Годунова *****/

    // определяем позицию
    xpos  = 1.0;
    // определяем размер
    len	  = 2.0;
    // определяем границу раздела
    diaph = 1.0;
    // определяем характеристику
    s = 0.0;
    // текущее время
    ctime = 0.0;

    while(ctime < time)
    {

        // нахождение переменного временного шага
        umax = 0.0;
        for(i=0 ; i<numcells ; i++)
        {
            u1 = fabs( U[i] + sqrt(GAMMA*P[i]/R[i]) );
            u2 = fabs( U[i] - sqrt(GAMMA*P[i]/R[i]) );
            u3 = fabs( U[i] );
            if(u1 > umax) umax = u1;
            if(u2 > umax) umax = u2;
            if(u3 > umax) umax = u3;
        }

        // определим шаг по времени
        tau = CFL*dx/umax;
        // ограничим его
        if(ctime + tau > time) tau = time - ctime;

        // находим значение потоков на границе ячеек
        for(i=1; i<numcells; i++)
        {
            // левая сторона
            left.r = R[i-1];
            left.p = P[i-1];
            left.u = U[i-1];
            left.c = sqrt(GAMMA*left.p/left.r);
            // правая сторона
            right.r = R[i];
            right.p = P[i];
            right.u = U[i];
            right.c = sqrt(GAMMA*right.p/right.r);

            // Проверка образования области вакуума
            if( g4*(left.c+right.c) <= (right.u-left.u) )
            {
                printf("*** Generated vacuum ***\n");
                return -1;
            }

            // Нахождение точного решения давления и скорости контактного разрыва
            starpu(pm,um, left, right);

            // Решение задачи распада разрыва
            starpu(pm,um, left, right);
//            cout << ctime << " " << i << " " << pm << " " << um << endl;
            sample(pm, um, s, ds, us, ps, left, right);

//            cout << ds << " " << us << " "  << ps << endl;
            // Формирование потоков
            FR[i-1]  = ds*us;
            FRU[i-1] = ds*us*us + ps;
            FRE[i-1] = (ps/g8 + 0.5*ds*us*us)*us + ps*us;
//            cout << i << " "<<  FR[i-1] << " " << FRU[i-1] << " " << FRE[i-1] << endl;
        }

        // реализация разностной схемы
        for(i=1 ; i<numcells-1 ; i++)
        {
//            cout << i << " "<<  R[i] << " " << RU[i] << " " << RE[i] << endl;
            R[i]  = R[i]  - tau * ( FR[i]  - FR[i-1]  )/dx;
            RU[i] = RU[i] - tau * ( FRU[i] - FRU[i-1] )/dx;
            RE[i] = RE[i] - tau * ( FRE[i] - FRE[i-1] )/dx;
//            cout << i << " "<<  R[i] << " " << RU[i] << " " << RE[i] << endl;

        }

        // постановка краевых условий
//        R[0] = R[1];
        R[numcells-1] = R[numcells-2];
//        RU[0] = RU[1];
        RU[numcells-1] = RU[numcells-2];
//        RE[0] = RE[1];
        RE[numcells-1] = RE[numcells-2];

        // пересчёт скорости и давления
        for(i=0 ; i<numcells ; i++)
        {
            U[i] = RU[i]/R[i];
            P[i] = g8 * ( RE[i] - 0.5 * RU[i] * U[i] );
        }
/*        for (int i=0; i< numcells; i++)
        {
            cout << i << " "<<  R[i] << " " << U[i] << " " << P[i] << endl;
        }*/

        ctime += tau;
        cout << ctime << endl;
    }

/***********************************************/


    /*** Вывод решения ***/
    for(i=0 ; i<numcells ; i++)
    {
        xpos = i*dx + 0.5*dx;
        /*****************************************************
         | x | density | speed |  pressure | internal energy |
        *****************************************************/
        ds = R[i];
        us = U[i];
        ps = P[i];
        result100 << fixed;
        result100 << setprecision(6) << xpos << " " << setprecision(6) << ds << " " << setprecision(6)  << us << " " <<setprecision(6)  << ps << endl;
/*        fout << setw(10) << xpos << setw(10) << ds << setw(10) << us << setw(10) << ps << setw(10) << ps/ds/g8;
        fpressure << setw(15) << xpos << setw(15) << ps << endl;
        fvelocity << setw(15) << xpos << setw(15) << us << endl;
        fdensity << setw(15) << xpos << setw(15) << ds << endl;
        entropy << setw(15) << xpos << setw(15) << ps/(pow(ds, GAMMA)) << endl;
        sound << setw(15) << xpos << setw(15) <<  us/sqrt(GAMMA*ps/ds) << endl;*/
    }

//     system(" python /home/nelly/CLionProjects/Godunov_Shock_Tube/Results/plots.py");

    //закрыть файлы

    /*** Удаление памяти массивов ***/
    delete[] R;
    delete[] P;
    delete[] U;
    delete[] RU;
    delete[] RE;
    delete[] FR;
    delete[] FRU;
    delete[] FRE;

    /********************************/

    return 0;
}
