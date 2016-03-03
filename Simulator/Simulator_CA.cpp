/**
 * @file Simulator_CA.cpp
 * @author Diego Rodríguez Boy
 * @brief Implementation of the Simulator_CA class.
 */


#include <random>
#include "Simulator_CA.hpp"


// Constructors
/**
 * @details Initialize everything to 0 and @a nullptr.
 */
Simulator_CA::Simulator_CA() : Simulator_CA(spaceDimensions_t(), std::vector<fluidInitParams_t>())
{
}



/**
 * @todo Manage CUDA memory.
 */
Simulator_CA::Simulator_CA(const Simulator_CA& that) : CellularAutomaton(that)
{
    this->fluidInitParams = that.fluidInitParams;
    this->numFluids = that.numFluids;
    this->numCells = that.numCells;

    delete[] this->lattice;
    this->lattice = new Cell[this->numCells];

    for(dimension_t i = 0; i < this->numCells; i++)
    {
        this->lattice[i] = Cell(1, 0, 0, this->numFluids);
    }
}



/**
 * @todo Manage CUDA memory.
 */
Simulator_CA::Simulator_CA(Simulator_CA&& that) : CellularAutomaton(that)
{
    this->fluidInitParams = that.fluidInitParams;
    this->numFluids = that.numFluids;
    this->numCells = that.numCells;

    delete[] this->lattice;
    this->lattice = new Cell[this->numCells];

    for(dimension_t i = 0; i < this->numCells; i++)
    {
        this->lattice[i] = that.lattice[i];
    }

    that.fluidInitParams.erase(that.fluidInitParams.begin(), that.fluidInitParams.end());
    that.numFluids = 0;
    that.numCells = 0;

    delete[] that.lattice;
}



/**
  * @todo Manage CUDA memory.
  */
//Simulator_CA::Simulator_CA(const Model &parsedModel, const std::vector<fluidInitParams_t>& fluidInitParams)
Simulator_CA::Simulator_CA(const spaceDimensions_t dimensions, std::vector<fluidInitParams_t> fluidInitParams)
{
    this->dimensions = dimensions;
    this->states = std::unordered_set<cellState_t>({0, 1});

    this->fluidInitParams = fluidInitParams;
    this->numFluids = fluidInitParams.size();

    this->numCells = dimensions.x * dimensions.y * dimensions.z;
    this->lattice = new Cell[this->numCells];
    this->buffer_d = new Cell[this->numCells];


    this->init();
}



// Destructor
/**
 * @todo Manage CUDA memory.
 */
Simulator_CA::~Simulator_CA()
{
    delete[] this->lattice;
    delete[] this->buffer_d;
}



// Operators
/**
 * @todo Manage CUDA memory.
 */
Simulator_CA& Simulator_CA::operator =(const Simulator_CA& that)
{
    if(this != &that)
    {
        CellularAutomaton::operator =(that);

        this->fluidInitParams = that.fluidInitParams;
        this->numFluids = that.numFluids;
        this->numCells = that.numCells;

        delete[] this->lattice;
        this->lattice = new Cell[this->numCells];

        for(dimension_t i = 0; i < this->numCells; i++)
        {
            this->lattice[i] = that.lattice[i];
        }
    }

    return *this;
}



/**
 * @todo Manage CUDA memory.
 */
Simulator_CA& Simulator_CA::operator =(Simulator_CA&& that)
{
    if(this != &that)
    {
        CellularAutomaton::operator =(that);

        this->fluidInitParams = that.fluidInitParams;
        this->numFluids = that.numFluids;
        this->numCells = that.numCells;

        delete[] this->lattice;
        this->lattice = new Cell[this->numCells];

        for(dimension_t i = 0; i < this->numCells; i++)
        {
            this->lattice[i] = that.lattice[i];
        }

        that.fluidInitParams.erase(that.fluidInitParams.begin(), that.fluidInitParams.end());
        that.numFluids = 0;
        that.numCells = 0;

        delete[] that.lattice;
    }

    return *this;
}



// Getters
const Cell* Simulator_CA::getConfig()
{
    const Cell* config = this->lattice;

    return config;
}



