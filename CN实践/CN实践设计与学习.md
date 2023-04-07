# 关于LAN
## access端口：

通过access端口的数据包都是不带VLAN tag的，且只属于一个VLAN；
在access端口进方向，交换机接收到数据包后，先判断是否带VLAN tag，有则丢弃数据包，没有则打上该端口已配置的VLAN tag；

在access端口出方向，交换机将打了与端口相同VLAN tag的数据包转发出去，并且去掉VLAN tag变成普通数据包。

## trunk端口：

通过trunk端口的数据包都必须带上VLAN tag；

在trunk端口进方向，交换机接收到数据包后，先判断是否带VLAN tag，没有则丢弃数据包，有则按照对应VLAN进行转发；

在trunk端口出方向，交换机将带VLAN tag的数据包原封不动转发出去，没有带VLAN tag数据包不会从trunk端口转发出去。

在trunk端口上有一种特殊情况，如果配置了native VLAN（也叫PVID），转发方式等同于access端口，当从端口进来的报文不带vlan tag时，就打上Native vlan tag； 当从端口出去的报文带Native vlan tag时，会剥离TAG。

## vlanif 
在配置好二层vlan后，三层交换机上使用vlanif命令建立对应vlan的路由，配置完成后，可以实现VLAN之间的通信。

# 关于网络共享


# 关于环路


# 关于 NAT 


# 关于ARP攻击

NAT 
防火墙
L2TP 
Windows 上的路由