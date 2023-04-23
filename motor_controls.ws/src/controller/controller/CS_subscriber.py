import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist

class JoySubscriber(Node):
    def __init__(self):
        super().__init__('joy_subscriber')
        self.subscription = self.create_subscription(
            Joy,
            'joy',
            self.joy_callback,
            10
        )
        self.subscription

    def joy_callback(self, msg):
        self.get_logger().info(f"Axes: {msg.axes}")
        self.get_logger().info(f"Buttons: {msg.buttons}")

class GamepadController(JoySubscriber):
    def __init__(self):
        super().__init__()

        self.deadval = 0.2
        self.max_vel = 1.0
        self.max_rot = 1.0

        self.vx = 0
        self.vy = 0
        self.rz = 0

        # Create a publisher for Twist messages
        self.twist_pub = self.create_publisher(Twist, 'cmd_vel', 10)

        # Initialize the gamepad environment
        self.setup_nav_cs_env()

    def setup_nav_cs_env(self):
        """
        sets the gamepad to take the "original" CS commands (used for normal operations)
        """
        self.vx = 0  # reset
        self.vy = 0
        self.rz = 0 


        def xv_pos_cb(self, val):  #updates the positive x velocity
            if self.vx > -self.deadval: #takes the value of the ltrig and gives itto self.
                self.vx = 0. if abs(
                    val+1) < (self.deadval+0.9) else self.max_vel*.5*(val+1)
            print("xv_pos_cb: ", self.vx)

        def xv_neg_cb(self, val): #updates the negative x velocity
            if self.vx < self.deadval:
                self.vx = 0. if abs(
                    val+1) < (self.deadval+0.9) else -self.max_vel*.5*(val+1)
            print("xv_neg_cb: ", self.vx)

        def yv_cb(self, val): #updates the y velocity
            self.vy = 0. if abs(val) < self.deadval else self.max_vel*val
            print("yv_cb: ", self.vy)

        def rz_cb(self, val_rot): #updates the rotation velocity
            if (abs(self.vx)<self.deadval):
                print(val_rot)
                self.rz = 0. if (abs(val_rot) == 0) else 2*self.max_rot*val_rot-1
            print("rz_cb: ", self.rz)

        self.set_default_env()
        self.rtrig_cb = lambda val: xv_neg_cb(self, val)   	    # forwards
        self.ltrig_cb = lambda val: xv_pos_cb(self, val)   	    # backwards
        self.X_cb = lambda val_rot: rz_cb(self, val_rot)               # rotation

        return self
    
    def set_default_env(self, default_callback=None):
        """
        sets the gamepad to take the a same default callback for all buttons
        """

        # define default callbacks
        if not default_callback:
            default_callback = self.default_callback

        self.X_cb = default_callback
        self.Y_cb = default_callback
        self.RX_cb = default_callback
        self.RY_cb = default_callback
        self.ltrig_cb = default_callback
        self.rtrig_cb = default_callback
        self.Abtn_cb = default_callback
        self.Bbtn_cb = default_callback
        self.Xbtn_cb = default_callback
        self.Ybtn_cb = default_callback
        self.lbumper_cb = default_callback
        self.rbumper_cb = default_callback
        self.bckbtn_cb = default_callback
        self.strtbtn_cb = default_callback
        self.lstick_cb = default_callback
        self.rstick_cb = default_callback
        self.cbtn_cb = default_callback
        self.dpadLR_cb = default_callback
        self.dpadUD_cb = default_callback

        return self
    
    def default_callback(self, value=None):
        """ default : do nothing """
        print("default callback")
        pass
        # print(value)

    def joy_callback(self, msg):
        '''
        # Process gamepad input
        self.ltrig_cb(msg.axes[2])  # Left trigger
        self.rtrig_cb(msg.axes[5])  # Right trigger
        self.X_cb(msg.axes[0])      # Left joystick x-axis
        self.Y_cb(msg.axes[1])      # Left joystick y-axis
        '''
        self.vx = 0  # reset
        self.vy = 0
        self.rz = 0

        self.X_cb(msg.axes[0])      # Left joystick x-axis
        self.Y_cb(msg.axes[1])      # Left joystick y-axis
        self.rtrig_cb(msg.axes[2])  # Left trigger
        self.ltrig_cb(msg.axes[5])  # Right trigger


        # Create and populate the Twist message
        twist = Twist()
        twist.linear.x = float(self.vx)
        twist.linear.y = float(self.vy)
        twist.angular.z = float(self.rz)

        # Publish the Twist message
        self.twist_pub.publish(twist)
        self.vx = 0  # reset
        self.vy = 0
        self.rz = 0

    # Add your gamepad methods and callbacks here
    # (default_callback, setup_nav_cs_env, setup_nav_debug_env, etc.)
    ...

def main(args=None):
    rclpy.init(args=args)

    gamepad_controller = GamepadController()

    rclpy.spin(gamepad_controller)

    gamepad_controller.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
