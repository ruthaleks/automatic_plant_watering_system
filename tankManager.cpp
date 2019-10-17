#include <cstdint>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "actuatorController.hpp"
#include "devices.hpp"
#include "sensorMonitor.hpp"
#include "tankManager.hpp"

TankManager::TankManager( SensorType sensor_type, ActuatorType actuator_type ) :
m_sensor_ptr{ new SensorMonitor{ sensor_type } }, 
m_actuator_ptr{ new ActuatorController{ actuator_type } } {}

// TODO: Add a method is_empty() and make level() private
// TODO: Add a private variable threshold 

uint32_t TankManager::level() const
{   
    std::cout << "Read the pressure sensor data..\n";
    return m_sensor_ptr->value(); 
}

SensorType TankManager::sensor() const
{
    return m_sensor_ptr->type() ;
}

ActuatorType TankManager::actuator() const
{
    return m_actuator_ptr->type();
}

void TankManager::add_water(float amout_in_millilitre) const
{
    // TODO: Add a guard in case no actuator
    std::cout << "Asked amount: " << amout_in_millilitre << " millilitres\n";
    float time{ amout_in_millilitre / m_actuator_ptr->rate_per_second() };
    m_actuator_ptr->set_velocity( 1 );
    std::cout << "Pour for " << (uint32_t) time << " second(s) \n"; 
    std::this_thread::sleep_for(std::chrono::seconds((uint32_t)time));
    m_actuator_ptr->set_velocity( 0 );     
}
