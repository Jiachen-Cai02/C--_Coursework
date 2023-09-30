#include <Eigen/Core>
#include <Eigen/Dense>
#include <set>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "particle.hpp"

using Catch::Matchers::WithinRel;

TEST_CASE("Particle test 1", "[mass, velocity, acceleration and position correct]") {
    double in_mass = 5.0;
    Eigen::Vector3d in_velocity(1, 1, 1);
    // Eigen::Vector3d in_acceleration(1, 1, 1);
    Eigen::Vector3d in_position(1, 1, 1);

    Particle test(in_mass, in_velocity, in_position);

    auto get_mass = test.getMass();
    // auto get_acceleration = test.get_Acceleration();
    auto get_velocity = test.get_Velocity();
    auto get_position = test.get_Position();

    REQUIRE(typeid(get_mass) == typeid(double));
    // REQUIRE(typeid(get_acceleration) == typeid(Eigen::Vector3d));
    REQUIRE(typeid(get_velocity) == typeid(Eigen::Vector3d));
    REQUIRE(typeid(get_position) == typeid(Eigen::Vector3d));

    REQUIRE(get_mass == in_mass);
    // REQUIRE(get_acceleration == in_acceleration);
    REQUIRE(get_velocity == in_velocity);
    REQUIRE(get_position == in_position);
}

TEST_CASE("Particle test 2", "[update method correct]") {
    double in_mass = 5.0;
    double interval = 2;
    Eigen::Vector3d in_velocity(1.5, 1.5, 1.5);
    Eigen::Vector3d in_acceleration(1, 1, 1);
    Eigen::Vector3d in_position(1, 1, 1);

    Particle test(in_mass, in_velocity, in_position);
    test.update(interval, in_acceleration);

    // auto get_acceleration = test.get_Acceleration();
    auto get_velocity = test.get_Velocity();
    auto get_position = test.get_Position();

    REQUIRE(get_position == Eigen::Vector3d(4, 4, 4));
    REQUIRE(get_velocity == Eigen::Vector3d(3.5, 3.5, 3.5));
}

TEST_CASE("Particle test 3", "[update acceleration correct when acceleration equals to minus position]") {
    double in_mass = 5.0;
    double interval = 2;
    Eigen::Vector3d in_velocity(1.5, 1.5, 1.5);
    Eigen::Vector3d in_acceleration(1, 1, 1);
    Eigen::Vector3d in_position(-1, -1, -1);

    Particle test(in_mass, in_velocity, in_position);
    test.update(interval, in_acceleration);

    // auto get_acceleration = test.get_Acceleration();
    auto get_position = test.get_Position();

    REQUIRE(get_position == Eigen::Vector3d(2, 2, 2));
    // REQUIRE(get_acceleration == Eigen::Vector3d(-2, -2, -2));
}

TEST_CASE("Particle test 4", "[update acceleration correct]") {
    double in_mass = 5.0;
    double interval = 2;
    Eigen::Vector3d in_velocity(1.5, 1.5, 1.5);
    Eigen::Vector3d in_acceleration(1, 1, 1);
    Eigen::Vector3d in_position(2, 2, 2);

    Particle test(in_mass, in_velocity, in_position);
    test.update(interval, in_acceleration);

    // auto get_acceleration = test.get_Acceleration();
    auto get_velocity = test.get_Velocity();
    auto get_position = test.get_Position();

    REQUIRE(get_position == Eigen::Vector3d(5, 5, 5));
    REQUIRE(get_velocity == Eigen::Vector3d(3.5, 3.5, 3.5));
    // REQUIRE(get_acceleration == Eigen::Vector3d(1, 1, 1));
}

TEST_CASE("Particle test 5", "[acceleration should be larger than 0]") {
    try {
        double in_mass = 5.0;
        Eigen::Vector3d in_velocity(1.5, 1.5, 1.5);
        Eigen::Vector3d in_acceleration(0, 0, 0);
        Eigen::Vector3d in_position(2, 2, 2);

        Particle test(in_mass, in_velocity, in_position);
    }

    catch (std::invalid_argument& e) {
        REQUIRE(strcmp(e.what(), "The acceleration should not equal to 0") == 0);
    }
}

TEST_CASE("Particle test 6", "[test for orbiting particle]") {
    double in_mass = 5.0;
    Eigen::Vector3d in_velocity(0, 1., 0);
    Eigen::Vector3d in_acceleration(-1., 0, 0);
    Eigen::Vector3d in_position(1., 0, 0);

    Particle test(in_mass, in_velocity, in_position);

    double dt = 0.001;
    double end_t = 2 * M_PI;

    for (double i = 0; i < end_t; i += dt) {
        test.update(dt, in_acceleration);
        in_acceleration = -test.position_particle;
    }

    REQUIRE(test.position_particle.isApprox(in_position, 0.005) == true);
}

