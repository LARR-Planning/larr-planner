# generated from rosidl_generator_py/resource/_idl.py.em
# with input from umv_msgs:msg/Obstacles.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'obs_xs'
# Member 'obs_ys'
# Member 'obs_ss'
# Member 'obs_eys'
# Member 'obs_eyaws'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Obstacles(type):
    """Metaclass of message 'Obstacles'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('umv_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'umv_msgs.msg.Obstacles')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__obstacles
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__obstacles
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__obstacles
            cls._TYPE_SUPPORT = module.type_support_msg__msg__obstacles
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__obstacles

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Obstacles(metaclass=Metaclass_Obstacles):
    """Message class 'Obstacles'."""

    __slots__ = [
        '_header',
        '_obs_cnt',
        '_obs_xs',
        '_obs_ys',
        '_obs_ss',
        '_obs_eys',
        '_obs_eyaws',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'obs_cnt': 'int32',
        'obs_xs': 'sequence<double>',
        'obs_ys': 'sequence<double>',
        'obs_ss': 'sequence<double>',
        'obs_eys': 'sequence<double>',
        'obs_eyaws': 'sequence<double>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.obs_cnt = kwargs.get('obs_cnt', int())
        self.obs_xs = array.array('d', kwargs.get('obs_xs', []))
        self.obs_ys = array.array('d', kwargs.get('obs_ys', []))
        self.obs_ss = array.array('d', kwargs.get('obs_ss', []))
        self.obs_eys = array.array('d', kwargs.get('obs_eys', []))
        self.obs_eyaws = array.array('d', kwargs.get('obs_eyaws', []))

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.obs_cnt != other.obs_cnt:
            return False
        if self.obs_xs != other.obs_xs:
            return False
        if self.obs_ys != other.obs_ys:
            return False
        if self.obs_ss != other.obs_ss:
            return False
        if self.obs_eys != other.obs_eys:
            return False
        if self.obs_eyaws != other.obs_eyaws:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def obs_cnt(self):
        """Message field 'obs_cnt'."""
        return self._obs_cnt

    @obs_cnt.setter
    def obs_cnt(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'obs_cnt' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'obs_cnt' field must be an integer in [-2147483648, 2147483647]"
        self._obs_cnt = value

    @builtins.property
    def obs_xs(self):
        """Message field 'obs_xs'."""
        return self._obs_xs

    @obs_xs.setter
    def obs_xs(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'obs_xs' array.array() must have the type code of 'd'"
            self._obs_xs = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'obs_xs' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._obs_xs = array.array('d', value)

    @builtins.property
    def obs_ys(self):
        """Message field 'obs_ys'."""
        return self._obs_ys

    @obs_ys.setter
    def obs_ys(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'obs_ys' array.array() must have the type code of 'd'"
            self._obs_ys = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'obs_ys' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._obs_ys = array.array('d', value)

    @builtins.property
    def obs_ss(self):
        """Message field 'obs_ss'."""
        return self._obs_ss

    @obs_ss.setter
    def obs_ss(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'obs_ss' array.array() must have the type code of 'd'"
            self._obs_ss = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'obs_ss' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._obs_ss = array.array('d', value)

    @builtins.property
    def obs_eys(self):
        """Message field 'obs_eys'."""
        return self._obs_eys

    @obs_eys.setter
    def obs_eys(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'obs_eys' array.array() must have the type code of 'd'"
            self._obs_eys = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'obs_eys' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._obs_eys = array.array('d', value)

    @builtins.property
    def obs_eyaws(self):
        """Message field 'obs_eyaws'."""
        return self._obs_eyaws

    @obs_eyaws.setter
    def obs_eyaws(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'obs_eyaws' array.array() must have the type code of 'd'"
            self._obs_eyaws = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'obs_eyaws' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._obs_eyaws = array.array('d', value)
