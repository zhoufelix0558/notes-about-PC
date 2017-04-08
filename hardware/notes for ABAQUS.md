###
1. 在结果visualization的时候，有时会出现看不到的情况，这时候File->Open odb的时候一定要注意，项目里面的odb文件不一定就是软件仿真产生的文件，有可能是根目录下的文件（./SIMULIA/tmp）
2. 建立耦合点的地方是在Interaction的时候，使用`Create Reference Point`
3. 点可以对多个面进行耦合。