#include <string>
#include <math.h>
#include <iostream>
#include "../include/Sphere.h"
#include "../include/Cone.h"
#include "../include/Box.h"
#include "../include/Plane.h"
#include "../include/Model.h"
#include "../include/Torus.h"
#include "../include/Bezier.h"

// O generator tem que ter sempre os seus argumentos para trabalhar
// Cada uma das operações gera uma classe Model que fará a escrita dos dados calculados para um ficheiro .3d
int main(int argc, char **argv) {
	std::string filename;
	std::shared_ptr<Model> m;
    if (argc>2) {
        std::string type=std::string(argv[1]);
        if (type=="sphere") {
            if (argc!=6) {
                std::cout<< "Not enough arguments\n";
                return 1;
            }
            int radius=atoi(argv[2]),slices=atoi(argv[3]),stacks=atoi(argv[4]);
            Sphere s = Sphere(radius,slices,stacks);
            m=s.generate();
            filename=std::string(argv[5]);
        }
        else if (type=="cone") {
            if (argc!=7) {
                std::cout<< "Not enough arguments\n";
                return 1;
            }
            int radiusBase=atoi(argv[2]), height=atoi(argv[3]),slices=atoi(argv[4]),stacks=atoi(argv[5]);
            Cone c = Cone(radiusBase,height,slices,stacks);
            m=c.generate();
            filename=std::string(argv[6]);
        }
        else if (type=="torus") {
            if (argc!=7) {
                std::cout<< "Not enough arguments\n";
                return 1;
            }
            int widenessRadius=atoi(argv[2]), thicknessRadius=atoi(argv[3]),rings=atoi(argv[4]),sides=atoi(argv[5]);
            Torus t = Torus(widenessRadius,thicknessRadius,rings,sides);
            m=t.generate();
            filename=std::string(argv[6]);
        }
        else if (type=="box") {
            if (argc!=6 && argc!=7) {
                std::cout<< "Not enough arguments\n";
                return 1;
            }
            int width=atoi(argv[2]),depth=atoi(argv[3]),height=atoi(argv[4]);
            Box b = Box(width,depth,height,argc==6?0:atoi(argv[5]));
            m=b.generate();
            filename=std::string(argv[argc==6?5:6]);
        }
        else if (type=="plane") {
            if (argc!=4) {
                std::cout<< "Not enough arguments\n";
                return 1;
            }
            int side=atoi(argv[2]);
            Plane p = Plane(side);
            m=p.generate();
            filename=std::string(argv[3]);
        }
        else if (type=="bezier") {
            if (argc!=5) {
                std::cout<< "Not enough arguments\n";
                return 1;
            }
            std::string patch_file=std::string(argv[2]);
            int tesselation_level = atoi(argv[3]);
            Bezier b = Bezier(patch_file,tesselation_level);
            m=b.generate();
            filename=std::string(argv[4]);
        }
		else return 1;
        m->saveToFile(filename);
    }
}
