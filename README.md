
说明：使用opencv的remap和initUndistortRectifyMap两个函数实现图像的去畸变
# 1.输入读取ROS畸变图像，包含内参，畸变参数，适用于针孔相机模型
# 2.输出opencv无畸变图像

# 3.使用方法
```
cd catkin_ws/src
git clone https://github.com/GuoFeng-X/image-undistort.git
```

```
cd ..
catkin_make
source devel/setup.bash
```
```
roscore
rosrun image_undistort image_undistort_node
```
# 4. 播放数据
rosbag play image_data.bag

