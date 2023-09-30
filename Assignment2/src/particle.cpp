#include "particle.hpp"

#include <Eigen/Core>
#include <iostream>
#include <set>

#define _USE_MATH_DEFINES
#include <math.h>
Particle::Particle(const double in_mass, Eigen::Vector3d in_velocity, Eigen::Vector3d in_position) {
    if (typeid(in_velocity) != typeid(Eigen::Vector3d)) {
        throw std::invalid_argument("The type of the velocity should be Eigen::Vector3d");
    }
    if (typeid(in_position) != typeid(Eigen::Vector3d)) {
        throw std::invalid_argument("The type of the position should be Eigen::Vector3d");
    }
    mass_particle = in_mass;
    velocity_particle = in_velocity;
    position_particle = in_position;
}

Particle::~Particle() {}

double Particle::getMass() const {
    return mass_particle;
}

Eigen::Vector3d Particle::get_Velocity() {
    return velocity_particle;
}

Eigen::Vector3d Particle::get_Position() {
    return position_particle;
}

void Particle::update(double dt, Eigen::Vector3d in_acceleration) {
    Eigen::Vector3d invalid(0, 0, 0);

    if (in_acceleration.isApprox(invalid) == true) {
        throw std::invalid_argument("The acceleration should not equal to 0");
    }

    acceleration_particle = in_acceleration;

    position_particle += dt * velocity_particle;
    velocity_particle += dt * acceleration_particle;
}

Eigen::Vector3d calcAcceleration(std::shared_ptr<Particle> particle_i, std::shared_ptr<Particle> particle_j, double epsilon) {
    Eigen::Vector3d position_i = particle_i->get_Position();
    Eigen::Vector3d position_j = particle_j->get_Position();

    double mass_j = particle_j->getMass();

    Eigen::Vector3d acceleration_i =
        mass_j * (position_j - position_i) / pow(((position_i - position_j).squaredNorm() + pow(epsilon, 2)), 1.5);

    return acceleration_i;
}

Eigen::Vector3d calc_Acc_all(std::shared_ptr<Particle> particle_i, std::vector<std::shared_ptr<Particle>> particles_vector,
                             double epsilon) {
    Eigen::Vector3d Acc_all(0.0, 0.0, 0.0);
    for (auto particle_ptr : particles_vector) {
        if (particle_i == particle_ptr) {
            Acc_all += Eigen::Vector3d(0.0, 0.0, 0.0);
        }
        else {
            Acc_all += calcAcceleration(particle_i, particle_ptr, epsilon);
        }
    }

    return Acc_all;
}

std::vector<std::shared_ptr<Particle>> Initial_condition_generator() {
    //The given conditions stored as vector
    std::vector<double> mass_particles = {1.,           1. / 6023600, 1. / 408524, 1. / 332946.038, 1. / 3098710,
                                          1. / 1047.55, 1. / 3499,    1. / 22962,  1. / 19352};
    std::vector<double> distance_particles = {0.0, 0.4, 0.7, 1., 1.5, 5.2, 9.5, 19.2, 30.1};

    std::vector<std::shared_ptr<Particle>> initial_vector;
    //For the random seed, you can fix the value of the seed to fix the generated value
    srand(time(NULL));

    for (int i = 0; i < 9; i++) {
        //random seed
        double theta = (double)(rand());
        double distance_i = distance_particles[i];

        double x_x_i = distance_i * sin(theta);
        double x_y_i = distance_i * cos(theta);

        double v_x_i = -cos(theta) / sqrt(distance_i);
        double v_y_i = sin(theta) / sqrt(distance_i);

        if (i == 0) {
            std::shared_ptr<Particle> ptr_i =
                std::make_shared<Particle>(mass_particles[i], Eigen::Vector3d(0.0, 0.0, 0.0), Eigen::Vector3d(0.0, 0.0, 0.0));
            initial_vector.push_back(ptr_i);
        }
        else {
            std::shared_ptr<Particle> ptr_i =
                std::make_shared<Particle>(mass_particles[i], Eigen::Vector3d(v_x_i, v_y_i, 0.0), Eigen::Vector3d(x_x_i, x_y_i, 0.0));
            initial_vector.push_back(ptr_i);
        }
    }

    return initial_vector;
}

