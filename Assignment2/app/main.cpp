#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#include <Eigen/Core>
#include <chrono>
#include <ctime>
#include <iostream>
#include <particle.hpp>
#include <random>
#include <set>

const double epsilon = 0.001;
void help_info() {
    std::cerr << "This is the help information of solar system simulator" << std::endl;
    std::cerr << "You can input --help or -h to check the help information" << std::endl;
    std::cerr << "For run this program, you can input the parameters like 1 or 2" << std::endl;
    std::cerr << "1. timestep (should be double) and total length of time (number of years, should be double) + 'time'" << std::endl;
    std::cerr << "E.g. 0.001, 1.5, time" << std::endl;
    std::cerr << "2. timestep (should be double) and total numbers of timesteps (should be and integer) + 'step'" << std::endl;
    std::cerr << "E.g. 0.001, 5, step" << std::endl;
}

int main(int argc, char* argv[]) {
    // check the number of the input and response based on different number
    if (argc == 1) {
        help_info();
        std::cerr << "You can input --help or -h to check the information again" << std::endl;
    }

    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        help_info();
        std::cerr << "You can input --help or -h to check the information again" << std::endl;
    }

    if (argc == 3) {
        std::cerr << "The number of input parameters should be 4" << std::endl;
        std::cerr << "You can input --help or -h to check the information again" << std::endl;
    }

    if (argc == 4) {
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        std::vector<std::string> particles_name = {"Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
        std::vector<std::shared_ptr<Particle>> particles_vector = Initial_condition_generator();

        double Kin_before = cal_kin_energy(particles_vector);
        double Pot_before = cal_pot_energy(particles_vector);
        double total_before = Kin_before + Pot_before;

        std::cerr << "The total kinetic energy of the system is:" << Kin_before << std::endl;
        std::cerr << "The total potential energy of the system is:" << Pot_before << std::endl;
        std::cerr << "The total energy of the system is:" << total_before << std::endl;
#ifdef DEBUG
        std::cerr << "The Initial postion of the particles are:" << std::endl;
#endif

        for (int i = 0; i < particles_vector.size(); i++) {
#ifdef DEBUG
            std::cerr << particles_name[i] << ":" << (particles_vector[i]->get_Position()).transpose() << std::endl;
#endif
        }

        double num_y = std::stod(argv[2]);
        double dt = std::stod(argv[1]);
        double end_t = num_y * 2 * M_PI;

        if (strcmp(argv[3], "time") == 0) {
            for (double i = 0; i < end_t; i += dt) {
                for (auto ptr_i : particles_vector) {
                    Eigen::Vector3d gra_add_i = calc_Acc_all(ptr_i, particles_vector, 0.0);
                    ptr_i->acceleration_particle = gra_add_i;
                }

                for (auto ptr_i : particles_vector) {
                    ptr_i->update(dt, ptr_i->acceleration_particle);
                }
            }
        }

        if (strcmp(argv[3], "step") == 0) {
            for (double i = 0; i < num_y; i += dt) {
                for (auto ptr_i : particles_vector) {
                    Eigen::Vector3d gra_add_i = calc_Acc_all(ptr_i, particles_vector, 0.0);
                    ptr_i->acceleration_particle = gra_add_i;
                }

                for (auto ptr_i : particles_vector) {
                    ptr_i->update(dt, ptr_i->acceleration_particle);
                }
            }
        }

        std::cerr << std::endl;
        double Kin_after = cal_kin_energy(particles_vector);
        double Pot_after = cal_pot_energy(particles_vector);
        double total_after = Kin_after + Pot_after;

        std::cerr << "The total kinetic energy of the system is:" << Kin_after << std::endl;
        std::cerr << "The total potential energy of the system is:" << Pot_after << std::endl;
        std::cerr << "The total energy of the system is:" << total_after << std::endl;

#ifdef DEBUG
        std::cerr << "The final postion of the particles are:" << std::endl;
#endif
        for (int i = 0; i < particles_vector.size(); i++) {
#ifdef DEBUG
            std::cerr << particles_name[i] << ":" << (particles_vector[i]->get_Position()).transpose() << std::endl;
#endif
        }

        std::cerr << "The energy loss of the simulation is: " << total_after - total_before << std::endl;

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

        std::cerr << std::endl;

        std::cerr << "The total time for the simulation is: " << time_span.count() << " seconds" << std::endl;
        std::cerr << "The average time per time step for the simulation is: " << (time_span.count()) / (end_t / dt) << " seconds"
                  << std::endl;
    }
    if (argc == 5) {
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        double num_y = std::stod(argv[2]);
        double dt = std::stod(argv[1]);
        double end_t = num_y * 2 * M_PI;
        int num_particles = std::stoi(argv[4]);

        std::shared_ptr<RandomSystem> gen_ptr = std::make_shared<RandomSystem>(num_particles);

        std::vector<std::shared_ptr<Particle>> particles_vector = gen_ptr->generateInitialConditions();

        std::shared_ptr<Particle> ptr_sun = particles_vector[0];

        double Kin_before = cal_kin_energy(particles_vector);
        double Pot_before = cal_pot_energy(particles_vector);
        double total_before = Kin_before + Pot_before;

        std::cerr << "The total kinetic energy of the system is:" << Kin_before << std::endl;
        std::cerr << "The total potential energy of the system is:" << Pot_before << std::endl;
        std::cerr << "The total energy of the system is:" << total_before << std::endl;
#ifdef DEBUG
        std::cerr << "The Initial postion of the particles are:" << std::endl;
#endif
        for (int i = 0; i < particles_vector.size(); i++) {
#ifdef DEBUG
            std::cerr << i << ":" << (particles_vector[i]->get_Position()).transpose() << std::endl;
#endif
        }

        if (strcmp(argv[3], "time") == 0) {
#pragma omp parallel
            {
                for (double i = 0; i < end_t; i += dt) {
#pragma omp for
                    for (auto ptr_i : particles_vector) {
                        Eigen::Vector3d gra_add_i = calc_Acc_all(ptr_i, particles_vector, epsilon);
                        ptr_i->acceleration_particle = gra_add_i;
                    }
#pragma omp for nowait
                    for (auto ptr_i : particles_vector) {
                        ptr_i->update(dt, ptr_i->acceleration_particle);
                    }
                }
            }
        }

        if (strcmp(argv[3], "step") == 0) {
#pragma omp parallel
            {
                for (double i = 0; i < num_y; i += dt) {
#pragma omp for
                    for (auto ptr_i : particles_vector) {
                        Eigen::Vector3d gra_add_i = calc_Acc_all(ptr_i, particles_vector, 0.0);
                        ptr_i->acceleration_particle = gra_add_i;
                    }
#pragma omp for nowait
                    for (auto ptr_i : particles_vector) {
                        if (ptr_i == ptr_sun) {
                            continue;
                        }
                        ptr_i->update(dt, ptr_i->acceleration_particle);
                    }
                }
            }
        }
        std::cerr << std::endl;
        double Kin_after = cal_kin_energy(particles_vector);
        double Pot_after = cal_pot_energy(particles_vector);
        double total_after = Kin_after + Pot_after;

        std::cerr << "The total kinetic energy of the system is:" << Kin_after << std::endl;
        std::cerr << "The total potential energy of the system is:" << Pot_after << std::endl;
        std::cerr << "The total energy of the system is:" << total_after << std::endl;
#ifdef DEBUG
        std::cerr << "The final postion of the particles are:" << std::endl;
#endif
        for (int i = 0; i < particles_vector.size(); i++) {
#ifdef DEBUG
            std::cerr << particles_name[i] << ":" << (particles_vector[i]->get_Position()).transpose() << std::endl;
#endif
        }

        std::cerr << "The energy loss of the simulation is: " << total_after - total_before << std::endl;

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

        std::cerr << std::endl;

        std::cerr << "The total time for the simulation is: " << time_span.count() << " seconds" << std::endl;
        std::cerr << "The average time per time step for the simulation is: " << (time_span.count()) / (end_t / dt) << " seconds"
                  << std::endl;
        std::cerr << std::endl;
        std::cerr << "| " << omp_get_max_threads() << " | " << time_span.count() << "secoonds" << std::endl;
    }
}
