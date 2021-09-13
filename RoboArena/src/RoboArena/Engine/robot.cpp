#include "robot.h"
#include "glm/gtx/rotate_vector.hpp"

const float PI_2f32 = 2.0f * M_PIf32;

const float BASE_ROTATION_VELOCITY_RADS = 5 * M_PI / 180;
const float BASE_ROTATION_VELOCITY_DEC_RADS = 0.75 * M_PI / 180;
const float TURRET_ROTATION_VELOCITY_RADS = 5 * M_PI / 180;
const float RADAR_ROTATION_VELOCITY_RADS = 5 * M_PI / 180;

const float ROBOT_RADIUS = 24;

void Robot::fire(std::set<Bullet> &bullets)
{
    heat = 1.0f + fire_power / 5.0f;
    energy = std::max(0.0f, energy - fire_power);
    should_fire = false;
    glm::vec2 turret_direction = glm::rotate(glm::vec2(1.0f, 0.0), turret_rotation);
    TRACE("Firing");
    bullets.emplace(this, position + turret_direction * 30.0f, turret_direction * (20.0f - (3.0f * fire_power)), fire_power);
};

const float Robot::RADIUS = 24;

void Robot::step()
{
    // PyObject_CallMethodObjArgs(scripted_robot, stop_name, NULL);
    speed = glm::clamp(speed + get_acceleration(), -8.0f, 8.0f);
    auto velocity = glm::rotate(glm::vec2(speed, 0.0f), base_rotation);
    position = position + velocity;
    float base_rotation_velocity =
        std::max(0.0f, (BASE_ROTATION_VELOCITY_RADS - BASE_ROTATION_VELOCITY_DEC_RADS * std::abs(speed))) * (float)base_turning;
    // std::cout << "Rotation " << base_rotation << "Turning " << base_turning << "Rot Vel " << (BASE_ROTATION_VELOCITY_RADS - BASE_ROTATION_VELOCITY_DEC_RADS * std::abs(velocity)) << std::endl;
    base_rotation = std::remainderf(base_rotation + base_rotation_velocity, PI_2f32);
    float turret_rotation_velocity = TURRET_ROTATION_VELOCITY_RADS * turret_turning + base_rotation_velocity;
    turret_rotation = std::remainderf(turret_rotation + turret_rotation_velocity, PI_2f32);
    float radar_rotation_velocity = RADAR_ROTATION_VELOCITY_RADS * radar_turning + turret_rotation_velocity;
    radar_rotation = std::remainderf(radar_rotation + radar_rotation_velocity, PI_2f32);
};


float Robot::get_acceleration()
{
    if (speed > 0.0f)
    {
        if (moving > 0)
            return 1.0f;
        else
            return -2.0f;
    }
    else if (speed < 0.0f)
    {
        if (moving < 0)
            return -1.0f;
        else
            return 2.0f;
    }
    else if (std::abs(moving) > 0)
        return 1.0f;
    else
        return 0.0f;
};
