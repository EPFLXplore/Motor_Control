// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from coucou:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#ifndef COUCOU__MSG__DETAIL__MOTOR_COMMAND__STRUCT_HPP_
#define COUCOU__MSG__DETAIL__MOTOR_COMMAND__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__coucou__msg__MotorCommand __attribute__((deprecated))
#else
# define DEPRECATED__coucou__msg__MotorCommand __declspec(deprecated)
#endif

namespace coucou
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorCommand_
{
  using Type = MotorCommand_<ContainerAllocator>;

  explicit MotorCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->mode = 0;
      this->commande = 0.0;
    }
  }

  explicit MotorCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->mode = 0;
      this->commande = 0.0;
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _name_type name;
  using _mode_type =
    uint8_t;
  _mode_type mode;
  using _commande_type =
    double;
  _commande_type commande;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__commande(
    const double & _arg)
  {
    this->commande = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    coucou::msg::MotorCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const coucou::msg::MotorCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<coucou::msg::MotorCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<coucou::msg::MotorCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      coucou::msg::MotorCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<coucou::msg::MotorCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      coucou::msg::MotorCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<coucou::msg::MotorCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<coucou::msg::MotorCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<coucou::msg::MotorCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__coucou__msg__MotorCommand
    std::shared_ptr<coucou::msg::MotorCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__coucou__msg__MotorCommand
    std::shared_ptr<coucou::msg::MotorCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorCommand_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->mode != other.mode) {
      return false;
    }
    if (this->commande != other.commande) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorCommand_

// alias to use template instance with default allocator
using MotorCommand =
  coucou::msg::MotorCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace coucou

#endif  // COUCOU__MSG__DETAIL__MOTOR_COMMAND__STRUCT_HPP_
