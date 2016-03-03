#include <iostream>
#include "Visualizer/viewer.hpp"

#include "Simulator/Simulator.hpp"



int main(int argc, char *argv[])
{
    dimension_t x = 100;
    dimension_t y = x;
    dimension_t z = 1;

    std::vector<fluidInitParams_t> fluid = { fluidInitParams_t(0.01, 1, 1), fluidInitParams_t(0.01, 1, 1) };
    spaceDimensions_t dims = spaceDimensions_t(x, y, z);

    Simulator life(dims, fluid);

    Viewer* viewer = new Viewer(life.getConfig(),x,y,z);
    //Viewer* viewer = new Viewer(NULL,x,y,z);

    while (!viewer->getViewer()->done()) {
        viewer->getViewer()->frame();
        life.calculateNextConfig();
        viewer->updateFromGrid(life.getConfig());
    }

}
