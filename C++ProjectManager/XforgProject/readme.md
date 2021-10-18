
// 项目编译目录，各种编译的临时文件和最终的目标文件皆存于此，分为 debug/ 和 release/ 子目录
project --+---build---+---debug
　　　　　|　　　　  |---release
　　　　　|---deploy
　　　　　|---doc    // 保存项目各种文档
　　　　　|---include---+---module1// 公共头文件目录，可以按模块划分组织目录来保存模块相关头文件
　　　　　|　　　　　 　|---module2
　　　　　|---lib // 外部依赖库目录
　　　　　|---module1
　　　　　|---module2
　　　　　|---res  // 资源目录
　　　　　|---samples---+---sample1
　　　　　|　　　　  　　|---sample2
　　　　　|---tools // 项目支撑工具目录
　　　　　|---copyleft
　　　　　|---Makefile // 项目构建配置文件，当然也有可能是其他类型的构建配置文件
　　　　　|---README // 项目的总体说明文件
　　　　　|--- ...