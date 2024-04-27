### 写在前面

#### 1. 项目依赖

本项目依赖于以下技术和工具：

- **OpenSceneGraph (osg)**: 一个开源的高性能 3D 图形工具库。
- **Visual Studio 2017**: 用于开发的集成开发环境，虽然本项目默认配置基于 Visual Studio 2022。

#### 2. 第一次运行

为了成功运行本项目，请按照以下步骤操作：

##### a. 本地编译安装 osg

首先，需要在本地编译并安装 OpenSceneGraph。详细的安装步骤可以参考下方的“参考链接”。

##### b. 配置 Visual Studio 2022 依赖

本项目的默认设置预期您的环境配置在 `D:/progameCode` 路径下。请确保 OpenSceneGraph 依赖和 publicApi 的设置与您的本地配置一致。如果您的环境配置有所不同，可能需要相应地调整`C++附加库目录`和`链接库配置`

下面介绍如何修改你的`c++附加库目录`和`链接库配置`

##### b1. C++附加库目录

路径：右键项目名-->属性-->C/C++-->常规-->附加包含目录

修改过程：

- 修改Physical2d的附加包含目录，将框选的路径修改你项目所在的路径

![image-20240427105634802](D:\git repority\Physics2D\readme.assets\image-20240427105634802.png)

- 修改PhysicalRendering附加包含目录，将**标号为1的框选路径**修改为你本地的OSG路径，将**标号为2的框选路径**修改你项目所在的路径

![image-20240427105933392](D:\git repority\Physics2D\readme.assets\image-20240427105933392.png)

##### b2.链接库配置

路径：右键项目名-->属性-->链接器-->常规-->附加目录

修改过程：

- 查看并保存Physci2D的输出目录（在配置**PhysicalRendering**时会用到），请注意配置类型为静态库,**注意Physci2D无需配置链接库**

![image-20240427110447168](D:\git repority\Physics2D\readme.assets\image-20240427110447168.png)

- 修改PhysicalRendering的链接库配置，红框为Physci2D的输出目录，绿框为osg的lib目录

![image-20240427110357229](D:\git repority\Physics2D\readme.assets\image-20240427110357229.png)

- 检查附加依赖项

![image-20240427110914371](D:\git repority\Physics2D\readme.assets\image-20240427110914371.png)

> OpenThreadsd.lib
> osgd.lib
> osgDBd.lib
> osgUtild.lib
> osgGAd.lib
> osgViewerd.lib
> osgTextd.lib
> osgWidgetd.lib
> Physics2D.lib

##### c. 启动运行

- 右键解决方案->重新生成解决方案
- 将PhysicalRendering设置为启动项目
- 点击运行（鼠标左键生成圆，右键生成正方形）

#### 3. 参考链接

- [OpenSceneGraph 安装教程](https://blog.csdn.net/cdjaodj/article/details/126593370)：这个链接提供了关于如何在不同操作系统上安装 OSG 的详细步骤。
- [部分 OpenSceneGraph 学习资料](https://pan.baidu.com/s/1NTD2vfMXyrIwJwVtQ6rEgA?pwd=2024)：可以在这个链接中找到一些有用的学习资源，帮助您更好地掌握 OSG 的使用。