double cal_kin_energy(std::vector<std::shared_ptr<Particle>> particles_vector) {
    double E_kin = 0.0;
#pragma omp parallel for reduction(+ : E_kin)
    for (auto particle_i : particles_vector) {
        Eigen::Vector3d vel_i = particle_i->get_Velocity();
        double mass_i = particle_i->getMass();

        E_kin += 0.5 * mass_i * vel_i.squaredNorm();
    }

    return E_kin;
}

double cal_pot_energy(std::vector<std::shared_ptr<Particle>> particles_vector) {
    double E_pot = 0.0;
    for (auto particle_i : particles_vector) {
        double mass_i = particle_i->getMass();
        Eigen::Vector3d position_i = particle_i->get_Position();
#pragma omp parallel for reduction(+ : E_pot)
        for (auto particle_ptr : particles_vector) {
            if (particle_i == particle_ptr) {
                E_pot += 0;
            }
            else {
                double mass_j = particle_ptr->getMass();
                Eigen::Vector3d position_j = particle_ptr->get_Position();
                E_pot += -0.5 * mass_i * mass_j / (position_i - position_j).norm();
            }
        }
    }

    return E_pot;
}

InitialConditionGenerator::InitialConditionGenerator() {}

SolarSystem::SolarSystem(int num_particles) : InitialConditionGenerator() {
    generator_num = num_particles;
}

std::vector<std::shared_ptr<Particle>> SolarSystem::generateInitialConditions() {
    std::vector<double> mass_particles = {1.,           1. / 6023600, 1. / 408524, 1. / 332946.038, 1. / 3098710,
                                          1. / 1047.55, 1. / 3499,    1. / 22962,  1. / 19352};
    std::vector<double> distance_particles = {0.0, 0.4, 0.7, 1., 1.5, 5.2, 9.5, 19.2, 30.1};

    std::vector<std::shared_ptr<Particle>> initial_vector;

    for (int i = 0; i < 9; i++) {
        srand(time(NULL));
        double theta_i = (double)(rand());

        double distance_i = distance_particles[i];

        double x_x_i = distance_i * sin(theta_i);
        double x_y_i = distance_i * cos(theta_i);

        double v_x_i = -cos(theta_i) / sqrt(distance_i);
        double v_y_i = sin(theta_i) / sqrt(distance_i);

        if (i == 0) {
            std::shared_ptr<Particle> ptr_i =
                std::make_shared<Particle>(mass_particles[i], Eigen::Vector3d(0.0, 0.0, 0.0), Eigen::Vector3d(0.0, 0.0, 0.0));
            initial_vector.push_back(ptr_i);
        }
        else {
            std::shared_ptr<Particle> ptr_i =
                std::make_shared<Particle>(mass_particles[i], Eigen::Vector3d(v_x_i, v_y_i, 0.0), Eigen::Vector3d(x_x_i, x_y_i, 0.0));
            initial_vector.push_back(ptr_i);
        }
    }

    return initial_vector;
}

RandomSystem::RandomSystem(int num_particles) : InitialConditionGenerator() {
    generator_num = num_particles;
}

std::vector<std::shared_ptr<Particle>> RandomSystem::generateInitialConditions() {
    std::vector<std::shared_ptr<Particle>> initial_vector;

    // construct a trivial random generator engine from a time_based seed;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    std::uniform_real_distribution<double> distribution_mass(1. / 6000000, 1. / 1000);
    std::uniform_real_distribution<double> distribution_distance(0.4, 30.);
    std::uniform_real_distribution<double> distribution_angle(0, 2 * M_PI);

    for (int i = 0; i < generator_num; i++) {
        double theta_i = distribution_angle(generator);
        double mass_i = distribution_mass(generator);
        double distance_i = distribution_distance(generator);

        double x_x_i = distance_i * sin(theta_i);
        double x_y_i = distance_i * cos(theta_i);

        double v_x_i = -cos(theta_i) / sqrt(distance_i);
        double v_y_i = sin(theta_i) / sqrt(distance_i);

        if (i == 0) {
            std::shared_ptr<Particle> ptr_i =
                std::make_shared<Particle>(1.0, Eigen::Vector3d(0.0, 0.0, 0.0), Eigen::Vector3d(0.0, 0.0, 0.0));
            initial_vector.push_back(ptr_i);
        }
        else {
            std::shared_ptr<Particle> ptr_i =
                std::make_shared<Particle>(mass_i, Eigen::Vector3d(v_x_i, v_y_i, 0.0), Eigen::Vector3d(x_x_i, x_y_i, 0.0));
            initial_vector.push_back(ptr_i);
        }
    }

    return initial_vector;
}
