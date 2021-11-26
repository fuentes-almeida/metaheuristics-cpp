#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "memo.hpp"
#include "functions.hpp"
#include "EvoDiff.h"

void CopyIndividual(int d, double *src, double *dst)
{
    for (int i=0;i<d;i++)
        dst[i]=src[i];
}

void InitPopulation(int N, int d, double xmin, double xmax, double **P, function fx, double *Fitness, int *Ibest, double *Fbest)
{
    double rank=xmax-xmin, mini=1e15;
    int imin;

    for (int i=0;i<N;i++)
    {
        for (int j=0;j<d;j++)
            P[i][j]=rank*rand()/RAND_MAX+xmin;

        Fitness[i]=fx(d,P[i]);
        if (Fitness[i]<mini)
        {
            mini=Fitness[i];
            imin=i;
        }
    }
    *Ibest=imin;
    *Fbest=Fitness[imin];
}

void Mutation(int N, int d, double xmin, double xmax, double **X, double **V, int Ibest, double Factor)
{
    int r1,r2,r3,r4;

    for (int i=0;i<N;i++)
    {
        do { r1=rand()%N; } while (r1==i);
        do { r2=rand()%N; } while (r2==i || r2==r1);
        do { r3=rand()%N; } while (r3==i || r3==r1 || r3==r2);
        do { r4=rand()%N; } while (r4==i || r4==r1 || r4==r2 || r4==r3);

        for (int j=0;j<d;j++)
        {
            double aux=X[r1][j]+Factor*(X[r2][j]-X[r3][j]);
            //double aux=X[i][j]+Factor*((X[Ibest][j]-X[i][j])+(X[r1][j]-X[r2][j]));
            //double aux=X[Ibest][j]+Factor*(X[r2][j]-X[r3][j]);
            //double aux=X[Ibest][j]+Factor*(X[r1][j]-X[r2][j])+Factor*(X[r3][j]-X[r4][j]);
            if (aux>xmax)
                aux-=(aux-xmax);
            if (aux<xmin)
                aux+=(xmin-aux);
            V[i][j]=aux;
        }
    }
}

void Crossover(int N, int d, double **X, double **V, double **U, double CR, int jrand)
{
    for (int i=0;i<N;i++)
    {
        double aux=1.0*rand()/RAND_MAX;

        if (aux<=CR || i==jrand)
            CopyIndividual(d,V[i],U[i]);
        else
            CopyIndividual(d,X[i],U[i]);
    }
}

void Selection(int N, int d, double **X, double **U, function fx, double *Fitness, int *Ibest, double *Fbest)
{
    for (int i=0;i<N;i++)
    {
        double fitness_new=fx(d,U[i]);

        if (fitness_new < Fitness[i])
        {
            CopyIndividual(d,U[i],X[i]);
            Fitness[i]=fitness_new;
            if (fitness_new < *Fbest)
            {
                *Fbest=fitness_new;
                *Ibest=i;
            }
        }
    }
}

double DifferentialEvol(int N, int d, function fx, double xmin, double xmax, double CR, double Factor)
{
    int MaxIte=1e5*d/N, k=0, Ibest;
    int r1,r2,r3,r4;
    double Fbest=1000;

    double **X=RequestMatrixDoubleMem(N,d);
    double *Fitness=RequestVectorDoubleMem(N);
    double *test=RequestVectorDoubleMem(d);

    InitPopulation(N,d,xmin,xmax,X,fx,Fitness,&Ibest,&Fbest);

    while (Fbest>1e-8 && k<MaxIte)
    {
        int jrand=rand()%N;

        for (int i=0;i<N;i++)
        {
            do { r1=rand()%N; } while (r1==i);
            do { r2=rand()%N; } while (r2==i || r2==r1);
            do { r3=rand()%N; } while (r3==i || r3==r1 || r3==r2);
            do { r4=rand()%N; } while (r4==i || r4==r1 || r4==r2 || r4==r3);

            for (int j=0;j<d;j++)
            {
                double aux=X[r1][j]+Factor*(X[r2][j]-X[r3][j]);
                //double aux=X[i][j]+Factor*((X[Ibest][j]-X[i][j])+(X[r1][j]-X[r2][j]));
                //double aux=X[Ibest][j]+Factor*(X[r2][j]-X[r3][j]);
                //double aux=X[Ibest][j]+Factor*(X[r1][j]-X[r2][j])+Factor*(X[r3][j]-X[r4][j]);
                if (aux>xmax)
                    aux-=(aux-xmax);
                if (aux<xmin)
                    aux+=(xmin-aux);
                test[j]=aux;
            }

            double aux=1.0*rand()/RAND_MAX;

            if (aux<=CR || i==jrand)
            {
                double fitness_new=fx(d,test);

                if (fitness_new < Fitness[i])
                {
                    CopyIndividual(d,test,X[i]);
                    Fitness[i]=fitness_new;
                    if (fitness_new < Fbest)
                    {
                        Fbest=fitness_new;
                        Ibest=i;
                    }
                }
            }
        }
        printf("%d %lf %e\n",k, Fbest,Fbest);
        k++;
    }
    printf("%.1lf %.1lf %d %lf %e\n",CR,Factor,k, Fbest,Fbest);
    return Fbest;
}