TEST_CASE("Particle test 7", "[test for cal functions: same position]") {
    double epsilon = 1.0;

    double in_mass_1 = 5.0;
    Eigen::Vector3d in_velocity_1(0, 1, 0), in_position_1(1, 1, 1);
    std::shared_ptr<Particle> ptr_1 = std::make_shared<Particle>(in_mass_1, in_velocity_1, in_position_1);

    double in_mass_2 = 4.0;
    Eigen::Vector3d in_velocity_2(0, 1, 0), in_position_2(1, 1, 1);
    std::shared_ptr<Particle> ptr_2 = std::make_shared<Particle>(in_mass_2, in_velocity_2, in_position_2);

    Eigen::Vector3d cal_1_2 = calcAcceleration(ptr_1, ptr_2, epsilon);

    REQUIRE(cal_1_2 == Eigen::Vector3d(0.0, 0.0, 0.0));
}

TEST_CASE("Particle test 8", "[test for cal functions: different positions when epsilon equals to 0]") {
    double epsilon = 0.0;

    double in_mass_1 = 5.0;
    Eigen::Vector3d in_velocity_1(0, 1, 0), in_position_1(1, 1, 1);
    std::shared_ptr<Particle> ptr_1 = std::make_shared<Particle>(in_mass_1, in_velocity_1, in_position_1);

    double in_mass_2 = sqrt(3);
    Eigen::Vector3d in_velocity_2(0, 1, 0), in_position_2(2, 2, 2);
    std::shared_ptr<Particle> ptr_2 = std::make_shared<Particle>(in_mass_2, in_velocity_2, in_position_2);

    Eigen::Vector3d cal_1_2 = calcAcceleration(ptr_1, ptr_2, epsilon);

    REQUIRE(cal_1_2 == Eigen::Vector3d(1.0 / 3, 1.0 / 3, 1.0 / 3));
}

TEST_CASE("Particle test 9", "[test for cal functions: different positions when epsilon not equals to 0]") {
    double epsilon = 2.0;

    double in_mass_1 = 5.0;
    Eigen::Vector3d in_velocity_1(0, 1, 0), in_position_1(1, 1, 1);
    std::shared_ptr<Particle> ptr_1 = std::make_shared<Particle>(in_mass_1, in_velocity_1, in_position_1);

    double in_mass_2 = sqrt(7);
    Eigen::Vector3d in_velocity_2(0, 1, 0), in_position_2(2, 2, 2);
    std::shared_ptr<Particle> ptr_2 = std::make_shared<Particle>(in_mass_2, in_velocity_2, in_position_2);

    Eigen::Vector3d cal_1_2 = calcAcceleration(ptr_1, ptr_2, epsilon);

    REQUIRE(cal_1_2 == Eigen::Vector3d(1.0 / 7, 1.0 / 7, 1.0 / 7));
}

TEST_CASE("Particle test 10", "[test for cal_total functions]") {
    double epsilon = 0.0;

    std::vector<std::shared_ptr<Particle>> particles_vector;

    double in_mass_1 = 5.0;
    Eigen::Vector3d in_velocity_1(0, 1, 0), in_position_1(1, 1, 1);
    std::shared_ptr<Particle> ptr_1 = std::make_shared<Particle>(in_mass_1, in_velocity_1, in_position_1);
    particles_vector.push_back(ptr_1);

    double in_mass_2 = 1.0;
    Eigen::Vector3d in_velocity_2(0, 1, 0), in_position_2(2, 2, 2);
    std::shared_ptr<Particle> ptr_2 = std::make_shared<Particle>(in_mass_2, in_velocity_2, in_position_2);
    particles_vector.push_back(ptr_2);

    double in_mass_3 = 3.0;
    Eigen::Vector3d in_velocity_3(0, 1, 0), in_position_3(2, 2, 2);
    std::shared_ptr<Particle> ptr_3 = std::make_shared<Particle>(in_mass_3, in_velocity_3, in_position_3);
    particles_vector.push_back(ptr_3);

    Eigen::Vector3d cal_total = calc_Acc_all(ptr_1, particles_vector, epsilon);

    REQUIRE(cal_total == Eigen::Vector3d(4.0 / sqrt(27), 4.0 / sqrt(27), 4.0 / sqrt(27)));
}

TEST_CASE("Particle test 11", "[test for cal_total with a list that just contains particle itself]") {
    double epsilon = 1.0;

    std::vector<std::shared_ptr<Particle>> particles_vector;

    double in_mass_1 = 5.0;
    Eigen::Vector3d in_velocity_1(0, 1, 0), in_position_1(1, 1, 1);
    std::shared_ptr<Particle> ptr_1 = std::make_shared<Particle>(in_mass_1, in_velocity_1, in_position_1);
    particles_vector.push_back(ptr_1);

    Eigen::Vector3d cal_total = calc_Acc_all(ptr_1, particles_vector, epsilon);

    REQUIRE(cal_total == Eigen::Vector3d(0.0, 0.0, 0.0));
}

