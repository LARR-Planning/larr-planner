# generated from rosidl_generator_py/resource/_idl.py.em
# with input from umv_msgs:msg/LocalRefPath.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'local_ref_xs'
# Member 'local_ref_ys'
# Member 'local_ref_ss'
# Member 'local_ref_yaws'
# Member 'local_ref_curvs'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_LocalRefPath(type):
    """Metaclass of message 'LocalRefPath'."""

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
                'umv_msgs.msg.LocalRefPath')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__local_ref_path
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__local_ref_path
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__local_ref_path
            cls._TYPE_SUPPORT = module.type_support_msg__msg__local_ref_path
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__local_ref_path

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


class LocalRefPath(metaclass=Metaclass_LocalRefPath):
    """Message class 'LocalRefPath'."""

    __slots__ = [
        '_header',
        '_local_ref_xs',
        '_local_ref_ys',
        '_local_ref_ss',
        '_local_ref_yaws',
        '_local_ref_curvs',
        '_ey',
        '_eyaw',
        '_ego_s',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'local_ref_xs': 'sequence<double>',
        'local_ref_ys': 'sequence<double>',
        'local_ref_ss': 'sequence<double>',
        'local_ref_yaws': 'sequence<double>',
        'local_ref_curvs': 'sequence<double>',
        'ey': 'double',
        'eyaw': 'double',
        'ego_s': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.local_ref_xs = array.array('d', kwargs.get('local_ref_xs', []))
        self.local_ref_ys = array.array('d', kwargs.get('local_ref_ys', []))
        self.local_ref_ss = array.array('d', kwargs.get('local_ref_ss', []))
        self.local_ref_yaws = array.array('d', kwargs.get('local_ref_yaws', []))
        self.local_ref_curvs = array.array('d', kwargs.get('local_ref_curvs', []))
        self.ey = kwargs.get('ey', float())
        self.eyaw = kwargs.get('eyaw', float())
        self.ego_s = kwargs.get('ego_s', float())

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
        if self.local_ref_xs != other.local_ref_xs:
            return False
        if self.local_ref_ys != other.local_ref_ys:
            return False
        if self.local_ref_ss != other.local_ref_ss:
            return False
        if self.local_ref_yaws != other.local_ref_yaws:
            return False
        if self.local_ref_curvs != other.local_ref_curvs:
            return False
        if self.ey != other.ey:
            return False
        if self.eyaw != other.eyaw:
            return False
        if self.ego_s != other.ego_s:
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
    def local_ref_xs(self):
        """Message field 'local_ref_xs'."""
        return self._local_ref_xs

    @local_ref_xs.setter
    def local_ref_xs(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'local_ref_xs' array.array() must have the type code of 'd'"
            self._local_ref_xs = value
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
                "The 'local_ref_xs' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._local_ref_xs = array.array('d', value)

    @builtins.property
    def local_ref_ys(self):
        """Message field 'local_ref_ys'."""
        return self._local_ref_ys

    @local_ref_ys.setter
    def local_ref_ys(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'local_ref_ys' array.array() must have the type code of 'd'"
            self._local_ref_ys = value
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
                "The 'local_ref_ys' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._local_ref_ys = array.array('d', value)

    @builtins.property
    def local_ref_ss(self):
        """Message field 'local_ref_ss'."""
        return self._local_ref_ss

    @local_ref_ss.setter
    def local_ref_ss(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'local_ref_ss' array.array() must have the type code of 'd'"
            self._local_ref_ss = value
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
                "The 'local_ref_ss' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._local_ref_ss = array.array('d', value)

    @builtins.property
    def local_ref_yaws(self):
        """Message field 'local_ref_yaws'."""
        return self._local_ref_yaws

    @local_ref_yaws.setter
    def local_ref_yaws(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'local_ref_yaws' array.array() must have the type code of 'd'"
            self._local_ref_yaws = value
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
                "The 'local_ref_yaws' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._local_ref_yaws = array.array('d', value)

    @builtins.property
    def local_ref_curvs(self):
        """Message field 'local_ref_curvs'."""
        return self._local_ref_curvs

    @local_ref_curvs.setter
    def local_ref_curvs(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'local_ref_curvs' array.array() must have the type code of 'd'"
            self._local_ref_curvs = value
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
                "The 'local_ref_curvs' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._local_ref_curvs = array.array('d', value)

    @builtins.property
    def ey(self):
        """Message field 'ey'."""
        return self._ey

    @ey.setter
    def ey(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ey' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'ey' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._ey = value

    @builtins.property
    def eyaw(self):
        """Message field 'eyaw'."""
        return self._eyaw

    @eyaw.setter
    def eyaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'eyaw' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'eyaw' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._eyaw = value

    @builtins.property
    def ego_s(self):
        """Message field 'ego_s'."""
        return self._ego_s

    @ego_s.setter
    def ego_s(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ego_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'ego_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._ego_s = value
