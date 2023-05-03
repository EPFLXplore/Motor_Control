import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
#from evdev import InputDevice, categorize, ecodes
import evdev
from evdev import InputDevice, categorize, ecodes
class JoyPublisher(Node):
    def __init__(self):
        super().__init__('joy_publisher')
        self.publisher_ = self.create_publisher(Joy, 'joy', 10)
        self.device_path = self.find_device_path()
        self.device = None
        if self.device_path:
            self.device = InputDevice(self.device_path)
            self.get_logger().info(f'Using device: {self.device}')

    def find_device_path(self):
        # You can modify this to match your joystick's name
        target_device_name = 'Generic X-Box pad'
        print(evdev.list_devices())
        devices = [InputDevice(path) for path in evdev.list_devices()]
        for device in devices:
            print(device.name)
            if device.name == target_device_name:
                self.axis_code_list, self.axis_info_list = zip(
                            *device.capabilities()[3])
                return device.path
        self.get_logger().error(f"Device '{target_device_name}' not found.")
        return None

    def publish_events(self):
        while rclpy.ok() and self.device:
            for event in self.device.read_loop():
                if event.type == ecodes.EV_KEY or event.type == ecodes.EV_ABS:
                    joy_msg = Joy()
                    joy_msg.header.stamp = self.get_clock().now().to_msg()
                    joy_msg.axes, joy_msg.buttons = self.process_event(event)
                    self.publisher_.publish(joy_msg)
                    self.get_logger().info(f"Published Axes: {joy_msg.axes}, Buttons: {joy_msg.buttons}")
                    #self.get_logger().info(f"buddyyyyy: {joy_msg}")

    def process_event(self, event):
        # Initialize the axes and buttons lists with the correct number of elements
        axes = [0.0] * 8  # Assuming 8 axes
        buttons = [0] * 17  # Assuming 17 buttons

        if event.type == ecodes.EV_ABS:
            ax_id = self.axis_code_list.index(event.code)  # get the axis id which represents the joystick being moved
            #val = 2*(float(event.value) - self.axis_info_list[ax_id].min) / (
            #   self.axis_info_list[ax_id].max - self.axis_info_list[ax_id].min) -1

            #val needs to be between 0  and 1
            val = (float(event.value) - self.axis_info_list[ax_id].min) / (
                self.axis_info_list[ax_id].max - self.axis_info_list[ax_id].min)
            axes[ax_id] = val  # Update the corresponding axis value


        if event.type == ecodes.EV_KEY:
            # Define a mapping from the event code to the button index
            button_mapping = {
                304: 0,
                305: 1,
                307: 2,
                308: 3,
                310: 4,
                311: 5,
                314: 6,
                315: 7,
                317: 8,
                318: 9,
                320: 10,
                321: 11,
                323: 12,
                324: 13,
                326: 14,
                327: 15,
                329: 16
            }

            button_index = button_mapping.get(event.code)
            if button_index is not None:
                buttons[button_index] = event.value  # Update the corresponding button value

        return axes, buttons

def main(args=None):
    rclpy.init(args=args)

    joy_publisher = JoyPublisher()

    try:
        joy_publisher.publish_events()
    except KeyboardInterrupt:
        pass

    joy_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