TEST_CASE("Particle test 12", "[test for cal_total functions with euqal sized opposite particles]") {
    double epsilon = 1.0;

    std::vector<std::shared_ptr<Particle>> particles_vector;

    double in_mass_1 = 5.0;
    Eigen::Vector3d in_velocity_1(0, 1, 0), in_position_1(0, 0, 0);
    std::shared_ptr<Particle> ptr_1 = std::make_shared<Particle>(in_mass_1, in_velocity_1, in_position_1);
    particles_vector.push_back(ptr_1);

    double in_mass_2 = 1.0;
    Eigen::Vector3d in_velocity_2(0, 1, 0), in_position_2(1, 0, 0);
    std::shared_ptr<Particle> ptr_2 = std::make_shared<Particle>(in_mass_2, in_velocity_2, in_position_2);
    particles_vector.push_back(ptr_2);

    double in_mass_3 = 1.0;
    Eigen::Vector3d in_velocity_3(0, 1, 0), in_position_3(-1, 0, 0);
    std::shared_ptr<Particle> ptr_3 = std::make_shared<Particle>(in_mass_3, in_velocity_3, in_position_3);
    particles_vector.push_back(ptr_3);

    Eigen::Vector3d cal_total = calc_Acc_all(ptr_1, particles_vector, epsilon);

    REQUIRE(cal_total == Eigen::Vector3d(0, 0, 0));
}

TEST_CASE("Particle test 13", "[test for Initial_condition_generator]") {
    std::vector<std::shared_ptr<Particle>> test_vector = Initial_condition_generator();

    std::vector<double> mass_particles = {1.,           1. / 6023600, 1. / 408524, 1. / 332946.038, 1. / 3098710,
                                          1. / 1047.55, 1. / 3499,    1. / 22962,  1. / 19352};
    std::vector<double> distance_particles = {0.0, 0.4, 0.7, 1, 1.5, 5.2, 9.5, 19.2, 30.1};

    std::vector<double> test_mass;

    for (auto ptr_i : test_vector) {
        test_mass.push_back(ptr_i->getMass());
    }

    REQUIRE(test_vector.size() == 9);
    REQUIRE(test_mass == mass_particles);
}

TEST_CASE("Particle test 14", "[test for single particle orbiting]") {
    std::vector<std::shared_ptr<Particle>> particles_vector = Initial_condition_generator();

    double dt = 0.0001;
    double end_t = 2 * M_PI;

    std::shared_ptr<Particle> ptr_earth = particles_vector[3];

    Eigen::Vector3d initial_position_earth = ptr_earth -> get_Position();

    for (double i = 0; i < end_t; i += dt) {
        for (auto ptr_i : particles_vector) {
            Eigen::Vector3d gra_add_i = calc_Acc_all(ptr_i, particles_vector, 0.0);
            ptr_i->acceleration_particle = gra_add_i;
        }

        for (auto ptr_i : particles_vector) {
            ptr_i->update(dt, ptr_i->acceleration_particle);
        }
    }

    REQUIRE(initial_position_earth.isApprox(ptr_earth -> get_Position(), 0.01) == true);
}

TEST_CASE("Particle test 15", "[test for the position of the sun]") {
    std::vector<std::shared_ptr<Particle>> particles_vector = Initial_condition_generator();

    double dt = 0.0001;
    double end_t = 2 * M_PI;

    std::shared_ptr<Particle> ptr_sun = particles_vector[0];


    for (double i = 0; i < end_t; i += dt) {
        for (auto ptr_i : particles_vector) {
            Eigen::Vector3d gra_add_i = calc_Acc_all(ptr_i, particles_vector, 0.0);
            ptr_i->acceleration_particle = gra_add_i;
        }

        for (auto ptr_i : particles_vector) {
            if (ptr_i == ptr_sun) {
                continue;
            }
            ptr_i->update(dt, ptr_i->acceleration_particle);
        }
    }

    REQUIRE(ptr_sun -> get_Position() == Eigen::Vector3d (0.0, 0.0, 0.0));
    REQUIRE(ptr_sun -> get_Velocity() == Eigen::Vector3d (0.0, 0.0, 0.0));
}

TEST_CASE("Particle test 16", "[Test the random generator]") {
    std::shared_ptr <RandomSystem> test_ptr = std::make_shared<RandomSystem>(2048);
    std::vector<std::shared_ptr<Particle>> particles_vector = test_ptr -> generateInitialConditions();

    REQUIRE(particles_vector.size() == 2048);
    REQUIRE(particles_vector[0] -> get_Position() == Eigen::Vector3d(0.0, 0.0, 0.0));
    REQUIRE(particles_vector[0] -> get_Velocity() == Eigen::Vector3d(0.0, 0.0, 0.0));
    REQUIRE(particles_vector[0] -> getMass() == 1.);
}