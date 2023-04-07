# 实践总结报告
一、课程任务及组员信息
二、方案设计及任务分工
三、个人承担任务的实现（配置操作过程）
四、实现结果测试与分析（分析结果截图）
五、心得体会（课程设计中遇到的问题及解决方法，课程设计体会、收获、建议等） 

# 设计流程
- [ ] IP地址划分
- [ ] VLAN规划
- [ ] 校区内路由规划：（1）内网路由
- [ ] 校区内路由规划： （2） internet出口路由
- [ ] Inter出口规划：
- [ ] 校区间路由规划：
- [ ] 校外终端接入：
- [ ] 可维护性

# 部件命名
为了 与其他文件做区分 **ace**  成为我们小组的专用开头
```
ace
-   n. （扑克牌中的）A牌；擅长……的人，一流高手；（网球中的）发球得分，爱司球；（击落多架敌机的）王牌飞行员；（高尔夫）一杆进洞
-   adj. <非正式>一流的；<非正式>极好的
-   v. 在……中取得好成绩；（网球或排球）发球得分；胜过；（在高尔夫球比赛中）一杆进穴，一杆得分
-   【名】 （Ace）（英、美、克）埃斯（人名）
```

查看组网图，从上到下经过的路由器和交换机，依次为：
ace_AR_wan
ace_AR_out
ace_Kernel_SW_1
ace_Kernel_SW_2
ace_converge_SW_1
ace_converge_SW_2
ace_access_SW_1
ace_access_SW_2
[[各层配置]]

# 基本操作！！！注意事项
## 登录
```
连接 console 口 ，启动时注意文件，账号：密码：
admin
admin@seu.com
```

```
Save xxx.cfg
离开实验室 admintemp.cfg 设置为启动文件
```

## 首次启动时
```
<HUAWEI>startup saved-configuration admintemp.cfg
<HUAWEI>reboot fast
```

## 后续实践：保存与恢复配置
```
<HUAWEI> save xxx.cfg //将当先配置保存进 flash:/ xxx.cfg
<HUAWEI> copy xxx.cfg xxxbk.cfg   //备份一下
```

```
<HUAWEI>startup saved-configuration xxx.cfg 
<HUAWEI>reboot fast

# 或者 从备份里拿，一下是恢复配置
<HUAWEI>copy flash:/xxxbk.cfg flash:/xxx.cfg
<HUAWEI>startup saved-configuration admintemp.cfg
<HUAWEI>reboot fast
```

## 查看日志操作-撤销
```
disp history-command all-users
```

---

# 配置操作
## 查看当前视图配置
```
<123456> system-view
[123456] display this
```

## 修改设备名称： (改成指定的名字，参照实验设计）
```
<HUAWEI> system-view
[HUAWEI] sysname 123456

[123456]undo sysname   //起错名字就undo
```

## 保存-备份文件
```
<HUAWEI> save 123456.cfg
<HUAWEI> save 123456.cfg //将当先配置保存进 flash:/ 123456.cfg
<HUAWEI> copy 123456.cfg 123456bk.cfg   //备份一下
```

## 恢复配置
```
<HUAWEI>startup saved-configuration xxx.cfg 
<HUAWEI>reboot fast

# 或者 从备份里拿，一下是恢复配置
<HUAWEI>copy flash:/xxxbk.cfg flash:/xxx.cfg
<HUAWEI>startup saved-configuration admintemp.cfg
<HUAWEI>reboot fast

```

## 查看当前配置、文件
```
[123456]display this #查看当前视图配置 
<123456> dir     #查看保存的配置文件
```

---

# 配置vlan
## 端口 vlan 设置成 access 
```
#交换机上全局开启 VLAN 资源，batch 可以创建多个
[Switch_1] vlan batch 10 20 30 

#接 PC 机接口设置为 access 接口，并配置缺省 VLAN
[Switch_1] interface gigabitethernet 0/0/1 //进入接口视图
[Switch_1-GigabitEthernet0/0/1] port link-type access //配置 access 类型
[Switch_1-GigabitEthernet0/0/1] port default vlan 10 //配置缺省 VLAN，VLAN10 与这个端口关联了
```

## 端口设置成 trunk
```
#接 2 号交换机接口 设置为 Trunk 接口，并配允许通过的 VLAN
[Switch_1] interface gigabitethernet 0/0/2
[Switch_1-GigabitEthernet0/0/2] port link-type trunk //配置 trunk 类型
[Switch_1-GigabitEthernet0/0/2] port trunk allow-pass vlan 10 20 //允许接口上VLAN 10 20 通过，VLAN 10 20与这个端口关联了
[Switch_1-GigabitEthernet0/0/2] quit
```

