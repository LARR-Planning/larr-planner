from setuptools import find_packages, setup

package_name = 'global_path'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('lib/python3.10/site-packages/global_path/', ['global_path/pawn_dict.pkl'])  # 파일 복사

    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jeongtae',
    maintainer_email='49ball@naver.com',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'global_path = global_path.global_path:main'
        ],
    },
)
