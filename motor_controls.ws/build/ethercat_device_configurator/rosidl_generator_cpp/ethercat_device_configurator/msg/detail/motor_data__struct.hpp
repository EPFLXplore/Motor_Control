// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ethercat_device_configurator:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_DATA__STRUCT_HPP_
#define ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_DATA__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__ethercat_device_configurator__msg__MotorData __attribute__((deprecated))
#else
# define DEPRECATED__ethercat_device_configurator__msg__MotorData __declspec(deprecated)
#endif

namespace ethercat_device_configurator
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorData_
{
  using Type = MotorData_<ContainerAllocator>;

  explicit MotorData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->position = 0.0;
      this->velocity = 0.0;
      this->currant = 0.0;
    }
  }

  explicit MotorData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->position = 0.0;
      this->velocity = 0.0;
      this->currant = 0.0;
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _name_type name;
  using _position_type =
    double;
  _position_type position;
  using _velocity_type =
    double;
  _velocity_type velocity;
  using _currant_type =
    double;
  _currant_type currant;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__position(
    const double & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const double & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__currant(
    const double & _arg)
  {
    this->currant = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ethercat_device_configurator::msg::MotorData_<ContainerAllocator> *;
  using ConstRawPtr =
    const ethercat_device_configurator::msg::MotorData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ethercat_device_configurator::msg::MotorData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ethercat_device_configurator::msg::MotorData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ethercat_device_configurator::msg::MotorData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ethercat_device_configurator::msg::MotorData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ethercat_device_configurator::msg::MotorData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ethercat_device_configurator::msg::MotorData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ethercat_device_configurator::msg::MotorData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ethercat_device_configurator::msg::MotorData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ethercat_device_configurator__msg__MotorData
    std::shared_ptr<ethercat_device_configurator::msg::MotorData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ethercat_device_configurator__msg__MotorData
    std::shared_ptr<ethercat_device_configurator::msg::MotorData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorData_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->currant != other.currant) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorData_

// alias to use template instance with default allocator
using MotorData =
  ethercat_device_configurator::msg::MotorData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ethercat_device_configurator

#endif  // ETHERCAT_DEVICE_CONFIGURATOR__MSG__DETAIL__MOTOR_DATA__STRUCT_HPP_
