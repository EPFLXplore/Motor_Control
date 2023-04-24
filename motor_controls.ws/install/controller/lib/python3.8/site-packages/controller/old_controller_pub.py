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
        # Implement your logic to process the joystick events and populate
        # the axes and buttons arrays accordingly
        axes = []
        buttons = []

        if event.type == ecodes.EV_ABS:
            ax_id = self.axis_code_list.index(event.code)  # get the axis id which represents the joystick being moved
            val = 2*(float(event.value) - self.axis_info_list[ax_id].min) / (
                self.axis_info_list[ax_id].max - self.axis_info_list[ax_id].min) - 1
            if event.code == 0:
                axes.append(float(val))
            if event.code == 1:
                axes.append(float(val))
            if event.code == 2:
                axes.append(float(val))
            if event.code == 3:
                axes.append(float(val))
            if event.code == 4:
                axes.append(float(val))
            if event.code == 5:
                axes.append(float(val))
            if event.code == 16:
                axes.append(float(val))
            if event.code == 17:
                axes.append(float(val))
        if event.type == ecodes.EV_KEY:
            if event.code == 304:
                buttons.append(event.value)
            if event.code == 305:
                buttons.append(event.value)
            if event.code == 307:
                buttons.append(event.value)
            if event.code == 308:
                buttons.append(event.value)
            if event.code == 310:
                buttons.append(event.value)
            if event.code == 311:
                buttons.append(event.value)
            if event.code == 314:
                buttons.append(event.value)
            if event.code == 315:
                buttons.append(event.value)
            if event.code == 317:
                buttons.append(event.value)
            if event.code == 318:
                buttons.append(event.value)
            if event.code == 320:
                buttons.append(event.value)
            if event.code == 321:
                buttons.append(event.value)
            if event.code == 323:
                buttons.append(event.value)
            if event.code == 324:
                buttons.append(event.value)
            if event.code == 326:
                buttons.append(event.value)
            if event.code == 327:
                buttons.append(event.value)
            if event.code == 329:
                buttons.append(event.value)
            if event.code == 330:
                buttons.append(event.value)
            if event.code == 332:
                buttons.append(event.value)
            if event.code == 333:
                buttons.append(event.value)
            if event.code == 335:
                buttons.append(event.value)
            if event.code == 336:
                buttons.append(event.value)
            if event.code == 338:
                buttons.append(event.value)
            if event.code == 339:
                buttons.append(event.value)
            if event.code == 341:
                buttons.append(event.value)
            if event.code == 342:
                buttons.append(event.value)
            if event.code == 344:
                buttons.append(event.value)
            if event.code == 345:
                buttons.append(event.value)
            if event.code == 347:
                buttons.append(event.value)
            if event.code == 348:
                buttons.append(event.value)
            if event.code == 350:
                buttons.append(event.value)
            if event.code == 351:
                buttons.append(event.value)
            if event.code == 353:
                buttons.append(event.value)
            if event.code == 354:
                buttons.append(event.value)
            if event.code == 356:
                buttons.append(event.value)
            if event.code == 357:
                buttons.append(event.value)
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
