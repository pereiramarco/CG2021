#include <string>
#include <math.h>
#include <iostream>
#include "../include/Sphere.h"
#include "../include/Cone.h"
#include "../include/Box.h"
#include "../include/Plane.h"
#include "../include/Model.h"
#include "../include/Torus.h"


using namespace std;

int main(int argc, char **argv) {
	string filename;
	Model* m;
    if (argc>2) {
        string type=string(argv[1]);
        if (type=="sphere") {
            if (argc!=6) {
                cout<< "Not enough arguments\n";
                return 1;
            }
            int radius=atoi(argv[2]),slices=atoi(argv[3]),stacks=atoi(argv[4]);
            Sphere *s = new Sphere(radius,slices,stacks);
            m=s->generate();
            filename=string(argv[5]);
        }
        else if (type=="cone") {
            if (argc!=7) {
                cout<< "Not enough arguments\n";
                return 1;
            }
            int radiusBase=atoi(argv[2]), height=atoi(argv[3]),slices=atoi(argv[4]),stacks=atoi(argv[5]);
            Cone *c = new Cone(radiusBase,height,slices,stacks);
            m=c->generate();
            filename=string(argv[6]);
        }
        else if (type=="torus") {
            if (argc!=7) {
                cout<< "Not enough arguments\n";
                return 1;
            }
            int widenessRadius=atoi(argv[2]), thicknessRadius=atoi(argv[3]),rings=atoi(argv[4]),sides=atoi(argv[5]);
            Torus *t = new Torus(widenessRadius,thicknessRadius,rings,sides);
            m=t->generate();
            filename=string(argv[6]);
        }
        else if (type=="box") {
            if (argc!=6 && argc!=7) {
                cout<< "Not enough arguments\n";
                return 1;
            }
            int width=atoi(argv[2]),depth=atoi(argv[3]),height=atoi(argv[4]);
            Box *b = new Box(width,depth,height,argc==6?0:atoi(argv[5]));
            m=b->generate();
            filename=string(argv[argc==6?5:6]);
        }
        else if (type=="plane") {
            if (argc!=4) {
                cout<< "Not enough arguments\n";
                return 1;
            }
            int side=atoi(argv[2]);
            Plane *p = new Plane(side);
            m=p->generate();
            filename=string(argv[3]);
        }
		else return 1;
        m->saveToFile(filename);
    }
}
