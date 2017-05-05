#include <vector>

#include "body.cpp"

#ifndef BODY_H
#define BODY_H

class body{
    public:
        body();
        void initBody(double,double,double,char*);
        void addToVectors(double*, double*);
        double frictionF(double, double);
        double upwardForceF();
        double totalForceF();
        double reactionForceF(double, double);
        double newton2forceF();
        void touch(double, double, char*);
        template <class T>
        int findV(std::vector<T>, T);
        double myy(char*, char*);
        double gravityF();
        
        double xloc;
        double yloc;
        double mass;
        double acceleration;
        double accelerationAngle;
        const char* material;
        const double g = 9.8;
        
        std::vector<double*> allForces;
        std::vector<double*> allForcesAngles;
        std::vector<std::vector <double> > plane;
        std::vector<double> touchX;
        std::vector<double> touchY;
        std::vector<const char*> mat;
        
        double friction = 0;
        double upwardForce = 0;
        double totalForce = 0;
        double reactionForce = 0;
        double newton2force = 0;
        double gravity = 0;
        
        double frictionAngle = 0;
        double upwardForceAngle = 90;
        double totalForceAngle = 0;
        double reactionForceAngle = 0;
        double newton2forceAngle = 0;
        double gravityAngle = 270;    
};

#endif