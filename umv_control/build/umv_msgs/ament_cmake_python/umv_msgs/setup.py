from setuptools import find_packages
from setuptools import setup

setup(
    name='umv_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('umv_msgs', 'umv_msgs.*')),
)