## vlanif 绑定
```
# 配置 Switch 1，交换机需要通过 VLANIF 配置 IP 地址

#与 PC 连接的端口，首先设置二层
#在已经开启 vlan 10 100 基础上 才 开启 vlanif

[Switch_1] vlan batch 10 100
[Switch_1] interface gigabitethernet 0/0/1
[Switch_1-GigabitEthernet0/0/1] port link-type access
[Switch_1-GigabitEthernet0/0/1] port default vlan 10
[Switch_1-GigabitEthernet0/0/1] quit

#与路由器连接的端口，首先设置二层
[Switch_1] interface gigabitethernet 0/0/2
[Switch_1-GigabitEthernet0/0/2] port link-type access
[Switch_1-GigabitEthernet0/0/2] port default vlan 100
[Switch_1-GigabitEthernet0/0/2] quit

#对应的 VLAN 上启用三层
[Switch_1] interface vlanif 10
[Switch_1-Vlanif10] ip address 10.10.10.1 24
[Switch_1-Vlanif10] quit

#对应的 VLAN 上启用三层
[Switch_1] interface vlanif 100
[Switch_1-Vlanif100] ip address 100.10.10.1 24
[Switch_1-Vlanif100] quit
```

## 查看vlan配置
```
display vlan
```


---

# DHCP
在交换机上开启服务后，
选择本 VLANIF 接口网段作为 DHCP server 分配的 IP 地址池网段
```
[Switch_1] dhcp enable
#配置 DHCP 地址池相关信息
在已经配置了接口 IP 地址，在此配置基础上增加地址池配置：
[Switch_1] interface vlanif 10 //vlanif 10 绑的是 10.10.10.1

#选择本 VLANIF 接口网段作为 DHCP server 分配的 IP 地址池网段
[Switch_1-Vlanif10] dhcp select interface

#可选，设置 DHCP 分配的网关地址。
[Switch_1-Vlanif10] dhcp server gateway-list 10.10.10.1 //不配置时会自动选择该接口的 ip 地址作为网关地址。ensp 不支持该命令

#设置 DHCP 分配的 DNS 服务器地址。
[Switch_1-Vlanif10] dhcp server dns-list 114.114.114.114 //可尝试修改 dns server 地址，抓包/PC 机 ipconfig 可见.
```

## 查看DHCP信息
```
display ip pool interface vlanif10
```


# OPSF 
## 配置 ospf router-id ，作为 OSPF 路由器标识。
Router-id 网络里唯一，不能冲突
不同网段之间：汇聚、核心、出口路由器使用OSPF发布路由
```
#配置 ospf router-id ，作为 OSPF 路由器标识。Router-id 网络里唯一，不能冲突

[Switch_1]interface loopback 0
[Switch_1-Loopback0] ip address 200.10.10.1 255.255.255.255 //router-id

#启动 OSPF 服务
[Switch_1] ospf 1 router-id 200.10.10.1 //1 的作用是进程号，路由器内部使用，用于为 VPN 网络分别不同的独立进程

#配置 OSPF area，本实验仅部署 area 0
[Switch_1-ospf-1] area 0

#与路由器间接口上使能 OSPF，并把这个的接口链路状态发布出去.注意反掩码
[Switch_1-ospf-1-area-0.0.0.0] network 100.10.10.0 0.0.0.255

```

```
AR1 上启用 OSPF

#配置 ospf router-id ，作为 OSPF 路由器标识。注意反掩码
[AR_1]interface loopback 0
[AR_1_Loopbak0] ip address 200.10.70.1 255.255.255.255
[AR_1] ospf 1 router-id 200.10.70.1

#与交换机间接口上使能 OSPF，并把这个接口的链路状态发布出去。
[AR_1-ospf-1] area 0
[AR_1-ospf-1-area-0.0.0.0] network 100.10.10.0 0.0.0.255 //for switch1
[AR_1-ospf-1-area-0.0.0.0] network 100.10.20.0 0.0.0.255 //for switch2
[AR_1-ospf-1-area-0.0.0.0] network 100.10.30.0 0.0.0.255 //for switch3
[AR_1-ospf-1-area-0.0.0.0] quit
```


## 查看 OSPF，
```
<>display ospf peer #查看 OSPF 是否建立，状态是否为 Full 状态
<>display ospf routing
<>display ip routing
```

--- 

# 出口路由器设置缺省静态路由，指向运营商出口


静态路由配置：
```
[SW1] ip route-static 0.0.0.0 0.0.0.0 192.168.5.4 //假设路由器与SW1相连接口的IP地址是
```
![[大三下/CN实践/attachments/1.png]]


# 出口路由器上配置NAT 
![[大三下/CN实践/attachments/2.png]]

![[大三下/CN实践/attachments/3.png]]

我们组 （ip映射）
```
东大
   IPv4 地址 . . . . . . . . . . . . : 10.203.135.149
   子网掩码  . . . . . . . . . . . . : 255.255.128.0

address-group 
address-group 
address-group 
permit source 10.1.1.0 0.0.0.255 //注意反掩码
permit source 10.1.2.0 0.0.0.255 //注意反掩码
permit source 10.101.1.0 0.0.0.255 //注意反掩码
```


# 出口路由器部署 ACL包过滤防火墙功能
![[大三下/CN实践/attachments/4.png]]


router上配置防火墙
![[大三下/CN实践/attachments/5.png]]

在Router上配置ACL
```
```