// Functions
void Simulator_CA::transition()
{
    static const int max_x = this->dimensions.x;
    static const int max_y = this->dimensions.y;
    static const int mask[] = {1, 2, 4, 8, 16, 32};

    for(int y = 0; y < max_y; y++)
    {
        for(int x = 0; x < max_x; x++)
        {
            cellState_t stateCurrent = this->lattice[max_x * y + x].getState();
            bool bounce_x = (x == 0 || x == max_x - 1);
            bool bounce_y = (y == 0 || y == max_y - 1);
            cellState_t state = 0;

            Cell currentCell = this->lattice[max_x * y + x];
            Cell bounceCell(6, currentCell.getType(), 0, this->numFluids);

            if(bounce_x)
            {
                if((stateCurrent & mask[0]) != 0)
                {
                    state |= mask[3];
                    bounceCell.setParticle(currentCell.getParticle(0), 3);
                }

                if((stateCurrent & mask[1]) != 0)
                {
                    state |= mask[2];
                    bounceCell.setParticle(currentCell.getParticle(1), 2);
                }

                if((stateCurrent & mask[2]) != 0)
                {
                    state |= mask[1];
                    bounceCell.setParticle(currentCell.getParticle(2), 1);
                }

                if((stateCurrent & mask[3]) != 0)
                {
                    state |= mask[0];
                    bounceCell.setParticle(currentCell.getParticle(3), 0);
                }

                if((stateCurrent & mask[4]) != 0)
                {
                    state |= mask[5];
                    bounceCell.setParticle(currentCell.getParticle(4), 5);
                }

                if((stateCurrent & mask[5]) != 0)
                {
                    state |= mask[4];
                    bounceCell.setParticle(currentCell.getParticle(5), 4);
                }
            }
            else if(bounce_y)
            {
                if((stateCurrent & mask[0]) != 0)
                {
                    state |= mask[3];
                    bounceCell.setParticle(currentCell.getParticle(0), 3);
                }

                if((stateCurrent & mask[1]) != 0)
                {
                    state |= mask[5];
                    bounceCell.setParticle(currentCell.getParticle(1), 5);
                }

                if((stateCurrent & mask[2]) != 0)
                {
                    state |= mask[4];
                    bounceCell.setParticle(currentCell.getParticle(2), 4);
                }

                if((stateCurrent & mask[3]) != 0)
                {
                    state |= mask[0];
                    bounceCell.setParticle(currentCell.getParticle(3), 0);
                }

                if((stateCurrent & mask[4]) != 0)
                {
                    state |= mask[2];
                    bounceCell.setParticle(currentCell.getParticle(4), 2);
                }

                if((stateCurrent & mask[5]) != 0)
                {
                    state |= mask[1];
                    bounceCell.setParticle(currentCell.getParticle(5), 1);
                }
            }
            else
            {
                if(stateCurrent == 21)
                {
                    state = 42;
                    bounceCell.setParticle(currentCell.getParticle(0), 1);
                    bounceCell.setParticle(currentCell.getParticle(2), 3);
                    bounceCell.setParticle(currentCell.getParticle(4), 5);
                }
                else if(stateCurrent == 42)
                {
                    state = 21;
                    bounceCell.setParticle(currentCell.getParticle(1), 0);
                    bounceCell.setParticle(currentCell.getParticle(3), 2);
                    bounceCell.setParticle(currentCell.getParticle(5), 4);
                }
                else if(stateCurrent == 9)
                {
                    double p = (double)rand() / RAND_MAX;

                    if(p < 0.5)
                    {
                        state = 18;
                        bounceCell.setParticle(currentCell.getParticle(0), 1);
                        bounceCell.setParticle(currentCell.getParticle(3), 4);
                    }
                    else
                    {
                        state = 36;
                        bounceCell.setParticle(currentCell.getParticle(0), 2);
                        bounceCell.setParticle(currentCell.getParticle(3), 5);
                    }
                }
                else if(stateCurrent == 18)
                {
                    double p = (double)rand() / RAND_MAX;

                    if(p < 0.5)
                    {
                        state = 9;
                        bounceCell.setParticle(currentCell.getParticle(1), 0);
                        bounceCell.setParticle(currentCell.getParticle(4), 3);
                    }
                    else
                    {
                        state = 36;
                        bounceCell.setParticle(currentCell.getParticle(1), 2);
                        bounceCell.setParticle(currentCell.getParticle(4), 5);
                    }
                }
                else if(stateCurrent == 36)
                {
                    double p = (double)rand() / RAND_MAX;

                    if(p < 0.5)
                    {
                        state = 18;
                        bounceCell.setParticle(currentCell.getParticle(2), 1);
                        bounceCell.setParticle(currentCell.getParticle(5), 4);
                    }
                    else
                    {
                        state = 9;
                        bounceCell.setParticle(currentCell.getParticle(2), 0);
                        bounceCell.setParticle(currentCell.getParticle(5), 3);
                    }
                }
                else
                {
                    state = stateCurrent;
                    bounceCell = currentCell;
                }
            }

            bounceCell.setState(state);
            this->lattice[max_x * y + x] = bounceCell;
        }
    }


    for(int y = 0; y < max_y; y++)
    {
        for(int x = 0; x < max_x; x++)
        {
            int state = 0;
            int offset = y & 1;
            int inv_offset = 1 - offset;

            if(x < max_x - 1)
            {
                state |= this->lattice[max_x * y + (x + 1)].getState() & mask[0];
                Particle* movedParticle = this->lattice[max_x * y + (x + 1)].getParticle(0);
                this->buffer_d[max_x * y + x].setParticle(movedParticle, 0);
            }

            if(y < max_y - 1 && (x < max_x - 1 || inv_offset == 0))
            {
                state |= this->lattice[max_x * (y + 1) + (x + inv_offset)].getState() & mask[1];
                Particle* movedParticle = this->lattice[max_x * (y + 1) + (x + inv_offset)].getParticle(1);
                this->buffer_d[max_x * y + x].setParticle(movedParticle, 1);
            }

            if(y < max_y - 1 && (x > 0 || offset == 0))
            {
                state |= this->lattice[max_x * (y + 1) + (x - offset)].getState() & mask[2];
                Particle* movedParticle = this->lattice[max_x * (y + 1) + (x - offset)].getParticle(2);
                this->buffer_d[max_x * y + x].setParticle(movedParticle, 2);
            }

            if(x > 0)
            {
                state |= this->lattice[max_x * y + (x - 1)].getState() & mask[3];
                Particle* movedParticle = this->lattice[max_x * y + (x - 1)].getParticle(3);
                this->buffer_d[max_x * y + x].setParticle(movedParticle, 3);
            }

            if(y > 0 && (x > 0 || offset == 0))
            {
                state |= this->lattice[max_x * (y - 1) + (x - offset)].getState() & mask[4];
                Particle* movedParticle = this->lattice[max_x * (y - 1) + (x - offset)].getParticle(4);
                this->buffer_d[max_x * y + x].setParticle(movedParticle, 4);
            }

            if(y > 0 && (x < max_x - 1 || inv_offset == 0))
            {
                state |= this->lattice[max_x * (y - 1) + (x + inv_offset)].getState() & mask[5];
                Particle* movedParticle = this->lattice[max_x * (y - 1) + (x + inv_offset)].getParticle(5);
                this->buffer_d[max_x * y + x].setParticle(movedParticle, 5);
            }

            this->buffer_d[max_x * y + x].setState(state);
        }
    }


    std::swap(this->lattice, this->buffer_d);
}



