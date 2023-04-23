import evdev
import sys
print(sys.path)
print(sys.version)

class GamePad():
    """
    This is a class for generalized GamePad usage.
    It is intended to be used with ROS, however, it can be used without, as
    long as fake_ros is "installed"
    """

    def __init__(self, rate=10, max_vel=1, max_rot=1, countroller_deadzone=5e-2, default_callback=None, verbose=False):

        # parameter setup
        self.verbose = verbose  #when true, prints out the values of the joysticks and buttons else it doesn't
        self.vx = 0.  # velocity in x can be updated with the left joystick
        self.vy = 0.  # velocity in y can be updated with the left joystick
        self.rz = 0.  # rotation can be updated with the right joystick
        self.max_vel = float(max_vel) # maximum velocity in x and y 
        self.max_rot = float(max_rot) # maximum rotation in z
        self.rate = float(rate) # rate at which the gamepad is read
        # within this epsilon around zero, we don't get reliable signals
        self.deadval = countroller_deadzone
        # maximum number of empty messages sent before they're silenced
        self.max_empty_mesgs = 3
        # this allows the use of multiple gampeads at the same time
        self.empty_mesgs = 0				# counter used to make sure we don't send empty messages
        # self.hd_pub  = rospy.Publisher('HD_joints', Int8MultiArray, queue_size=1)

        self.set_default_env()

        self.connect()  # connect to the gamepad
        # store the callback function
        self.callback = default_callback

    def connect(self): # connect to the gamepad
        """
        tries to connect to a gamepad.
        will not exit until one is found
        """
        print("Connecting to device...")

        self.vx = 0.  # reset
        self.vy = 0.
        self.rz = 0.

        self.device = None #device is the gamepad
        self.devicename = 'None' #name of the gamepad
        while not self.device: #test if the gamepad is connected
            for device in [evdev.InputDevice(path) for path in evdev.list_devices()]: #list_devices() returns a list of all the devices connected to the computer
                try:
                    if device.capabilities():  # check if the device has any capabilities which are basically the buttons and joysticks
                        self.device = device
                        self.devicename = self.device.name
                        self.axis_code_list, self.axis_info_list = zip(
                            *device.capabilities()[3]) #capabilities()[3] returns a list of tuples of the axis code and axis info which are the joysticks
                        break
                except KeyboardInterrupt:
                    break
        print("Found {} ".format(self.devicename))
        return self.device
    
    def read_loop(self):
        """
        This is the main loop of the program
        """
        try:
            try:
                for event in self.device.read_loop():
                    self._evdev_event_handler(event) #this is the function that handles the events which are the buttons and joysticks being pressed
            except IOError:
                print("Device disconnected !")
                self.connect()
                self.read_loop()
            except AttributeError : 
                self.stop_pub()
                raise KeyboardInterrupt

        except KeyboardInterrupt:
            print("keyboard interrupt, shutting down")

    def _evdev_event_handler(self, event): #this is the function that handles the events which are the buttons and joysticks being pressed
        #print strings when keys are pressed

        if event.type == evdev.ecodes.EV_KEY: #if the event is a button being pressed
            # rospy.loginfo(rospy.get_caller_id() + ": " + str(event))
            if event.code == 315 and self.device.name == 'Logitech Gamepad F710': #if the event is the start button being pressed
                self.strtbtn_cb(event.value) #this is the function that handles the start button being pressed
            if event.code == 313 and self.device.name == 'Bigben Interactive PS4 Compact Controller': #if the event is the start button being pressed
                self.strtbtn_cb(event.value) #this is the function that handles the start button being pressed
            

        # check joystick event
        if event.type == evdev.ecodes.EV_ABS: #if the event is a joystick being moved
            # automatic normalization to [-1, 1[, like in pygame
            ax_id = self.axis_code_list.index(event.code)  # get the axis id which represents the joystick being moved
            val = 2*(float(event.value) - self.axis_info_list[ax_id].min) / (
                self.axis_info_list[ax_id].max - self.axis_info_list[ax_id].min) - 1 # normalize the joystick value to be between -1 and 1
            # rospy.loginfo(rospy.get_caller_id() + ": " + str(event))
            if event.code == 0: #if the event is the left joystick being moved
                self.X_cb(val) #this does the callback function which is the function that handles the left joystick being moved
            elif event.code == 1: #if the event is the right joystick being moved
                self.Y_cb(val) #Y_cb is the function that handles the right joystick being moved 
            elif event.code == 2: #if the event is the left trigger being moved
                if self.device.name == 'Logitech Gamepad F710':
                    self.ltrig_cb(val)
                else:
                    self.RX_cb(val)
            elif event.code == 3: #if the event is the right trigger being moved
                if self.device.name == 'Logitech Gamepad F710':
                    self.RX_cb(val)
                else:
                    self.ltrig_cb(val)
            elif event.code == 4: #if the event is the left trigger being moved
                if self.device.name == 'Logitech Gamepad F710':
                    self.RY_cb(val)
                else:
                    self.rtrig_cb(val)
            elif event.code == 5: #if the event is the right trigger being moved
                if self.device.name == 'Logitech Gamepad F710':
                    self.rtrig_cb(val)
                else:
                    self.RY_cb(val)
            else:
                pass

    #we want to create a method that prints out the names of the buttons and joysticks being pressed:

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

    def setup_nav_cs_env(self):
        """
        sets the gamepad to take the "original" CS commands (used for normal operations)
        """
        self.vx = 0  # reset
        self.vy = 0
        self.rz = 0

        def xv_pos_cb(self, val):  #updates the positive x velocity
            if self.vx > -self.deadval:
                self.vx = 0. if abs(
                    val+1) < self.deadval else self.max_vel*.5*(val+1)
                print("xv_pos_cb: ", self.vx)

        def xv_neg_cb(self, val): #updates the negative x velocity
            if self.vx < self.deadval:
                self.vx = 0. if abs(
                    val+1) < self.deadval else -self.max_vel*.5*(val+1)
            print("xv_neg_cb: ", self.vx)
        def yv_cb(self, val): #updates the y velocity
            self.vy = 0. if abs(val) < self.deadval else self.max_vel*val
            print("yv_cb: ", self.vy)

        def rz_cb(self, val): #updates the rotation velocity
            self.rz = 0. if abs(val) < self.deadval else self.max_rot*val
            print("rz_cb: ", self.rz)
        #def switch_mode(self, val):
        #    if val == 1:
        #        self.stop_pub()
        #        self.setup_nav_debug_env()

        self.set_default_env()
        self.rtrig_cb = lambda val: xv_pos_cb(self, val)   	    # forwards
        self.ltrig_cb = lambda val: xv_neg_cb(self, val)   	    # backwards
        # self.X_cb = lambda val: yv_cb(self, val)                # crab mode
        self.X_cb = lambda val: rz_cb(self, val)               # rotation
        # self.RX_cb = lambda val: rz_cb(self, val)               # rotation

        return self
    
    def setup_nav_debug_env(self):
        """
        sets the gamepad to take the "original" NAV commands (used for debugging)
        """
        self.vx = 0  # reset
        self.vy = 0
        self.rz = 0

        def xv_cb(self, val): 
            self.vx = 0. if abs(val) < self.deadval else -self.max_vel*val

        def yv_cb(self, val):
            self.vy = 0. if abs(val) < self.deadval else self.max_vel*val

        def rz_cb(self, val):
            self.rz = 0. if abs(val) < self.deadval else self.max_rot*val

        def switch_mode(self, val):
            if val == 1:
                self.setup_nav_cs_env()

        self.set_default_env()
        self.X_cb = lambda val: yv_cb(self, val)			# crab mode
        self.Y_cb = lambda val: xv_cb(self, val)			# forwards/backwards
        self.RX_cb = lambda val: rz_cb(self, val)			# rotation
        self.strtbtn_cb = lambda val: switch_mode(self, val)  # switching modes

        return self

def gamepad_node(mode='CS'):
    # gp = GamePad()
    gp = GamePad(verbose=False, max_vel=0.5, max_rot=0.3)
    if mode == 'DBG':
        gp.setup_nav_debug_env() #for debugging and what it does is it sets up the gamepad to take the "original" NAV commands.
    elif mode == 'CS':
        gp.setup_nav_cs_env() #for normal operations and what it does is it sets up the gamepad to take the "original" CS commands.
    else:
        gp.set_default_env() #for default and what it does is it sets the gamepad to take the a same default callback for all buttons.
    gp.read_loop()


if __name__ == '__main__':

    # gamepad_node('DBG')
    gamepad_node('CS')
