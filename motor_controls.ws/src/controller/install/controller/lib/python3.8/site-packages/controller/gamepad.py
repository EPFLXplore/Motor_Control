#!/usr/bin/env python2

import threading

try:  # import ROS if it exists
    import rospy
    from geometry_msgs.msg import Twist
except ImportError:  # else do something stupid
    print("Sorry, I can't find ROS on your system\nSubstituiting fake garbage instead")
    import fake_ros.fake_rospy as rospy   # https://github.com/mbiselx/Fake_ROS
    from fake_ros.fake_msgs import Twist  # https://github.com/mbiselx/Fake_ROS

try:  # import evdev if it exists
    import evdev
    gamepad_lib = "evdev"
except ImportError:  # else import pygame if it exists
    import pygame
    gamepad_lib = "pygame"
    # TODO: could also try HID library (weird) or inputs library (similar to evdev) ?


class GamePad():
    """
    This is a class for generalized GamePad usage.
    It is intended to be used with ROS, however, it can be used without, as
    long as fake_ros is "installed"
    """

    def __init__(self, rate=10, max_vel=1, max_rot=1, countroller_deadzone=5e-2, default_callback=None, verbose=False):

        # first do some ROS stuff
        rospy.init_node('gamepad_reader_node')
        self.wc_publisher = rospy.Publisher("cmd_vel", Twist, queue_size=1)

        # parameter setup
        self.verbose = verbose
        self.vx = 0.
        self.vy = 0.
        self.rz = 0.
        self.max_vel = float(max_vel)
        self.max_rot = float(max_rot)
        self.rate = float(rate)
        # within this epsilon around zero, we don't get reliable signals
        self.deadval = countroller_deadzone
        # maximum number of empty messages sent before they're silenced
        self.max_empty_mesgs = 3
        # this allows the use of multiple gampeads at the same time
        self.empty_mesgs = 0				# counter used to make sure we don't send empty messages
        # self.hd_pub  = rospy.Publisher('HD_joints', Int8MultiArray, queue_size=1)

        if gamepad_lib == "pygame":
            pygame.display.init()
            pygame.joystick.init()

        elif gamepad_lib == "evdev":
            pass

        self.set_default_env()
        rospy.loginfo(rospy.get_caller_id() + " : ROS setup done")

        self.connect()  # connect to the gamepad

    def connect(self):
        """
        tries to connect to a gamepad.
        will not exit until one is found
        """
        if rospy.core.is_initialized():
            rospy.loginfo(rospy.get_caller_id() + " : Connecting to device...")
        else:
            print("Connecting to device...")

        self.vx = 0.  # reset
        self.vy = 0.
        self.rz = 0.

        self.device = None
        self.devicename = 'None'
        while not self.device:
            if rospy.is_shutdown():
                break
            rospy.Rate(2).sleep()

            if gamepad_lib == "pygame":
                pygame.event.pump()  # refresh the event queue
                if pygame.joystick.get_count():
                    self.device = pygame.joystick.Joystick(
                        0)  # just get the first one
                    self.device.init()
                    self.devicename = self.device.get_name()
                    self.device_id = self.device.get_instance_id()

            elif gamepad_lib == "evdev":
                for device in [evdev.InputDevice(path) for path in evdev.list_devices()]:
                    try:
                        if device.capabilities():
                            self.device = device
                            self.devicename = self.device.name
                            self.axis_code_list, self.axis_info_list = zip(
                                *device.capabilities()[3])
                            break
                    except KeyboardInterrupt:
                        break
                    # except :
                    # 	continue

        if rospy.core.is_initialized():
            rospy.loginfo(rospy.get_caller_id() +
                          " : found {} ".format(self.devicename))
        else:
            print("Found {} ".format(self.devicename))
        return self.device

    def read_loop(self):
        """
        This is the main loop of the program
        """
        try:
            if gamepad_lib == "pygame":
                pygame.event.set_blocked(pygame.JOYDEVICEADDED)
                pygame.event.clear()
                while (rospy.core.is_initialized() and not rospy.is_shutdown()) ^ (not rospy.core.is_initialized()):
                    rospy.Rate(100).sleep()
                    for event in pygame.event.get():
                        # reconnect to a device if disconnected
                        if event.instance_id == self.device_id and event.type == pygame.JOYDEVICEREMOVED:
                            if rospy.core.is_initialized():
                                rospy.logwarn(
                                    rospy.get_caller_id() + " : device disconnected !")
                            else:
                                print("Device disconnected !")
                            self.connect()
                        else:
                            self._pygame_event_handler(event)

            elif gamepad_lib == "evdev":
                try:
                    for event in self.device.read_loop():
                        self._evdev_event_handler(event)
                except IOError:
                    # reconnect to a device if disconnected
                    if rospy.core.is_initialized():
                        rospy.logwarn(rospy.get_caller_id() +
                                      " : device disconnected !")
                    else:
                        print("Device disconnected !")
                    self.connect()
                    self.read_loop()
                except AttributeError : 
                    self.stop_pub()
                    raise KeyboardInterrupt

        except KeyboardInterrupt:
            if not rospy.is_initialized():
                print("keyboard interrupt, shutting down")
            else:
                pass

    def _pygame_event_handler(self, event):
        """
        event handler for the pygame library
        """
        # only process relevant events
        if event.instance_id == self.device_id:

            # check joystick event
            if event.type == pygame.JOYAXISMOTION:
                if event.axis == 0:
                    self.X_cb(event.value)
                elif event.axis == 1:
                    self.Y_cb(event.value)
                elif event.axis == 2:
                    self.RX_cb(event.value)
                elif event.axis == 3:
                    self.RY_cb(event.value)
                elif event.axis == 4:
                    self.ltrig_cb(event.value)
                elif event.axis == 5:
                    self.rtrig_cb(event.value)
                else:
                    if rospy.core.is_initialized():
                        rospy.logdebug(rospy.get_caller_id() +
                                       ": " + str(event))
                    else:
                        print(event)

            # check button events
            elif event.type == pygame.JOYBUTTONDOWN or event.type == pygame.JOYBUTTONUP:
                if event.button == 0:
                    self.Abtn_cb(1 if event.type ==
                                 pygame.JOYBUTTONDOWN else 0)
                elif event.button == 1:
                    self.Bbtn_cb(1 if event.type ==
                                 pygame.JOYBUTTONDOWN else 0)
                elif event.button == 2:
                    self.Xbtn_cb(1 if event.type ==
                                 pygame.JOYBUTTONDOWN else 0)
                elif event.button == 3:
                    self.Ybtn_cb(1 if event.type ==
                                 pygame.JOYBUTTONDOWN else 0)
                elif event.button == 4:
                    self.lbumper_cb(1 if event.type ==
                                    pygame.JOYBUTTONDOWN else 0)
                elif event.button == 5:
                    self.rbumper_cb(1 if event.type ==
                                    pygame.JOYBUTTONDOWN else 0)
                elif event.button == 6:
                    self.bckbtn_cb(1 if event.type ==
                                   pygame.JOYBUTTONDOWN else 0)
                elif event.button == 7:
                    self.strtbtn_cb(1 if event.type ==
                                    pygame.JOYBUTTONDOWN else 0)
                elif event.button == 8:
                    self.lstick_cb(1 if event.type ==
                                   pygame.JOYBUTTONDOWN else 0)
                elif event.button == 9:
                    self.rstick_cb(1 if event.type ==
                                   pygame.JOYBUTTONDOWN else 0)
                elif event.button == 10:
                    self.cbtn_cb(1 if event.type ==
                                 pygame.JOYBUTTONDOWN else 0)
                else:
                    pass
                    # if rospy.core.is_initialized():
                    #     rospy.logdebug(rospy.get_caller_id() +
                    #                    ": " + str(event))
                    # else:
                    #     print(event)

            # check D-pad events
            elif event.type == pygame.JOYHATMOTION:
                self.dpadLR_cb(event.value[0])
                self.dpadUD_cb(event.value[1])

    def _evdev_event_handler(self, event):

        if event.type == evdev.ecodes.EV_KEY:
            # rospy.loginfo(rospy.get_caller_id() + ": " + str(event))
            if event.code == 315 and self.device.name == 'Logitech Gamepad F710':
                self.strtbtn_cb(event.value)
            if event.code == 313 and self.device.name == 'Bigben Interactive PS4 Compact Controller':
                self.strtbtn_cb(event.value)

        # check joystick event
        if event.type == evdev.ecodes.EV_ABS:
            # automatic normalization to [-1, 1[, like in pygame
            ax_id = self.axis_code_list.index(event.code)
            val = 2*(float(event.value) - self.axis_info_list[ax_id].min) / (
                self.axis_info_list[ax_id].max - self.axis_info_list[ax_id].min) - 1
            # rospy.loginfo(rospy.get_caller_id() + ": " + str(event))
            if event.code == 0:
                self.X_cb(val)
            elif event.code == 1:
                self.Y_cb(val)
            elif event.code == 2:
                if self.device.name == 'Logitech Gamepad F710':
                    self.ltrig_cb(val)
                else:
                    self.RX_cb(val)
            elif event.code == 3:
                if self.device.name == 'Logitech Gamepad F710':
                    self.RX_cb(val)
                else:
                    self.ltrig_cb(val)
            elif event.code == 4:
                if self.device.name == 'Logitech Gamepad F710':
                    self.RY_cb(val)
                else:
                    self.rtrig_cb(val)
            elif event.code == 5:
                if self.device.name == 'Logitech Gamepad F710':
                    self.rtrig_cb(val)
                else:
                    self.RY_cb(val)
            else:
                pass
                # if rospy.core.is_initialized():
                #     rospy.logdebug(rospy.get_caller_id() + ": " + str(event))
                # else:
                #     print(event)