void Simulator_CA::transition_CUDA()
{

}

#include <iostream>
using namespace std;

void Simulator_CA::init()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<> distribution(0, 1);

    std::default_random_engine int_generator;
    std::uniform_int_distribution<int> int_distribution(0, 5);

    double random;
    concentration_t hotFluid = this->fluidInitParams[0].concentration;
    concentration_t coldFluid = this->fluidInitParams[1].concentration;

    for(dimension_t y = 0; y < this->dimensions.y; y++)
    {
        for(dimension_t x = 0; x < this->dimensions.x; x++)
        {
            bool zero_position = (x == 0 || y == 0);
            bool max_position = (x == this->dimensions.x - 1 || y == this->dimensions.y - 1);

            if(zero_position || max_position)
            {
                this->lattice[this->dimensions.x * y + x] = Cell(6, spacePointType_e::wall, 0, this->numFluids);
                this->buffer_d[this->dimensions.x * y + x] = Cell(6, spacePointType_e::wall, 0, this->numFluids);
            }
            else
            {
                random = distribution(generator);

                this->lattice[this->dimensions.x * y + x] = Cell(6, spacePointType_e::empty, 0, this->numFluids);
                this->buffer_d[this->dimensions.x * y + x] = Cell(6, spacePointType_e::empty, 0, this->numFluids);

                if(hotFluid > random)
                {
                    Particle particle(1, 1, 1);
                    int position = int_distribution(int_generator);
                    cellState_t state = 1 << position;

                    this->lattice[this->dimensions.x * y + x].setState(state);
                    this->lattice[this->dimensions.x * y + x].setParticle(&particle, position);
                }
                else if(coldFluid + hotFluid > random)
                {
                    Particle particle(2, 1, 1);
                    int position = int_distribution(int_generator);
                    cellState_t state = 1 << position;

                    this->lattice[this->dimensions.x * y + x].setState(state);
                    this->lattice[this->dimensions.x * y + x].setParticle(&particle, position);
                }
            }
        }
    }
}
