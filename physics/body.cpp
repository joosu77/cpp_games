#include <math.h>
#include <vector>

#include "body.h"

body::body(){
    addToVectors(friction*, frictionAngle*);
    addToVectors(upwardForce*, upwardForceAngle*);
    addToVectors(reactionForce*, reactionForceAngle*);
    addToVectors(newton2force*, newton2forceAngle*);
    addToVectors(gravity*, gravityAngle*);
    
    plane.push_back(touchX);
    plane.push_back(touchY); 
    plane.push_back(mat);
}

void body::initBody(double xl, double yl, double m, char* mat){
    this->xloc = xl;
    yloc = yl;
    mass = m;
    material = mat;
}

void body::addToVectors(double* in, double* ang){
    allForces.push_back(&in);
    allForcesAngles.push_back(&ang);
}

double body::frictionF(double tochX, double tochY){
    int pos = findV(plane[0], tochX);
    friction = myy(plane[2][pos], material)*reactionForce(tochX, tochY);
    if (totalForceAngle>reactionForceAngle && totalForceAngle<(reactionForceAngle+180)){
        frictionAngle = reactionForceAngle+90;
    } else {
        frictionAngle = reactionForceAngle-90;
    }
    return friction;
}

double body::upwardForceF(){
    upwardForce = 0;
    for (int i=0;i<allForces.size();i++){
        upwardForce += allForces[i] * math::sin(allForcesAngles[i]);
    }
    return upwardForce;
}

double body::totalForceF(){
    upwardForce = upwardForcex = upwardForcey = 0;
    for (int i=0;i<allForces.size();i++){
        double forceX = allForces[i]*cos(allForcesAngles[i]);
        double forceY = allForces[i]*sin(allForcesAngles[i]);
        totalForcex += forceX;
        totalForcey += forceY;
    }
    totalForce = sqrt(totalForceX **2 + totalForceY **2);
    totalForceAngle = math::arctan(totalForceY/totalForceX);
    return totalForce;
}

double body::reactionForceF(double xTouch, double yTouche){
    reactionForceAngle = arccos(math::sqrt(max(xTouch, xloc)-min(xTouch, xloc)+max(yTouch,yloc)-min(yTouch,yloc))/max(xTouch, xloc)-min(xTouch, xloc));
    reactionForce = totalForce()*math::cos(180-totalForceAngle+reactionForceAngle);
    return reactionForce;
    
}

double body::newton2forceF(){
    newton2froce = mass * acceleration;
    newton2forceAngle = accelerationAngle;
    return newton2force;
}

void body::touch(double posX, double posY, char* material){
    if (findV(plane[0], posX) != -1 && findV(plane[1], posY) != -1){
        plane[0].push_back(posX);
        plane[1].push_back(posY);
        plane[2].push_back(material);
    } else {
        int pos = findV(plane[0], posX);
        plane[0].erase(pos);
        plane[1].erase(pos);
        plane[2].erase(pos);
    }
}

template <class T>;
int body::findV(std::vector<T> vec, T var){
    for(int i=0;i<vec.size();i++){
        if (vec[i] == var){
            return i;
        }
    }
    return -1;
}

double myy(char* m1, char* m2){
    std::vector<std::vector <double> > table;
    // materjalid: 1 metall, 2puit...
    int mats = 2;
    std::vector<const*> matsV;
    matsV.push_back("metall");
    matsV.push_back("puit");
    for (int i=0;i<mats;i++){
        table.push_back(std::vector<double>);
        for (int u=0;u<mats;u++){
            double conmy = 0.5;
            table[i].push_back(conmy);
        }
    }
    int m1pos = findV(matsV,m1);
    int m2pos = findV(matsV,m2);
    return table[m1pos][m2pos];
}

double gravityF(){
    gravity = mass*g;
    return gravity;
}