################################################################################
# ROS stuff


    def pub_twist(self, vx=0, vy=0, vz=0, rx=0, ry=0, rz=0):
        """
        creates and publishes a Twist message based on the passed variables
                [
                 linear  : [ vx, vy, vz]
                 angular : [ rx, ry, rz]
                ]

        usage :
                gp = GamePad()
                gp.pub_twist(twist_mesg)	 		# publishes a given Twist message
                gp.pub_twist([vx, vy, 0, 0, 0, rz])	# publishes list or numpy array as a Twist
                gp.pub_twist(vx=vx, vy=0, rz=rz)	# publishes individual numbers a Twist

        Note : this is not directly defined as a callback, so that it can be used
                for other things as well (e.g. a Dancer routine)
        """
        intype = type(vx)
        if intype != "Twist":
            mesg = Twist()

            if intype == 'list' or intype == 'numpy.ndarray':
                if intype == 'numpy.ndarray':
                    vx = vx.tolist()
                while len(vx) < 6:
                    vx.append(0)
                mesg.linear.x = float(vx[0])
                mesg.linear.y = float(vx[1])
                mesg.linear.z = float(vx[2])
                mesg.angular.x = float(vx[3])
                mesg.angular.y = float(vx[4])
                mesg.angular.z = float(vx[5])

            else:
                mesg.linear.x = float(vx)
                mesg.linear.y = float(vy)
                mesg.linear.z = float(vz)
                mesg.angular.x = float(rx)
                mesg.angular.y = float(ry)
                mesg.angular.z = float(rz)

        else:
            mesg = v

        self.wc_publisher.publish(mesg)
        if self.verbose:
            print(mesg)

    def pub_twist_cb(self):
        """
        defines the callback that is called periodically to publish the current Twist.
        this also checks to make sure we're not spamming zero Twists
        """
        if self.vx == 0 and self.vy == 0 and self.rz == 0:
            if self.empty_mesgs < self.max_empty_mesgs:
                self.empty_mesgs = self.empty_mesgs + 1
        else:
            self.empty_mesgs = 0

        if self.empty_mesgs < self.max_empty_mesgs:
            self.pub_twist(vx=self.vx, vy=self.vy, rz=self.rz)

        self.start_pub()

    def start_pub(self):
        self.pub_thread = threading.Timer(1/self.rate, self.pub_twist_cb)
        self.pub_thread.daemon = True
        self.pub_thread.start()

    def stop_pub(self):
        self.pub_thread.cancel()

