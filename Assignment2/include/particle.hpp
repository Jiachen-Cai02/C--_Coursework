#include <omp.h>
#include <stdlib.h>
#include <time.h>

#include <Eigen/Core>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <vector>
#ifndef particle_hpp
#define particle_hpp

class Particle {
public:
    Particle(const double in_mass, Eigen::Vector3d in_velocity, Eigen::Vector3d in_position);
    ~Particle();
    double mass_particle;
    Eigen::Vector3d velocity_particle;
    Eigen::Vector3d position_particle;
    Eigen::Vector3d acceleration_particle;
    double getMass() const;
    Eigen::Vector3d get_Velocity();
    Eigen::Vector3d get_Position();
    void update(double dt, Eigen::Vector3d in_acceleration);
};

Eigen::Vector3d calcAcceleration(std::shared_ptr<Particle> particle_i, std::shared_ptr<Particle> particle_j, double epsilon);
Eigen::Vector3d calc_Acc_all(std::shared_ptr<Particle> particle_i, std::vector<std::shared_ptr<Particle>> particles_vector, double epsilon);
std::vector<std::shared_ptr<Particle>> Initial_condition_generator();

double cal_kin_energy(std::vector<std::shared_ptr<Particle>> particles_vector);
double cal_pot_energy(std::vector<std::shared_ptr<Particle>> particles_vector);

class InitialConditionGenerator {
public:
    InitialConditionGenerator();
    virtual std::vector<std::shared_ptr<Particle>> generateInitialConditions() = 0;
    int generator_num;
};

class SolarSystem : public InitialConditionGenerator {
public:
    SolarSystem(int num_particles);
    std::vector<std::shared_ptr<Particle>> generateInitialConditions();
};

class RandomSystem : public InitialConditionGenerator {
public:
    RandomSystem(int num_particles);
    std::vector<std::shared_ptr<Particle>> generateInitialConditions();
};

#endif