################################################################################
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
        pass
        # print(value)

################################################################################
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
                self.stop_pub()
                rospy.loginfo(rospy.get_caller_id() +
                              " : Switching to NAV CS layout")
                self.setup_nav_cs_env()

        self.set_default_env()
        self.X_cb = lambda val: yv_cb(self, val)			# crab mode
        self.Y_cb = lambda val: xv_cb(self, val)			# forwards/backwards
        self.RX_cb = lambda val: rz_cb(self, val)			# rotation
        self.strtbtn_cb = lambda val: switch_mode(self, val)  # switching modes

        self.start_pub()
        return self

################################################################################
    def setup_nav_cs_env(self):
        """
        sets the gamepad to take the "original" CS commands (used for normal operations)
        """
        self.vx = 0  # reset
        self.vy = 0
        self.rz = 0

        def xv_pos_cb(self, val):
            if self.vx > -self.deadval:
                self.vx = 0. if abs(
                    val+1) < self.deadval else self.max_vel*.5*(val+1)

        def xv_neg_cb(self, val):
            if self.vx < self.deadval:
                self.vx = 0. if abs(
                    val+1) < self.deadval else -self.max_vel*.5*(val+1)

        def yv_cb(self, val):
            self.vy = 0. if abs(val) < self.deadval else self.max_vel*val

        def rz_cb(self, val):
            self.rz = 0. if abs(val) < self.deadval else self.max_rot*val

        def switch_mode(self, val):
            if val == 1:
                self.stop_pub()
                rospy.loginfo(rospy.get_caller_id() +
                              " : Switching to NAV DEBUG layout")
                self.setup_nav_debug_env()

        self.set_default_env()
        self.rtrig_cb = lambda val: xv_pos_cb(self, val)   	    # forwards
        self.ltrig_cb = lambda val: xv_neg_cb(self, val)   	    # backwards
        # self.X_cb = lambda val: yv_cb(self, val)                # crab mode
        self.X_cb = lambda val: rz_cb(self, val)               # rotation
        # self.RX_cb = lambda val: rz_cb(self, val)               # rotation
        self.strtbtn_cb = lambda val: switch_mode(self, val) 	# switching modes

        self.start_pub()
        return self

################################################################################


def gamepad_node(mode='CS'):
    # gp = GamePad()
    gp = GamePad(verbose=False, max_vel=0.5, max_rot=0.3)
    if mode == 'DBG':
        gp.setup_nav_debug_env()
    elif mode == 'CS':
        gp.setup_nav_cs_env()
    else:
        gp.set_default_env()
    gp.read_loop()


if __name__ == '__main__':

    # gamepad_node('DBG')
    gamepad_node('CS')
